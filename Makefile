CXX=g++
CXXFLAGS=-g -std=c++0x -Werror -Wall

EMULATOR=emulator
EMULATOR_SOURCES=\
	morse.cpp \
	gerwalk.cpp \
	emulator.cpp

EMULATOR_OBJECTS=$(EMULATOR_SOURCES:%.cpp=%.o)

$(EMULATOR): $(EMULATOR_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(@) $(^) -lcurses

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $(@) $(<)

clean:
	rm -f $(EMULATOR_OBJECTS) $(EMULATOR_TARGET)
