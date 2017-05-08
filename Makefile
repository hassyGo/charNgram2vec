CXX=g++

EIGEN_LOCATION=$$HOME/local/eigen_3.3-beta1 # Modify here to use Eigen
BUILD_DIR=objs

CXXFLAGS =-Wall
CXXFLAGS+=-O3
CXXFLAGS+=-std=c++11
CXXFLAGS+=-DUSE_FLOAT
CXXFLAGS+=-DUSE_EIGEN_TANH
CXXFLAGS+=-lm
CXXFLAGS+=-funroll-loops
CXXFLAGS+=-march=native
CXXFLAGS+=-m64
CXXFLAGS+=-DEIGEN_DONT_PARALLELIZE
CXXFLAGS+=-DEIGEN_NO_DEBUG
CXXFLAGS+=-DEIGEN_NO_STATIC_ASSERT
CXXFLAGS+=-I$(EIGEN_LOCATION)
CXXFLAGS+=-fopenmp

SRCS=$(shell ls *.cpp)
OBJS=$(SRCS:.cpp=.o)

PROGRAM=c2v

all : $(BUILD_DIR) $(patsubst %,$(BUILD_DIR)/%,$(PROGRAM))

$(BUILD_DIR)/%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

$(BUILD_DIR)/$(PROGRAM) : $(patsubst %,$(BUILD_DIR)/%,$(OBJS))
	$(CXX) $(CXXFLAGS) $(CXXLIBS) -o $@ $^
	mv $(BUILD_DIR)/$(PROGRAM) ./
	rm -f ?*~

clean:
	rm -f $(BUILD_DIR)/* $(PROGRAM) ?*~
	echo "dummy" > objs/dummy