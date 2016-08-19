# 3D Snake

It is a simple 3D Snake video game. eat the fishes without eating the baby shark following you

## Warning

The project is very old and may need adaptation to work now.


## Requirements
[Ogre library 1.7.3](http://www.ogre3d.org/tikiwiki/tiki-index.php)
[OIS 1.3](www.ogre3d.org/tikiwiki/Using+OIS)
[CEGUI 0.7.1](http://static.cegui.org.uk/docs/)
[Freetype](https://www.freetype.org/)
[Freeimage](http://freeimage.sourceforge.net/)
[Nvidia CG toolkit](https://developer.nvidia.com/cg-toolkit)

Project was started using [ogre3D basic and intermediate tutorials](http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Tutorials).
You could follow them to start on this project.

## Old ogre install commands:
These could be deprecated and may need a refresh.
```bash

# On an ubuntu based system
sudo apt-get install libois-dev libfreeimage-dev libfreetype6-dev libzzip-dev libxaw7-dev libglew1.5-dev libxrandr-dev
sudo apt-get install cmake cmake-guibuild-essential autoconf libtool libdevil-dev libfreeimage-dev libfreetype6-dev libglew1.5-dev libxaw7-dev libxrandr-dev libxt-dev libxxf86vm-dev libzzip-dev
sudo apt-get install libboost1.40-dev 
sudo apt-get install nvidia-glx-185-dev
sudo apt-get install g++

# Install OIS:

./bootstrap
./configure
make
sudo make install

# Install CG nvidia:
# see distribution repository

# Install Ogre3D :
cmake ./
make
sudo make install

# Install FreeImage
make
sudo make install

# Install CEGUI
./bootstrap

# Add OgreCore.zip in the packs
```
