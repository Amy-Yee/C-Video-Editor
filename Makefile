#######################################################################
# Homework Assignment 5, for EECS 22, Fall 2017
#
# Author: Tim Schmidt
# Date: 11/09/2017
#
# Makefile: Makefile for HW 5
#
#######################################################################

# Variables
CC = gcc
DEBUG = -g
#DEBUG = -O2
CFLAGS = -Wall -ansi -std=c99 $(DEBUG) -c $(DEBUG)
LFLAGAS = -Wall -ansi -std=c99 $(DEBUG)
MAIN = -DMAIN

OBJS = MovieLab.o FileIO.o DIPs.o Image.o ImageList.o Movie.o

# Default target
all: MovieLab

test: all
	valgrind ./MovieLab

######################### Generate object files #######################
# Target for MovieLab.o
MovieLab.o: MovieLab.c FileIO.h DIPs.h Movie.h Constants.h Image.h

# Target for FileIO.o
FileIO.o: FileIO.c FileIO.h Constants.h Image.h
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o

# Target for DIPs.o
DIPs.o: DIPs.c Constants.h DIPs.h
	$(CC) $(CFLAGS) DIPs.c -o DIPs.o

# Target for Image.o
Image.o: Image.c Image.h
	$(CC) $(CFLAGS) Image.c -o Image.o

# Target for ImageList.o
ImageList.o: ImageList.c ImageList.h Image.h
	$(CC) $(CFLAGS) ImageList.c -o ImageList.o

# Target for Movie.o
Movie.o: Movie.c Movie.h ImageList.h Image.h
	$(CC) $(CFLAGS) Movie.c -o Movie.o

######################### Generate the executable #####################
# Target for MovieLab
MovieLab: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o MovieLab


###############################  others  ##############################
# Target for clean-up
clean:
	rm -f *.o MovieLab `find . -name '*.ppm'! -name 'watermark_template.ppm'`
