from __future__ import annotations

from typing import Protocol, TypeVar

_T_co = TypeVar("_T_co", covariant=True)
_T_contra = TypeVar("_T_contra", contravariant=True)


# --- Legacy-style Generic Protocols ---
class SupportsAdd(Protocol[_T_contra, _T_co]):
    def __add__(self, other: _T_contra, /) -> _T_co: ...


class SupportsRAdd(Protocol[_T_contra, _T_co]):
    def __radd__(self, other: _T_contra, /) -> _T_co: ...


class SupportsSub(Protocol[_T_contra, _T_co]):
    def __sub__(self, other: _T_contra, /) -> _T_co: ...


class SupportsRSub(Protocol[_T_contra, _T_co]):
    def __rsub__(self, other: _T_contra, /) -> _T_co: ...


class SupportsMul(Protocol[_T_contra, _T_co]):
    def __mul__(self, other: _T_contra, /) -> _T_co: ...


class SupportsRMul(Protocol[_T_contra, _T_co]):
    def __rmul__(self, other: _T_contra, /) -> _T_co: ...


class SupportsTrueDiv(Protocol[_T_contra, _T_co]):
    def __truediv__(self, other: _T_contra, /) -> _T_co: ...


class SupportsRTrueDiv(Protocol[_T_contra, _T_co]):
    def __rtruediv__(self, other: _T_contra, /) -> _T_co: ...


class SupportsFloorDiv(Protocol[_T_contra, _T_co]):
    def __floordiv__(self, other: _T_contra, /) -> _T_co: ...


class SupportsRFloorDiv(Protocol[_T_contra, _T_co]):
    def __rfloordiv__(self, other: _T_contra, /) -> _T_co: ...


class SupportsMod(Protocol[_T_contra, _T_co]):
    def __mod__(self, other: _T_contra, /) -> _T_co: ...


class SupportsRMod(Protocol[_T_contra, _T_co]):
    def __rmod__(self, other: _T_contra, /) -> _T_co: ...


class SupportsDivMod(Protocol[_T_contra, _T_co]):
    def __divmod__(self, other: _T_contra, /) -> _T_co: ...


class SupportsRDivMod(Protocol[_T_contra, _T_co]):
    def __rdivmod__(self, other: _T_contra, /) -> _T_co: ...


class SupportsAddAndMul(Protocol[_T_contra, _T_co]):
    def __add__(self, other: _T_contra, /) -> _T_co: ...
    def __mul__(self, other: _T_contra, /) -> _T_co: ...
