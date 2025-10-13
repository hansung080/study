#!/usr/bin/env python3
import os
import sys

if len(sys.argv) not in (2, 3):
    print("usage: python3 sub_dir_search.py <dir> [ext]", file=sys.stderr)
    sys.exit(1)


def search(dirname):
    try:
        filenames = os.listdir(dirname)
        for filename in filenames:
            full_filename = os.path.join(dirname, filename)
            if os.path.isdir(full_filename):
                search(full_filename)
            else:
                if len(sys.argv) == 3:
                    ext = os.path.splitext(full_filename)[-1]
                    if ext == f".{sys.argv[2]}":
                        print(full_filename)
                else:
                    print(full_filename)
    except PermissionError:
        pass


search(sys.argv[1])
