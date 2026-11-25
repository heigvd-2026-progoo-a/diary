CXX      ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra
CPPFLAGS += -I.
LDLIBS   += -pthread

TARGET := parse

all: $(TARGET)

$(TARGET): parse.cpp peglib.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@ $(LDLIBS)

clean:
	$(RM) $(TARGET) a.out

.PHONY: all clean
