OPT = -g

DEPN = Parser.o Instance.o Passageiro.o Cidade.o

Compile: Main

Main: Main.cpp $(DEPN)
	$(GXX) $(OPT) -o Main Main.cpp $(DEPN)

%.o: %.cpp %.hpp
	$(GXX) $(OPT) -c $<

clear:
	rm *.o Main