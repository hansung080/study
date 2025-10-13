#!/usr/bin/env python3
import sys

if len(sys.argv) != 3:
    print("usage: python3 tabto4.py <src> <dst>", file=sys.stderr)
    sys.exit(1)

src = sys.argv[1]
dst = sys.argv[2]

f = open(src)
content = f.read()
f.close()

content = content.replace("\t", " " * 4)

f = open(dst, "w")
f.write(content)
f.close()
