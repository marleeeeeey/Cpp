# Arkanoid

## Idea

The idea is to create a copy of the original arkanoid game from ZX Spectrum:

![image-20200108163600764](ReadMe/image-20200108163600764.png)

Latest version available [here](https://github.com/marleeeeeey/PublicStore/tree/master/releases). Fill free to contribute to this project. If you have any questions let me know.

## Original levels

![image-20200108163721990](ReadMe/image-20200108163721990.png)

Not all of the levels is implemented now. The levels order is random.

## Important

- Start the application from the **root working directory** but not from the `bin` directory. It is needed to find the configuration file with relative paths in the code. Use shortcut from the start menu - it works well.
- Project builds for Windows(VS 2017) via CMAKE. See `build_installer.cmd` script as example. Source code use hard coded fonts name. It should be fixed to prevent runtime errors on other OS. I did not build this project for other OS. 

## Level editor

To edit levels change file `config/levels.txt`. Original version can be used as example. There are list of matrix split by empty lines. Every line in one matrix should have the same symbol length. See list of available symbols to construct level (DO NOT USE OTHER SYMBOLS - it leads to error):

- `.` - empty brick (DO NOT USE ` ` "space" symbol to create empty spaces)
- `0` - immortal brick
- `1..9` - usual brick with lives
- `R` - RenewableBalls
- `M` - MultiBalls
- `A` - AddPlateLive (coming soon)
- `L` - LongPlate
- `G` - MagnetPaddle
- `D` - DisableBonuses
- `W` - AroundWall (coming soon)
- `N` - NextLevel (coming soon)
- `S` - DecreaseBallSpeed
- `F` - FireBall

In case of errors in level editor you will see special level in runtime:

![image-20200108162548083](ReadMe/image-20200108162548083.png)

## Prerequisites

1. cmake
2. gtest
3. gmock
4. sfml
5. nsis (windows)

## UML

Diagrams may be not relevant with current source code.

![image-20200109142342702](ReadMe/image-20200109142342702.png)

![image-20200109143328391](ReadMe/image-20200109143328391.png)