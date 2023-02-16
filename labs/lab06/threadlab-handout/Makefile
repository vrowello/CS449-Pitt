#
# Sample Makefile for the shared buffer lab.
#

MAKEFILE_PATH := $(shell dirname "$(abspath $(lastword $(MAKEFILE_LIST)))")

#
# Ask for debugging and warnings, and enable pthreads.
#
override CFLAGS += -O0 -g -Wall -I include
override LFLAGS += -pthread


all:    sem pi

.PHONY: all

build/%.o: src/%.c
	mkdir -p "$(MAKEFILE_PATH)/$(shell dirname $@)"
	$(CC) $(CFLAGS) -c $< -o $@

pi: build/pi/main.o build/pi/pi.o
	$(CC) $(LFLAGS) -o pi $^

sem: build/semaphore/main.o build/semaphore/sem.o
	$(CC) $(CFLAGS) $(LFLAGS) -o sem $^

sem_solution: build/semaphore/main.o build/semaphore/sem_native.o
	$(CC) $(CFLAGS) $(LFLAGS) -o sem_solution $^

clean:
	rm -f sem
	rm -f sem_solution
	rm -f pi
	rm -f *.o
	rm -rf build
	rm -f *.json
	rm -f stderr.txt
	rm -f stdout.txt
