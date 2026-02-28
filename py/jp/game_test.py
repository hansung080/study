#!/usr/bin/env python3
from __future__ import annotations

# <<< How to Access Items in a Package >>>
# 1. import <module>
import game.sound.echo
game.sound.echo.echo_test()

# 2. from <package> import <module>
from game.sound import echo
echo.echo_test()

# 3. from <module> import <item>
from game.sound.echo import echo_test
echo_test()

# 4. import <package>
# On old Python versions
#   -> AttributeError: 'module' object has no attribute 'sound'
#   -> The `game` package can only access items defined in the `game/__init__.py` file.
# On new Python versions (testing on Python 3.12.2)
#   -> O.K.
import game
game.sound.echo.echo_test()

# 5. import <item>
#   -> ModuleNotFoundError: No module named 'game.sound.echo.echo_test'; 'game.sound.echo' is not a package
# import game.sound.echo.echo_test

# <<< How to Use the `__init__.py` File >>>
# 2. To import items in a package in advance.
import game
game.render_test()

# 4. To define the `__all__` variable.
from game.sound import *
echo.echo_test()
