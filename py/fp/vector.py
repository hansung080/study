"""
Multi-Dimensional Vector Class

Creation Examples:

>>> Vector([3.1, 4.2])
Vector([3.1, 4.2])
>>> Vector((3, 4, 5))
Vector([3.0, 4.0, 5.0])
>>> Vector(range(10))
Vector([0.0, 1.0, 2.0, 3.0, 4.0, ...])


2D Vector Examples:

>>> v = Vector([3, 4])
>>> x, y = v
>>> x, y
(3.0, 4.0)
>>> v
Vector([3.0, 4.0])
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
>>> bool(v), bool(Vector([0, 0]))
(True, False)


``frombytes`` Method Examples:

>>> v_clone = Vector.frombytes(bytes(v))
>>> v_clone
Vector([3.0, 4.0])
>>> v == v_clone
True


3D Vector Examples:

>>> v = Vector([3, 4, 5])
>>> x, y, z = v
>>> x, y, z
(3.0, 4.0, 5.0)
>>> v
Vector([3.0, 4.0, 5.0])
>>> v_clone = eval(repr(v))
>>> v == v_clone
True
>>> print(v)
(3.0, 4.0, 5.0)
>>> abs(v)  # doctest: +ELLIPSIS
7.071067811...
>>> bool(v), bool(Vector([0, 0, 0]))
(True, False)


ND Vector Examples:

>>> v = Vector(range(7))
>>> v
Vector([0.0, 1.0, 2.0, 3.0, 4.0, ...])
>>> abs(v)  # doctest: +ELLIPSIS
9.53939201...


``frombytes`` Method Examples:

>>> v = Vector([3, 4, 5])
>>> v_clone = Vector.frombytes(bytes(v))
>>> v_clone
Vector([3.0, 4.0, 5.0])
>>> v == v_clone
True


Sequence Behavior Examples:

>>> v = Vector([3, 4, 5])
>>> len(v)
3
>>> v[0], v[len(v) - 1], v[-1]
(3.0, 5.0, 5.0)


Slicing Examples:

>>> v = Vector(range(7))
>>> v[-1]
6.0
>>> v[1:4]
Vector([1.0, 2.0, 3.0])
>>> v[-1:]
Vector([6.0])
>>> v[1, 2]
Traceback (most recent call last):
  ...
TypeError: 'tuple' object cannot be interpreted as an integer
>>> v[1.0]
Traceback (most recent call last):
  ...
TypeError: 'float' object cannot be interpreted as an integer


Dynamic Attributes Get Examples:

>>> v = Vector(range(10))
>>> v.x
0.0
>>> v.y, v.z, v.w
(1.0, 2.0, 3.0)


Dynamic Attributes Get Failure Examples:

>>> v.k
Traceback (most recent call last):
  ...
AttributeError: 'Vector' object has no attribute 'k'
>>> v = Vector(range(3))
>>> v.w
Traceback (most recent call last):
  ...
AttributeError: 'Vector' object has no attribute 'w'
>>> v.spam
Traceback (most recent call last):
  ...
AttributeError: 'Vector' object has no attribute 'spam'


Dynamic Attributes Set Examples:

>>> v = Vector(range(10))
>>> v.X = 100
>>> v.K = 101
>>> v.spam = 102
>>> v.X
100
>>> v.K
101
>>> v.spam
102

Dynamic Attributes Set Failure Examples:
>>> v.x = 200
Traceback (most recent call last):
  ...
AttributeError: readonly attribute 'x' in 'Vector'
>>> v.k = 201
Traceback (most recent call last):
  ...
AttributeError: can't set attribute 'a' to 'z' in 'Vector'


Integer Components Hash Examples:

>>> v1 = Vector([3, 4])
>>> v2 = Vector([3, 4, 5])
>>> v3 = Vector(range(6))
>>> hash(v1), hash(v2), hash(v3)
(7, 2, 1)


Non-integer Components Hash Examples:
In CPython, the hash values of most non-integer objects differ between the 32-bit and 64-bit versions.

>>> import sys
>>> v = Vector([3.1, 4.2])
>>> hash(v) == (384307168202284039 if sys.maxsize > 2 ** 32 else 357915986)
True


``format`` Function with 2D Cartesian Coordinates Examples:

>>> v = Vector([3, 4])
>>> format(v)
'(3.0, 4.0)'
>>> format(v, ".2f")
'(3.00, 4.00)'
>>> format(v, ".3e")
'(3.000e+00, 4.000e+00)'


``format`` Function with 3D, 7D Cartesian Coordinates Examples:

>>> format(Vector([3, 4, 5]))
'(3.0, 4.0, 5.0)'
>>> format(Vector(range(7)))
'(0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0)'


``format`` Function with 2D, 3D, 4D Spherical Coordinates Examples:

>>> format(Vector([1, 1]), "h")  # doctest: +ELLIPSIS
'<1.414213..., 0.785398...>'
>>> format(Vector([1, 1]), ".3eh")
'<1.414e+00, 7.854e-01>'
>>> format(Vector([1, 1]), "0.5fh")
'<1.41421, 0.78540>'
>>> format(Vector([1, 1, 1]), "h")  # doctest: +ELLIPSIS
'<1.73205..., 0.95531..., 0.78539...>'
>>> format(Vector([2, 2, 2]), ".3eh")
'<3.464e+00, 9.553e-01, 7.854e-01>'
>>> format(Vector([0, 0, 0]), "0.5fh")
'<0.00000, 0.00000, 0.00000>'
>>> format(Vector([-1, -1, -1, -1]), "h")  # doctest: +ELLIPSIS
'<2.0, 2.09439..., 2.18627..., 3.92699...>'
>>> format(Vector([2, 2, 2, 2]), ".3eh")
'<4.000e+00, 1.047e+00, 9.553e-01, 7.854e-01>'
>>> format(Vector([0, 1, 0, 0]), "0.5fh")
'<1.00000, 1.57080, 0.00000, 0.00000>'

"""

from __future__ import annotations

import math
import operator
import reprlib
from array import array
from collections.abc import Iterable, Iterator, Sized
from functools import reduce
from itertools import chain
from typing import Any, Self, overload


class Vector:
    typecode = "d"

    _components: array  # type annotation of instance attribute `_components` (not required)

    # Passing `list[int]` to `Iterable[float]` is OK,
    # because `Iterable` is covariant and `int` is a subtype of `float` (note that `list` is invariant).
    def __init__(self, components: Iterable[float]) -> None:
        self._components = array(self.typecode, components)

    def __iter__(self) -> Iterator[float]:
        return iter(self._components)

    def __repr__(self) -> str:
        components = reprlib.repr(self._components)
        components = components[components.find("["):-1]
        return f"Vector({components})"

    def __str__(self) -> str:
        return str(tuple(self))

    def __bytes__(self) -> bytes:
        return (
            bytes([ord(self.typecode)]) +
            bytes(self._components)
        )

    def __eq__(self, other: Iterable[Any] & Sized) -> bool:
        return (
            len(self) == len(other) and
            all(s == o for s, o in zip(self, other))
        )

    def __hash__(self) -> int:
        hashes = (hash(c) for c in self)
        return reduce(operator.xor, hashes, 0)

    def __abs__(self) -> float:
        return math.hypot(*self)

    def __bool__(self) -> bool:
        return bool(abs(self))

    def __len__(self) -> int:
        return len(self._components)

    @overload
    def __getitem__(self, key: int) -> float: ...
    @overload
    def __getitem__(self, key: slice) -> Self: ...

    def __getitem__(self, key):
        if isinstance(key, slice):
            cls = type(self)
            return cls(self._components[key])
        index = operator.index(key)
        return self._components[index]

    __match_args__ = ("x", "y", "z", "w")

    def __getattr__(self, name: str) -> float:
        cls = type(self)
        try:
            index = cls.__match_args__.index(name)
        except ValueError:
            index = -1
        if index < 0 or index >= len(self._components):
            raise AttributeError(f"{cls.__name__!r} object has no attribute {name!r}")
        return self._components[index]

    def __setattr__(self, name: str, value: Any) -> None:
        cls = type(self)
        if len(name) == 1:
            if name in cls.__match_args__:
                error = "readonly attribute {attr_name!r} in {class_name!r}"
            elif name.islower():
                error = "can't set attribute 'a' to 'z' in {class_name!r}"
            else:
                error = ""
            if error:
                raise AttributeError(error.format(class_name=cls.__name__, attr_name=name))
        super().__setattr__(name, value)

    def angle(self, n: int) -> float:
        r = math.hypot(*self[n:])
        a = math.atan2(r, self[n - 1])
        if (n == len(self) - 1) and (self[-1] < 0):
            return math.pi * 2 - a
        else:
            return a

    def angles(self) -> Iterator[float]:
        return (self.angle(n) for n in range(1, len(self)))

    def __format__(self, spec: str = "") -> str:
        if spec.endswith("h"):
            spec = spec[:-1]
            coords = chain([abs(self)], self.angles())
            outer = "<{}>"
        else:
            coords = self
            outer = "({})"
        components = (format(c, spec) for c in coords)
        return outer.format(", ".join(components))

    @classmethod
    def frombytes(cls, octets: bytes | bytearray | memoryview) -> Self:
        typecode = chr(octets[0])
        memv = memoryview(octets[1:]).cast(typecode)
        return cls(memv)


if __name__ == "__main__":
    import doctest

    doctest.testmod()
