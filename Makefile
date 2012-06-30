
######################################
######################################

CXX=g++

CFLAGS=-Wall -c

LDFLAGS=

all: Beagle_GPIO.o Beagle_GPIO_test

Beagle_GPIO.o: Beagle_GPIO.cc
	@echo Compiling $< to $@
	@$(CXX) $(CFLAGS) Beagle_GPIO.cc

Beagle_GPIO_test.o: Beagle_GPIO_test.cc
	@echo Compiling $< to $@
	@$(CXX) $(CFLAGS) Beagle_GPIO_test.cc

Beagle_GPIO_test: Beagle_GPIO.o Beagle_GPIO_test.o
	@echo Linking $@
	@$(CXX) Beagle_GPIO.o Beagle_GPIO_test.o -o Beagle_GPIO_test

clean:
	@rm -rf *~ *.o Beagle_GPIO_test


######################################
######################################

