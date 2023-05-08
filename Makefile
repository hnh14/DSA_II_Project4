CXX = g++
CXXFLAGS = -g -std=c++17 -Wall -Werror=return-type  -Werror=uninitialized 

SRCS = $(wildcard *.hpp)
OBJECTS = $(SRCS:%.hpp=%.o)

CATCH = test/catch/catch.o
TEST_SRCS = $(wildcard test/*.cpp)
TESTS = $(TEST_SRCS:test/%.cpp=%)
#TESTS := $(shell find ./test -name "*cpp")

main: $(OBJECTS) main.cpp monte.o
	$(CXX) $(CXXFLAGS) -o $@ $^

rm:
	rm -rf batch-sets/*.txt

clean:
	rm -rf *.dSYM
	$(RM) *.o *.gc* test/*.o test/*.gc* *.dSYM $(addprefix test/,$(TESTS)) core main $(CATCH)

$(TESTS): $(CATCH)
	$(CXX) $(CXXFLAGS) -o test/$@ $^
	test/$@ --success

test-all: $(TESTS)
test-1: test/test-1.cpp priority.o fifo.o customer.o $(CATCH)
	$(CXX) $(CXXFLAGS) -o test/$@ $^
	test/$@ --success

test-2: test/test-2.cpp stats.o $(CATCH)
	$(CXX) $(CXXFLAGS) -o test/$@ $^
	test/$@ --success
