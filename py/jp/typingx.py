from __future__ import annotations

from decimal import Decimal
from fractions import Fraction
from typing import Protocol

type NumberLike = (
    int
    | float
    | complex
    | Decimal
    | Fraction
)


# Modern-style Generic Protocols (PEP 695)
class SupportsAdd[T, R](Protocol):
    def __add__(self, other: T, /) -> R: ...


class SupportsRAdd[T, R](Protocol):
    def __radd__(self, other: T, /) -> R: ...


class SupportsSub[T, R](Protocol):
    def __sub__(self, other: T, /) -> R: ...


class SupportsRSub[T, R](Protocol):
    def __rsub__(self, other: T, /) -> R: ...


class SupportsMul[T, R](Protocol):
    def __mul__(self, other: T, /) -> R: ...


class SupportsRMul[T, R](Protocol):
    def __rmul__(self, other: T, /) -> R: ...


class SupportsTrueDiv[T, R](Protocol):
    def __truediv__(self, other: T, /) -> R: ...


class SupportsRTrueDiv[T, R](Protocol):
    def __rtruediv__(self, other: T, /) -> R: ...


class SupportsFloorDiv[T, R](Protocol):
    def __floordiv__(self, other: T, /) -> R: ...


class SupportsRFloorDiv[T, R](Protocol):
    def __rfloordiv__(self, other: T, /) -> R: ...


class SupportsMod[T, R](Protocol):
    def __mod__(self, other: T, /) -> R: ...


class SupportsRMod[T, R](Protocol):
    def __rmod__(self, other: T, /) -> R: ...


class SupportsDivMod[T, R](Protocol):
    def __divmod__(self, other: T, /) -> R: ...


class SupportsRDivMod[T, R](Protocol):
    def __rdivmod__(self, other: T, /) -> R: ...


class SupportsAddAndMul[T, R](Protocol):
    def __add__(self, other: T, /) -> R: ...
    def __mul__(self, other: T, /) -> R: ...
