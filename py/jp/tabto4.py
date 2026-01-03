#!/usr/bin/env python3
from __future__ import annotations

import sys

if len(sys.argv) != 3:
    print("usage: ./tabto4.py <src> <dst>", file=sys.stderr)
    sys.exit(1)

src: str = sys.argv[1]
dst: str = sys.argv[2]

with open(src, "r") as file:
    content = file.read()

content = content.replace("\t", " " * 4)

with open(dst, "w") as file:
    file.write(content)
