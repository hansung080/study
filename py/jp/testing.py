from __future__ import annotations

import sys
from typing import Any, Callable, TypeVar

T = TypeVar("T")


def assert_eq(left: T, right: T, *, msg: str = "") -> None:
    if left != right:
        print(f"assert_eq failed: {msg}\n  left: {left}\n right: {right}", file=sys.stderr)
        sys.exit(1)


def assert_ne(left: T, right: T, *, msg: str = "") -> None:
    if left == right:
        print(f"assert_ne failed: {msg}\n  left: {left}\n right: {right}", file=sys.stderr)
        sys.exit(1)


def _validate_exception_type(typ: Any) -> None:
    if isinstance(typ, tuple):
        for elem in typ:
            if not isinstance(elem, type) or not issubclass(elem, BaseException):
                raise TypeError(f"{elem!r} in tuple is not a subclass of BaseException")
    else:
        if not isinstance(typ, type) or not issubclass(typ, BaseException):
            raise TypeError(f"{typ!r} is not a subclass of BaseException")


def assert_raises(
    func: Callable[[], Any],
    *,
    expected: type[BaseException] | tuple[type[BaseException], ...] | None = Exception,
    msg: str = "",
) -> None:
    if expected is not None:
        _validate_exception_type(expected)
    try:
        func()
    except BaseException as got:
        if expected is None or not isinstance(got, expected):
            print(f"assert_raises failed: {msg}\n      got: {type(got)!r}\n expected: {expected!r}", file=sys.stderr)
            sys.exit(1)
    else:
        if expected is not None:
            print(f"assert_raises failed: {msg}\n      got: {None}\n expected: {expected!r}", file=sys.stderr)
            sys.exit(1)


if __name__ == "__main__":
    assert_eq(1, 1)
    assert_ne(1, 2)

    def raise_value_error() -> None:
        raise ValueError()

    assert_raises(raise_value_error)
    assert_raises(raise_value_error, expected=ValueError)
    assert_raises(raise_value_error, expected=(ValueError, TypeError))
    assert_raises(raise_value_error, expected=(TypeError, ValueError))
    assert_raises(lambda: (), expected=None)

    # The following assertions will be failed.
    # assert_raises(raise_value_error, expected=TypeError)
    # assert_raises(raise_value_error, expected=None)
    # assert_raises(lambda: (), expected=ValueError)
