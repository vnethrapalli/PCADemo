CC = gcc
CFLAGS = -g
DEPS = utils/serial.h
OBJ = utils/serial.o
LIBS = -lm

all: testing pca_serial

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

testing: $(OBJ) testing.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

pca_serial: $(OBJ) pca_serial.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
