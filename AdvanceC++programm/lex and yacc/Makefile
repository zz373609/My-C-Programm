EXE = calc
SOURCE = calc.y calc.l main.cc node.cc node.h Makefile

default: $(SOURCE)
	yacc -t -o $(EXE).tab.cc -d calc.y
	lex -o $(EXE).yy.cc calc.l
	g++ -DYYDEBUG=1 -Wall -Werror -o $(EXE) $(EXE).tab.cc $(EXE).yy.cc main.cc node.cc -Wno-unneeded-internal-declaration

clean:
	rm -f *.o y.tab.* $(EXE).tab.* $(EXE) $(EXE).yy.*

run:
	./$(EXE)

test:
	./$(EXE) < input.txt

