# MINES
Minesweeper game for 8088 computers with CGA graphics

## Compatibility

MINES works with original Intel 8088 hardware and requires a CGA compatible graphics card

## How to build

This project is built using Borland Turbo C 2.01

To build the regular build:
```
C:\SOURCE\MINES\> make all
```

To build the debug build:
```
C:\SOURCE\MINES\> make -DDEBUG=1 all
```

## Usage
```
MINES.EXE [MODE] [WIDTH] [HEIGHT] [MINES]

Modes: EASY, MEDIUM, HARD, CUSTOM
```

Custom mode allows for custom board size and number of mines, otherwise the arguments are ignored
