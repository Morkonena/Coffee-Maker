CC=g++
INCLUDES:=-I../External/Glm
CFLAGS:=-std=c++14 -w -DLINUX -fPIC
SRC:=$(wildcard Cappuccino/*.cpp)
LIBS:=-lGL
OUTPUT=libcm.so

release:
	$(CC) -shared $(CFLAGS) $(SRC) $(LIBS) $(INCLUDES) -o $(OUTPUT)

debug:
	$(CC) -shared $(CFLAGS) -g $(SRC) $(LIBS) $(INCLUDES) -o $(OUTPUT)

clean:
	rm $(OUTPUT)
