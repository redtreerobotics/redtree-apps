# Redtree Robotics
#
# Sample Makefile for a user program
# 
CC = g++-4.8
LIBS = -lrt -ltcmalloc_minimal -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab -lglut -lGLU -lGL -lSDLmain -lGLEW
CPPFLAGS = -Wall -lsqlite3 -pthread -std=c++11 -fpic -Iinclude -I/usr/include/mysql -I/usr/include/cppconn/ -shared -Wl,-soname,librtruser.so -o librtruser.so

hello_rover: .PHONY
	$(CC) $(CPPFLAGS) $(LIBS) *.cpp
	sudo mv librtruser.so /lib

.PHONY:
	bash ../depcheck.sh
