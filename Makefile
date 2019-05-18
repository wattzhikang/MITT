TST = tst
SRC = src
BIN = bin
GEN = $(BIN)/generated_files

GTEST_DIR = $(TST)/googletest/googletest
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
				$(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h \
				$(GTEST_HEADERS)
CPPFLAGS += -isystem $(GTEST_DIR)/include

OBJS = Body

FLAGS = -g -Wall

# This rule generates the MITT binary by linking all the generated
# files
$(BIN)/mitt : $(GEN)/$(OBJS).o
	@ echo "Linking MITT"
	@ g++ $(FLAGS) $^ -o $@

# This rule generates all the object files needed for the binary
$(GEN)/$(OBJS).o : $(SRC)/$(OBJS).cpp
	@ echo Compiling $<
	@ g++ $(FLAGS) -c $< -o $@

.PHONY: clean test

# These next few rules compile the Google Test framework and
# prepare it for linkage

$(GEN)/gtest-all.o : $(GTEST_SRCS_)
	@ echo "Compiling Google Test Framework..."
	@ g++ $(CPPFLAGS) -I$(GTEST_DIR) $(FLAGS) -c \
		$(GTEST_DIR)/src/gtest-all.cc -o $@

$(GEN)/gtest_main.o : $(GTEST_SRCS_)
	@ echo "Compiling Google Test Framework..."
	@ g++ $(CPPFLAGS) -I$(GTEST_DIR) $(FLAGS) -c \
		$(GTEST_DIR)/src/gtest_main.cc -o $@

$(GEN)/libgtest.a : $(GEN)/gtest-all.o
	@ echo "Packaging Google Test Framework..."
	@ $(AR) $(ARFLAGS) $@ $^ > /dev/null

$(GEN)/libgtest_main.a : $(GEN)/gtest-all.o $(GEN)/gtest_main.o
	@ echo "Packaging Google Test Framework..."
	@ $(AR) $(ARFLAGS) $@ $^ > /dev/null

# These next two rules compile the object files for the tests and
# link the binaries together

$(GEN)/$(OBJS)Test.o : $(TST)/$(OBJS)Test.cpp $(GTEST_HEADERS)
	@ echo "Compiling unit test " $< "..."
	@ g++ $(CPPFLAGS) $(FLAGS) -c $< -o $@

$(GEN)/$(OBJS)Test : $(GEN)/$(OBJS).o $(GEN)/$(OBJS)Test.o \
                     $(GEN)/libgtest.a $(GEN)/libgtest_main.a
	@ echo "Linking Unit Test " $< "..."
	@ g++ $(CPPFLAGS) $(FLAGS) -L$(GEN) -lgtest_main -lpthread $^ -o $@

# This rule runs the unit tests
test : $(GEN)/$(OBJS)Test
	@ echo "Running Test" $<
	@ $(GEN)/$(OBJS)Test

clean : 
	rm $(GEN)/*
