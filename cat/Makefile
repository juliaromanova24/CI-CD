CC = gcc
CC_FLAGS = -c -std=c11 -Wall -Werror -Wextra
BUILD_NAME = s21_cat
FILE = s21_cat.c

all: build

build: s21_cat

rebuild: clean build

s21_cat: s21_cat.o 
	${CC} s21_cat.o -o ${BUILD_NAME}


test:
	sh tests.sh
	
clean:
	rm -rf ./*.o ${BUILD_NAME}

rebuild : make clean make all
