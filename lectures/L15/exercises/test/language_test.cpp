/**
 * @file The suite's always-on tests: claims §5.1 and §5.2 makes about templates and type traits,
 * checked.
 *
 *       Every lecture's suite has one binary that is built whether or not you have written
 *       anything, because qacademy::test::runAllTests() reports failure when it has no tests to
 *       run, and a suite that is red on a fresh clone looks broken when it is merely empty. It
 *       may as well hold something worth knowing, so these tests are the appendix's statements
 *       about function templates and type traits, each in a form the compiler can confirm.
 *       The class-template facts are in L16's suite, whose appendix introduces them.
 */
#include <cstddef>
#include <cstdint>
#include <type_traits>

#include "qacademy/test/test.hpp"

namespace
{
/** The function template from §5.1 and §5.2. */
template<typename T>
[[nodiscard]] constexpr T add(const T x, const T y) noexcept
{
    return x + y;
}

/** Set one bit in a register of any integral type (§5.1 and §5.2). */
template<typename T>
constexpr void set(T& reg, const std::uint8_t bit) noexcept
{
    reg |= (static_cast<T>(1U) << bit);
}

/** The custom trait from §5.1 and §5.2: false for every type... */
template<typename T>
struct isUnsigned
{
    static constexpr bool value{false};
};

/** ...except those it is specialized for. */
template<>
struct isUnsigned<std::uint8_t>
{
    static constexpr bool value{true};
};

template<>
struct isUnsigned<std::uint16_t>
{
    static constexpr bool value{true};
};

template<>
struct isUnsigned<std::uint32_t>
{
    static constexpr bool value{true};
};

/** The variable template from §5.1 and §5.2. */
template<typename T>
inline constexpr bool isUnsigned_v{isUnsigned<T>::value};

/**
 * @brief Count the arguments in a parameter pack.
 *
 * @return How many arguments were passed.
 */
template<typename... Args>
[[nodiscard]] constexpr std::size_t countArgs(const Args&...) noexcept
{
    return sizeof...(Args);
}
} // namespace

/**
 * @brief §5.1 and §5.2: add(1, 2) and add(1.0, 2.0) instantiate add<int> and add<double>, and each
 *        returns its own type.
 */
TEST(Language, EachCallInstantiatesForItsType)
{
    const auto sum1 = add(1, 2);
    const auto sum2 = add(1.0, 2.0);
    EXPECT_TRUE((std::is_same<decltype(sum1), const int>::value));
    EXPECT_TRUE((std::is_same<decltype(sum2), const double>::value));
    EXPECT_EQ(sum1, 3);
    EXPECT_NEAR(sum2, 3.0, 1e-12);
    static_assert(add(20, 22) == 42, "a constexpr template is usable at compile time");
}

/**
 * @brief §5.1 and §5.2: set(std::uint8_t&, ...) and set(std::uint32_t&, ...) are two separate
 *        functions, at two separate addresses, which is where a template's code size comes from.
 */
TEST(Language, EachTypeIsASeparateFunction)
{
    void (*const setByte)(std::uint8_t&, std::uint8_t) noexcept {&set<std::uint8_t>};
    void (*const setWord)(std::uint32_t&, std::uint8_t) noexcept {&set<std::uint32_t>};
    EXPECT_NE(reinterpret_cast<const void*>(setByte), reinterpret_cast<const void*>(setWord));

    std::uint8_t reg1{};
    std::uint32_t reg2{};
    set(reg1, 1U);
    set(reg2, 12U);
    EXPECT_EQ(static_cast<std::uint32_t>(reg1), 0x02U);
    EXPECT_EQ(reg2, 0x1000U);
}

/**
 * @brief §5.1 and §5.2: is_integral accepts only integers, while is_arithmetic lets floating point
 *        through, which is why a bit operation must check the first.
 */
TEST(Language, IntegralIsNarrowerThanArithmetic)
{
    EXPECT_TRUE(std::is_integral<int>::value);
    EXPECT_FALSE(std::is_integral<double>::value);
    EXPECT_TRUE(std::is_arithmetic<double>::value);
    EXPECT_TRUE(std::is_floating_point<float>::value);
    EXPECT_TRUE(std::is_integral_v<std::uint64_t>);
}

/**
 * @brief §5.1 and §5.2: is_unsigned, the standard trait the custom isUnsigned imitates.
 */
TEST(Language, IsUnsignedSeparatesTheSignedTypes)
{
    EXPECT_TRUE(std::is_unsigned<std::uint8_t>::value);
    EXPECT_TRUE(std::is_unsigned<std::uint32_t>::value);
    EXPECT_FALSE(std::is_unsigned<int>::value);
    EXPECT_FALSE(std::is_unsigned<float>::value);
}

/**
 * @brief §5.1 and §5.2: the custom trait is false for every type but those it is specialized for,
 *        and the variable template reads the same value.
 */
TEST(Language, CustomTraitsAreSpecializations)
{
    EXPECT_TRUE(isUnsigned<std::uint16_t>::value);
    EXPECT_FALSE(isUnsigned<int>::value);
    EXPECT_FALSE(isUnsigned<double>::value);
    EXPECT_TRUE(isUnsigned_v<std::uint32_t>);
    EXPECT_FALSE(isUnsigned_v<char>);
}

/**
 * @brief §5.1 and §5.2: sizeof... counts the arguments in a parameter pack, at compile time.
 */
TEST(Language, SizeofCountsAParameterPack)
{
    static_assert(countArgs() == 0U, "an empty pack has no arguments");
    EXPECT_EQ(countArgs(1, 2.0, 'c'), static_cast<std::size_t>(3U));
}
