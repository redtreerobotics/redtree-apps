#!/bin/bash

# install all non-found packages that are required
if [ ! -e include ]; then
	svn co http://www.redtreerobotics.com/svn/redtree-lib-headers/trunk include
else
	cd include
	svn update	# todo: update this so that it only does this when necessary
	cd ..
fi

# OPENCV
OPENCV=$(pkg-config --libs opencv 2>&1 | grep "not found")
if [ ! -z "$OPENCV" ]; then
	sudo apt-get install libcv-dev libcvaux-dev cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev libopencv-dev python-opencv
fi

# GLU
GLU=$(pkg-config --libs glu 2>&1 | grep "not found")
if [ ! -z "$GLU" ]; then
        sudo apt-get install libglu1-mesa libglu1-mesa-dev
fi

# GLEW
GLEW=$(pkg-config --libs glew 2>&1 | grep "not found")
if [ ! -z "$GLEW" ]; then
        sudo apt-get install libglew-dev
fi

# SDL 
SDL=$(pkg-config --libs sdl 2>&1 | grep "not found")
if [ ! -z "$SDL" ]; then
        sudo apt-get install libsdl1.2-dev
fi

# SDL2
SDL2=$(pkg-config --libs sdl2 2>&1 | grep "not found")
if [ ! -z "$SDL2" ]; then
        sudo apt-get install libsdl2-dev
fi

# TCMALLOC
if [ ! -e "/usr/lib/libtcmalloc_minimal.so" ]; then
	sudo apt-get install libtcmalloc-minimal4
	sudo ln -s /usr/lib/libtcmalloc_minimal.so.4 /usr/lib/libtcmalloc_minimal.so
fi

# GLUT
if [ ! -e "/usr/lib/i386-linux-gnu/libglut.so.3" ] && [ ! -e "/usr/lib/x86_64-linux-gnu/libglut.so.3" ] ; then
	sudo apt-get install freeglut3 freeglut3-dev 
fi

# MYSQL
SQL=$(pkg-config --libs libmysqlclient-dev 2>&1 | grep "not found")
if [ ! -z "$SQL" ]; then
        sudo apt-get install libmysqlclient-dev
fi

# MYSQL-CONNECTOR
SQLC=$(pkg-config --libs libmysqlcppconn-dev 2>&1 | grep "not found")
if [ ! -z "$SQLC" ]; then
        sudo apt-get install libmysqlcppconn-dev
fi
