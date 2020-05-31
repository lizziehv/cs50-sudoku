# CS50 Final Project Extra Credit

## Acknowledgements (Github username)
* Lizzie Hernandez (lizziehv)
* Maria Paula Mora (mpmora00)
* Ethan Trepka (et22)
* Kshitij Jain (jkshitij77)


## Sudoku Puzzle Creator/Solver Overview
### Setup

#### Prerequisites
- [Homebrew]() - package manager for macOS

#### Installationhttps://brew.sh/
The program is dependent on two libraries, which are `SDL2` and `SDL2_ttf` and can be compiled as follows.


##### For MacOS
Run the following commands from your terminal:

``` bash
$ /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
# Follow the instructions that say:
    # Configure Homebrew in your /net/ifs-users/USERNAME/.bash_profile by running
    # Add Homebrew to your PATH
    # We recommend that you install GCC by running
$ brew install sdl2
$ brew install sdl2_ttf
```

##### For other servers
For installation on Windows and Linux servers visit [this webpage](http://headerphile.blogspot.com/2014/04/setting-up-sdl2.html) to install `SDL2` and [this webpage](http://headerphile.blogspot.com/2014/07/sdl2-part-10-text-rendering.html) to install `SDL2_TTF`.

### Compiling and running
To compile run `make` from the project directory.<br />
To run the program, run `./game` from the command line.<br />
To clean up run `make clean` from the project directory.<br />

Make will compile using a C compiler and the following flags:
```bash
gcc -Wall -pedantic -std=c11 -ggdb -lSDL2 -lSDL2_ttf game.c -o game
```