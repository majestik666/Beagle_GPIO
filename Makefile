
######################################
######################################

CXX=g++

CFLAGS=-Wall -c -O3

LDFLAGS=-Wall -O3

TARGETS = Beagle_GPIO.o	\
	  Beagle_GPIO_test \
	  Beagle_GPIO_HD44780.o \
	  Beagle_GPIO_HD44780_test \
	  Beagle_GPIO_KS0108.o \
	  Beagle_GPIO_KS0108_test \
	  Beagle_GPIO_Nokia6100.o \
	  FrameBuffer.o \
	  Beagle_GPIO_Nokia6100_test \
	  Beagle_GPIO_Nokia6100_test_3d

all: $(TARGETS)

Beagle_GPIO.o: Beagle_GPIO.cc Beagle_GPIO.hh
	@echo Compiling $< to $@
	@$(CXX) $(CFLAGS) Beagle_GPIO.cc

Beagle_GPIO_HD44780.o: Beagle_GPIO_HD44780.cc Beagle_GPIO_HD44780.hh
	@echo Compiling $< to $@
	@$(CXX) $(CFLAGS) Beagle_GPIO_HD44780.cc -o $@

Beagle_GPIO_KS0108.o: Beagle_GPIO_KS0108.cc Beagle_GPIO_KS0108.hh
	@echo Compiling $< to $@
	@$(CXX) $(CFLAGS) Beagle_GPIO_KS0108.cc -o $@

Beagle_GPIO_Nokia6100.o: Beagle_GPIO_Nokia6100.cc Beagle_GPIO_Nokia6100.hh
	@echo Compiling $< to $@
	@$(CXX) $(CFLAGS) Beagle_GPIO_Nokia6100.cc -o $@

FrameBuffer.o: FrameBuffer.cc FrameBuffer.hh
	@echo Compiling $< to $@
	@$(CXX) $(CFLAGS) FrameBuffer.cc -o $@

Beagle_GPIO_test: Beagle_GPIO_test.cc Beagle_GPIO.o
	@echo Compiling $< to $@
	@$(CXX) $(LDLAGS) Beagle_GPIO_test.cc Beagle_GPIO.o -o Beagle_GPIO_test

Beagle_GPIO_HD44780_test: Beagle_GPIO_HD44780_test.cc Beagle_GPIO.o Beagle_GPIO_HD44780.o
	@echo Compiling $< to $@
	@$(CXX) $(LDLAGS) Beagle_GPIO_HD44780_test.cc Beagle_GPIO.o Beagle_GPIO_HD44780.o -o $@

Beagle_GPIO_KS0108_test: Beagle_GPIO_KS0108_test.cc Beagle_GPIO.o Beagle_GPIO_KS0108.o
	@echo Compiling $< to $@
	@$(CXX) $(LDLAGS) Beagle_GPIO_KS0108_test.cc Beagle_GPIO.o Beagle_GPIO_KS0108.o -o $@

Beagle_GPIO_Nokia6100_test: Beagle_GPIO_Nokia6100_test.cc Beagle_GPIO.o Beagle_GPIO_Nokia6100.o
	@echo Compiling $< to $@
	@$(CXX) $(LDLAGS) Beagle_GPIO_Nokia6100_test.cc Beagle_GPIO.o Beagle_GPIO_Nokia6100.o -o $@

Beagle_GPIO_Nokia6100_test_3d: Beagle_GPIO_Nokia6100_test_3d.cc Beagle_GPIO.o Beagle_GPIO_Nokia6100.o FrameBuffer.o
	@echo Compiling $< to $@
	@$(CXX) $(LDLAGS) Beagle_GPIO_Nokia6100_test_3d.cc Beagle_GPIO.o Beagle_GPIO_Nokia6100.o FrameBuffer.o -o $@

clean:
	@rm -rf *~ *.o $(TARGETS) 


######################################
######################################

