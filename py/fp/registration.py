from __future__ import annotations

from collections.abc import Callable
from typing import Any

type _Func[**P, R] = Callable[P, R]

_registry: list[_Func[..., Any]] = []


def register[**P, R](func: _Func[P, R]) -> _Func[P, R]:
    print(f"running register({func})")
    _registry.append(func)
    return func


@register
def f1() -> None:
    print("running f1()")


@register
def f2(i: int) -> int:
    print(f"running f2({i})")
    return i


def f3(s: str, *, b: bool = False) -> str:
    print(f"running f3({s}, {b})")
    return s + str(b)


def test_main() -> None:
    print("running test_main()")
    print(f"registry: {_registry}")
    f1()
    _ = f2(1)
    _ = f3("a", b=True)


if __name__ == "__main__":
    test_main()

    # Output:
    # running register(<function f1 at 0x100a362a0>)
    # running register(<function f2 at 0x100a9cf40>)
    # running test_main()
    # registry: [<function f1 at 0x100a362a0>, <function f2 at 0x100a9cf40>]
    # running f1()
    # running f2(1)
    # running f3(a, True)
