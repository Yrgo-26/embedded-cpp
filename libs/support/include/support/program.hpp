/**
 * @file Run your program, the executable, and check what it printed and how it ended.
 */
#pragma once

#include <cstdint>
#include <cstdio>
#include <string>

#include <sys/wait.h>

#include "support/output.hpp"

namespace support
{
/** Exit status of a program that ran to the end successfully. */
constexpr int successStatus{0};

/** Exit status reported for a program that did not exit at all, because a signal ended it. */
constexpr int noExitStatus{-1};

/** No signal ended the program. */
constexpr int noSignal{0};

/** Exit status `timeout` reports when it had to stop the program itself. */
constexpr int timedOutStatus{124};

/** `timeout` reports a signalled program as this value plus the signal number. */
constexpr int signalledStatusBase{128};

/** How long a program may run, in seconds, before `timeout` stops it. */
constexpr std::uint16_t defaultTimeout_s{30U};

/**
 * @brief What a program printed, and how it ended.
 */
struct ProgramResult
{
    /** Everything the program wrote to standard output. */
    std::string output;

    /** The exit status if the program exited, otherwise noExitStatus. */
    int exitStatus;

    /** The signal that killed the program, otherwise noSignal. An exitStatus of timedOutStatus
        means the program timed out. */
    int signal;
};

/**
 * @brief Run a program and collect its output.
 *
 * @param[in] path The program to run.
 * @param[in] timeout_s How long it may run, in seconds, before it is stopped.
 *
 * @return What the program printed, and how it ended.
 */
[[nodiscard]] inline ProgramResult runProgram(const std::string& path,
                                              const std::uint16_t timeout_s = defaultTimeout_s)
{
    ProgramResult result{"", noExitStatus, noSignal};
    const std::string command{"timeout " + std::to_string(timeout_s) + "s '" + path + "'"};
    std::FILE* pipe{popen(command.c_str(), "r")};
    if (nullptr == pipe) { return result; }

    for (auto c = std::fgetc(pipe); EOF != c; c = std::fgetc(pipe))
    {
        result.output += static_cast<char>(c);
    }
    const auto status = pclose(pipe);

    if (WIFEXITED(status)) { result.exitStatus = WEXITSTATUS(status); }
    if (WIFSIGNALED(status)) { result.signal = WTERMSIG(status); }

    // Timeout reports a program killed by a signal as signalledStatusBase plus the signal, and one
    // it had to stop as timedOutStatus; either way the program did not exit, so say which signal
    // ended it.
    if (signalledStatusBase < result.exitStatus)
    {
        result.signal     = result.exitStatus - signalledStatusBase;
        result.exitStatus = noExitStatus;
    }
    return result;
}

namespace detail
{
/**
 * @brief Fail unless the program ran to the end and returned 0, saying how it ended otherwise.
 *
 * @param[in] result How the program ended.
 * @param[in] file The test's source file.
 * @param[in] line The line of the expectation.
 */
inline void expectCleanExit(const ProgramResult& result, const char* file, const int line)
{
    if (successStatus == result.exitStatus && noSignal == result.signal) { return; }
    if (timedOutStatus == result.exitStatus)
    {
        fail("the program was still running after its timeout", file, line);
    }
    if (noSignal != result.signal)
    {
        fail("the program crashed (signal " + std::to_string(result.signal) +
                 "): a null or dangling pointer, or a double delete?",
             file, line);
    }
    fail("the program exited with status " + std::to_string(result.exitStatus) + ", not 0", file,
         line);
}
} // namespace detail
} // namespace support

/**
 * @brief Fail unless a program run with runProgram() ended normally, returning 0. For a test that
 *        checks the output its own way, e.g. only its first line, or lines from several threads.
 */
#define EXPECT_CLEAN_EXIT(result) support::detail::expectCleanExit((result), __FILE__, __LINE__)

/**
 * @brief Run the set's program: it must end normally, returning 0, and print exactly the expected
 *        output.
 */
#define EXPECT_PROGRAM_OUTPUT(expected)                                           \
    do                                                                            \
    {                                                                             \
        const support::ProgramResult programResult{support::runProgram(PROGRAM)}; \
        support::detail::expectCleanExit(programResult, __FILE__, __LINE__);      \
        EXPECT_OUTPUT(programResult.output, (expected));                          \
    } while (false)
