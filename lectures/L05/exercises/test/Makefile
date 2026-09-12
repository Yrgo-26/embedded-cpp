# L05 test suite: one binary per exercise set, plus the always-on language tests. What each
# variable means is in ci/suite.mk, which does the building; see README.md for what is tested.

BINARIES := language exercise1 exercise2 exercise3

# Always built: the facts about classes that §2.1 and §2.2 of the book state, checked.
language_NEEDS :=

# Exercise Set 1: the Led and Button classes, header-only, and the program that uses them.
exercise1_NEEDS    := exercise1/include/driver/gpio/led.hpp
exercise1_INCLUDES := exercise1/include exercise1
exercise1_PROGRAM  := exercise1/main.cpp

# Exercise Set 2: the same classes, controlled and blinked by the program in main.cpp.
exercise2_NEEDS    := exercise2/main.cpp
exercise2_INCLUDES := exercise2/include exercise2
exercise2_PROGRAM  := exercise2/main.cpp

# Exercise Set 3: the Buzzer class, split into a header and a source file.
exercise3_NEEDS    := exercise3/include/driver/buzzer.hpp exercise3/source/driver/buzzer.cpp
exercise3_INCLUDES := exercise3/include exercise3/source
exercise3_SOURCES  := exercise3/source/driver/*.cpp
exercise3_PROGRAM  := exercise3/source/driver/*.cpp exercise3/source/main.cpp

include ../../../../ci/suite.mk
