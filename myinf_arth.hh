#include<string>
using namespace std;

namespace InfiniteArthmetic{
    class Integer{
        private :
            string num;
            string add(string,string);
            string subraact(string,string);
            string multiply(string,string);
            void parse();
        public :
            Integer();
            Integer(string s);
            Integer(const Integer& I);
            ~Integer();
            string getValue() const;
            void Erase_minus();
            void Erasezero();
            Integer& operator=(Integer&);
            Integer operator+(Integer&);
            Integer operator-(Integer&);
            Integer operator*(Integer&);
    };

    class Float{
        private :
            string num;
            void parse();
        public :
            Float();
            Float(string s);
            Float(const Float& I);
            ~Float();        
            string getValue() const;
            void Erasezero();
            Float& operator=(Float&);
            Float operator+(Float&);
            Float operator-(Float&);
            Float operator*(Float&);
    };
}