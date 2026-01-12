from __future__ import annotations

from typing import Callable, ParamSpec, TypeAlias, TypeVar

P = ParamSpec("P")
R = TypeVar("R")
Func: TypeAlias = Callable[P, R]

# In Python, generic type variables (`TypeVar`, `ParamSpec`) are instantiated only as type parameters of functions or
# classes. Even if a generic type is used in a global variable annotation, the variable itself is not fixed to
# a single concrete type. Therefore, the code below represents a list of Callables whose elements may each have
# their own distinct `P` and `R`. In other words, this is not a generic container, but a container holding generic
# elements, and in practice it behaves almost like `list[Callable[..., Any]]`.
registry: list[Func] = []


def register(func: Func) -> Func:
    print(f"running register({func})")
    registry.append(func)
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


def test_main():
    print("running test_main()")
    print(f"registry: {registry}")
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
