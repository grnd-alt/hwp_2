CC=gcc
CPP=g++
CFLAGS=-I. -lb15fdrv
OBJ = serialctl.o 

%.o: %.c $(DEPS)
	$(CPP) -c -o $@ $< $(CFLAGS)

serialctl: $(OBJ)
	$(CPP) -o $@ $^ $(CFLAGS)
