# Project Mansuba


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


## Sources

La page de spécification du projet :

<https://www.labri.fr/perso/renault/working/teaching/projets/2022-23-S5-Mansuba.php>

La page du projet sur la forge :

https://thor.enseirb-matmeca.fr/ruby/projects/projetss5

La page des projets en général :

<https://www.labri.fr/perso/renault/working/teaching/projets/projets.php>
