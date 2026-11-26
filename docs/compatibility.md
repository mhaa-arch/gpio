# Using GPIO across targets

The only project dependency is the matching `gpio-contract`. Keep its API revision aligned with this Core.

Callers can keep the same direction, drive and read workflow across ports. An initial output level needs the optional setup path. A hardware toggle can differ from a software read/modify/write, and Core never synthesizes it from the input reading. Check supported pulls and pin mappings before reusing board configuration.

This repository's host simulations and shared API compile/link checks provide source-level evidence. Target timing and physical behavior require hardware validation.
