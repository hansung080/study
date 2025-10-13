#!/usr/bin/env python3
import os
import sys

if len(sys.argv) not in (2, 3):
    print("usage: python3 sub_dir_search_walk.py <dir> [ext]", file=sys.stderr)
    sys.exit(1)


def search(top):
    try:
        for dirpath, _, filenames in os.walk(top):  # os.walk() returns (dirpath, dirnames, filenames)
            for filename in filenames:
                if len(sys.argv) == 3:
                    ext = os.path.splitext(filename)[-1]
                    if ext == f".{sys.argv[2]}":
                        print(os.path.join(dirpath, filename))
                else:
                    print(os.path.join(dirpath, filename))
    except PermissionError:
        pass


search(sys.argv[1])
