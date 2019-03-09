CC=g++
INCLUDES:=-I../Cappuccino/Cappuccino -L../Cappuccino
CFLAGS=-std=c++14 -w -DLINUX -fPIC -fpermissive
SRC:=$(wildcard Affogato/*.cpp)
OUTPUT=libcm2d.so
LIBS:=-lcm

release:
	$(CC) -shared $(CFLAGS) $(SRC) $(LIBS) $(INCLUDES) -o $(OUTPUT)

debug:
	$(CC) -shared $(CFLAGS) -g $(SRC) $(LIBS) $(INCLUDES) -o $(OUTPUT)

clean:
	rm $(OUTPUT)
