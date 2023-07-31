# Dungeon Crawler

![Screenshot 2023-07-30 at 15 58 10](https://github.com/pyrylss/dungeon_crawler/assets/97807894/db9977c6-ee94-4e88-b5c3-53f280c4c66e)


## Overview 

This project is a simple top-down roguelike dungeon crawler game, where the player clears rooms of enemies and eventually wins the game by clearing enough rooms and killing the final boss. 
The game is themed in a traditional fantasy style. After clearing the room, the player can choose from different doors to go to. Different doors have different prizes such as weapon upgrades, health potions and a speed boost. 
The game is realtime, and the player and monsters use magical based ranged weapons. 

## Software structure

![Screenshot 2023-07-30 at 16 03 46](https://github.com/pyrylss/dungeon_crawler/assets/97807894/ced28fe2-6cc0-46ff-9af1-c3c3936c76cf)

The derived classes of the Prize class (ExtraHP, Speedboost, WeaponUpgrade and Healthpotion) that represent different types of prizes are omitted from the UML graph for clarity.
Game: 
Creates the game, updates game state and renders it while game is running 
Level: 
Creates monsters, obstacles and borders of the room and draws them into same window.
 
Player: 
Character that can move and attack by user commands. 
 
Monster: 
Monsters try to damage the player. All the monsters need to be killed to win the game. 
 
Weapon: 
Class for weapons that the player and monsters use. Launches a projectile that causes the damage on hit. 
 
Projectile: 
Class for projectile that the weapon shoots. Weapon class determines damage of projectiles. 
 
Prize: 
Class for prizes that player gets from doors. 
 
Doors:
Class for doors that appear to the room when all the monsters are killed. Creates and handels the prizes as well as the needed graphics for the doors.
 
Stats:
Class that draws the stat boxes

## Instructions for building and using the software
The Linux build is very simple and the recommended method. Mac is fine as well (at least on ARM). WSL is not ideal, and building on Windows natively is not supported.

### Build instructions:
This is assuming everything (WSL,C++ compiler, CMake, etc.) is installed on your computer.
Two disclaimers regarding WSL:
  - The program will run very slowly on WSL due to the lack of GPU acceleration
  - You need to install the WSL Gui support using the following guide
      - Due to this will only work on Windows 11
      - https://ubuntu.com/tutorials/install-ubuntu-on-wsl2-on-windows-11-with-gui-support#5-install-and-use-a-gui-package


1. Make sure SFML 2.5.1 (Simple Fast Media Library) is installed on your computer.
  a. If it is not installed use the command sudo apt-get install libsfml-dev (Linux/WSL (Debian))
  b. On Mac install it using homebrew (https://brew.sh/) with brew install sfml
2. Clone the project
3. Go inside the cloned folder using cd dungeon_crawler
4. Create a build directory and navigate into it
	- 'mkdir build'
	- 'cd build'
5. Configure CMake with 'cmake ..'
	- This part might fail if something is not right with your install
6. Build with make
7. Open the successfully compiled program with ./DungeonCrawler1 (Linux/WSL), or open DungeonCrawler1 (Mac)
8. Done!
   
### Controls:
The player is controlled using the W,A,S and D keys, while using the Left Mouse Button makes the player shoot in the direction of the cursor. Once all the enemies have been vanquished, three doors will appear, which will give the player a buff and spawn them in a new room with more enemies. The player can restart the game at any point by pressing the P button. Health potions are used by pressing the R button. Doors can be used simply by running into them. 
PS. (Pressing Enter kills all the enemies in the room you are currently in. This is a cheat meant to help with testing, but if you find the game too difficult, this can help with seeing the game to its conclusion)
![Screenshot 2023-07-30 at 16 14 11](https://github.com/pyrylss/dungeon_crawler/assets/97807894/53392562-eac9-49fe-bdb0-137b88b8f7e9)


