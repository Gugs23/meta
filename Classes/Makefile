OPT = -g

DEPN = Parser.o Instance.o Passageiro.o Cidade.o Dupla.o

Compile: Main Teste

Teste: Teste.cpp $(DEPN)
	$(CXX) $(OPT) -o Teste Teste.cpp $(DEPN)

Main: Main.cpp $(DEPN)
	$(CXX) $(OPT) -o Main Main.cpp $(DEPN)

%.o: %.cpp %.hpp
	$(CXX) $(OPT) -c $<

clear:
	rm *.o Main Teste