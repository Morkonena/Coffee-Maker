CC=g++
INCLUDES:=-I../Cappuccino/Cappuccino -L../Cappuccino -I../External/Png/include -L../External/Png/lib/Linux
CFLAGS:=-std=c++14 -w -DLINUX -fPIC
SRC:=$(wildcard Espresso/*.cpp)
OUTPUT=libcmi.so
LIBS:=-lcm -lpng -lz

release:
	$(CC) -shared $(CFLAGS) $(SRC) $(LIBS) $(INCLUDES) -o $(OUTPUT)

debug:
	$(CC) -shared $(CFLAGS) -g $(SRC) $(LIBS) $(INCLUDES) -o $(OUTPUT)

clean:
	rm $(OUTPUT)
