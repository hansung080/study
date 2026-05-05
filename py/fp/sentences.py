from __future__ import annotations

import re
import reprlib
from collections.abc import Iterator, Sequence
from typing import overload

RE_WORD: re.Pattern[str] = re.compile(r"\w+")


class BaseSentence:
    def __init__(self, text: str) -> None:
        self._text = text

    def __repr__(self) -> str:
        return f"{type(self).__name__}({reprlib.repr(self._text)})"


class EagerSentence(BaseSentence):
    def __init__(self, text: str) -> None:
        super().__init__(text)
        self._words: list[str] = RE_WORD.findall(text)


class LazySentence(BaseSentence):
    pass


# --- ABC Inheritance Principle ---
# - Inheritance Recommended (Nominal Typing): ABCs that define the identity
#   e.g. Iterator, Sequence, MutableSequence, Mapping, MutableMapping
# - Inheritance Not Recommended (Structural Typing): ABCs that provide a capability
#   e.g. Iterable, Reversible, Sized, Container

# --- How to Make an Iterable ---
# 1. EagerSentence as Sequence
class Sentence1(EagerSentence, Sequence[str]):
    def __len__(self) -> int:
        return len(self._words)

    @overload
    def __getitem__(self, key: int) -> str: ...
    @overload
    def __getitem__(self, key: slice) -> list[str]: ...

    # NOTE: When slicing, returning a `Self` rather than a `list[str]` is generally considered better API design.
    def __getitem__(self, key):
        return self._words[key]


# 2. EagerSentence as Iterable with Custom Iterator
class Sentence2(EagerSentence):
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


# 3. EagerSentence as Iterable with Delegating Iterator
class Sentence3(EagerSentence):
    def __iter__(self) -> Iterator[str]:
        return iter(self._words)


# 4. EagerSentence as Iterable with Generator
class Sentence4(EagerSentence):
    def __iter__(self) -> Iterator[str]:
        for word in self._words:
            yield word


# 5. EagerSentence as Iterable with Delegating Generator
class Sentence5(EagerSentence):
    def __iter__(self) -> Iterator[str]:
        yield from self._words


# 6. LazySentence as Iterable with Generator
class Sentence6(LazySentence):
    def __iter__(self) -> Iterator[str]:
        for match in RE_WORD.finditer(self._text):
            yield match.group()


# 7. LazySentence as Iterable with Generator Expression
class Sentence7(LazySentence):
    def __iter__(self) -> Iterator[str]:
        return (match.group() for match in RE_WORD.finditer(self._text))


if __name__ == "__main__":
    text_ = '"The time has come," the Walrus said,'
    expected = ["The", "time", "has", "come", "the", "Walrus", "said"]

    s = Sentence1(text_)
    assert repr(s) == 'Sentence1(\'"The time ha... Walrus said,\')'
    assert len(s) == 7
    assert s[0] == "The"
    assert s[1:3] == ["time", "has"]
    assert list(s) == expected

    s = Sentence2(text_)
    assert list(s) == expected

    s = Sentence3(text_)
    assert list(s) == expected

    s = Sentence4(text_)
    assert list(s) == expected

    s = Sentence5(text_)
    assert list(s) == expected

    s = Sentence6(text_)
    assert list(s) == expected

    s = Sentence7(text_)
    assert list(s) == expected
