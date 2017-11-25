OPT = -g

DEPN = Parser.o Instance.o Passageiro.o Cidade.o Dupla.o

Compile: Main

Main: Main.cpp $(DEPN)
	$(CXX) $(OPT) -o Main Main.cpp $(DEPN)

%.o: %.cpp %.hpp
	$(CXX) $(OPT) -c $<

clear:
	rm *.o Main