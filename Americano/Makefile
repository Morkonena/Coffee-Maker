CC=g++
INCLUDES:=-I../Cappuccino/Cappuccino -L../Cappuccino
CFLAGS:=-std=c++14 -w -DLINUX -fPIC
SRC:=$(wildcard Americano/*.cpp)
LIBS:=-lGLEW -lGL -lX11 -lcm
OUTPUT=libcmw.so

release:
	$(CC) -shared $(CFLAGS) $(SRC) $(LIBS) $(INCLUDES) -o $(OUTPUT)

debug:
	$(CC) -shared $(CFLAGS) -g $(SRC) $(LIBS) $(INCLUDES) -o $(OUTPUT)

clean:
	rm $(OUTPUT)
