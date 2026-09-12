/**
 * @file Capture what a piece of code prints, so a test can compare it with the output an exercise
 *       specifies.
 */
#pragma once

#include <cstddef>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <unistd.h>

namespace support
{
namespace detail
{
/** Offset from a 0-based index to the 1-based line number a reader is shown. */
constexpr std::size_t firstLineNumber{1U};

/**
 * @brief Redirect standard output to a file for as long as this object lives.
 */
class Redirect final
{
public:
    /**
     * @brief Redirect standard output to the given file.
     *
     * @param[in] file The file to write to.
     */
    explicit Redirect(std::FILE* file) noexcept
        : mySaved{dup(fileno(stdout))}
    {
        // Anything already buffered belongs to the test runner, not to the code under test.
        flush();
        dup2(fileno(file), fileno(stdout));
    }

    /**
     * @brief Restore standard output, flushing what was written to the file first.
     */
    ~Redirect() noexcept
    {
        flush();
        dup2(mySaved, fileno(stdout));
        close(mySaved);
    }

    Redirect(const Redirect&)            = delete; // No copy constructor.
    Redirect(Redirect&&)                 = delete; // No move constructor.
    Redirect& operator=(const Redirect&) = delete; // No copy assignment.
    Redirect& operator=(Redirect&&)      = delete; // No move assignment.

private:
    /**
     * @brief Flush std::cout and stdout, which are synchronized and so share a destination.
     */
    static void flush() noexcept
    {
        std::cout.flush();
        std::fflush(stdout);
    }

    /** Standard output as it was before the redirection. */
    const int mySaved;
};
} // namespace detail

/**
 * @brief Run a callable and return everything it printed to standard output.
 *
 * @tparam Function Any callable taking no arguments.
 *
 * @param[in] function The code to run.
 *
 * @return The text the callable printed, exactly as printed.
 */
template<typename Function>
[[nodiscard]] std::string captureOutput(Function&& function)
{
    /** What is returned when the capture could not be set up at all. */
    constexpr const char* noFileMessage{"<captureOutput: no temporary file>"};

    std::FILE* file{std::tmpfile()};
    if (nullptr == file) { return noFileMessage; }
    try
    {
        detail::Redirect redirect{file};
        function();
    }
    catch (...)
    {
        std::fclose(file);
        throw;
    }
    std::string text{};
    std::rewind(file);

    for (auto c = std::fgetc(file); EOF != c; c = std::fgetc(file))
    {
        text += static_cast<char>(c);
    }
    std::fclose(file);
    return text;
}

/**
 * @brief Run a callable with its printing swallowed, for code whose output a test does not check.
 *
 *        captureOutput() is [[nodiscard]], because a caller that wants the text and drops it has a
 *        bug. A test that runs a driver only to keep its prints out of the test report wants the
 *        side effect and nothing else, and says so by calling this instead.
 *
 * @tparam Function Any callable taking no arguments.
 *
 * @param[in] function The code to run.
 */
template<typename Function>
void suppressOutput(Function&& function)
{
    static_cast<void>(captureOutput(std::forward<Function>(function)));
}

namespace detail
{
/**
 * @brief Split text into lines, without their newlines.
 *
 * @param[in] text The text to split.
 *
 * @return The lines, in order. Text ending in a newline has no empty last line.
 */
[[nodiscard]] inline std::vector<std::string> lines(const std::string& text)
{
    std::vector<std::string> result{};
    std::istringstream stream{text};

    for (std::string line{}; std::getline(stream, line);)
    {
        result.push_back(line);
    }
    return result;
}

/**
 * @brief Fail the current test, the way the framework's own EXPECT_* macros do: by throwing.
 *
 * @param[in] message What went wrong.
 * @param[in] file The test's source file.
 * @param[in] line The line of the expectation.
 */
[[noreturn]] inline void fail(const std::string& message, const char* file, const int line)
{
    throw std::runtime_error{message + " (" + file + ":" + std::to_string(line) + ")"};
}

/**
 * @brief Compare a program's output with the output it should have printed.
 *
 * @param[in] actual What the code printed.
 * @param[in] expected What it should have printed.
 * @param[in] file The test's source file.
 * @param[in] line The line of the expectation.
 */
inline void expectOutput(const std::string& actual, const std::string& expected, const char* file,
                         const int line)
{
    /** Placeholder shown where one side has no line left to compare. */
    constexpr const char* endOfOutput{"<no more output>"};

    if (actual == expected) { return; }
    const auto got  = lines(actual);
    const auto want = lines(expected);
    std::ostringstream message{};
    message << "the output differs from the expected output";

    for (std::size_t i{}; i < got.size() || i < want.size(); ++i)
    {
        const std::string gotLine{i < got.size() ? got[i] : endOfOutput};
        const std::string wantLine{i < want.size() ? want[i] : endOfOutput};
        if (gotLine != wantLine)
        {
            message << " at line " << (i + firstLineNumber) << ":\n      expected: \"" << wantLine
                    << "\"\n      printed:  \"" << gotLine << "\"\n     ";
            break;
        }
    }
    if (got == want) { message << ": the lines match, but not the final newline;"; }
    message << " expected " << want.size() << " line(s), printed " << got.size();
    fail(message.str(), file, line);
}
} // namespace detail
} // namespace support

/**
 * @brief Fail if the printed output is not exactly the expected output, and say where they part.
 */
#define EXPECT_OUTPUT(actual, expected) \
    support::detail::expectOutput((actual), (expected), __FILE__, __LINE__)
