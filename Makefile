CC := gcc
CFLAGS := -Wall -pthread

all: diningOut

diningOut: diningOut.c
	$(CC) $(CFLAGS) -o diningOut diningOut.c
