from __future__ import annotations

import re
import reprlib
from collections.abc import Iterator, Sequence
from typing import overload

RE_WORD: re.Pattern[str] = re.compile(r"\w+")

# <<< ABC Inheritance Principle >>>
# - Inheritance Recommended (Nominal Typing): ABCs that define the identity
#   e.g. Iterator, Sequence, MutableSequence, Mapping, MutableMapping
# - Inheritance Not Recommended (Structural Typing): ABCs that provide a capability
#   e.g. Iterable, Reversible, Sized, Container


# <<< How to Make an Iterable >>>
# 1. Sentence as Sequence
class Sentence1(Sequence[str]):
    def __init__(self, text: str) -> None:
        self._text = text
        self._words: list[str] = RE_WORD.findall(text)

    def __repr__(self) -> str:
        return f"{type(self).__name__}({reprlib.repr(self._text)})"

    def __len__(self) -> int:
        return len(self._words)

    @overload
    def __getitem__(self, key: int) -> str: ...
    @overload
    def __getitem__(self, key: slice) -> list[str]: ...

    # NOTE: When slicing, returning a `Self` rather than a `list[str]` is generally considered better API design.
    def __getitem__(self, key):
        return self._words[key]


# 2. Sentence as Iterable with Custom Iterator
class Sentence2:
    def __init__(self, text: str) -> None:
        self._text = text
        self._words: list[str] = RE_WORD.findall(text)

    def __repr__(self) -> str:
        return f"{type(self).__name__}({reprlib.repr(self._text)})"

    def __iter__(self) -> Iterator[str]:
        return SentenceIterator(self._words)


class SentenceIterator(Iterator[str]):
    def __init__(self, words: list[str]) -> None:
        self._words = words
        self._index = 0

    def __iter__(self) -> Iterator[str]:
        return self

    def __next__(self) -> str:
        if self._index >= len(self._words):
            raise StopIteration
        word = self._words[self._index]
        self._index += 1
        return word


# 3. Sentence as Iterable with Delegating Iterator
class Sentence3:
    def __init__(self, text: str) -> None:
        self._text = text
        self._words: list[str] = RE_WORD.findall(text)

    def __repr__(self) -> str:
        return f"{type(self).__name__}({reprlib.repr(self._text)})"

    def __iter__(self) -> Iterator[str]:
        return iter(self._words)


if __name__ == "__main__":
    text_ = '"The time has come," the Walrus said,'
    expected = ["The", "time", "has", "come", "the", "Walrus", "said"]

    s1 = Sentence1(text_)
    assert list(s1) == expected
    assert s1[0] == "The"
    assert s1[1:3] == ["time", "has"]

    s2 = Sentence2(text_)
    assert list(s2) == expected

    s3 = Sentence3(text_)
    assert list(s3) == expected
