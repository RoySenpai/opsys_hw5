#################################################################################
# 	Operation Systems (OSs) Course Assignment 5 Makefile			#
# 	Authors: Roy Simanovich and Linor Ronen (c) 2023			#
# 	Description: This Makefile compiles the programs and libraries 		#
# 				Date: 2023-06					#
# 			Course: Operating Systems				#
# 				Assignment: 5					#
# 				Compiler: gcc					#
# 				OS: Linux					#
# 			IDE: Visual Studio Code					#
#################################################################################

# Flags for the compiler and linker.
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -g -pedantic
LFLAGS = -pthread -lmath
HFILES = Queue.h ActiveObject.h Task.h
RM = rm -f

# Phony targets - targets that are not files but commands to be executed by make.
.PHONY: all default clean

# Default target - compile everything and create the executables and libraries.
all: st_pipeline

# Alias for the default target.
default: all


############
# Programs #
############
st_pipeline: Main.o Queue.o ActiveObject.o Task.o
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

################
# Object files #
################
%.o: %.c $(HFILES)
	$(CC) $(CFLAGS) -c $<
	
#################
# Cleanup files #
#################
clean:
	$(RM) *.o *.so st_pipeline