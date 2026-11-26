#ifndef MHAA_GPIO_EXAMPLE_FAKE_HPP
#define MHAA_GPIO_EXAMPLE_FAKE_HPP

#include <gpio/port.hpp>
#include <gpio/output_setup.hpp>
#include <gpio/output_latch.hpp>
#include <gpio/output_toggle.hpp>
#include <gpio/pull_control.hpp>

namespace example
{
    using namespace mhaa::gpio;

    class Fake final : public OutputSetup, public OutputLatch, public OutputToggle, public PullControl
    {
    public:
        bool valid(PinId pin) const override { return pin == static_cast<PinId>(2); }
        Status set_direction(PinId pin, Direction direction) override
        {
            if (!valid(pin))
            {
                return Status::InvalidPin;
            }
            output = direction == Direction::Output;
            return Status::Success;
        }
        Status write(PinId pin, Level level) override
        {
            if (!valid(pin))
            {
                return Status::InvalidPin;
            }
            if (!output)
            {
                return Status::WrongDirection;
            }
            latch = level;
            return Status::Success;
        }
        Status read(PinId pin, Level &level) const override
        {
            if (!valid(pin))
            {
                return Status::InvalidPin;
            }
            level = physical;
            return Status::Success;
        }
        Status configure_output(PinId pin, Level initial) override
        {
            if (!valid(pin))
            {
                return Status::InvalidPin;
            }
            latch = initial;
            output = true;
            ++setups;
            return Status::Success;
        }

        Status read_latch(PinId pin, Level &level) const override
        {
            if (!valid(pin))
            {
                return Status::InvalidPin;
            }
            level = latch;
            return Status::Success;
        }

        Status toggle(PinId pin) override
        {
            return write(pin, latch == Level::High ? Level::Low : Level::High);
        }

        Status set_pull(PinId pin, Pull value) override
        {
            if (!valid(pin))
            {
                return Status::InvalidPin;
            }
            pull = value;
            return Status::Success;
        }

        Pull pull = Pull::None;
        bool output = false;
        Level latch = Level::Low;
        Level physical = Level::Low;
        unsigned setups = 0;
    };
}

#endif
