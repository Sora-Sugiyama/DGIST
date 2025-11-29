CXXFLAGS := -std=gnu++20 -O2 -Wall
OBJS := main.o
CXX := g++
all: exe

exe: $(OBJS)
	$(CXX) $(CXXFLAGS) -o exe $^
	
%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

main: main.o
