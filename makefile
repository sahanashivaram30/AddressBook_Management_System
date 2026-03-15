out.exe : main.o contact.o file_implement.o
	gcc -o out.exe main.o contact.o file_implement.o
main.o : main.c
	gcc -c main.c 
contact.o : contact.c 
	gcc -c contact.c 
file_implement.o : file_implement.c 
	gcc -c file_implement.c