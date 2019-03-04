CC=g++
INCLUDES:=-I../Cappuccino/Cappuccino -I../External/Box2D -L../Cappuccino
CFLAGS:=-std=c++14 -w -DLINUX -fPIC
SRC:=$(wildcard Mocha/*.cpp)
OUTPUT=libcmp.so
LIBS:=-lcm -lbox2d

release:
	$(CC) -shared $(CFLAGS) $(SRC) $(LIBS) $(INCLUDES) -L../External/Box2D/Build/bin/x86_64/Release -o $(OUTPUT)

debug:
	$(CC) -shared $(CFLAGS) -g $(SRC) $(LIBS) $(INCLUDES) -L../External/Box2D/Build/bin/x86_64/Debug -o $(OUTPUT)

clean:
	rm $(OUTPUT)
