/**
 * @file The main() every test binary in the course shares: run the tests the binary was built
 *       with, and report the result as its exit status.
 */
#include <cstddef>
#include <cstdio>

#include "qacademy/test/test.hpp"

namespace
{
/** Exit status returned when every test passed. */
constexpr int success{0};

/** Exit status returned when a test failed, or no test was registered. */
constexpr int failure{1};

/** Buffer size handed to std::setvbuf: 0 lets the implementation pick one. */
constexpr std::size_t defaultBufferSize{0U};
} // namespace

/**
 * @brief Run all test cases.
 *
 * @return success if every test passed, failure if one failed or none was registered.
 */
int main()
{
    // Line-buffered, so each result line is written as soon as it is printed. Under make, standard
    // output is a pipe and fully buffered, and a test that crashes the binary would otherwise take
    // the results of every test before it down with it.
    std::setvbuf(stdout, nullptr, _IOLBF, defaultBufferSize);
    return qacademy::test::runAllTests() ? success : failure;
}
