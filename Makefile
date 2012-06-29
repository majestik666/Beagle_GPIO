
CXX=g++

CFLAGS=-Wall -c

LDFLAGS=

all: Beagle_GPIO.o Beagle_GPIO_test

Beagle_GPIO.o: Beagle_GPIO.cc
	$(CXX) $(CFLAGS) Beagle_GPIO.cc

Beagle_GPIO_test.o: Beagle_GPIO_test.cc
	$(CC) $(CFLAGS) Beagle_GPIO_test.cc

Beagle_GPIO_test: Beagle_GPIO.o Beagle_GPIO_test.o
	$(CXX) Beagle_GPIO.o Beagle_GPIO_test.o -o Beagle_GPIO_test

clean:
	rm -rf *.o Beagle_GPIO_test

