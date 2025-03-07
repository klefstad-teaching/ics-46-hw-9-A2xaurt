CXXFLAGS=-ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic
main: 
	g++ $(CXXFLAGS) src/dijkstras_main.cpp src/dijkstras.cpp src/ladder_main.cpp src/ladder.cpp -o main
clean:
	/bin/rm main
output:
	g++ $(CXXFLAGS) src/dijkstras_main.cpp src/dijkstras.cpp src/ladder_main.cpp src/ladder.cpp -o main
	./main > output.txt
	/bin/rm main
full:
	g++ $(CXXFLAGS) src/dijkstras_main.cpp src/dijkstras.cpp src/ladder_main.cpp src/ladder.cpp -o main
	./main
	/bin/rm main
build:
	cmake -B build -S .
gtests:
	cmake --build build
	./build/student_gtests