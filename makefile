CC = gcc
CFLAGS = -g
DEPS = utils/serial.h
OBJ = testing.o utils/serial.o
LIBS = -lm

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

testing: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
