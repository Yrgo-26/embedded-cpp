# L06 test suite: the lecture has one exercise set, the Timer class split across a header and a
# source file. What each variable means is in ci/suite.mk, which does the building; see README.md
# for what is tested. The always-on language tests live in L05, whose appendices state the facts
# about classes that this lecture practises.

BINARIES := exercise1

# Exercise set 4 of §2.4: the Timer class, and the program that tests it.
exercise1_NEEDS    := exercise1/include/driver/timer.hpp exercise1/source/driver/timer.cpp
exercise1_INCLUDES := exercise1/include exercise1/source
exercise1_SOURCES  := exercise1/source/driver/*.cpp
exercise1_PROGRAM  := exercise1/source/driver/*.cpp exercise1/source/main.cpp

include ../../../../ci/suite.mk
