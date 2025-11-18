from __future__ import annotations

# <<< How to use the '__init__.py' file >>>
# 1. To define package-level items such as variables, functions, etc.
VERSION = 3.5


def print_version_info() -> None:
    print(f"The version of this game is {VERSION}.")


# 2. To import items in a package in advance.
from .graphic.render import render_test

# 3. To write the package initialization code.
print("Initializing game...")

# 4. To define the '__all__' variable.
#   -> See the 'game/sound/__init__.py' file.
