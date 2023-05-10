#pragma once

#include "file.hpp"

#include <linux/gpio.h>

#include <string>
#include <type_traits>

namespace phosphor
{
namespace gpio
{

typedef std::remove_reference<
    decltype(gpiohandle_request::lineoffsets[0])>::type gpioNum_t;

typedef std::remove_reference<decltype(gpiohandle_data::values[0])>::type
    gpioValue_t;

/**
 * Represents a GPIO.
 *
 * Operations are setting low or high.
 *
 * Read support may be added in the future.
 */
class GPIO
{
  public:
    /**
     * If the GPIO is an input or output
     */
    enum class Direction
    {
        input,
        output
    };

    /**
     * The possible values - low or high
     */
    enum class Value
    {
        low,
        high
    };

    GPIO() = delete;
    GPIO(const GPIO&) = delete;
    GPIO(GPIO&&) = default;
    GPIO& operator=(const GPIO&) = delete;
    GPIO& operator=(GPIO&&) = default;
    ~GPIO() = default;

    /**
     * Constructor
     *
     * @param[in] device - the GPIO device file
     * @param[in] gpio - the GPIO number
     * @param[in] direction - the GPIO direction
     */
    GPIO(const std::string& device, gpioNum_t gpio, Direction direction) :
        device(device), gpio(gpio), direction(direction)
    {}

    /**
     * Sets the GPIO value
     *
     * Requests the GPIO line if it hasn't been done already.
     */
    void set(Value value);

  private:
    /**
     * Requests a GPIO line from the GPIO device
     *
     * @param[in] defaultValue - The default value, required for
     *                           output GPIOs only.
     */
    void requestLine(Value defaultValue = Value::high);

    /**
     * The GPIO device name, like /dev/gpiochip0
     */
    const std::string device;

    /**
     * The GPIO number
     */
    const gpioNum_t gpio;

    /**
     * The GPIO direction
     */
    const Direction direction;

    /**
     * File descriptor for the GPIO line
     */
    FileDescriptor lineFD;
};

} // namespace gpio
} // namespace phosphor
