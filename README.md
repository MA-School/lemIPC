made by Maxime Aubanel

REQUIREMENTS:
- Linux Environment
- CSFML ( sudo apt-get install libcsfml-dev )

1 - Launch ./lemipc with 2 parameters.

                  The first one is the pwd, you can use . or `pwd`.
                  The second one is the team of the first player.


2 - Launch ./Graphic with one parameters.

                  The first one is the pwd, you can use . or `pwd`.


3 - Add player to the game by using "./lemipc `pwd` X"

                  X = team number (1,2,3,4,5 ...)


4 - For more fun, use the script.sh


THE RULES


The goal is to fight players (spread over several teams) on a two dimensions game
board.

The last team remaining on the board is the winner.

To kill a player, a minimum of two players from the same team (and different from
the first) need to be in contact with the player to kill. It means on a square next
to the one where the player you want to kill stands on. (including diagonally)

When a player realizes he is surrounded by at least 2 players of the same opponent
team, he must leave the board game

A square cannot host more than one player simultaneously


TECHNICAL CONSTRAINTS

Each client is a process and there should be only one executable, which means that
the first player to start will create shared resources (shm, msgq, semaphores)

Similarly, when a player leaves the game, he must check if he is the last player
on the board. Indeed, the last process to quit is responsible for cleaning all IPCs
created by the first process.

The board must be stored in a shared memory segment (shm). Each player can see
the contents of the board as he wishes, but to change it, it must respect the shared
resource constraints and competitive access (semaphores).

A player can only communicate with other players by msgQ.

You must implement a team strategy of some kind.

On the board, a player can see if a square is empty or if it contains a player. In this
case, it’s the number of the team which is available. It is not possible to differentiate
two players of the same team.
