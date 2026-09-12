# L14 test suite: the lecture has one exercise set, the factory rewritten with std::unique_ptr,
# plus the always-on ownership tests. What each variable means is in ci/suite.mk, which does the
# building; see README.md for what is tested.

BINARIES := language exercise1

# Always built: what §4.2 of the book says about std::unique_ptr, checked.
language_NEEDS :=

# Övningsset 1: the same program as in L13, in smart_factory. Built once the new factory interface
# exists; the factories and the logic class are tested as they appear.
exercise1_NEEDS    := smart_factory/include/driver/factory/interface.hpp
exercise1_INCLUDES := smart_factory/include smart_factory/source

include ../../../../ci/suite.mk
