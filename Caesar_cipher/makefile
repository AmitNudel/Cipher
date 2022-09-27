CPP = g++
CPPFLAG = std=c++11 -g -pedantic -Wall -Weffc++ -Wextra
DEBUG = -DNDEBUG -O3

main.o: main.o
	$(CPP) -I ./hpp/. ./cpp/*.cpp -o ./out/main.o 

debug.o: debug.o
	$(CPP) $(DEBUG) -I ./hpp/. ./test/main_test.cpp ./cpp/caesar_cipher.cpp ./cpp/helpers.cpp ./cpp/user_interface.cpp -o ./out/debug.o 

all: main.o debug.o

clean:
	$(RM) ./out/*.o ./out/debug.out ./out/main.out