#include "BigInteger.h"
#include <cstdlib>

//Compares two BigIntegers to see if the first is larger than the second
bool firstIsBigger(const BigInteger& b1, const BigInteger& b2) {
  BigInteger temp1 = b1, temp2 = b2;
  std::string str1 = temp1.to_string(), str2 = temp2.to_string();
  for (int i = 0; i < str1.length(); i++)
  {
    if ((str1[i]-'0') > (str2[i]-'0')) //this block goes through same length string to see which is larger
      return true;
    else if ((str1[i]-'0') < (str2[i]-'0'))
      return false;
  }
  return false;
}

BigInteger::BigInteger() {
  digit_list.clear();
  isNegative = false;
}

BigInteger::BigInteger(std::string really_big_number) {
  std::string tmp ="";
  bool isValid = true, allZeros = false;
  int counter = 0;
  isNegative = false;
  for (int i = 0; i < really_big_number.length(); i++)
  {
    try
    {
      if (i == 0)
      {
	      if (!(really_big_number[0] == '-' || (really_big_number[0] >= 48 && really_big_number[0] <= 57))) //check to see if first digit is a - or a number
        {
          throw BigIntException();
	      }
      }
      else
      {
        if (really_big_number[i] < 48 || really_big_number[i] > 57) //check to see if the rest of the digits are numbers
        {
          throw BigIntException();
        }
      }
    }
    catch (BigIntException &e)
    {
      cout << "Error occurred: " << e.what() << endl;
      i = really_big_number.length();
      isValid = false;

    }
  }
  if (really_big_number[0] != '-') //if number isn't negative, remove leading zeros
  {
    while (counter < really_big_number.length()-1 && really_big_number[counter] == '0')
      counter++;

    for (int i = counter; i < really_big_number.length(); i++)
      tmp+=really_big_number[i];

    if (counter != 0)
      really_big_number = tmp;

    if (tmp=="" && counter == really_big_number.length()-1)
      really_big_number = "0";
  }
  else //if number is negative, remove leading zeros
  {
    really_big_number = really_big_number.substr(1);

    while (counter < really_big_number.length()-1 && really_big_number[counter] == '0')
      counter++;

    tmp+='-';
    for (int i = counter; i < really_big_number.length(); i++)
      tmp+=really_big_number[i];

    if (tmp!="-")
      really_big_number = tmp;

    if (tmp=="-" && counter == really_big_number.length()-1)
      really_big_number = "0";
  }

  if (really_big_number == "-0")
    really_big_number = "0";

  if (!isValid)
    really_big_number = "";

  if (really_big_number[0] == '-')
    isNegative = true;
  if (isValid && isNegative)
    for (int i = 0; i < really_big_number.length()-1; i++) //this block fills the digit vector with the string that was inputted
      digit_list.push_back(really_big_number[i+1]-'0');
  else if (isValid)
    for (int i = 0; i < really_big_number.length(); i++)
      digit_list.push_back(really_big_number[i]-'0');
}

std::string BigInteger::to_string() {
  std::string tmp = "";
  int j = digit_list.size();
  for(auto i = 0; i < j; i++)
  {
    tmp+=(digit_list.back()+'0');
    digit_list.pop_back();
  }

  for (int i = tmp.length()-1; i >=0; i--)
    digit_list.push_back(tmp[i]-'0');

  if (isNegative)
    tmp+='-';

  for (int i = 0; i < tmp.length()/2; i++)
    swap(tmp[i],tmp[tmp.length()-1-i]);

  return tmp;
}

bool operator==(const BigInteger &bi1, const BigInteger &bi2) {
  BigInteger temp1 = bi1, temp2 = bi2;
  std::string Stemp1 = temp1.to_string(), Stemp2 = temp2.to_string();
  if (Stemp1.length() != Stemp2.length())
    return false;
  else
    for (int i = 0; i < Stemp1.length(); i++)
      if (Stemp1[i] != Stemp2[i])
        return false;
  return true;
}

bool operator!=(const BigInteger &bi1, const BigInteger &bi2) {
  return !(bi1 == bi2);
}

bool operator<(const BigInteger &bi1, const BigInteger &bi2) {
  BigInteger temp1 = bi1, temp2 = bi2;
  std::string Stemp1 = temp1.to_string(), Stemp2 = temp2.to_string();
  if (Stemp1.length() < Stemp2.length())
    return true;
  else if (Stemp1.length() > Stemp2.length())
    return false;
  for (int i = 0; i < Stemp1.length(); i++)
  {
    if (Stemp1[i] > Stemp2[i])
      return false;
  }
  return true;
}

bool operator>(const BigInteger &bi1, const BigInteger &bi2) {
  return !(bi1 < bi2);
}

BigInteger operator%(const BigInteger &bi1, const BigInteger &bi2)
{
  if (bi1 == bi2)
    return BigInteger("0");
  if (bi1 < bi2)
    return bi1;
  BigInteger result = bi1/bi2;
  result = result * bi2;
  result = bi1 - result;

  return result;
}

BigInteger operator+(const BigInteger &bi1, const BigInteger &bi2) {
  MyList<int> list1 = bi1.digit_list, list2 = bi2.digit_list, result;
  BigInteger answer;
  int carry = 0;

  if (list1.size() < list2.size())
    swap(list1,list2);

  if (bi1.isNegative == bi2.isNegative)
  {
    while (list1.size() > 0 && list2.size() > 0)
    {
      int tmp = list1.back() + list2.back() + carry;
      carry = 0;
      if (tmp > 9)
      {
        carry = 1;
        tmp-=10;
      }
      result.push_front(tmp);
      list1.pop_back();
      list2.pop_back();
    }

    while (list1.size() > 0)
    {
      int tmp = list1.back() + carry;
      carry = 0;
      if (tmp > 9)
      {
        carry = 1;
        tmp-=10;
      }

      result.push_front(tmp);
      list1.pop_back();
    }

    if (carry)
      result.push_front(1);

    answer.digit_list = result;

    if (bi1.isNegative && bi2.isNegative)
      answer.isNegative = true;

    return answer;
  }
  else if (bi1.isNegative)
  {
    BigInteger bi3 = bi1;
    bi3.isNegative = false;
    return (bi2-bi3);
  }
  else
  {
    BigInteger bi4 = bi2;
    bi4.isNegative = false;
    return (bi1-bi4);
  }
}

BigInteger operator-(const BigInteger &bi1, const BigInteger &bi2) {
  MyList<int> list1 = bi1.digit_list, list2 = bi2.digit_list, result;
  int l1Sz = list1.size(), l2Sz = list2.size(), borrow = 0;
  if (bi1.isNegative != bi2.isNegative)
  {
    BigInteger bi3 = bi2;
    bi3.isNegative = !bi2.isNegative;
    return bi1+bi3;
  }
  else //either both are negative or both are positive
  {
    if (((l1Sz == l2Sz) && !firstIsBigger(bi1,bi2)) || list1.size() < list2.size())
      swap(list1,list2);

    while (list1.size() > 0 && list2.size() > 0)
    {
      int tmp = list1.back() - list2.back() - borrow;
      borrow = 0;
      if (tmp < 0)
      {
        borrow = 1;
        tmp+=10;
      }
      result.push_front(tmp);
      list1.pop_back();
      list2.pop_back();
    }

    while (list1.size() > 0)
    {
      int tmp = list1.back() - borrow;
      borrow = 0;
      if (tmp < 0)
      {
        borrow = 1;
        tmp+=10;
      }
      result.push_front(tmp);
      list1.pop_back();
    }

    BigInteger temp;
    temp.digit_list = result;
    BigInteger answer(temp.to_string());

    if ((answer.to_string() != "0") &&
        ((bi1.isNegative && bi2.isNegative && (l1Sz == l2Sz) && firstIsBigger(bi1,bi2)) ||
        (bi1.isNegative && bi2.isNegative && (l1Sz > l2Sz)) ||
        (!bi1.isNegative && !bi2.isNegative && (l1Sz == l2Sz) && !firstIsBigger(bi1,bi2)) ||
        (!bi1.isNegative && !bi2.isNegative && (l1Sz < l2Sz))))
    {
      answer.isNegative = true;
    }

    return answer;
  }
}

BigInteger operator*(const BigInteger &bi1, const BigInteger &bi2) {
  BigInteger temp1 = bi1, temp2 = bi2, result("0");
  int l1Sz = temp1.digit_list.size(), l2Sz = temp2.digit_list.size();

  for (int i = 0; i < l2Sz; i++)
  {
    for (int i = temp2.digit_list.back(); i > 0; i--)
    {
      result = result + temp1;
    }
    temp2.digit_list.pop_back();
    temp1.digit_list.push_back(0);
  }

  if (bi1.isNegative == bi2.isNegative)
    result.isNegative = false;
  else
    result.isNegative = true;

  return result;
}

BigInteger operator/(const BigInteger &bi1, const BigInteger &bi2) {
  BigInteger temp1 = bi1, temp2 = bi2, result("0"), counter("0"), zero("0"), one("1"), multiplicity("1");
  temp1.isNegative = temp2.isNegative = false;
  int diffLsSz, lSz2 = temp2.digit_list.size();

  if (temp2.digit_list.size() == 1 && temp2.digit_list.back() == 0)
  {
    cout << "Can't divide by 0!" << endl;
    return BigInteger();
  }

  if ((temp1 - temp2).digit_list.back() == 0 && (temp1 - temp2).digit_list.size() == 1 && (temp1 != temp2))
    return BigInteger("1");

  while (!(temp1 - temp2).isNegative)
  {
    counter = zero;
    multiplicity = one;
    diffLsSz = temp1.digit_list.size() - temp2.digit_list.size();
    for (int i = 0; i < diffLsSz; i++)
    {
      temp2.digit_list.push_back(0);
      multiplicity.digit_list.push_back(0);
    }
    if (firstIsBigger(temp1,temp2))
    {
      while (!temp1.isNegative)
      {
        temp1 = temp1 - temp2;
        counter = counter + one;
      }
      temp1 = temp1 + temp2;
      counter = counter - one;
      result = result + (counter * multiplicity);
    }
    else
    {
      if (temp2.digit_list.size() > 1)
        temp2.digit_list.pop_back();
      if (multiplicity.digit_list.size() > 1)
        multiplicity.digit_list.pop_back();
      while (!temp1.isNegative)
      {
        temp1 = temp1 - temp2;
        counter = counter + one;
      }
      temp1 = temp1 + temp2;
      counter = counter - one;
      result = result + (counter * multiplicity);
    }
    temp2 = bi2;
    temp2.isNegative = false;
  }

  if (bi1.isNegative != bi2.isNegative && result != zero)
    result.isNegative = true;

  return result;
}

//Helper function to the Fermat method used in is_prime() below
//It calculates modular exponentation based on the three passed in values
BigInteger power(BigInteger &a, BigInteger &n, BigInteger &p) {
  BigInteger result("1"), zero("0"), one("1"), two("2");
  a = a % p;

  while (n > zero)
  {
    if ((n % two) == one)
      result = (result * a) % p;

    n = n / two;
    a = (a * a) % p;
  }

  return result;
}

//The main core of this uses the Fermat method after checking multiple base cases
bool BigInteger::is_prime() {
  BigInteger temp, divisor("11"), eight("8"), seven("7"), five("5"),four("4"), three("3"), two("2"), one("1"), zero("0");
  if ((*this).isNegative || (*this) == one || (*this) == zero)
    return false;
  else if ((*this) == two ||
           (*this) == three ||
           (*this) == five ||
           (*this) == seven)
    return true;
  else if ((*this)%two == zero)
    return false;
  else if ((*this)%three == zero)
    return false;
  else if ((*this)%five == zero)
    return false;
  else if ((*this)%seven == zero)
    return false;
  else
  {
    int k = 1;
    while (k > 0)
    {
      BigInteger random(std::to_string(std::rand()));
      BigInteger a = two + (random%((*this) - four));
      BigInteger n = (*this - one);

      if (power(a, n, (*this)) != one)
        return false;

      k--;
    }
    return true;
  }
}

BigInteger gcd(const BigInteger dividend, const BigInteger divisor) {
  BigInteger bi1 = dividend, bi2 = divisor;
  bi1.isNegative = bi2.isNegative = false;
  if (bi2.digit_list.back() == 0 && bi2.digit_list.size() == 1)
  {
    bi1.isNegative = false;
    return bi1;
  }
  else
    return gcd(bi2,bi1%bi2);
}

BigInteger gefficient_exp(const BigInteger base, long long power) {
  BigInteger one("1"), zero("0");
  if (power <= 0 && base == zero)
    return base/zero;
  else if (power <= 0 && base != zero)
    return zero;
  else if (power == 1)
    return base;
  else if ((power & 1) == 0)
    return gefficient_exp(base * base,power/2);
  else
    return gefficient_exp(base * base,power/2) * base;
}
