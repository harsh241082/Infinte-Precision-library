#include "myinf_arth.hh"
#include <cstring>

using namespace std;
using namespace InfiniteArthmetic;

string Integer::add(string num1, string num2)
{
    string result;
    int carry = 0;
    for (int i = 0; i < num1.size(); i++)
    {
        int add = 0;
        if (i < num2.size())
        {
            add = num1[num1.size() - 1 - i] - '0' + num2[num2.size() - 1 - i] - '0' + carry;
        }
        else
        {
            add = num1[num1.size() - 1 - i] - '0' + carry;
        }
        if (add >= 10)
        {
            add = add % 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        result.insert(0, to_string(add));
    }
    if (carry == 1)
    {
        result.insert(0, to_string(carry));
    }

    return result;
}
string Integer::subraact(string num1, string num2)
{
    string result;
    int borrow = 0;
    for (int i = 0; i < num1.size(); i++)
    {
        int sub = 0;
        if (i < num2.size())
        {
            sub = num1[num1.size() - 1 - i] - '0' - num2[num2.size() - 1 - i] + '0' - borrow;
        }
        else
        {
            sub = num1[num1.size() - 1 - i] - '0' - borrow;
        }

        if (sub < 0)
        {
            sub = sub + 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        result.insert(0, to_string(sub));
    }

    return result;
}
string Integer::multiply(string num1, string num2)
{
    string result(num1.size() + num2.size(), '0');
    for (int i = 0; i < num1.size(); i++)
    {
        int carry = 0;
        for (int j = 0; j < num2.size(); j++)
        {
            int mul = (num1[num1.size() - i - 1] - '0') * (num2[num2.size() - j - 1] - '0');
            int sum = mul + (result[num1.size() + num2.size() - i - j - 1] - '0') + carry;
            result[num1.size() + num2.size() - i - j - 1] = sum % 10 + '0';
            carry = sum / 10;
        }
        result[num1.size() - i - 1] += carry;
    }
    while (result.size() > 1 && result[0] == '0')
    {
        result.erase(0, 1);
    }

    return result;
}

void Integer::parse()
{
    int i = 0;
    while (i != num.size())
    {
        if (num[i] == ',')
        {
            num.erase(i, 1);
        }
        else
        {
            i++;
        }
    }
}
Integer::Integer()
{
    num = "0";
}
Integer::Integer(string s)
{
    num = s;
    this->parse();
}
Integer::Integer(const Integer &I)
{
    num = I.getValue();
    this->parse();parse();
}

Integer::~Integer()
{
}

string Integer::getValue() const
{
    return num;
}

void Integer::Erase_minus()
{
    num.erase(num.begin());
}

void Integer::Erasezero()
{
    while (1)
    {
        if (num.front() == '0')
        {
            num.erase(num.begin());
        }
        else
        {
            break;
        }
    }
}

Integer Integer::operator+(Integer &number)
{
    Integer result;
    Integer temp1 = *this;
    Integer temp2 = number;
    int choice;
    if (temp1.num.front() == '-' && temp2.num.front() == '-')
    {
        temp1.Erase_minus();
        temp2.Erase_minus();
        choice = 1;
    }
    else if (temp1.num.front() == '-')
    {
        temp1.Erase_minus();
        choice = 2;
    }
    else if (temp2.num.front() == '-')
    {
        temp2.Erase_minus();
        choice = 3;
    }
    else
    {
        choice = 4;
    }
    temp1.Erasezero();
    temp2.Erasezero();

    int Choice = 0;
    switch (choice)
    {
    case 1:
    case 4:
        if (temp1.num.size() > temp2.num.size())
            Choice = 1;
        else
            Choice = 2;
        switch (Choice)
        {
        case 1:
            result.num = add(temp1.num, temp2.num);
            result.Erasezero();
            break;
        case 2:
            result.num = add(temp2.num, temp1.num);
            result.Erasezero();
            break;
        default:
            break;
        }
        break;
    case 2:
        if (temp2.num.size() == temp1.num.size())
        {
            int i = 0;

            while (1)
            {
                if (temp1.num[i] < temp2.num[i])
                {
                    Choice = 3;
                    break;
                }
                if (temp1.num[i] > temp2.num[i])
                {
                    Choice = 4;
                    break;
                }
                if (i == (temp2.num.size() - 1))
                {
                    Choice = 5;
                    break;
                }
                i++;
            }
        }
        else
        {
            if (max(temp2.num.size(), temp1.num.size()) == temp2.num.size())
                Choice = 1;
            else
                Choice = 2;
        }
        switch (Choice)
        {
        case 1:
            result.num = subraact(temp2.num, temp1.num);
            result.Erasezero();
            break;
        case 2:
            result.num = subraact(temp1.num, temp2.num);
            result.Erasezero();
            result.num.insert(0, "-");
            break;
        case 3:
            result.num = subraact(temp2.num, temp1.num);
            result.Erasezero();
            break;
        case 4:
            result.num = subraact(temp1.num, temp2.num);
            result.Erasezero();
            result.num.insert(0, "-");
            break;
        case 5:
            result.num = "0";
            break;
        default:
            break;
        }
        break;
    case 3:
        if (temp1.num.size() == temp2.num.size())
        {
            int i = 0;

            while (1)
            {
                if (temp1.num[i] > temp2.num[i])
                {
                    Choice = 3;
                    break;
                }
                if (temp1.num[i] < temp2.num[i])
                {
                    Choice = 4;
                    break;
                }
                if (i == (temp1.num.size() - 1))
                {
                    Choice = 5;
                    break;
                }
                i++;
            }
        }
        else
        {
            if (max(temp1.num.size(), temp2.num.size()) == num.size())
                Choice = 1;
            else
                Choice = 2;
        }
        switch (Choice)
        {
        case 1:
            result.num = subraact(temp1.num, temp2.num);
            result.Erasezero();
            break;
        case 2:
            result.num = subraact(temp2.num, temp1.num);
            result.Erasezero();
            result.num.insert(0, "-");
            break;
        case 3:
            result.num = subraact(temp1.num, temp2.num);
            result.Erasezero();
            break;
        case 4:
            result.num = subraact(temp2.num, temp1.num);
            result.Erasezero();
            result.num.insert(0, "-");
            break;
        case 5:
            result.num = "0";
            break;
        default:
            break;
        }
        break;
    }
    if (choice == 1)
    {
        result.num.insert(0, "-");
    }

    return result;
}

Integer &Integer::operator=(Integer &number)
{
    num.assign(number.num);
    return *this;
}

Integer Integer::operator-(Integer &number)
{
    Integer temp = number;
    if (temp.num.front() == '-')
        temp.Erase_minus();
    else
        temp.num.insert(0, "-");
    Integer result = *this + temp;
    return result;
}

Integer Integer::operator*(Integer &number)
{
    Integer result;
    Integer temp1 = *this;
    Integer temp2 = number;
    int choice = 0;
    if (temp1.num == "0" || temp2.num == "0")
    {
        return result;
    }
    if (temp1.num.front() == '-' && temp2.num.front() == '-')
    {
        temp1.Erase_minus();
        temp2.Erase_minus();
        choice = 1;
    }
    else if (temp1.num.front() == '-')
    {
        temp1.Erase_minus();
        choice = 2;
    }
    else if (temp2.num.front() == '-')
    {
        temp2.Erase_minus();
        choice = 3;
    }
    else
    {
        choice = 4;
    }
    temp1.Erasezero();
    temp2.Erasezero();

    string r = multiply(temp1.num, temp2.num);
    result.num = r;
    if (choice == 2 || choice == 3)
    {
        result.num.insert(0, "-");
    }

    return result;
}


Float::Float()
{
    num = "0";
}
Float::Float(string s)
{
    num = s;
    this->parse();
}
Float::Float(const Float &I)
{

    num = I.getValue();
    this->parse();
}

Float::~Float()
{
}

string Float::getValue() const
{
    return num;
}

void Float::Erasezero()
{
    while (!num.empty() && num.back() == '0' && num[num.size() - 2] != '.')
    {
        num.erase(num.end() - 1);
    }
}

void Float::parse()
{
    int i = 0;
    while (i != num.size())
    {
        if (num[i] == ',')
        {
            num.erase(i, 1);
        }
        else
        {
            i++;
        }
    }
}

Float &Float::operator=(Float &number)
{
    num = number.num;
    return *this;
}

Float Float::operator+(Float &number)
{
    string temp_string1 = this->getValue();
    string temp_string2 = number.getValue();
    bool has_decimal_1 = (temp_string1.find('.') != string::npos);
    bool has_decimal_2 = (temp_string2.find('.') != string::npos);

    if (!has_decimal_1 && has_decimal_2)
    {
        temp_string1 += ".0";
    }
    else if (has_decimal_1 && !has_decimal_2)
    {
        temp_string2 += ".0";
    }
    else if (!has_decimal_1 && !has_decimal_2)
    {
        temp_string1 += ".0";
        temp_string2 += ".0";
    }

    int dot_index_1 = temp_string1.find('.');
    int dot_index_2 = temp_string2.find('.');
    if (dot_index_1 != string::npos)
        temp_string1.erase(dot_index_1, 1);
    if (dot_index_2 != string::npos)
        temp_string2.erase(dot_index_2, 1);

    int max_decimal_length = max(temp_string1.size() - dot_index_1, temp_string2.size() - dot_index_2);
    int padding_length_1 = max_decimal_length - (temp_string1.size() - dot_index_1);
    int padding_length_2 = max_decimal_length - (temp_string2.size() - dot_index_2);

    temp_string1.append(padding_length_1, '0');
    temp_string2.append(padding_length_2, '0');

    Integer int_temp1(temp_string1);
    Integer int_temp2(temp_string2);
    Integer int_temp3 = int_temp1 + int_temp2;

    string temp_string3 = int_temp3.getValue();

    temp_string3.insert(temp_string3.size() - max_decimal_length, 1, '.');
    Float result(temp_string3);
    result.Erasezero();

    return result;
}

Float Float::operator-(Float &number)
{
    string temp_string1 = this->getValue();
    string temp_string2 = number.getValue();
    bool has_decimal_1 = (temp_string1.find('.') != string::npos);
    bool has_decimal_2 = (temp_string2.find('.') != string::npos);

    if (!has_decimal_1 && has_decimal_2)
    {
        temp_string1 += ".0";
    }
    else if (has_decimal_1 && !has_decimal_2)
    {
        temp_string2 += ".0";
    }
    else if (!has_decimal_1 && !has_decimal_2)
    {
        temp_string1 += ".0";
        temp_string2 += ".0";
    }

    int dot_index_1 = temp_string1.find('.');
    int dot_index_2 = temp_string2.find('.');
    if (dot_index_1 != string::npos)
        temp_string1.erase(dot_index_1, 1);
    if (dot_index_2 != string::npos)
        temp_string2.erase(dot_index_2, 1);

    int max_decimal_length = max(temp_string1.size() - dot_index_1, temp_string2.size() - dot_index_2);
    int padding_length_1 = max_decimal_length - (temp_string1.size() - dot_index_1);
    int padding_length_2 = max_decimal_length - (temp_string2.size() - dot_index_2);

    temp_string1.append(padding_length_1, '0');
    temp_string2.append(padding_length_2, '0');

    Integer int_temp1(temp_string1);
    Integer int_temp2(temp_string2);
    Integer int_temp3 = int_temp1 - int_temp2;

    string temp_string3 = int_temp3.getValue();
    temp_string3.insert(temp_string3.size() - max_decimal_length, 1, '.');
    Float result(temp_string3);
    result.Erasezero();

    return result;
}

Float Float::operator*(Float &number)
{
    string temp_string1 = this->getValue();
    string temp_string2 = number.getValue();
    if (temp_string1 == "0" || temp_string2 == "0")
    {
        return Float("0");
    }
    bool has_decimal_1 = (temp_string1.find('.') != string::npos);
    bool has_decimal_2 = (temp_string2.find('.') != string::npos);

    if (!has_decimal_1 && has_decimal_2)
    {
        temp_string1 += ".0";
    }
    else if (has_decimal_1 && !has_decimal_2)
    {
        temp_string2 += ".0";
    }
    else if (!has_decimal_1 && !has_decimal_2)
    {
        temp_string1 += ".0";
        temp_string2 += ".0";
    }

    int dot_index_1 = temp_string1.find('.');
    int dot_index_2 = temp_string2.find('.');
    if (dot_index_1 != string::npos)
        temp_string1.erase(dot_index_1, 1);
    if (dot_index_2 != string::npos)
        temp_string2.erase(dot_index_2, 1);

    int max_decimal_length = temp_string1.size() - dot_index_1 + temp_string2.size() - dot_index_2;

    Integer int_temp1(temp_string1);
    Integer int_temp2(temp_string2);
    Integer int_temp3 = int_temp1 * int_temp2;

    string temp_string3 = int_temp3.getValue();
    temp_string3.insert(temp_string3.size() - max_decimal_length, 1, '.');
    Float result(temp_string3);
    result.Erasezero();

    return result;
}