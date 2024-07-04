all : final

final : main.o input.o
	gcc build/main.o build/input.o -o main.exe
	mv main.exe bin/main.exe

main.o : src/main.c
	gcc -c src/main.c
	mv main.o build/main.o

input.o : src/input.c
	gcc -c src/input.c
	mv input.o build/input.o

clean : 
	echo "Removing object files and executable"
	rm build/*.o
	rm bin/main.exe
