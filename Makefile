CFLAGS=-I . -std=c99

shim.o:shim.c shim.h
	gcc $(CFLAGS) -c $< -lpthread -lpfm

userRDPMC: userRDPMC.o shim.o
	gcc $(CFLAGS) -o $@ $^ -lpthread -lpfm
userRDPMC.o: userRDPMC.c
	gcc $(CFLAGS) -c $< -lpthread -lpfm
