CXX = g++
CXXFLAGS = -std=c++20 -Wall -Werror -Wpedantic -O2
TESTFLAGS = -lgtest -lgtest_main -lpthread

TEST_SRC = main.cpp
TEST_TARGET = game

all:

test: $(TEST_SRC)
	$(CXX) $(TEST_SRC) $(CXXFLAGS) -o $(TEST_TARGET) $(TESTFLAGS)

clean:
	rm -f $(TEST_TARGET)
