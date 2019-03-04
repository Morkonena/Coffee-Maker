CC=g++
INCLUDES:=-I../Cappuccino/Cappuccino -L../Cappuccino -I../External/Fmod/Linux/include -L../External/Fmod/Linux/lib/x86_64
CFLAGS=-std=c++14 -w -DLINUX -fPIC -fpermissive
SRC:=$(wildcard Affogato/*.cpp)
OUTPUT=libcm2d.so
LIBS:=-lcm -lfmod

release:
	$(CC) -shared $(CFLAGS) $(SRC) $(LIBS) $(INCLUDES) -o $(OUTPUT)

debug:
	$(CC) -shared $(CFLAGS) -g $(SRC) $(LIBS) $(INCLUDES) -o $(OUTPUT)

clean:
	rm $(OUTPUT)
