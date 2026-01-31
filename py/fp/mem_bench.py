#!/usr/bin/env python3
# Reference: https://github.com/fluentpython/example-code-2e/blob/master/11-pythonic-obj/mem_test.py
from __future__ import annotations

import importlib
import resource
import sys
import time
from collections.abc import Sequence
from dataclasses import dataclass
from pathlib import Path
from types import ModuleType
from typing import Any, Callable, Self


def print_usage() -> None:
    filename = Path(__file__).name
    print(f"usage: ./{filename} <module> <expr> [<count>=1]", file=sys.stderr)
    print(f"  e.g. ./{filename} vector2d 'Vector2d(3, 4)' 1000000", file=sys.stderr)


@dataclass(frozen=True)
class Args:
    module: ModuleType
    expr: str
    count: int

    @classmethod
    def from_argv(cls, argv: Sequence[str]) -> Self:
        args = argv[1:]
        if len(args) not in (2, 3):
            raise ValueError(f"invalid number of arguments: expected 2 or 3, got {len(args)}")

        module_name = args[0].replace(".py", "")
        module = importlib.import_module(module_name)
        expr = args[1]
        count = int(args[2]) if len(args) == 3 else 1
        return cls(module, expr, count)

    @classmethod
    def from_argv_or_exit(cls, argv: Sequence[str]) -> Self:
        try:
            return cls.from_argv(argv)
        except (ValueError, ModuleNotFoundError) as e:
            print(f"error: {e}", file=sys.stderr)
            print_usage()
            sys.exit(1)


def benchmark_expression(module: ModuleType, expr: str, count: int) -> list[Any]:
    print(f"Benchmarking '{module.__name__}.{expr}' for {count:,} iterations")
    namespace: dict[str, Any] = vars(module).copy()
    return [eval(expr, namespace) for _ in range(count)]


def get_max_rss_bytes() -> int:
    max_rss = resource.getrusage(resource.RUSAGE_SELF).ru_maxrss
    if sys.platform == "darwin":
        return max_rss
    return max_rss * 1024


def measure_memory(func: Callable[[], Any]) -> None:
    start = get_max_rss_bytes()
    _ = func()
    delta = get_max_rss_bytes() - start
    print(f"  Memory increase (peak RSS): {delta / (1024 ** 2):,.0f} MiB ({delta:,} bytes)")


def measure_time(func: Callable[[], Any]) -> None:
    start = time.perf_counter()
    _ = func()
    elapsed = time.perf_counter() - start
    print(f"  Elapsed time              : {elapsed:0.8f}s")


def main() -> None:
    args = Args.from_argv_or_exit(sys.argv)
    measure_time(lambda: measure_memory(lambda: benchmark_expression(args.module, args.expr, args.count)))


if __name__ == "__main__":
    main()
