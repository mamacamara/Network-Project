CXX=g++
CFLAGS=-Wall -std=c++0x

EXEC=build/ChaToYou

SRC = $(notdir $(wildcard src/*.cpp))
OBJS = $(SRC:.cpp=.o)

vpath %.cpp src

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CFLAGS) -o $@ $^
	mv *.o build/
	cp src/server.cfg build/
%.o: %.cpp
	$(CXX) $(CFLAGS) -o $@ -c $<

clean :
	rm -rf *.o rm -rf build/* rm -rf src/*~ rm -rf src/#* rm -rf *.o

