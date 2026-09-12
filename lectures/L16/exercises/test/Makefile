# L16 test suite: one binary for the lecture's exercise set, plus the always-on language tests.
# What each variable means is in ci/suite.mk, which does the building; see README.md for what is
# tested.

BINARIES := language class_template

# Always built: the facts about class templates that §5.3 of the book states, checked.
language_NEEDS :=

# Övningsset 1: the Timer class template and its STM32 specialization, and the program that uses
# them once source/main.cpp exists too.
class_template_NEEDS    := class_template/include/driver/timer/timer.hpp
class_template_INCLUDES := class_template/include class_template/source
class_template_PROGRAM  := class_template/source/main.cpp

include ../../../../ci/suite.mk
