from __future__ import annotations

from typing import TYPE_CHECKING, reveal_type


def test_narrowing() -> None:
    # --- Type-based Narrowing (for all types) ---
    a: str | int = "a"
    if TYPE_CHECKING:
        reveal_type(a)  # builtins.str | builtins.int

    assert isinstance(a, str)
    if TYPE_CHECKING:
        reveal_type(a)  # builtins.str

    print(a.upper())

    # --- Value-based Narrowing (for value-restricted types, e.g. None, Enum, Literal) ---
    b: str | None = "b"
    if TYPE_CHECKING:
        reveal_type(b)  # builtins.str | None

    assert b is not None
    if TYPE_CHECKING:
        reveal_type(b)  # builtins.str

    print(b.upper())

    # --- Assignment-based Narrowing (for all types) ---
    c: str | int = 0
    if TYPE_CHECKING:
        reveal_type(c)  # builtins.str | builtins.int

    c = "c"
    if TYPE_CHECKING:
        reveal_type(c)  # builtins.str

    print(c.upper())


if __name__ == "__main__":
    test_narrowing()
