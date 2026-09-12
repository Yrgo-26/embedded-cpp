/**
 * @file The suite's always-on tests: what §4.1 says about owning an object, checked.
 *
 *       Every lecture's suite has one binary that is built whether or not you have written
 *       anything, because qacademy::test::runAllTests() reports failure when it has no tests to
 *       run. This one holds §4.1's claims about new and delete, each in a form the compiler
 *       or a running program can confirm. The std::unique_ptr facts are in L14's suite,
 *       whose appendix introduces them.
 */
#include <type_traits>

#include "qacademy/test/test.hpp"

namespace
{
/** How many Derived objects have been destroyed. */
int destroyed{};

/** A base class with a virtual destructor, like every interface in the course. */
struct Base
{
    virtual ~Base() noexcept = default;
};

/** A derived class that counts its own destruction. */
struct Derived final : Base
{
    ~Derived() noexcept override { ++destroyed; }
};
} // namespace

/**
 * @brief §4.1: new calls the constructor, and delete through a base-class pointer calls the
 *        derived class's destructor, because the base's destructor is virtual.
 */
TEST(Ownership, DeleteThroughTheInterfaceDestroysTheDriver)
{
    destroyed = 0;
    Base* object{new Derived{}};
    delete object;
    EXPECT_EQ(destroyed, 1);
    EXPECT_TRUE(std::has_virtual_destructor<Base>::value);
}
