CXX = g++
LDLIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
LDFLAGS = -W -t

app: main.o dijkstra.o
	$(CXX) -o app $^ $(LDLIBS)

main.o: src/main.cpp src/dijkstra.h
	$(CXX) -c src/main.cpp

dijkstra.o: src/dijkstra.cpp src/dijkstra.h
	$(CXX) -c src/dijkstra.cpp

