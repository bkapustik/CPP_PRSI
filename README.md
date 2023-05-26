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

sudo apt-get install libpthread-stubs0-dev libgl1-mesa-dev libx11-dev libxrandr-dev libfreetype6-dev libglew-dev libjpeg8-dev libsndfile1-dev libopenal-dev libxcursor-dev libudev-dev libflac-dev libvorbis-dev

Then you had to the root folder. And use the following commands : 
mkdir build
cd build
cmake ..

This should create a MakeFile, so you use command
make

Then you can start the executable.