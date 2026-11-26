# GPIO Core guide

A pin's physical input and its output latch can report different levels. Each `PinId` is scoped to its port.

Start with pin identity and the difference between input and latch, then choose the capabilities the board needs.

- [Use the facade](api.md) for construction, results and optional capabilities.
- [Run the example](examples.md) to see the same API with a simulated resource.
- [Check portability](compatibility.md) for assumptions that belong to the target.
