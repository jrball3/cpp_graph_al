FLAGS=-g -std=c++14
OBJECTS=Graph.o Driver.o
OUT=graphme

all: $(OBJECTS)
	g++ -o $(OUT) $(OBJECTS)

Graph.o: Graph.cpp Vertex.h
	g++ $(FLAGS) -c Graph.cpp

Driver.o: Driver.cpp
	g++ $(FLAGS) -c Driver.cpp

clean:
	rm -rf $(OBJECTS) $(OUT)
