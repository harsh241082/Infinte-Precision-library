#include<string>
#include<vector>
using namespace std;

namespace InfiniteArthmetic{
    class Integer{
        private :
            string magnitude;      // Absolute value of the number
            bool isNegative;       // Sign flag: true for negative, false for positive
            
            // Private helper methods
            string addMagnitudes(const string& num1, const string& num2) const;
            string subtractMagnitudes(const string& num1, const string& num2) const;
            string multiplyMagnitudes(const string& num1, const string& num2) const;
            string divideMagnitudes(const string& num1, const string& num2) const;
            int compareMagnitudes(const string& num1, const string& num2) const;
            void trimLeadingZeros();
            void parse(string s);
            bool isValidNumber(const string& s) const;
            
        public :
            Integer();
            Integer(string s);
            Integer(const Integer& I);
            ~Integer();
            
            string getValue() const;
            string getMagnitude() const;
            bool getSign() const;
            void setValue(string s);
            
            Integer& operator=(const Integer& number);
            Integer operator+(const Integer& number) const;
            Integer operator-(const Integer& number) const;
            Integer operator*(const Integer& number) const;
            Integer operator/(const Integer& number) const;
            Integer operator-() const;  // Unary negation
            
            bool operator==(const Integer& number) const;
            bool operator<(const Integer& number) const;
            bool operator>(const Integer& number) const;
    };

    class Float{
        private :
            Integer integerPart;
            Integer decimalPart;
            int decimalPlaces;
            bool isNegative;
            
            // Private helper methods
            void alignDecimalPlaces(Float& other);
            void normalizeDecimal();
            void parse(string s);
            bool isValidFloat(const string& s) const;
            
        public :
            Float();
            Float(string s);
            Float(const Float& f);
            ~Float();
            
            string getValue() const;
            void setValue(string s);
            
            Float& operator=(const Float& number);
            Float operator+(const Float& number) const;
            Float operator-(const Float& number) const;
            Float operator*(const Float& number) const;
            Float operator/(const Float& number) const;
            Float operator-() const;  // Unary negation
            
            bool operator==(const Float& number) const;
            bool operator<(const Float& number) const;
            bool operator>(const Float& number) const;
    };
}