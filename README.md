**ECE243 Project Report**  
Rudra Dey and Sean Nishanthan

**Project Description:**

Our ECE243 project, *Turf War* is a 2-player turn-based game implemented on the Nios-V Processor inspired by the popular online game *Territory War*. In our game, the red team and blue team have a face off, and each player controls a team of three characters. The game takes place in a beach-inspired map consisting of a wide battlefield (via three buffers for the VGA display). The PS/2 keyboard is used for user input to control player movement and grenade attacks. Players take turns controlling their characters with the goal of winning the game by eliminating all characters of the opposing team. This can be done by throwing grenades at characters to deal damage or by knocking them off the battlefield. Once a team is eliminated, the game result is displayed along with a sound effect using the speakers, with the option to restart if the users choose to do so.

**How To Operate the Project:**

First, add all the .c files to your Monitor Program project, download the system, and compile and load the project (project does not work in CPUlator). There will be a start game screen where the users can press ‘Enter’ on the PS/2 keyboard when they are ready to begin the game. 

The red team will start their turn with the option of clicking ‘1’ to move or ‘2’ to stay where their character is and end their turn. If they choose to move their character, the movement controls are displayed at the bottom of the screen and they can move and jump using the arrow keys. Also, there is a maximum displacement for this stage of the turn (indicated with a green bar in the bottom right corner). 

After that, the player can choose whether they want to throw a grenade by clicking ‘1’ or stay and end their turn by clicking ‘2’. If they choose to throw the grenade, the player has the option to vary the launch angle with the arrow keys (indicated with an arrow on the player) and the launch power of their attack by holding the spacebar (indicated with a green bar in the bottom right corner). A grenade detonates based on two conditions: a time limit or if it bounces with one of the platforms in the map. If any character is within the blast radius of the grenade’s explosion they lose 50 HP and are knocked back depending on their position relative to the grenade’s final position. Players can also be eliminated by falling off the edges of the map or into the shark’s pit in the middle of the map. 

Once the red team’s turn is done, it will be the first character on the blue team’s turn and then the turns continue to alternate between teams while rotating through the three characters on each team.

Once all the players on a team are eliminated, a sound effect will be played using the speakers and a message will appear indicating the game result: “Red Team Wins”, “Blue Team Wins”, or “Tie”. Then, the users are prompted to click the spacebar to restart the game and return to the starting screen if they wish to play again.
