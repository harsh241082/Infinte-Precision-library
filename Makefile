all: final

final: libmy_inf_arith.a my_inf_arith.cpp
	g++ my_inf_arith.cpp -o my_inf_arith -lmy_inf_arith -L.

libmy_inf_arith.a: inf_arth.o
	ar rcs libmy_inf_arith.a inf_arth.o

inf_arth.o: inf_arth.cpp myinf_arth.hh
	g++ -c inf_arth.cpp

clean: 
	rm *.o my_inf_arith