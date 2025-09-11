SOURCE := $(wildcard *.cpp)
HEADER := $(wildcard *.h)

build : a.exe

run : a.exe
	./a.exe

a.exe : $(SOURCE) $(HEADER)
	g++ -g $(SOURCE) -g --std=c++20

