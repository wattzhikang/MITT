# These are the main directories in the project
TST = tst
SRC = src
BIN = bin
GEN = $(BIN)/generated_files

# These variables are only used for compiling the Google Test Framework
GTEST_DIR = $(TST)/googletest/googletest
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
				$(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h \
				$(GTEST_HEADERS)
CPPFLAGS += -isystem $(GTEST_DIR)/include

# This is the most important variable. It is a list of all the
# compilation units except header-only sources (see next item)
ITMS := Body Maneuver System Frame

# Header-only sources go here. They still need to be tested,
# but not compiled standalone.
HDR_ONLY := Thruster State

# The source files of the compilation units
SRCS := $(foreach ITM,$(ITMS),$(SRC)/$(ITM).cpp)

# The object files of the compilation units
OBJS := $(foreach ITM,$(ITMS),$(GEN)/$(ITM).o)

# The source, object, and executable files of the tests for the
# compilation units
TST_SRCS := $(foreach ITM,$(ITMS),$(TST)/$(ITM)Test.cpp)
TST_SRCS += $(foreach ITM,$(HDR_ONLY),$(TST)/$(ITM)Test.cpp)
TST_OBJS := $(foreach ITM,$(ITMS),$(GEN)/$(ITM)Test.o)
TST_OBJS += $(foreach ITM,$(HDR_ONLY),$(GEN)/$(ITM)Test.o)
TST_EX := $(foreach ITM,$(ITMS),$(GEN)/$(ITM)Test)
TST_EX += $(foreach ITM,$(HDR_ONLY),$(GEN)/$(ITM)Test)

# Compiler flags
FLAGS = -g -Wall

# This rule generates the MITT binary by linking all the generated
# files
$(BIN)/mitt : test $(GEN)/$(OBJS).o
	@ echo "Linking MITT"
	@ g++ $(FLAGS) $^ -o $@

# This rule generates all the object files needed for the binary
$(OBJS) : $(SRCS)
	@ echo Compiling $@
	@ g++ $(FLAGS) -c $(patsubst $(GEN)%,$(SRC)%,$(@:.o=.cpp)) -o $@

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

$(TST_OBJS) : $(TST_SRCS) $(GTEST_HEADERS)
	@ echo "Compiling unit test " $@ "..."
	@ g++ $(CPPFLAGS) $(FLAGS) -c $(patsubst $(GEN)%,$(TST)%,$(@:.o=.cpp)) -o $@

$(TST_EX) : $(OBJS) $(TST_OBJS) \
            $(GEN)/libgtest.a $(GEN)/libgtest_main.a
	@ echo "Linking Unit Test " $@ "..."
	@ g++ $(CPPFLAGS) $(FLAGS) -L$(GEN) -lgtest_main -lpthread $^ -o $@

# This rule runs the unit tests
test : $(TST_EX)
	@ echo "A list of all the tests: " $(TST_EX)
	@ echo "Running Test" $<
	@ $<

clean : 
	@ rm -v $(GEN)/*
