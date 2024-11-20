#include "myinf_arth.hh"
#include <iostream>
using namespace InfiniteArthmetic;

int main(int argc, char *argv[]){
    
    if(*argv[1] == 'i'){
        if(*argv[2] == 'a'){
            Integer i1(argv[3]);
            Integer i2(argv[4]);
            Integer i3 = i1 + i2;
            std::cout << i3.getValue() << '\n';
        }
        if(*argv[2] == 's'){
            Integer i1(argv[3]);
            Integer i2(argv[4]);
            Integer i3 = i1 - i2;
            std::cout << i3.getValue() << '\n';
        }
        if(*argv[2] == 'm'){
            Integer i1(argv[3]);
            Integer i2(argv[4]);
            Integer i3 = i1 * i2;
            std::cout << i3.getValue() << '\n';
        }
        if(*argv[2] == 'd'){
            std::cout << "Division operator is not overloaded!!"<< '\n';
        }
    }
    if(*argv[1] == 'f'){
        if(*argv[2] == 'a'){
            Float f1(argv[3]);
            Float f2(argv[4]);
            Float f3 = f1 + f2;
            std::cout << f3.getValue() << '\n';
        }
        if(*argv[2] == 's'){
            Float f1(argv[3]);
            Float f2(argv[4]);
            Float f3 = f1 - f2;
            std::cout << f3.getValue() << '\n';
        }
        if(*argv[2] == 'm'){
            Float f1(argv[3]);
            Float f2(argv[4]);
            Float f3 = f1 * f2;
            std::cout << f3.getValue() << '\n';
        }
        if(*argv[2] == 'd'){
            std::cout << "Division operator is not overloaded!!"<< '\n';
        }
    }
    
    return 0;

}