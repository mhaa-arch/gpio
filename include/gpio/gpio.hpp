#ifndef MHAA_GPIO_HPP
#define MHAA_GPIO_HPP

#include <gpio/port.hpp>
#include <gpio/output_setup.hpp>
#include <gpio/output_latch.hpp>
#include <gpio/output_toggle.hpp>
#include <gpio/pull_control.hpp>
#include <gpio/types.hpp>

namespace mhaa
{
    namespace gpio
    {
        /** @brief Operations on one borrowed logical port. */
        class GPIO
        {
        public:
            explicit GPIO(Port &port, PullControl *pull = nullptr,
                          OutputLatch *latch = nullptr, OutputToggle *toggle = nullptr)
                : port_(port), setup_(nullptr), pull_(pull), latch_(latch), toggle_(toggle) {}

            explicit GPIO(OutputSetup &port, PullControl *pull = nullptr,
                          OutputLatch *latch = nullptr, OutputToggle *toggle = nullptr)
                : GPIO(static_cast<Port &>(port), pull, latch, toggle)
            {
                setup_ = &port;
            }

            Status input(PinId pin) { return port_.set_direction(pin, Direction::Input); }
            Status output(PinId pin) { return port_.set_direction(pin, Direction::Output); }
            /** @brief Applies an initial level through the same port's optional setup. */
            Status output(PinId pin, Level initial_level)
            {
                if (!port_.valid(pin))
                {
                    return Status::InvalidPin;
                }
                return setup_ ? setup_->configure_output(pin, initial_level) : Status::Unsupported;
            }

            Status high(PinId pin) { return port_.write(pin, Level::High); }
            Status low(PinId pin) { return port_.write(pin, Level::Low); }

            /** @brief Samples the physical level. Returns InvalidPin for unavailable pins. */
            Status read(PinId pin, Level &level) const { return port_.read(pin, level); }

            /** @brief Sets an optional internal bias on the same port. */
            Status set_pull(PinId pin, Pull pull)
            {
                if (!port_.valid(pin))
                {
                    return Status::InvalidPin;
                }
                return pull_ ? pull_->set_pull(pin, pull) : Status::Unsupported;
            }

            /** @brief Preserves level on error. This reads the programmed value. */
            Status read_latch(PinId pin, Level &level) const
            {
                if (!port_.valid(pin))
                {
                    return Status::InvalidPin;
                }
                return latch_ ? latch_->read_latch(pin, level) : Status::Unsupported;
            }

            Status toggle(PinId pin)
            {
                if (!port_.valid(pin))
                {
                    return Status::InvalidPin;
                }
                return toggle_ ? toggle_->toggle(pin) : Status::Unsupported;
            }

        private:
            Port &port_;
            OutputSetup *setup_;
            PullControl *pull_;
            OutputLatch *latch_;
            OutputToggle *toggle_;
        };
    }
}

#endif
