CC := gcc
CFLAGS := -g -Wall -Wno-deprecated-declarations -Werror -lpthreads

all: diningOut

diningOut: diningOut.c
	$(CC) $(CFLAGS) -o diningOut diningOut.c