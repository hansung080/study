#!/usr/bin/env python3
from __future__ import annotations

import sys
from collections.abc import Iterator


def tree(cls: type, level: int = 0, *, max_level: int | None = None) -> Iterator[tuple[str, int]]:
    if max_level is not None and level > max_level:
        return
    yield cls.__name__, level
    for sub_cls in cls.__subclasses__():
        yield from tree(sub_cls, level + 1, max_level=max_level)


def display(cls: type, *, max_level: int | None = None) -> None:
    for cls_name, level in tree(cls, max_level=max_level):
        indent = " " * 4 * level
        print(f"{indent}{cls_name}")


if __name__ == "__main__":
    try:
        max_level_ = int(sys.argv[1])
    except (IndexError, ValueError):
        max_level_ = None
    display(BaseException, max_level=max_level_)
