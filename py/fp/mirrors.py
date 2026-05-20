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


``LookingGlass`` Class without ``with`` Block Examples:

>>> manager = LookingGlass()
>>> manager  # doctest: +ELLIPSIS
<__main__.LookingGlass object at 0x...>
>>> monster = manager.__enter__()
>>> monster == "JABBERWOCKY"
eurT
>>> monster
'YKCOWREBBAJ'
>>> manager  # doctest: +ELLIPSIS
>...x0 ta tcejbo ssalGgnikooL.__niam__<
>>> manager.__exit__(None, None, None)
>>> monster
'JABBERWOCKY'

"""

from __future__ import annotations

import sys
from collections.abc import Callable
from contextlib import contextmanager
from types import TracebackType


class LookingGlass:
    def __enter__(self) -> str:
        self.original_write: Callable[[str], int] = sys.stdout.write
        sys.stdout.write = self.write_reversed  # type: ignore[method-assign]
        return "JABBERWOCKY"

    def write_reversed(self, text: str) -> int:
        return self.original_write(text[::-1])

    def __exit__(
        self,
        exc_type: type[BaseException] | None,
        exc_value: BaseException | None,
        traceback: TracebackType | None,
    ) -> bool | None:
        sys.stdout.write = self.original_write  # type: ignore[method-assign]
        if exc_type is ZeroDivisionError:
            print("Please DO NOT divide by zero!")
            return True  # True: suppress the exception
        return None  # None or False: propagate the exception


# @contextmanager
# def looking_glass():
#     pass


if __name__ == "__main__":
    import doctest

    doctest.testmod()
