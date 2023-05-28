This project contains a C++ card game called Prší.

## How to build

First of all, this project contains multi media library SFML and an application using this library.

This project is multiplatform, however in order to run it you need to compile on your platform.
This project uses CMake to setup the build enviroment.
Depending on your platform the process may vary. 

#### Windows

On windows there are multiple options how to build the application.

You need to download c++ compiler first. For this you can use Visual Studio or you can download g++.

Then you can either download CMake GUI where you specify the source code as the root of this project.
And <root>/build as a folder where binaries will be built.

Or you can use VSCode cmake extension, or Visual Studio cmake support.

#### Linux

On linux, first you need to download some libraries.

The following command should be enough for this
```
sudo apt-get install libpthread-stubs0-dev libgl1-mesa-dev libx11-dev libxrandr-dev libfreetype6-dev libglew-dev libjpeg8-dev libsndfile1-dev libopenal-dev libxcursor-dev libudev-dev libflac-dev libvorbis-dev
```
Then you head to the root folder. And use the following commands : 
```
mkdir build
cd build
cmake ..
```
This should create a MakeFile, so you use command
```
make
```
Then you can start the executable.
  
  
##### Supported and tested senarios
  
So far the game is capable of caasual playing according to official game rules.
When any player plays Ace, another player has to either be skipped or play ace as well.
If multiple players play ace, the effect is stacked.

Player can be skipped either by a displayed button or pressing the deck.
  
Similliar scenarios happen when a player plays card 7. Next player has to either take 3 cards, or play green Bot or play 7.
The effect is stacked as well.
  
If you as a human player play cardd Top, you have to chose a color which will be played.

A computer player has to follow these rules and if he plays Top, he will chose a random color.
  
There are exactly 32 cards in the game which are rotated between players.
  
If you have 0 cards you win.
  
If all other players have 0 cards you lose.
  
If the game is beginning or you lose or win, the game is stopped until you press a button to start the game. Then all values are reset and game starts again.
