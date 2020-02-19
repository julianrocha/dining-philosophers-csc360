CC := gcc
CFLAGS := -Wall -lpthread -lrt

all: diningOut

diningOut: diningOut.c
	$(CC) $(CFLAGS) -o diningOut diningOut.c
