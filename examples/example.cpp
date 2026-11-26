#include <gpio/gpio.hpp>
#include "fake.hpp"

using namespace mhaa::gpio;
using namespace example;

int main()
{
    Fake port;
    GPIO gpio(port);
    return gpio.output(static_cast<PinId>(2), Level::High) == Status::Success &&
                   gpio.low(static_cast<PinId>(2)) == Status::Success
               ? 0
               : 1;
}
