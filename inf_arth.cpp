#include "myinf_arth.hh"
#include <algorithm>
#include <cctype>

using namespace std;
using namespace InfiniteArthmetic;

// ============================================================================
// INTEGER CLASS IMPLEMENTATION
// ============================================================================

// Private Helper Methods

bool Integer::isValidNumber(const string &s) const
{
    if (s.empty())
        return false;

    int start = 0;
    if (s[0] == '-' || s[0] == '+')
        start = 1;
    if (start >= s.length())
        return false;

    for (int i = start; i < s.length(); i++)
    {
        if (s[i] == ',')
            continue; // Allow commas as separators
        if (!isdigit(s[i]))
            return false;
    }
    return true;
}

void Integer::parse(string s)
{
    // Remove whitespace and validate
    string cleaned;
    bool hasMinusSign = false;

    for (char c : s)
    {
        if (c == '-')
            hasMinusSign = true;
        else if (c != ' ' && c != ',')
            cleaned += c;
    }

    if (cleaned.empty())
    {
        magnitude = "0";
        isNegative = false;
        return;
    }

    magnitude = cleaned;
    isNegative = hasMinusSign;
    trimLeadingZeros();
}

void Integer::trimLeadingZeros()
{
    size_t pos = 0;
    while (pos < magnitude.length() - 1 && magnitude[pos] == '0')
        pos++;
    magnitude = magnitude.substr(pos);

    if (magnitude == "0")
        isNegative = false;
}

int Integer::compareMagnitudes(const string &num1, const string &num2) const
{
    if (num1.length() != num2.length())
        return num1.length() < num2.length() ? -1 : 1;

    return num1.compare(num2);
}

string Integer::addMagnitudes(const string &num1, const string &num2) const
{
    string result;
    int carry = 0;
    int i = num1.length() - 1;
    int j = num2.length() - 1;

    while (i >= 0 || j >= 0 || carry)
    {
        int digit1 = i >= 0 ? num1[i] - '0' : 0;
        int digit2 = j >= 0 ? num2[j] - '0' : 0;

        int sum = digit1 + digit2 + carry;
        result = char('0' + sum % 10) + result;
        carry = sum / 10;

        i--;
        j--;
    }

    return result;
}

string Integer::subtractMagnitudes(const string &num1, const string &num2) const
{
    // Assumes num1 >= num2 in magnitude
    string result;
    int borrow = 0;
    int i = num1.length() - 1;
    int j = num2.length() - 1;

    while (i >= 0)
    {
        int digit1 = num1[i] - '0';
        int digit2 = j >= 0 ? num2[j] - '0' : 0;

        int diff = digit1 - digit2 - borrow;
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        result = char('0' + diff) + result;
        i--;
        j--;
    }

    return result;
}

string Integer::multiplyMagnitudes(const string &num1, const string &num2) const
{
    int n = num1.length(), m = num2.length();
    string result(n + m, '0');

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = m - 1; j >= 0; j--)
        {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int sum = mul + (result[i + j + 1] - '0');

            result[i + j + 1] = char('0' + sum % 10);
            result[i + j] += sum / 10;
        }
    }

    // Remove leading zeros
    size_t pos = 0;
    while (pos < result.length() - 1 && result[pos] == '0')
        pos++;

    return result.substr(pos);
}

string Integer::divideMagnitudes(const string& num1, const string& num2) const
{
    // Long division algorithm
    if (num2 == "0") return "0";  // Avoid division by zero
    
    if (compareMagnitudes(num1, num2) < 0) return "0";
    
    string quotient;
    string current;
    
    for (int i = 0; i < num1.length(); i++)
    {
        current += num1[i];
        
        // Remove leading zeros from current
        while (current.length() > 1 && current[0] == '0')
            current = current.substr(1);
        
        // Find digit for quotient
        int digit = 0;
        while (digit <= 9)
        {
            string product = multiplyMagnitudes(num2, to_string(digit));
            if (compareMagnitudes(product, current) > 0) break;
            digit++;
        }
        digit--;
        
        quotient += char('0' + digit);
        
        // Subtract product from current
        if (digit > 0)
        {
            string product = multiplyMagnitudes(num2, to_string(digit));
            current = subtractMagnitudes(current, product);
        }
    }
    
    // Remove leading zeros
    size_t pos = 0;
    while (pos < quotient.length() - 1 && quotient[pos] == '0')
        pos++;
    
    return quotient.substr(pos);
}

Integer::Integer() : magnitude("0"), isNegative(false) {}

Integer::Integer(string s)
{
    parse(s);
}

Integer::Integer(const Integer &I) : magnitude(I.magnitude), isNegative(I.isNegative) {}

Integer::~Integer() {}

string Integer::getValue() const
{
    if (magnitude == "0")
        return "0";
    return (isNegative ? "-" : "") + magnitude;
}

string Integer::getMagnitude() const
{
    return magnitude;
}

bool Integer::getSign() const
{
    return isNegative;
}

void Integer::setValue(string s)
{
    parse(s);
}

Integer &Integer::operator=(const Integer &number)
{
    magnitude = number.magnitude;
    isNegative = number.isNegative;
    return *this;
}

Integer Integer::operator+(const Integer &number) const
{
    Integer result;

    if (isNegative == number.isNegative)
    {
        // Same sign: add magnitudes
        result.magnitude = addMagnitudes(magnitude, number.magnitude);
        result.isNegative = isNegative;
    }
    else
    {
        // Different signs: subtract magnitudes
        int cmp = compareMagnitudes(magnitude, number.magnitude);

        if (cmp >= 0)
        {
            result.magnitude = subtractMagnitudes(magnitude, number.magnitude);
            result.isNegative = isNegative;
        }
        else
        {
            result.magnitude = subtractMagnitudes(number.magnitude, magnitude);
            result.isNegative = number.isNegative;
        }
    }

    result.trimLeadingZeros();
    return result;
}

Integer Integer::operator-(const Integer &number) const
{
    Integer negated = -number;
    return *this + negated;
}

Integer Integer::operator*(const Integer &number) const
{
    Integer result;
    result.magnitude = multiplyMagnitudes(magnitude, number.magnitude);
    result.isNegative = (isNegative != number.isNegative) && result.magnitude != "0";
    result.trimLeadingZeros();
    return result;
}

Integer Integer::operator/(const Integer &number) const
{
    Integer result;
    if (number.magnitude == "0") 
        return Integer("0");  // Avoid division by zero
    
    result.magnitude = divideMagnitudes(magnitude, number.magnitude);
    result.isNegative = (isNegative != number.isNegative) && result.magnitude != "0";
    result.trimLeadingZeros();
    return result;
}

Integer Integer::operator-() const
{
    Integer result = *this;
    if (result.magnitude != "0")
        result.isNegative = !result.isNegative;
    return result;
}

bool Integer::operator==(const Integer &number) const
{
    return magnitude == number.magnitude && isNegative == number.isNegative;
}

bool Integer::operator<(const Integer &number) const
{
    if (isNegative != number.isNegative)
        return isNegative;

    int cmp = compareMagnitudes(magnitude, number.magnitude);
    return isNegative ? cmp > 0 : cmp < 0;
}

bool Integer::operator>(const Integer &number) const
{
    return number < *this;
}

// ============================================================================
// FLOAT CLASS IMPLEMENTATION
// ============================================================================

// Private Helper Methods

bool Float::isValidFloat(const string &s) const
{
    if (s.empty())
        return false;

    bool hasDot = false;
    int start = 0;
    if (s[0] == '-' || s[0] == '+')
        start = 1;

    for (int i = start; i < s.length(); i++)
    {
        if (s[i] == '.')
        {
            if (hasDot)
                return false;
            hasDot = true;
        }
        else if (s[i] == ',')
        {
            continue;
        }
        else if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

void Float::parse(string s)
{
    // Remove whitespace and commas
    string cleaned;
    bool hasMinusSign = false;
    size_t dotPos = string::npos;

    for (char c : s)
    {
        if (c == '-')
            hasMinusSign = true;
        else if (c != ' ' && c != ',')
        {
            if (c == '.')
            {
                if (dotPos != string::npos)
                {
                    // Multiple dots, take first
                    continue;
                }
                dotPos = cleaned.length();
            }
            cleaned += c;
        }
    }

    if (cleaned.empty())
    {
        integerPart = Integer("0");
        decimalPart = Integer("0");
        decimalPlaces = 0;
        isNegative = false;
        return;
    }

    // Split into integer and decimal parts
    string intPart, decPart;

    if (dotPos != string::npos)
    {
        intPart = cleaned.substr(0, dotPos);
        decPart = cleaned.substr(dotPos + 1);
        decimalPlaces = decPart.length();
    }
    else
    {
        intPart = cleaned;
        decPart = "0";
        decimalPlaces = 0;
    }

    if (intPart.empty())
        intPart = "0";
    if (decPart.empty())
        decPart = "0";

    integerPart = Integer(intPart);
    decimalPart = Integer(decPart);
    isNegative = hasMinusSign;

    normalizeDecimal();
}

void Float::normalizeDecimal()
{
    // Remove trailing zeros from decimal part
    string decStr = decimalPart.getMagnitude();
    while (decStr.length() > 1 && decStr.back() == '0')
    {
        decStr.pop_back();
        decimalPlaces--;
    }

    if (decStr == "0")
        decimalPlaces = 0;
    decimalPart = Integer(decStr);

    // Ensure integer part is not negative
    if (isNegative && integerPart.getMagnitude() == "0" && decimalPart.getMagnitude() == "0")
        isNegative = false;
}

void Float::alignDecimalPlaces(Float &other)
{
    if (decimalPlaces < other.decimalPlaces)
    {
        string padding(other.decimalPlaces - decimalPlaces, '0');
        decimalPart = Integer(decimalPart.getMagnitude() + padding);
        decimalPlaces = other.decimalPlaces;
    }
    else if (other.decimalPlaces < decimalPlaces)
    {
        string padding(decimalPlaces - other.decimalPlaces, '0');
        other.decimalPart = Integer(other.decimalPart.getMagnitude() + padding);
        other.decimalPlaces = decimalPlaces;
    }
}

// Public Methods

Float::Float() : integerPart("0"), decimalPart("0"), decimalPlaces(0), isNegative(false) {}

Float::Float(string s)
{
    parse(s);
}

Float::Float(const Float &f) : integerPart(f.integerPart), decimalPart(f.decimalPart),
                               decimalPlaces(f.decimalPlaces), isNegative(f.isNegative) {}

Float::~Float() {}

string Float::getValue() const
{
    if (integerPart.getMagnitude() == "0" && decimalPart.getMagnitude() == "0")
        return "0";

    string result;
    if (isNegative)
        result += "-";

    result += integerPart.getMagnitude();

    if (decimalPlaces > 0)
    {
        result += ".";
        string decStr = decimalPart.getMagnitude();
        // Pad with leading zeros if necessary
        while (decStr.length() < decimalPlaces)
            decStr = "0" + decStr;
        result += decStr;
    }

    return result;
}

void Float::setValue(string s)
{
    parse(s);
}

Float &Float::operator=(const Float &number)
{
    integerPart = number.integerPart;
    decimalPart = number.decimalPart;
    decimalPlaces = number.decimalPlaces;
    isNegative = number.isNegative;
    return *this;
}

Float Float::operator+(const Float &number) const
{
    Float a = *this;
    Float b = number;
    a.alignDecimalPlaces(b);

    // Convert to integers by treating as integers with decimal places
    Integer intA(a.integerPart.getMagnitude() + a.decimalPart.getMagnitude());
    Integer intB(b.integerPart.getMagnitude() + b.decimalPart.getMagnitude());

    if (a.isNegative)
        intA = -intA;
    if (b.isNegative)
        intB = -intB;

    Integer sum = intA + intB;

    Float result;
    string sumStr = sum.getValue();
    bool resultNegative = sum.getSign();

    if (sumStr[0] == '-')
        sumStr = sumStr.substr(1);

    // Reconstruct float with proper decimal places
    if (sumStr.length() <= a.decimalPlaces)
    {
        sumStr = string(a.decimalPlaces - sumStr.length() + 1, '0') + sumStr;
    }

    size_t intPartLen = sumStr.length() - a.decimalPlaces;
    string intPart = sumStr.substr(0, intPartLen);
    string decPart = sumStr.substr(intPartLen);

    if (intPart.empty())
        intPart = "0";
    if (decPart.empty())
        decPart = "0";

    result.integerPart = Integer(intPart);
    result.decimalPart = Integer(decPart);
    result.decimalPlaces = a.decimalPlaces;
    result.isNegative = resultNegative && intPart != "0";

    result.normalizeDecimal();
    return result;
}

Float Float::operator-(const Float &number) const
{
    return *this + (-number);
}

Float Float::operator*(const Float &number) const
{
    // Multiply magnitudes and adjust decimal places
    Integer intA(integerPart.getMagnitude() + decimalPart.getMagnitude());
    Integer intB(number.integerPart.getMagnitude() + number.decimalPart.getMagnitude());

    Integer product = intA * intB;

    Float result;
    string prodStr = product.getValue();

    if (prodStr[0] == '-')
        prodStr = prodStr.substr(1);

    int newDecimalPlaces = decimalPlaces + number.decimalPlaces;

    // Pad with zeros if necessary
    if (prodStr.length() <= newDecimalPlaces)
    {
        prodStr = string(newDecimalPlaces - prodStr.length() + 1, '0') + prodStr;
    }

    size_t intPartLen = prodStr.length() - newDecimalPlaces;
    string intPart = prodStr.substr(0, intPartLen);
    string decPart = prodStr.substr(intPartLen);

    if (intPart.empty())
        intPart = "0";
    if (decPart.empty())
        decPart = "0";

    result.integerPart = Integer(intPart);
    result.decimalPart = Integer(decPart);
    result.decimalPlaces = newDecimalPlaces;
    result.isNegative = (isNegative != number.isNegative) && intPart != "0";

    result.normalizeDecimal();
    return result;
}

Float Float::operator/(const Float &number) const
{
    if (number.integerPart.getMagnitude() == "0" && number.decimalPart.getMagnitude() == "0")
    {
        return Float("0");  // Avoid division by zero
    }

    Float a = *this;
    Float b = number;
    
    // Align decimal places for division
    a.alignDecimalPlaces(b);
    
    // Precision: add extra decimal places for division (e.g., 10 more places)
    int extraPrecision = 10;
    string paddedA = a.integerPart.getMagnitude() + a.decimalPart.getMagnitude();
    string paddedB = b.integerPart.getMagnitude() + b.decimalPart.getMagnitude();
    
    // Add zeros for precision
    paddedA += string(extraPrecision, '0');
    
    Integer intA(paddedA);
    Integer intB(paddedB);
    
    if (a.isNegative) intA = -intA;
    if (b.isNegative) intB = -intB;
    
    Integer quotient = intA / intB;
    
    Float result;
    string quotStr = quotient.getValue();
    bool resultNegative = quotient.getSign();
    
    if (quotStr[0] == '-') quotStr = quotStr.substr(1);
    
    // Reconstruct float with correct decimal places
    int resultDecimalPlaces = a.decimalPlaces + extraPrecision;
    
    if (quotStr.length() <= resultDecimalPlaces)
    {
        quotStr = string(resultDecimalPlaces - quotStr.length() + 1, '0') + quotStr;
    }
    
    size_t intPartLen = quotStr.length() - resultDecimalPlaces;
    string intPart = quotStr.substr(0, intPartLen);
    string decPart = quotStr.substr(intPartLen);
    
    if (intPart.empty()) intPart = "0";
    if (decPart.empty()) decPart = "0";
    
    result.integerPart = Integer(intPart);
    result.decimalPart = Integer(decPart);
    result.decimalPlaces = resultDecimalPlaces;
    result.isNegative = resultNegative && intPart != "0";
    
    result.normalizeDecimal();
    return result;
}

Float Float::operator-() const
{
    Float result = *this;
    if (result.integerPart.getMagnitude() != "0" || result.decimalPart.getMagnitude() != "0")
        result.isNegative = !result.isNegative;
    return result;
}

bool Float::operator==(const Float &number) const
{
    return getValue() == number.getValue();
}

bool Float::operator<(const Float &number) const
{
    Float a = *this;
    Float b = number;
    a.alignDecimalPlaces(b);

    if (a.isNegative != b.isNegative)
        return a.isNegative;

    if (a.integerPart == b.integerPart)
    {
        Integer decCmp = a.decimalPart < b.decimalPart ? a.decimalPart : b.decimalPart;
        return a.isNegative ? a.decimalPart > b.decimalPart : a.decimalPart < b.decimalPart;
    }

    return a.isNegative ? a.integerPart > b.integerPart : a.integerPart < b.integerPart;
}

bool Float::operator>(const Float &number) const
{
    return number < *this;
}