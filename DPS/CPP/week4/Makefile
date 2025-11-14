#
#  Makefile
#  dpslang
#
#  Created by Sora Sugiyama on 11/1/25.
#

CXX := g++
# -Wall 은 에러 표시 ;
CXXFLAGS := -std=gnu++20 -O2 -Wall
OBJS := main.o variable.o

all: exe

exe: $(OBJS)
	$(CXX) $(CXXFLAGS) -o exe $^


# %는 앞에 아무거나 올 수 있다는 것.
# $@는 target (label). $< 는 첫 번째 의존 파일. $^ 는 모든 의존 파일
%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

main: main.o

variable: variable.o
