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


``looking_glass`` Function Examples:

>>> with looking_glass() as what:
...     print("Alice, Kitty and Snowdrop")
...     print(what)
pordwonS dna yttiK ,ecilA
YKCOWREBBAJ
>>> what
'JABBERWOCKY'
>>> print("Back to normal.")
Back to normal.


``looking_glass`` Function as a Decorator Examples:

>>> @looking_glass()
... def verse() -> None:
...     print("The time has come")
>>> verse()
emoc sah emit ehT
>>> print("Back to normal.")
Back to normal.

"""

from __future__ import annotations

import sys
from collections.abc import Callable, Iterator
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


@contextmanager
def looking_glass() -> Iterator[str]:
    original_write: Callable[[str], int] = sys.stdout.write

    def write_reversed(text: str) -> int:
        return original_write(text[::-1])

    sys.stdout.write = write_reversed  # type: ignore[method-assign]
    msg = ""
    try:
        yield "JABBERWOCKY"
    except ZeroDivisionError:
        msg = "Please DO NOT divide by zero!"
    finally:
        sys.stdout.write = original_write  # type: ignore[method-assign]
        if msg:
            print(msg)


if __name__ == "__main__":
    import doctest

    doctest.testmod()
