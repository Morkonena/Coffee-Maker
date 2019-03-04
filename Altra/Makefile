CC=g++
INCLUDES:=-I../Cappuccino/Cappuccino -I../Affogato/Affogato -I../Americano/Americano -I../Espresso/Espresso -I../Mocha/Mocha \
					  -L../Cappuccino -L../Affogato -L../Americano -L../Espresso -L../Mocha -L../External/Fmod/Linux/lib/x86_64

CFLAGS=-std=c++14 -w -DLINUX -fpermissive
SRC:=$(wildcard Altra/*.cpp) Altra/Simplex/Noise.cpp Altra/Linux/Adapter.cpp
OUTPUT=Run/Altra
LIBS:=-lcm -lcm2d -lcmw -lcmi -lcmp -lfmod

release:
	$(CC) $(CFLAGS) $(SRC) $(LIBS) $(INCLUDES) -o $(OUTPUT)
	cp ../Cappuccino/libcm.so Run/Binaries
	cp ../Affogato/libcm2d.so Run/Binaries
	cp ../Americano/libcmw.so Run/Binaries
	cp ../Espresso/libcmi.so Run/Binaries
	cp ../Mocha/libcmp.so Run/Binaries

debug:
	$(CC) $(CFLAGS) -g $(SRC) $(LIBS) $(INCLUDES) -o $(OUTPUT)
	cp ../Cappuccino/libcm.so Run/Binaries
	cp ../Affogato/libcm2d.so Run/Binaries
	cp ../Americano/libcmw.so Run/Binaries
	cp ../Espresso/libcmi.so Run/Binaries
	cp ../Mocha/libcmp.so Run/Binaries

clean:
	rm $(OUTPUT)
	rm Run/Binaries/libcm.so
	rm Run/Binaries/libcm2d.so
	rm Run/Binaries/libcmw.so
	rm Run/Binaries/libcmi.so
	rm Run/Binaries/libcmp.so
