hepsi: derle calistir

derle:
	g++ -I ./include/ -o ./lib/Data.o -c ./src/Data.cpp
	g++ -I ./include/ -o ./lib/NodeTree.o -c ./src/NodeTree.cpp
	g++ -I ./include/ -o ./lib/Tree.o -c ./src/Tree.cpp
	g++ -I ./include/ -o ./lib/Gini.o -c ./src/Gini.cpp
	g++ -I ./include/ -o ./bin/test ./lib/Data.o ./lib/Gini.o  ./lib/NodeTree.o ./lib/Tree.o  ./src/test.cpp
	
calistir:
	./bin/test