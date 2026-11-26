#include <gpio/gpio.hpp>
#include "../examples/fake.hpp"

#include <cassert>

using namespace mhaa::gpio;
using namespace example;

int main()
{
    Fake port;
    GPIO gpio(port);
    assert(gpio.high(static_cast<PinId>(2)) == Status::WrongDirection);
    assert(gpio.output(static_cast<PinId>(1), Level::High) == Status::InvalidPin);
    assert(gpio.output(static_cast<PinId>(2), Level::High) == Status::Success);
    assert(port.setups == 1 && port.latch == Level::High && port.output);
    Level observed = Level::High;
    assert(gpio.read(static_cast<PinId>(2), observed) == Status::Success && observed == Level::Low);
    observed = Level::High;
    assert(gpio.read(static_cast<PinId>(1), observed) == Status::InvalidPin && observed == Level::High);
    assert(gpio.low(static_cast<PinId>(2)) == Status::Success && port.latch == Level::Low);
    GPIO basic(static_cast<Port &>(port));
    assert(basic.output(static_cast<PinId>(2), Level::High) == Status::Unsupported && port.setups == 1);
    assert(basic.input(static_cast<PinId>(2)) == Status::Success && !port.output);

    GPIO equipped(port, &port, &port, &port);
    const auto pin = static_cast<PinId>(2);
    assert(basic.set_pull(pin, Pull::Up) == Status::Unsupported);
    assert(basic.toggle(pin) == Status::Unsupported);
    assert(basic.read_latch(pin, observed) == Status::Unsupported && observed == Level::High);
    assert(equipped.set_pull(static_cast<PinId>(99), Pull::Up) == Status::InvalidPin);
    assert(equipped.set_pull(pin, Pull::Up) == Status::Success && port.pull == Pull::Up);
    assert(equipped.output(pin, Level::Low) == Status::Success);
    assert(equipped.toggle(pin) == Status::Success);
    assert(equipped.read_latch(pin, observed) == Status::Success && observed == Level::High);
    assert(equipped.read(pin, observed) == Status::Success && observed == Level::Low);
}
