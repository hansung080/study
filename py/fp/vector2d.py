"""
2-Dimensional Vector Class

Basic Examples:

>>> v = Vector2d(3, 4)
>>> print(v.x, v.y)
3.0 4.0
>>> x, y = v
>>> x, y
(3.0, 4.0)
>>> v
Vector2d(3.0, 4.0)
>>> v_clone = eval(repr(v))
>>> v == v_clone
True
>>> print(v)
(3.0, 4.0)
>>> octets = bytes(v)
>>> octets
b'd\\x00\\x00\\x00\\x00\\x00\\x00\\x08@\\x00\\x00\\x00\\x00\\x00\\x00\\x10@'
>>> abs(v)
5.0
>>> bool(v), bool(Vector2d(0, 0))
(True, False)


``frombytes`` Method Examples:

>>> v_clone = Vector2d.frombytes(bytes(v))
>>> v_clone
Vector2d(3.0, 4.0)
>>> v == v_clone
True


``format`` Function with Cartesian Coordinates Examples:

>>> format(v)
'(3.0, 4.0)'
>>> format(v, ".2f")
'(3.00, 4.00)'
>>> format(v, ".3e")
'(3.000e+00, 4.000e+00)'


``angle`` Method Examples:

>>> Vector2d(0, 0).angle()
0.0
>>> Vector2d(1, 0).angle()
0.0
>>> epsilon = 10 ** -8
>>> abs(Vector2d(0, 1).angle() - math.pi / 2) < epsilon
True
>>> abs(Vector2d(1, 1).angle() - math.pi / 4) < epsilon
True


``format`` Function with Polar Coordinates Examples:

>>> format(Vector2d(1, 1), "p")  # doctest: +ELLIPSIS
'<1.414213..., 0.785398...>'
>>> format(Vector2d(1, 1), ".3ep")
'<1.414e+00, 7.854e-01>'
>>> format(Vector2d(1, 1), "0.5fp")
'<1.41421, 0.78540>'


``x`` and ``y`` Read-only Properties Examples:

>>> v.x, v.y
(3.0, 4.0)
>>> v.x = 123
Traceback (most recent call last):
  ...
AttributeError: property 'x' of 'Vector2d' object has no setter


Hash Examples:

>>> v1 = Vector2d(3, 4)
>>> v2 = Vector2d(3.1, 4.2)
>>> len({v1, v2})
2


Pattern Match Examples:

>>> v = Vector2d(3, 3)
>>> kind_kw(v)
'diagonal'
>>> kind_po(v)
'diagonal'


``__complex__`` and ``fromcomplex`` Methods Examples:

>>> v = Vector2d(3, 4)
>>> isinstance(v, SupportsComplex)
True
>>> complex(v)
(3+4j)
>>> Vector2d.fromcomplex(3+4j)
Vector2d(3.0, 4.0)

"""

from __future__ import annotations

import math
from array import array
from collections.abc import Iterable, Iterator
from typing import Any, Self, SupportsComplex, SupportsFloat


class Vector2d:
    __match_args__ = ("x", "y")
    __slots__ = ("__x", "__y")

    typecode = "d"

    def __init__(self, x: SupportsFloat, y: SupportsFloat) -> None:
        self.__x = float(x)
        self.__y = float(y)

    @property
    def x(self) -> float:
        return self.__x

    @property
    def y(self) -> float:
        return self.__y

    def __iter__(self) -> Iterator[float]:
        return (c for c in (self.x, self.y))

    def __repr__(self) -> str:
        class_name = type(self).__name__
        return "{}({!r}, {!r})".format(class_name, *self)

    def __str__(self) -> str:
        return str(tuple(self))

    def __bytes__(self) -> bytes:
        return (
            bytes([ord(self.typecode)]) +
            bytes(array(self.typecode, self))
        )

    def __eq__(self, other: Iterable[Any]) -> bool:
        return tuple(self) == tuple(other)

    def __hash__(self) -> int:
        return hash(tuple(self))

    def __abs__(self) -> float:
        return math.hypot(self.x, self.y)

    def __bool__(self) -> bool:
        return bool(abs(self))

    def angle(self) -> float:
        return math.atan2(self.y, self.x)

    def __format__(self, spec: str = "") -> str:
        if spec.endswith("p"):
            spec = spec[:-1]
            coords = (abs(self), self.angle())
            outer = "<{}, {}>"
        else:
            coords = self
            outer = "({}, {})"
        components = (format(c, spec) for c in coords)
        return outer.format(*components)

    def __complex__(self) -> complex:
        return complex(self.x, self.y)

    @classmethod
    def frombytes(cls, octets: bytes | bytearray | memoryview) -> Self:
        typecode = chr(octets[0])
        memv = memoryview(octets[1:]).cast(typecode)
        return cls(*memv)

    @classmethod
    def fromcomplex(cls, datum: SupportsComplex) -> Self:
        c = complex(datum)
        return cls(c.real, c.imag)


def kind_kw(v: Vector2d) -> str:
    match v:
        case Vector2d(x=0, y=0):
            return "zero"
        case Vector2d(x=0):
            return "vertical"
        case Vector2d(y=0):
            return "horizontal"
        case Vector2d(x=x, y=y) if x == y:
            return "diagonal"
        case _:
            return "oblique"


def kind_po(v: Vector2d) -> str:
    match v:
        case Vector2d(0, 0):
            return "zero"
        case Vector2d(0):
            return "vertical"
        case Vector2d(_, 0):
            return "horizontal"
        case Vector2d(x, y) if x == y:
            return "diagonal"
        case _:
            return "oblique"


if __name__ == "__main__":
    import doctest

    doctest.testmod()
