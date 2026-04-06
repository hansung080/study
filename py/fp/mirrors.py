"""
``mirrors`` Module

``LookingGlass`` Class Examples:

>>> with LookingGlass() as what:
...     print("Alice, Kitty and Snowdrop")
...     print(what)
pordwonS dna yttiK ,ecilA
YKCOWREBBAJ
>>> what
'JABBERWOCKY'
>>> print("Back to normal.")
Back to normal.

"""

from __future__ import annotations

import sys
from collections.abc import Callable
from types import TracebackType


class LookingGlass:
    def __enter__(self) -> str:
        self.original_write: Callable[[str], int] = sys.stdout.write
        sys.stdout.write = self.write_reversed
        return "JABBERWOCKY"

    def write_reversed(self, text: str) -> int:
        return self.original_write(text[::-1])

    def __exit__(
        self,
        exc_type: type[BaseException] | None,
        exc_value: BaseException | None,
        traceback: TracebackType | None,
    ) -> bool:
        sys.stdout.write = self.original_write
        if exc_type is ZeroDivisionError:
            print("Please DO NOT divide by zero!")
            return True
        return False


if __name__ == "__main__":
    import doctest

    doctest.testmod()
