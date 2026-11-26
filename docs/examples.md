# Run the GPIO Core example

The fake extends `OutputSetup`, so passing it to `GPIO` selects the initial-level constructor. Logical pin 2 starts as a high output, then `low` drives it low. Both calls must succeed. The behavior tests compare physical input and latch values, check invalid pins, and show what happens when the Core is constructed from a base `Port&` without optional controls.

## Example program

The [program](../examples/example.cpp) uses the [local fake](../examples/fake.hpp) to demonstrate injection. A concrete Adapter implementing the same Contract can be supplied to the same facade.

```cpp
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
```

## Build and run

Build from this repository root. Set `contract_include` to the matching Contract's `include/` directory. The value below applies to the MHAA development workspace. Both programs exit with status 0 on success and print no output. On Windows execute `example.exe` and `behavior.exe`.

```sh
contract_include=../../contracts/gpio-contract/include
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude -I"$contract_include" examples/example.cpp -o example
./example
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude -I"$contract_include" tests/behavior.cpp -o behavior
./behavior
```

See the [behavior test](../tests/behavior.cpp) for the additional cases described above.
