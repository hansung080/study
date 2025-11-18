#!/usr/bin/env python3
from __future__ import annotations

import os
import sys

if len(sys.argv) < 2:
    print("usage: python3 memo.py <mode> [memos]...", file=sys.stderr)
    print("  mode: -a: append", file=sys.stderr)
    print("        -r: read", file=sys.stderr)
    print("        -d: delete", file=sys.stderr)
    sys.exit(1)

FILE: str = "memo.txt"
mode: str = sys.argv[1]

if mode == "-a":
    if len(sys.argv) < 3:
        print("usage: python3 memo.py -a [memos]...", file=sys.stderr)
        sys.exit(1)

    with open(FILE, "a", encoding="utf-8") as file:
        for memo in sys.argv[2:]:
            file.write(f"{memo}\n")
elif mode == "-r":
    try:
        with open(FILE, "r", encoding="utf-8") as file:
            content = file.read()
        print(content, end="")
    except FileNotFoundError:
        print(f"error: file not found: '{FILE}'", file=sys.stderr)
        sys.exit(1)
    except PermissionError:
        print(f"error: permission denied: '{FILE}'", file=sys.stderr)
        sys.exit(1)
    except OSError as e:
        print(f"error: os: {e}", file=sys.stderr)
        sys.exit(1)
elif mode == "-d":
    if os.path.exists(FILE):
        os.remove(FILE)
else:
    print(f"error: invalid mode: {mode}", file=sys.stderr)
    sys.exit(1)
