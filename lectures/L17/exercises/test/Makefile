# L17 test suite: one binary per solution program, plus the always-on language tests. What each
# variable means is in ci/suite.mk, which does the building; see README.md for what is tested.
# Every binary starts threads, so every binary is built with -pthread.

BINARIES := language exercise1 exercise2 exercise3 exercise4-5 exercise6 exercise7

# Always built: the claims §6.1 of the book makes about threads, mutexes, atomics and futures.
language_NEEDS :=
language_FLAGS := -pthread

# Övningsset 1: workerThread with an atomic stop flag, in exercise1.cpp.
exercise1_NEEDS    := exercise1/exercise1.cpp
exercise1_INCLUDES := exercise1
exercise1_FLAGS    := -pthread

# Övningsset 2: incrementCounter on an atomic counter, in exercise2.cpp.
exercise2_NEEDS    := exercise2/exercise2.cpp
exercise2_INCLUDES := exercise2
exercise2_FLAGS    := -pthread
exercise2_PROGRAM  := exercise2/exercise2.cpp

# Övningsset 3: SharedMem, txThread and rxThread, in exercise3.cpp.
exercise3_NEEDS    := exercise3/exercise3.cpp
exercise3_INCLUDES := exercise3
exercise3_FLAGS    := -pthread

# Övningsset 4 och 5: the counter interface, the thread-safe stub, and the program using them.
exercise4-5_NEEDS    := exercise4-5/include/driver/counter/interface.hpp \
                        exercise4-5/include/driver/counter/stub.hpp
exercise4-5_INCLUDES := exercise4-5/include exercise4-5/source
exercise4-5_FLAGS    := -pthread
exercise4-5_PROGRAM  := exercise4-5/source/main.cpp

# Övningsset 6: the condition variable version of Set 3, in exercise6.cpp.
exercise6_NEEDS    := exercise6/exercise6.cpp
exercise6_INCLUDES := exercise6
exercise6_FLAGS    := -pthread

# Övningsset 7: validateFirmware run through std::async, in exercise7.cpp.
exercise7_NEEDS    := exercise7/exercise7.cpp
exercise7_INCLUDES := exercise7
exercise7_FLAGS    := -pthread
exercise7_PROGRAM  := exercise7/exercise7.cpp

include ../../../../ci/suite.mk
