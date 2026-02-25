from __future__ import annotations

import re
import reprlib
from typing import overload

RE_WORD: re.Pattern[str] = re.compile(r"\w+")


class Sentence1:
    def __init__(self, text: str) -> None:
        self._text = text
        self._words: list[str] = RE_WORD.findall(text)

    def __repr__(self) -> str:
        return f"Sentence1({reprlib.repr(self._text)})"

    def __len__(self) -> int:
        return len(self._words)

    @overload
    def __getitem__(self, key: int) -> str: ...
    @overload
    def __getitem__(self, key: slice) -> list[str]: ...

    # NOTE: When slicing, returning a `Self` rather than a `list[str]` is generally considered better API design.
    def __getitem__(self, key):
        return self._words[key]


if __name__ == "__main__":
    sentences = [
        Sentence1('"The time has come," the Walrus said,'),
    ]

    for sentence in sentences:
        words: list[str] = []
        for word in sentence:
            words.append(word)
        assert words == ["The", "time", "has", "come", "the", "Walrus", "said"]
        assert list(sentence) == words

        assert sentence[0] == "The"
        assert sentence[5] == "Walrus"
        assert sentence[-1] == "said"
        assert sentence[2:5] == ["has", "come", "the"]
