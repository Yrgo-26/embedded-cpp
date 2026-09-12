# L15 test suite: one binary for the exercise set that has a program, plus the always-on language
# tests. What each variable means is in ci/suite.mk, which does the building; see README.md for
# what is tested. Övningsset 2 is questions to answer in prose, so it has no binary.

BINARIES := language function_template

# Always built: the facts about function templates and type traits that §5.1 and §5.2 of the book state, checked.
language_NEEDS :=

# Övningsset 1: the clear and toggle function templates, in main.cpp.
function_template_NEEDS    := function_template/main.cpp
function_template_INCLUDES := function_template
function_template_PROGRAM  := function_template/main.cpp
function_template_REJECTS  := function_template_rejects_float_clear.cpp \
                              function_template_rejects_float_toggle.cpp

include ../../../../ci/suite.mk
