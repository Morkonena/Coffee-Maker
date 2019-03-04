altra:
	(cd Altra && make)

kernel:
	(cd Cappuccino && make)
	(cd Affogato && make) &
	(cd Americano && make) &
	(cd Espresso && make) &
	(cd Mocha && make) &
	wait

all:
	kernel
	altra

clean:
	(cd Cappuccino && make clean) &
	(cd Affogato && make clean) &
	(cd Americano && make clean) &
	(cd Espresso && make clean) &
	(cd Mocha && make clean) &
	wait
