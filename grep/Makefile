CC=gcc
FLAGS=-Wall -Wextra -Werror -std=c11
TARGET=s21_grep
LINK=s21_grep.c

all: $(TARGET)

clean:
	rm -rf s21_grep

$(TARGET):
	$(CC) $(FLAGS) $(LINK) -o $(TARGET)

test:
	sh tests.sh

rebuild:
		make clean
		make all
