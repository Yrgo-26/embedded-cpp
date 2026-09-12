/**
 * @file The suite's always-on tests: claims §5.3 makes about class templates, checked.
 *
 *       Every lecture's suite has one binary that is built whether or not you have written
 *       anything, because qacademy::test::runAllTests() reports failure when it has no tests to
 *       run, and a suite that is red on a fresh clone looks broken when it is merely empty. It
 *       may as well hold something worth knowing, so these tests are the appendix's statements
 *       about class templates, each in a form the compiler can confirm. The function-template
 *       and type-trait facts are in L15's suite.
 */
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <type_traits>

#include "qacademy/test/test.hpp"

namespace
{
/** A class template, as in §5.3: one blueprint, a separate type per argument. */
template<typename T>
class Vector
{
public:
    Vector() noexcept
        : myData{nullptr}
        , mySize{}
    {}

    [[nodiscard]] std::size_t size() const noexcept { return mySize; }

private:
    T* myData;
    std::size_t mySize;
};

/** A primary template and a full specialization, as the timer driver in Övning 1.1 has. */
template<typename T>
struct Implementation
{
    static constexpr const char* name{"primary"};
};

template<>
struct Implementation<float>
{
    static constexpr const char* name{"specialization"};
};

/** A default template argument, as Timer<Type T = Type::Stub> has. */
template<std::size_t Capacity = 8U>
struct Buffer
{
    std::uint8_t data[Capacity];
};

} // namespace

/**
 * @brief §5.3: Vector<int> and Vector<double> are two different types, generated from one
 *        blueprint at compile time.
 */
TEST(Language, EachArgumentIsASeparateType)
{
    EXPECT_FALSE((std::is_same<Vector<int>, Vector<double>>::value));
    const Vector<int> a{};
    const Vector<double> b{};
    EXPECT_EQ(a.size(), b.size());
}

/**
 * @brief Övning 1.1: a full specialization is chosen over the primary template for its own
 *        argument, and the primary template is used for every other.
 */
TEST(Language, FullSpecializationWinsForItsArgument)
{
    EXPECT_EQ(std::strcmp(Implementation<float>::name, "specialization"), 0);
    EXPECT_EQ(std::strcmp(Implementation<int>::name, "primary"), 0);
    EXPECT_EQ(std::strcmp(Implementation<double>::name, "primary"), 0);
}

/**
 * @brief A default template argument is used when none is given, so Buffer<> is Buffer<8>; and a
 *        value in the type is part of the type, so different capacities are different sizes.
 */
TEST(Language, TemplateArgumentsArePartOfTheType)
{
    EXPECT_TRUE((std::is_same<Buffer<>, Buffer<8U>>::value));
    EXPECT_EQ(sizeof(Buffer<4U>), static_cast<std::size_t>(4U));
    EXPECT_EQ(sizeof(Buffer<16U>), static_cast<std::size_t>(16U));
    EXPECT_EQ((std::array<std::uint8_t, 12U>{}.size()), static_cast<std::size_t>(12U));
}
