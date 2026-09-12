/**
 * @file Tests for exercise set 4 of §2.4: the Timer class, declared in
 * exercise1/include/driver/timer.hpp and defined in exercise1/source/driver/timer.cpp, and the
 * program in exercise1/source/main.cpp once it exists.
 *
 *       A running timer prints when it is destroyed, and a stopped one prints nothing; both are
 *       part of the specification, so tests that destroy a timer capture the output.
 */
#include <cstdint>
#include <type_traits>

#include "driver/timer.hpp"
#include "qacademy/test/test.hpp"
#include "support/output.hpp"
#include "support/program.hpp"

using driver::Timer;
using support::captureOutput;
using support::suppressOutput;

namespace
{
/**
 * @brief Tick a timer a number of times, and count how many of those ticks timed out.
 *
 * @param[in, out] timer The timer to tick.
 * @param[in] ticks How many times to tick it.
 *
 * @return The number of timeouts.
 */
[[nodiscard]] std::uint32_t timeoutsAfter(Timer& timer, const std::uint32_t ticks) noexcept
{
    std::uint32_t timeouts{};
    for (std::uint32_t i{}; i < ticks; ++i)
    {
        timer.tick();
        if (timer.hasTimedOut()) { ++timeouts; }
    }
    return timeouts;
}
} // namespace

/**
 * @brief §2.4 set 4, task b), c) and e): an explicit, noexcept constructor from a timeout, a
 * noexcept destructor, no default constructor and no copy or move operations, and a final class.
 */
TEST(Timer, DeclarationsAreAsSpecified)
{
    EXPECT_TRUE((std::is_nothrow_constructible<Timer, std::uint32_t>::value));
    EXPECT_FALSE((std::is_convertible<std::uint32_t, Timer>::value));
    EXPECT_TRUE(std::is_nothrow_destructible<Timer>::value);
    EXPECT_FALSE(std::is_default_constructible<Timer>::value);
    EXPECT_FALSE(std::is_copy_constructible<Timer>::value);
    EXPECT_FALSE(std::is_move_constructible<Timer>::value);
    EXPECT_FALSE(std::is_copy_assignable<Timer>::value);
    EXPECT_FALSE(std::is_move_assignable<Timer>::value);
    EXPECT_TRUE(std::is_final<Timer>::value);
}

/**
 * @brief §2.4 set 4, task b) and d): a timer with a valid timeout is initialized and stopped, and
 *        reports its timeout. The queries are const and noexcept.
 */
TEST(Timer, StartsInitializedAndStopped)
{
    const Timer timer{1000U};
    EXPECT_EQ(timer.timeout_ms(), 1000U);
    EXPECT_TRUE(timer.isInitialized());
    EXPECT_FALSE(timer.isRunning());
    EXPECT_TRUE(noexcept(timer.timeout_ms()));
    EXPECT_TRUE(noexcept(timer.isRunning()));
    EXPECT_TRUE(noexcept(timer.isInitialized()));
}

/**
 * @brief §2.4 set 4, task b) and d): a timeout of 0 is invalid, so the timer is not initialized,
 * and start() and toggle() leave it stopped.
 */
TEST(Timer, AZeroTimeoutIsNotInitializedAndNeverRuns)
{
    suppressOutput(
        []
        {
            Timer timer{0U};
            EXPECT_FALSE(timer.isInitialized());
            timer.start();
            EXPECT_FALSE(timer.isRunning());
            timer.toggle();
            EXPECT_FALSE(timer.isRunning());
        });
}

/**
 * @brief §2.4 set 4, task d): start(), stop() and toggle() change the running state of an
 * initialized timer, and are noexcept.
 */
TEST(Timer, StartStopAndToggle)
{
    suppressOutput(
        []
        {
            Timer timer{100U};
            timer.start();
            EXPECT_TRUE(timer.isRunning());
            timer.stop();
            EXPECT_FALSE(timer.isRunning());
            timer.toggle();
            EXPECT_TRUE(timer.isRunning());
            timer.toggle();
            EXPECT_FALSE(timer.isRunning());
            EXPECT_TRUE(noexcept(timer.start()));
            EXPECT_TRUE(noexcept(timer.stop()));
            EXPECT_TRUE(noexcept(timer.toggle()));
        });
}

/**
 * @brief §2.4 set 4, task d): a running timer times out on exactly its timeout-th tick, and
 *        hasTimedOut() resets the counter so the next timeout is a whole timeout later.
 */
TEST(Timer, TimesOutAfterExactlyItsTimeout)
{
    suppressOutput(
        []
        {
            Timer timer{100U};
            timer.start();
            EXPECT_EQ(timeoutsAfter(timer, 99U), 0U);
            timer.tick();
            EXPECT_TRUE(timer.hasTimedOut());
            EXPECT_EQ(timeoutsAfter(timer, 99U), 0U);
            EXPECT_EQ(timeoutsAfter(timer, 400U), 4U);
            EXPECT_TRUE(noexcept(timer.tick()));
            EXPECT_TRUE(noexcept(timer.hasTimedOut()));
        });
}

/**
 * @brief §2.4 set 4, task d): tick() counts only while the timer is running.
 */
TEST(Timer, DoesNotCountWhileStopped)
{
    suppressOutput(
        []
        {
            Timer timer{100U};
            EXPECT_EQ(timeoutsAfter(timer, 1000U), 0U);
            timer.start();
            EXPECT_EQ(timeoutsAfter(timer, 100U), 1U);
        });
}

/**
 * @brief §2.4 set 4, task c): a timer destroyed while running says so; a stopped one says nothing.
 */
TEST(Timer, AnnouncesOnlyARunningTimerStoppedAtDeletion)
{
    EXPECT_OUTPUT(captureOutput(
                      []
                      {
                          Timer timer{100U};
                          timer.start();
                      }),
                  "Stopping timer before deletion!\n");
    EXPECT_OUTPUT(captureOutput([] { const Timer timer{100U}; }), "");
    EXPECT_OUTPUT(captureOutput(
                      []
                      {
                          Timer timer{100U};
                          timer.start();
                          timer.stop();
                      }),
                  "");
}

#ifdef PROGRAM

/**
 * @brief §2.4 set 4, task f): three timeouts in 3000 ticks of a 1000 ms timer, then the
 * destructor's message, because the timer is still running when main() returns.
 */
TEST(Program, PrintsTheExampleOutput)
{
    EXPECT_PROGRAM_OUTPUT("Timeout after 1000 ms!\n"
                          "Timeout after 1000 ms!\n"
                          "Timeout after 1000 ms!\n"
                          "Stopping timer before deletion!\n");
}

#endif
