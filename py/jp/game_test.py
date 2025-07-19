# <<< How to access items in a package >>>
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
#   -> The 'game' package can only access items defined in the 'game/__init__.py' file.
# On new Python versions (testing on Python 3.12.2)
#   -> O.K.
import game
game.sound.echo.echo_test()

# 5. import <item>
#   -> ModuleNotFoundError: No module named 'game.sound.echo.echo_test'; 'game.sound.echo' is not a package
# import game.sound.echo.echo_test


# <<< How to use the '__init__.py' file >>>
# 2. To import items in a package in advance.
import game
game.render_test()

# 4. To define the '__all__' variable.
from game.sound import *
echo.echo_test()
