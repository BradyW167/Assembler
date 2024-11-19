all: Assembler

run: all
	./Assembler

Assembler: driver.o
	g++ driver.o -o Assembler

driver.o: driver.cpp
	g++ -c driver.cpp -o driver.o

clean:
	rm -rf *.o Assembler Assembler.exe
