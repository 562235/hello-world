CC = arm-linux-gcc
SRC = $(wildcard ./src/*.c)  $(wildcard ./src/*.s)
I_DIR = -I ./inc
L_DIR = -L ./lib/ -ljpeg -lfont -lm
CFLAG = -g

TARGET = ./bin/main

$(TARGET):$(SRC)
	$(CC) $(SRC) -o $@ $(I_DIR) $(L_DIR) $(CFLAG)
	cp ./inc/*.h ./obj/

.PHONY: clean
clean:
	rm ./bin/main
