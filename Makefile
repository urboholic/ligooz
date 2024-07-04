all : final

final : main.o input.o commands.o
	gcc build/main.o build/input.o build/commands.o -o main.exe
	mv main.exe bin/main.exe

main.o : src/main.c
	gcc -c src/main.c
	mv main.o build/main.o

input.o : src/input.c
	gcc -c src/input.c
	mv input.o build/input.o

commands.o : src/commands.c
	gcc -c src/commands.c
	mv commands.o build/commands.o

clean : 
	echo "Removing object files and executable"
	rm build/*.o
	rm bin/main.exe
