CC = gcc
CFLAGS = -g
DEPS = utils/serial.h
OBJ = mult_test.o utils/serial.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

serial_mult: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^