#!/usr/bin/env python3
from __future__ import annotations

import re
import sys
from collections import defaultdict
from collections.abc import Sequence
from pathlib import Path
from typing import Iterator, NamedTuple

WORD_RE: re.Pattern[str] = re.compile(r"\w+")


def print_usage() -> None:
    filename = Path(__file__).name
    print("Usage:", file=sys.stderr)
    print(f"  ./{filename} <file> [<mode>]", file=sys.stderr)
    print(file=sys.stderr)
    print("Modes:", file=sys.stderr)
    print("  1  Key hashing occurs 2 or 3 times per iteration (WORSE)", file=sys.stderr)
    print("  2  Key hashing occurs 1 or 2 times per iteration (BAD)", file=sys.stderr)
    print("  3  Key hashing occurs 1 or 2 times per iteration (BAD)", file=sys.stderr)
    print("  4  Key hashing occurs 1 time per iteration (GOOD)", file=sys.stderr)
    print("  5  Key hashing occurs 1 time per iteration (BETTER, default)", file=sys.stderr)


class Args(NamedTuple):
    filename: str
    mode: str


def parse_args(args: Sequence[str] | None = None) -> Args:
    if args is None:
        args = sys.argv[1:]

    if len(args) not in (1, 2):
        raise ValueError(f"invalid number of arguments: expected 1 or 2, got {len(args)}")

    filename = args[0]
    mode = args[1] if len(args) == 2 else "5"
    return Args(filename, mode)


def parse_args_or_exit(args: Sequence[str] | None = None) -> Args:
    try:
        return parse_args(args)
    except ValueError as e:
        print(f"Error: {e}\n", file=sys.stderr)
        print_usage()
        sys.exit(1)


def iter_word_locations(filename: str) -> Iterator[tuple[str, tuple[int, int]]]:
    with open(filename, "r", encoding="utf-8") as file:
        for line_no, line in enumerate(file, 1):
            for match in WORD_RE.finditer(line):
                word = match.group()
                column_no = match.start() + 1
                location = (line_no, column_no)
                yield word, location


def print_index(index: dict[str, list[tuple[int, int]]] | defaultdict[str, list[tuple[int, int]]]) -> None:
    # for word in sorted(index, key=str.upper):  # `str.upper` causes the warning by the type checker.
    for word in sorted(index, key=lambda k: k.upper()):
        print(f"{word} => {index[word]}")


def main() -> None:
    filename, mode = parse_args_or_exit()

    # WORSE: Key hashing occurs 2 or 3 times per iteration.
    if mode == "1":
        index: dict[str, list[tuple[int, int]]] = {}
        for word, location in iter_word_locations(filename):
            if word not in index:
                index[word] = []
            index[word].append(location)
    # BAD: Key hashing occurs 1 or 2 times per iteration.
    elif mode == "2":
        index: dict[str, list[tuple[int, int]]] = {}
        for word, location in iter_word_locations(filename):
            occurrences = index.get(word)
            if occurrences is None:
                index[word] = [location]
            else:
                occurrences.append(location)
    # BAD: Key hashing occurs 1 or 2 times per iteration.
    elif mode == "3":
        index: dict[str, list[tuple[int, int]]] = {}
        for word, location in iter_word_locations(filename):
            occurrences = index.get(word, [])
            occurrences.append(location)
            if len(occurrences) == 1:
                index[word] = occurrences
    # GOOD: Key hashing occurs 1 time per iteration.
    elif mode == "4":
        index: dict[str, list[tuple[int, int]]] = {}
        for word, location in iter_word_locations(filename):
            index.setdefault(word, []).append(location)
    # BETTER: Key hashing occurs 1 time per iteration.
    elif mode == "5":
        index: defaultdict[str, list[tuple[int, int]]] = defaultdict(list)
        for word, location in iter_word_locations(filename):
            index[word].append(location)
    else:
        print(f"Error: invalid mode: {mode!r}\n", file=sys.stderr)
        print_usage()
        sys.exit(1)

    print_index(index)


if __name__ == "__main__":
    main()
