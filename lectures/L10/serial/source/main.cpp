/**
 * @brief Serial driver demo.
 */
#include <cstdint>
#include <cstdio>

#include "driver/serial/stub.hpp"

namespace
{
/**
 * @brief Run the system with a serial device.
 *
 * @param serial Serial interface used for writing and reading.
 */
void runSystem(driver::serial::Interface& serial) noexcept
{
    static_cast<void>(serial.write("Available serial data: "));

    // Read and print available data byte by byte.
    while (serial.isDataAvailable())
    {
        // Print bytes in two-digit hexadecimal form.
        const std::uint8_t byte{serial.read()};
        std::printf("%02X ", byte);
    }
    static_cast<void>(serial.write("\n"));
}
} // namespace

/**
 * @brief Create a serial stub and process simulated input.
 *
 * @return Exit code 0 on success, 1 if the stub could not be set up.
 */
int main()
{
    constexpr int success{0};
    constexpr int failure{1};

    // Create and connect a serial stub.
    driver::serial::Stub serial{};

    if (!serial.connect())
    {
        std::printf("Failed to connect the serial stub!\n");
        return failure;
    }

    // Simulate incoming serial data.
    constexpr std::uint8_t bufLen{5U};
    const std::uint8_t buf[bufLen]{0x10U, 0xFFU, 0xA0U, 0x01U, 0x7FU};

    if (bufLen != serial.simulateInput(buf, bufLen))
    {
        std::printf("Failed to buffer all %u simulated bytes!\n", bufLen);
        return failure;
    }

    // Pass serial driver to system logic.
    runSystem(serial);
    return success;
}
