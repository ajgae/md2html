CC=gcc
SRC=src/main.c \
	src/config.c \
	src/context.c \
	src/blocks.c \
	src/header.c \
	src/paragraph.c \
	src/utils.c

.PHONY: all
all:
	$(CC) $(SRC) -ggdb
