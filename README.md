# Project Mansuba

Board game framework for the "Projet d'algorithmique et de programmation n°1" at ENSEIRB-MATMECA made by Samuel Khalifa and Louis Peyrondet.

## Compile the .tex
### Prerequisites
* xcolor
* subfig
* framed
* tikz
  * With the tikz library `graphs`
* graphicx
* minted
  * You will also need to install the pygmentize library (`apt install python3-pygments`)
* hyperref
* float

### Command to compile
    cd rapport && <latex-compiler> -shell-escape rapport/rapport.tex


## Build
For the default executable (4*5 grid):

    make

For a specific width 'w' and height 'h' executable :

    make WIDTH=w HEIGHT=h

To generate the Doxygen documentation :

    make doc


## Execution

For the default configuration :

    ./project


## Execution Options

Here are the different options 

| Define | Description | Default |
| ----------- | ----------- | ----------- |
| -s | The random seed used for the game. eg: "-s 125" | random |
| -t | The type of victory used to win the game. Either 's' for simple or 'c' for complex victory. eg : "-t c" | 's' |
| -m | The maximum amount of turn before ex-aequo. eg: "-m 50" | 2*WORLD_SIZE |
| -v | The verbose level. Values ranges from : 0 (display only the seed and who won), 1 (standard display witht the game grid), 2 (Debug mode, gives every move tree and selection done) eg: "-v 2" | 1 |
| -c | The preset configuration to use. Preset available : "dame-chinoises" eg: "-c dame-chinoises"| default_config |
| -p | The number of real player. 0 equivalent to bot against bot, 2 is 1 player against another eg: "-p 1" | 0 |
