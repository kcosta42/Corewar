Corewar
======

About
-----

>Core War is a 1984 programming game created by D. G. Jones and A. K. Dewdney in which two or more battle programs (called "warriors") compete for control of a virtual computer.
These battle programs are written in an abstract assembly language called Redcode.

42 Version
----------

Here's how it looks like:

![Corewar](https://raw.githubusercontent.com/kcosta42/Corewar/master/images/Corewar.gif)
![Life](https://raw.githubusercontent.com/kcosta42/Corewar/master/images/Life.gif)

We don't use the same set of assembly instructions as the original Corewar and we have some modulo limitations for the read and write ranges.

##### How to use it ?

* First you'll need to write a .s file with a set of assembly instructions
    * You can find this set in either [corewar.pdf](https://raw.githubusercontent.com/kcosta42/Corewar/master/corewar.pdf) or in [corewar_en.pdf](https://raw.githubusercontent.com/kcosta42/Corewar/master/corewar_en.pdf)
    * Or you can just use one of the many warriors in the resources/champions directory
* Then you'll have to compile it using the `asm` binary
* Then just execute the `corewar` binary with your warrior(s) as arguments

>This was the final project of the Algorithm branch.

The Team
--------

This project was made by these awesome people:
* [Benjamin](https://github.com/bduron)
* [Cedric](https://github.com/cpoulet)
* [Pierre](https://github.com/wolrajhti)
* [Myself](https://github.com/kcosta42)

Installation
------------

Just run `make -C Corewar fclean && make -C Corewar`... enjoy!

Work on OS X El Capitan and macOS Sierra, the `ncurse` library is used for the viewer.

Usage
-----

### Binaries

#### corewar
`./corewar [-d N -s N -v N | -b --stealth | -n --stealth] [-a] <champion1.cor> <...>`
* -a	: Prints output from "aff" (Default is to hide it)
* -d N	: Dumps memory after N cycles then exits
* -s N	: Runs N cycles, dumps memory, pauses, then repeat
* -v N	: Verbosity levels, can be added together to enable several
* - 0	: Show only essentials
* - 1	: Show lives
* - 2	: Show cycles
* - 4	: Show operations (Params are NOT litteral ...)
* - 8	: Show deaths
* - 16	: Show PC movements (Except for jumps)
* -i	: Ncurses output mode

#### asm
`./asm [-d champion.cor] | champion.s`
* -d : Reverse compiler
    * Generate an assembly file from a corewar file (.cor)
    * (Comments are lost as well as label)
    * (Default is to generate a corewar file from an assembly file)

### Scripts

#### check_asm
`./check_asm.sh [-del] [-exec] [-diff] [-deasm]`
* -del  : Delete created files
* -exec : Execute the script
* -diff : Execute `diff` on all compiled files
* -deasm : Execute the reverse compiler option then execute `diff`

#### script_v
`./script_v [number of champ 1-4] <champ name> <...>`
* champ name are given without the .cor extension
* champ have to be placed in the folder resources/champions

Licence
-------

##### Do what you want.
