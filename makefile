all: Assembler

run: all
	./Assembler

Assembler: driver.o Entry.o Symbol_Table.o
	g++ driver.o Entry.o Symbol_Table.o -o Assembler

driver.o: driver.cpp
	g++ -c driver.cpp -o driver.o

Entry.o: Entry.cpp
	g++ -c Entry.cpp -o Entry.o

Symbol_Table.o: Symbol_Table.cpp
	g++ -c Symbol_Table.cpp -o Symbol_Table.o

clean:
	rm -rf *.o Assembler Assembler.exe
