
######################################
######################################

CXX=g++

CFLAGS=-Wall -c

LDFLAGS=-Wall

TARGETS = Beagle_GPIO.o	\
	  Beagle_GPIO_test \
	  Beagle_GPIO_HD44780.o \
	  Beagle_GPIO_HD44780_test \
	  Beagle_GPIO_KS0108.o \
	  Beagle_GPIO_KS0108_test

all: $(TARGETS)

Beagle_GPIO.o: Beagle_GPIO.cc
	@echo Compiling $< to $@
	@$(CXX) $(CFLAGS) Beagle_GPIO.cc

Beagle_GPIO_HD44780.o: Beagle_GPIO_HD44780.cc
	@echo Compiling $< to $@
	@$(CXX) $(CFLAGS) Beagle_GPIO_HD44780.cc

Beagle_GPIO_KS0108.o: Beagle_GPIO_KS0108.cc
	@echo Compiling $< to $@
	@$(CXX) $(CFLAGS) Beagle_GPIO_KS0108.cc

Beagle_GPIO_test: Beagle_GPIO_test.cc Beagle_GPIO.o
	@echo Compiling $< to $@
	@$(CXX) $(LDLAGS) Beagle_GPIO_test.cc Beagle_GPIO.o -o Beagle_GPIO_test

Beagle_GPIO_HD44780_test: Beagle_GPIO_HD44780_test.cc Beagle_GPIO.o Beagle_GPIO_HD44780.o
	@echo Compiling $< to $@
	@$(CXX) $(LDLAGS) Beagle_GPIO_HD44780_test.cc Beagle_GPIO.o Beagle_GPIO_HD44780.o -o Beagle_GPIO_HD44780_test

Beagle_GPIO_KS0108_test: Beagle_GPIO_KS0108_test.cc Beagle_GPIO.o Beagle_GPIO_KS0108.o
	@echo Compiling $< to $@
	@$(CXX) $(LDLAGS) Beagle_GPIO_KS0108_test.cc Beagle_GPIO.o Beagle_GPIO_KS0108.o -o Beagle_GPIO_KS0108_test

clean:
	@rm -rf *~ *.o $(TARGETS) 


######################################
######################################

