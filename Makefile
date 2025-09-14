SOURCE := $(wildcard *.cpp)
HEADER := $(wildcard *.h)

build : a.exe

run : a.exe
	./a.exe

a.exe : $(SOURCE) $(HEADER)
	g++ -g $(SOURCE) -g --std=c++20

playground.exe : playground.cpp
	g++ -g playground.cpp -g --std=c++20 -o playground

play : playground.exe
	./playground.exe
