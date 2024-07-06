SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio


all: run

run:
	g++ -std=c++17 -o tetris *.cpp -I./include -L./lib $(SFML_LIBS)
	./tetris