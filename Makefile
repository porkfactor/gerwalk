CXX=g++
CXXFLAGS=-g -std=c++0x -Werror -Wall

TARGET=gerwalk
SOURCES=\
	morse.cc \
	gerwalk.cc \
	arduino.cc \
	main.cc

OBJECTS=$(SOURCES:%.cc=%.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(@) $(^)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $(@) $(<)

clean:
	rm -f $(OBJECTS) $(TARGET)
