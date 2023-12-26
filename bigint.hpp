#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

/**
 * @class BigInt
 * @brief A class for representing and calculating large integers.
 */
class BigInt
{

private:
    bool isNegative = 0;     /** @brief Indicates the sign of the number, if the number is zero, it should be treated as positive in this class. */
    vector<uint8_t> numbers; /** @brief Stores the digits of the number in reverse order. */

public:
    /**
     * @brief Default constructor, initialize the digit to zero.
     */
    BigInt();

    /**
     * @brief Construct a new BigInt object from a 64-bit integer.
     * @param _num 64-bit integer
     */
    BigInt(int64_t);

    /**
     * @brief Construct a new BigInt object from another BigInt object.
     * @param other A BigInt object
     */
    BigInt(const BigInt &);

    /**
     * @brief Construct a new BigInt object from a digit string
     * @param _numbers A digit string
     */
    BigInt(const string &);

    /**
     * @brief Get the Sign of the BigInt object
     * @return True if the number is negative, false otherwise
     */
    bool getSign() const;

    /**
     * @brief Get the length of the digits
     * @return An integer (the length of the digits)
     */
    size_t getSize() const;

    /**
     * @brief Get the digit at a specific position
     * @param idx index of the digit
     * @return The digit at the index position
     */
    uint8_t getNum(const size_t) const;

    /**
     * @brief Checks if the absolute value of this BigInt is greater than or equal to another.
     * @param rhs The BigInt to compare with.
     * @return True if the absolute value of this BigInt object is greater or equal, false otherwise.
     */
    bool isAbsGreaterOrEqual(const BigInt &) const;

    /**
     * @brief Adds the absolute value of two BigInt object.
     * @param rhs another BigInt object to add.
     */
    void additionAbs(const BigInt &);

    /**
     * @brief Subtracts the absolute value of another BigInt object.
     * @param rhs another BigInt object to subtract.
     */
    void subtractionAbs(const BigInt &);

    /**
     * @brief multiplies this BigInt absolute value by another BigInt absolute value.
     * @param rhs another BigInt object to multiply with.
     */
    void multiplicationAbs(const BigInt &);

    /**
     * @brief Overloads the += operator for BigInt.
     * @param rhs another BigInt object to add.
     * @return Reference to the current object.
     */
    BigInt &operator+=(const BigInt &);

    /**
     * @brief Overloads the -= operator for BigInt.
     * @param rhs another BigInt object to subtract.
     * @return Reference to the current object.
     */
    BigInt &operator-=(const BigInt &);

    /**
     * @brief Overloads the *= operator for BigInt.
     * @param rhs another BigInt object to multiply.
     * @return Reference to the current object.
     */
    BigInt &operator*=(const BigInt &);

    /**
     * @brief Overloads the unary minus operator for BigInt.
     * @return Reference to the current object with its sign negated.
     */
    BigInt &operator-();

    /**
     * @brief Overloads the copy assignment operator for BigInt.
     * @param rhs another BigInt object to copy from.
     * @return Reference to the current object.
     */
    BigInt &operator=(const BigInt &);

    /**
     * @brief Overloads the copy assignment operator for BigInt.
     * @param  _num a 64-bit integer to copy from.
     * @return Reference to the current object.
     */
    BigInt &operator=(int64_t);

    /**
     * @brief Overloads the copy assignment operator for BigInt.
     * @param _numbers a digit string to copy from.
     * @return Reference to the current object.
     */
    BigInt &operator=(const string &);
};

/**
 * @brief Overloads the + operator for two BigInt objects.
 * @param lhs, rhs two BigInt objects.
 * @return Reference to a BigInt object.
 */
BigInt operator+(BigInt, const BigInt &);

/**
 * @brief Overloads the - operator for two BigInt objects.
 * @param lhs, rhs two BigInt objects.
 * @return Reference to a BigInt object.
 */
BigInt operator-(BigInt, const BigInt &);

/**
 * @brief Overloads the * operator for two BigInt objects.
 * @param lhs, rhs two BigInt objects.
 * @return Reference to a BigInt object.
 */
BigInt operator*(BigInt, const BigInt &);

/**
 * @brief Overloads == operator for two BigInt objects.
 * @param lhs,rhs two BigInt objects.
 * @return True if lhs and rhs are equal, false otherwise.
 */
bool operator==(const BigInt &, const BigInt &);

/**
 * @brief Overloads != operator for two BigInt objects.
 * @param lhs,rhs two BigInt objects.
 * @return True if lhs and rhs are not equal, false otherwise.
 */
bool operator!=(const BigInt &, const BigInt &);

/**
 * @brief Overloads <= operator for two BigInt objects.
 * @param lhs,rhs two BigInt objects.
 * @return True if lhs is less than or equal to rhs, false otherwise.
 */
bool operator<=(const BigInt &, const BigInt &);

/**
 * @brief Overloads > operator for two BigInt objects.
 * @param lhs,rhs two BigInt objects.
 * @return True if lhs is larger than rhs, false otherwise.
 */
bool operator>(const BigInt &, const BigInt &);

/**
 * @brief Overloads >= operator for two BigInt objects.
 * @param lhs,rhs two BigInt objects.
 * @return True if lhs is larger than or equal to rhs, false otherwise.
 */
bool operator>=(const BigInt &, const BigInt &);

/**
 * @brief Overloads < operator for two BigInt objects.
 * @param lhs,rhs two BigInt objects.
 * @return True if lhs is less than rhs, false otherwise.
 */
bool operator<(const BigInt &, const BigInt &);

/**
 * @brief Overloads the stream insertion operator for BigInt.
 * @param out the output stream.
 * @param bigint the BigInt object to be output.
 * @return output stream after modification for BigInt.
 */
ostream &operator<<(ostream &, const BigInt &);

BigInt::BigInt()
{
    numbers.push_back(0);
}

BigInt::BigInt(int64_t _num)
{
    isNegative = (_num < 0);
    _num = abs(_num);
    if (_num == 0)
        numbers.push_back(0);
    for (; _num != 0; _num /= 10)
        numbers.push_back(static_cast<uint8_t>(_num % 10)); // Stores the digits of the number in reverse order, which is convenient for calculation.
}

BigInt::BigInt(const BigInt &other) : isNegative(other.isNegative), numbers(other.numbers) {}

BigInt::BigInt(const string &_numbers)
{
    uint64_t temp = 0; // temp is used to mark the first digit position.
    if (_numbers[0] == '-')
    {
        isNegative = 1;
        temp = 1;
    }
    else if (_numbers[0] == '+')
    {
        isNegative = 0;
        temp = 1;
    }
    if (_numbers.size() == 1 && (_numbers[0] == '-' || _numbers[0] == '+'))
        throw invalid_argument("Invalid input: only contains sign character");
    for (size_t i = temp; i < _numbers.size(); i++)
    {
        if (!((_numbers[i] - '0') <= 9 && (_numbers[i] - '0') >= 0))
            throw invalid_argument("Invalid input: contains non-digit character");
        numbers.push_back(static_cast<uint8_t>(_numbers[i] - '0'));
    }
    reverse(numbers.begin(), numbers.end()); // Stores the digits of the number in reverse order, which is convenient for calculation.
}

bool BigInt::getSign() const
{
    return isNegative;
}

size_t BigInt::getSize() const
{
    return numbers.size();
}

uint8_t BigInt::getNum(const size_t idx) const
{
    return numbers.at(idx);
}

bool BigInt::isAbsGreaterOrEqual(const BigInt &rhs) const
{
    if (numbers.size() != rhs.numbers.size())
        return numbers.size() > rhs.numbers.size();
    for (size_t i = numbers.size() - 1; i >= 1; i--)
    {
        if (numbers[i] != rhs.numbers[i])
            return numbers[i] > rhs.numbers[i];
    }
    return numbers[0] >= rhs.numbers[0];
}

void BigInt::additionAbs(const BigInt &rhs)
{
    uint64_t length = max(numbers.size(), rhs.numbers.size());
    uint8_t carry = 0; // carry is used to represent the carry-over in addition.
    uint8_t sum;
    for (size_t i = 0; i < length || carry != 0; i++)
    {
        if (i == numbers.size())
            numbers.push_back(0); // extend the vector when it has exceeded the current number's length.
        if (i < rhs.numbers.size())
            sum = (uint8_t)(numbers[i] + rhs.numbers[i] + carry);
        else
            sum = numbers[i] + carry;
        carry = (uint8_t)(sum / 10); // calculate carry for next iteration.
        numbers[i] = (uint8_t)(sum % 10);
    }
}

void BigInt::subtractionAbs(const BigInt &rhs)
{
    // we assume that current BigInt object absolute value is greater than or equal to rhs absolute value.
    uint8_t borrow = 0; // borrow variable is used to store the borrow value that is needed.
    uint8_t sub;
    for (size_t i = 0; i < numbers.size(); i++)
    {
        if (i < rhs.numbers.size())
            sub = (uint8_t)(numbers[i] - rhs.numbers[i] - borrow);
        else
            sub = numbers[i] - borrow;
        borrow = 0;
        if (sub > numbers[i]) // // underflow happens since sub is an unsigned 8 digit integer, so here we use the condition "sub > numbers[i]"
        {
            sub += 10;
            borrow = 1;
        }
        numbers[i] = sub;
    }
    while (numbers.size() > 1 && numbers.back() == 0) // Remove redundant zeros
        numbers.pop_back();
}

void BigInt::multiplicationAbs(const BigInt &rhs)
{
    vector<uint8_t> temp(numbers.size() + rhs.numbers.size(), 0); // create a temporary vector to store the multiplication result.
    for (size_t i = 0; i < numbers.size(); i++)
    {
        uint8_t carry = 0;
        uint64_t result;
        for (size_t j = 0; j < rhs.numbers.size() || carry != 0; j++) // Multiply the current digit of the first number with each digit of the second number.
        {
            if (j < rhs.numbers.size())
                result = (uint64_t)(temp[i + j] + rhs.numbers[j] * numbers[i] + carry);
            else
                result = temp[i + j] + carry;
            temp[i + j] = (uint8_t)(result % 10);
            carry = (uint8_t)(result / 10);
        }
    }
    while (temp.size() > 1 && temp.back() == 0) // Remove redundant zeros
        temp.pop_back();
    numbers = move(temp);
}

BigInt &BigInt::operator+=(const BigInt &rhs)
{
    if (isNegative == rhs.isNegative)
        additionAbs(rhs);
    else if (isAbsGreaterOrEqual(rhs))
        subtractionAbs(rhs);
    else
    {
        isNegative = rhs.isNegative;
        BigInt temp(rhs);
        temp.subtractionAbs(*this);
        *this = move(temp);
    }
    return *this;
}

BigInt &BigInt::operator-=(const BigInt &rhs)
{
    if (isNegative != rhs.isNegative)
        additionAbs(rhs);
    else if (isAbsGreaterOrEqual(rhs))
        subtractionAbs(rhs);
    else
    {
        isNegative = !isNegative;
        BigInt temp(rhs);
        temp.subtractionAbs(*this);
        *this = move(temp);
    }
    return *this;
}

BigInt &BigInt::operator*=(const BigInt &rhs)
{
    if (isNegative != rhs.isNegative)
        isNegative = 1;
    else if (isNegative == 1)
        isNegative = 0;
    multiplicationAbs(rhs);
    return *this;
}

BigInt &BigInt::operator-()
{
    if (!(numbers.size() == 1 && numbers[0] == 0)) // Don't negate if the number is zero
        isNegative = !isNegative;
    return *this;
}

BigInt &BigInt::operator=(const BigInt &rhs)
{
    isNegative = rhs.isNegative;
    numbers = rhs.numbers;
    return *this;
}

BigInt &BigInt::operator=(int64_t _num)
{
    isNegative = (_num < 0);
    _num = abs(_num);
    numbers.clear();
    if (_num == 0)
        numbers.push_back(0);
    for (; _num != 0; _num /= 10)
        numbers.push_back(static_cast<uint8_t>(_num % 10));
    return *this;
}

BigInt &BigInt::operator=(const string &_numbers)
{
    uint64_t temp = 0;  // temp is used to mark the first digit position.
    if (_numbers[0] == '-')
    {
        isNegative = 1;
        temp = 1;
    }
    else if (_numbers[0] == '+')
    {
        isNegative = 0;
        temp = 1;
    }
    if (_numbers.size() == 1 && (_numbers[0] == '-' || _numbers[0] == '+'))
        throw invalid_argument("Invalid assignment: only contains sign character");
    numbers.clear();
    for (size_t i = temp; i < _numbers.size(); i++)
    {
        if (!((_numbers[i] - '0') <= 9 && (_numbers[i] - '0') >= 0))
            throw invalid_argument("Invalid assignment: contains non-digit character");
        numbers.push_back(static_cast<uint8_t>(_numbers[i] - '0'));
    }
    reverse(numbers.begin(), numbers.end());
    return *this;
}

bool operator==(const BigInt &lhs, const BigInt &rhs)
{
    if (lhs.getSign() != rhs.getSign())
        return 0;
    return (lhs.isAbsGreaterOrEqual(rhs) && rhs.isAbsGreaterOrEqual(lhs));
}

bool operator!=(const BigInt &lhs, const BigInt &rhs)
{
    return !(lhs == rhs);
}

bool operator<=(const BigInt &lhs, const BigInt &rhs)
{
    if (lhs.getSign() == 0 && rhs.getSign() == 1)
        return 0;
    else if (lhs.getSign() == 1 && rhs.getSign() == 0)
        return 1;
    else
        return rhs.isAbsGreaterOrEqual(lhs);
}

bool operator>(const BigInt &lhs, const BigInt &rhs)
{
    return !(lhs <= rhs);
}

bool operator>=(const BigInt &lhs, const BigInt &rhs)
{
    if (lhs.getSign() == 1 && rhs.getSign() == 0)
        return 0;
    else if (lhs.getSign() == 0 && rhs.getSign() == 1)
        return 1;
    else
        return lhs.isAbsGreaterOrEqual(rhs);
}

bool operator<(const BigInt &lhs, const BigInt &rhs)
{
    return !(lhs >= rhs);
}

ostream &operator<<(ostream &out, const BigInt &bigint)
{
    if (bigint.getSign() && !(bigint.getSize() == 1 && bigint.getNum(0) == 0))
        out << '-';
    for (size_t i = bigint.getSize() - 1; i >= 1; i--)
        out << static_cast<int>(bigint.getNum(i));
    out << (static_cast<int>(bigint.getNum(0)));
    return out;
}

BigInt operator+(BigInt lhs, const BigInt &rhs)
{
    lhs += rhs;
    return lhs;
}

BigInt operator-(BigInt lhs, const BigInt &rhs)
{
    lhs -= rhs;
    return lhs;
}

BigInt operator*(BigInt lhs, const BigInt &rhs)
{
    lhs *= rhs;
    return lhs;
}