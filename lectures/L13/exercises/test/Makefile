# L13 test suite: one binary per exercise set, plus the always-on ownership tests. What each
# variable means is in ci/suite.mk, which does the building; see README.md for what is tested.

BINARIES := language exercise1 exercise2 exercise3

# Always built: what §4.1 of the book says about owning an object, checked.
language_NEEDS :=

# Övningsset 1: the serial interface, the stub, and the ESP32-S3 driver, in raw_factory.
exercise1_NEEDS    := raw_factory/include/driver/serial/interface.hpp \
                      raw_factory/include/driver/serial/stub.hpp \
                      raw_factory/include/driver/serial/esp32s3.hpp
exercise1_INCLUDES := raw_factory/include

# Övningsset 2: the factory interface and the two factories, returning raw pointers.
exercise2_NEEDS    := raw_factory/include/driver/factory/interface.hpp \
                      raw_factory/include/driver/factory/esp32s3.hpp \
                      raw_factory/include/driver/factory/stub.hpp
exercise2_INCLUDES := raw_factory/include

# Övningsset 3: the logic class that owns a raw pointer, and the program that uses it.
exercise3_NEEDS    := raw_factory/include/app/logic/logic.hpp
exercise3_INCLUDES := raw_factory/include raw_factory/source

include ../../../../ci/suite.mk
