# dependencies for ./closure.c
./closure.o: ./closure.c

closure.a: ./closure.o
	ar rcs $@ $^

CLEAN_closure.a:
	rm -rf closure.a  ./closure.o
