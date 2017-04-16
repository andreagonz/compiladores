CXX=g++
CXXFLAGS=-g -std=c++11
BIN=interprete

SRC=$(wildcard *.cpp *.cc)
OBJ=$(SRC:%.cpp=%.o)

all: $(OBJ)
	$(CXX) -g -std=c++11 -o $(BIN) $^ -lfl

%.o: %.c
	$(CXX) $@ -c $<

.PHONY: clean
clean :
		rm -f interprete *.o

.PHONY: flex
flex:
		flex++ scanner.lex
