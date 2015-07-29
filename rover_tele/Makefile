# Redtree Robotics
#
# Sample Makefile for a user program
# 
CC = g++-4.8
LIBS = -lrt -ltcmalloc_minimal -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab -lglut -lGLU -lGL -lSDLmain -lGLEW
CPPFLAGS = -Wall -lsqlite3 -pthread -std=c++11 -fpic -rdynamic -Iinclude -I/usr/include/mysql -I/usr/include/cppconn/ -shared -Wl,-soname,librtruser.so -o librtruser.so

all: rover computer

rover: .PHONY rover.cpp rover.h video_sender.cpp video_sender.h
	$(CC) $(CPPFLAGS) $(LIBS) -L/lib -lrtr rover.cpp video_sender.cpp
	sudo mv librtruser.so /lib

computer: .PHONY computer.cpp computer.h video_receiver.cpp video_receiver.h
	$(CC) $(CPPFLAGS) $(LIBS) -L/lib -lrtr computer.cpp video_receiver.cpp
	sudo mv librtruser.so /lib

.PHONY:
	bash ../depcheck.sh
