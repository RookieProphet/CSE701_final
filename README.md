# BigInt: C++ Solution for Large Integers Precision Computing
## Introduction
In the field of scientific computing, the need to deal with large integers is extremely important. These calculations often involve extremely large values that are far beyond the scope of conventional data types. In the standard of C++, basic integer types such as ***int*** or ***long*** are limited in the range of values they are deal with. For example, a standard ***int*** type can only represent values in the range from -2,147,483,648 to 2,147,483,647. For the field of scientific computing, such a limitation is clearly a shortcoming. In contrast, some high-level programming languages, such as Python, provide automatic handling of large integers, allowing the user not to worry about upper bounds on values. However, it doesn't naturally exist in C++, requiring developers to implement the functionality themselves.

Therefore, we developed the BigInt project, a class designed for C++ that can deal with large integers of arbitrary length. It not only supports basic arithmetic and comparison operations, but also has good encapsulation and extensibility, making it easy to use in various applications. With BigInt, C++ programmers can now work with large integers beyond the limits of standard data types without sacrificing performance and precision.

## Class Members and Implementation
### Private Variables
```cpp
    vector <uint8_t> numbers; 
```
The ***BigInt*** class uses a `vector <uint8_t>` to store each digit of the large integer and the digits are stored in reverse order.
```cpp
    bool isNegative;
```
The ***BigInt*** class uses a boolean variable to indicate the sign of the large integer. If the value is `true`, it indicates the large number is negative. If the value is `false`, the large number is negative. If the number is exactly Zero, this sign flag should be considered positive.
### Public Functions
```cpp
    BigInt();
    BigInt(int64_t);
    BigInt(const BigInt& );
    BigInt(const string& );
```
The ***BigInt*** class provides several constructors.  
`BigInt()` is a default constructor, which initializes the numbers to zero.  
`BigInt(int64_t)` is a constructor which creates a `BigInt` object from a 64-bit integer. This allows for easy conversion from standard C++ integers types to `BigInt`.  
`BigInt(const BigInt&)` is a constructor that creates a `BigInt` object from another `BigInt` object. It will copy the sign and numbers directly.   
`BigInt(const string&)` is a constructor that creates a `BigInt` object from a string representation of a large integer. If the string contains any non-digit characters (excluding an initial sign character), or if it's an empty string, the constructor throws an exception, ensuring that only valid numeric strings are used to initialize BigInt objects.
```cpp
    bool getSign() const;
```
The `getSign()` function is used to get the sign of the `BigInt` object. It will return `true` if the `BigInt` object represents a negative number and return `false` if the `BigInt` object represents a non-negative number (including zero).

```cpp
    size_t getSize() const;
```
The `getSize()` function is used to provide the number of digits in the `BigInt` object.
```cpp
    uint8_t getNum (const size_t) const;
```
The `getNum()` function is used to access to a specific digit of the `BigInt` object and the parameter is the index of the digit to be accessed. This function is essential for operations where digits need to be accessed individually and the operations are not members functions.
```cpp
    BigInt& operator+=(const BigInt&);
```
We overload the operator `+=` to adds the value of another `BigInt` object to current object. The function first checks the signs of both `BigInt` objects. If they have the same sign, it proceeds with the addition of their absolute values, using `additionAbs()` function. If they have different signs, it performs a subtraction of their absolute values, using `subtractionAbs()` function. The sign of the result is based on the signs of the operands. It will change only when the signs of the two operands are different and the absolute value of `rhs` is greater than  `*this`.
```cpp
    BigInt& operator-=(const BigInt&);
```
We overload the operator `-=` to subtract the value of another `BigInt` object from current object. The function first checks the signs of the operands, if they have different signs, it performs an addition of their absolute values, using `additionAbs()`. If they have the same sign, it proceeds with subtraction, using `subtractionAbs()` The sign of the result depends on the relative magnitude of the operands and their signs.
```cpp
    BigInt& operator*=(const BigInt&);
```
We overload the operator `*=` to multiply the value of current `BigInt` object with another `BigInt` object. The function will call the `multiplicationsAbs` function directly to calculate the product of these two value. The sign of the result is determined by the signs of the two operands. If they are different, the result is negative. otherwise, it is positive.
```cpp
    BigInt& BigInt::operator-()
```
We overload the unary operator `-` to negate the current `BigInt` object. It will change the sign of the number. If the number is zero, it will not change the sign (still positive).
```cpp
    BigInt& BigInt::operator=(const BigInt& rhs)
    BigInt& BigInt::operator=(int64_t _num)
    BigInt& BigInt::operator=(const string &_numbers)
```
The `BigInt` class provides three overloads of the assignment operator, each designed to handle different types of assignment sources: another `BigInt` object, a 64-bit integer, and a string representing a large integer (also will throws an exception if the string contains invalid characters). These operators ensure the `BigInt` object can be easily and flexibly assigned values from various sources.
### Non-member Functions
#### Arithmetic Functions
```cpp
    BigInt operator+(BigInt, const BigInt&);
    BigInt operator-(BigInt, const BigInt&);
    BigInt operator*(BigInt, const BigInt&);
```
We overload the `+-*` operator by using the member function `+= -= *=`, the biggest difference is that it can return a new `BigInt` object representing the sum, difference or product separately.
#### Comparison Functions
```cpp
    bool operator==(const BigInt&, const BigInt&);
    bool operator!=(const BigInt&, const BigInt&);
    bool operator<=(const BigInt&, const BigInt&);
    bool operator>(const BigInt&, const BigInt&);
    bool operator>=(const BigInt&, const BigInt&);
    bool operator<(const BigInt&, const BigInt&);
```
When we overload the comparison operators, we all call the `isAbsGreaterOrEqual()` function, which will return true if current `BigInt` object value is larger than or equal to `rhs` value.  
For the operator `==`, First step is to check sign. if they are different, they cannot be equal，otherwise, we go to the next step. Next step is we use the logic `A == B` if and only if `A >= B` and `B >= A` (A and B are two `BigInt` objects). So we call the `isAbsGreaterOrEqual()` function twice, if both of the return value is `true`, they are equal.  
For the operator `!=`, we just `return !(lhs==rhs)`.  
For the operator `<=`, First step is to check sign. If they are different, the positive one is larger. If they have the same sign, we also call the `isAbsGreaterOrEqual(lhs)`, It will return `true` if `lhs<=rhs`.  
For the operator `>`, we just `return !(lhs<=rhs)` .  
For the operator `>=`, First step is to check sign. If they are different, the positive one is larger. If they have the same sign, we also call the `isAbsGreaterOrEqual(rhs)`, It will return `true` if `lhs>=rhs`.  
For the operator `<`, we just `return !(lhs>=rhs)` .  
#### Insertion Function
```cpp
    ostream& operator<<(ostream&, const BigInt&);
```
We overload the  `<<` operator for the `BigInt` class, enabling the `BigInt` to be output to standard output stream like `std::cout`. When it is invoked, it first checks the sign of the `BigInt` object and output a `-` if the number is negative. Then it will iterate over the digits stored in `vector<uint8_t> numbers` and output each digit in correct order.

### Key Algorithm.
```cpp
    bool BigInt::isAbsGreaterOrEqual(const BigInt &rhs) const
```
This function is very crucial since almost all the arithmetic and comparison functions will call the function. There are mainly three steps in this function.  
The first step is to compare the size of two `numbers` vector. If the current object has more digits than`rhs`, it mean its absolute value is greater, and teh method returns `true`. Conversly, if `rhs` has more digits, the current object's absolute value is smaller, returns `false`.  
Next step is to compare digit by digit if the number of digits is the same in both objects. The comparison starts from the highest significant digit which is the last element in the `numbers` vector, and moves towards the least significant digit. During this digit-by-digit comparison, if any corresponding digit in the current object is found to be greater than that in `rhs`, the method returns `true`. Conversely, if any corresponding digit in the current object is found to be smaller than that in `rhs`, the method returns `false`.  
Last step is if all the digits are equal, that means the absolute values of both `BigInt` objects are equal. Finally, It will return `true`.

```cpp
    void BigInt::additionAbs(const BigInt& rhs)
```
This function is designed to add the absolute values of two `BigInt` objects. It can be divided into several steps.  
The first step is to calculate the length by determining the maximum length of two numbers, which makes all the digits in the large number can participate in the addition loop. Also it will initialized the `carrier` variable to zero which is used to store the carry-over during the addition process.  
Next step is in the addition loop. The addition loop continues until it has proceeded all the digits and the carry-over. If the loop reaches a digit position that is beyond the length of the
current object, a zero is appended to the vector to accommodate the addition. For each digit position `i`, the method calculates the sum of the corresponding digits from both numbers and the current carry. If `i` is within the bounds of `rhs.numbers`, both digits are included in the sum; otherwise, only the digit from the current object and the carry are added.  
Last step is also in the addition loop. It is time to update the current digit and carry. The digit at position `i` of the current object's numbers vector is updated to `(sum % 10)`, and the carry is updated to `(sum / 10)`.
```cpp
    void BigInt::subtractionAbs(const BigInt& rhs)
```
This function is designed to subtract the absolute value of `rhs` from `*this`. We assume that the absolute value of current object is larger than or equal to that of `rhs`. It can be divided into several steps.  
The first step is to initialize the `borrow` variable to zero. The variable is to keep track of any borrow that occurs during the subtraction process.  
Then it will come to the subtraction loop that iterates over each digit in the current `BigInt` object. For each digit position `i`, if `i` is within the bounds of `rhs.numbers`, it subtracts the digit at position `i` of `rhs` and the `borrow` from the digit at position `i` of current object. If `i` is beyond the bounds of `rhs.numbers`, it only subtracts the `borrow` from the current object. After the subtraction, if the result is greater than the original digit in the current object `(numbers[i])`, it indicates that an underflow has occurred (since `sub` is an unsigned 8-bit integer , if it is signed, it should be a negative integer). To correct this, 10 is added to `sub`, and `borrow` is set to 1 for the next iteration.  
The last step is to update the current digit at position `i` from `sub` and remove the redundant zeros which is at the end of the `numbers` vector.
```cpp
    void BigInt::multiplicationAbs(const BigInt& rhs)
```

This function is designed to multiply the absolute values of two `BigInt` objects. Compared with Add and subtract, it is a little more complicated. It can be divided into several steps.  
The first step is create a temporary vector to store the multiplication result. The size of the temporary vector should make sure that it can hold the result of the multiplication.  
Next step is double for loop. The outer loop iterates over each digit of the current `BigInt` numbers and inner loop iterates over each digit of the  `rhs.numbers`. It multiplies the digit at position `i` of the current object with the digit at position `j` of `rhs`, adds any carry from the previous step, and adds the current value at position `i+j` in `temp`. The result of this multiplication and addition is stored in `temp[i + j]` and `carry`.  
The last step is to remove redundant zeros which is at the end of the `numbers` vector and update current object from the `temp` vector.
## Examples
### How to use the BigInt class
The BigInt project read input from a txt file `demo.txt`. In the current `BigInt` class， all the operators are either unary or binary operators. So in the `demo.txt` file, the first two lines should be the Big Integers that participate in the calculation, and the third line should be the operator if it's a binary operators. If it's a unary operator, the first line is a big integer and the second line is that operator. The output will be printed into the terminal.
### Some examples of possible inputs and outputs.
```
Input:
999999999999999999999999999999
1
+

Output:
999999999999999999999999999999+1       
Result: 1000000000000000000000000000000
```
```
Input:
-99999999999999
1000
+

Output:
-99999999999999+1000
Result: -99999999998999
```
```
Input:
-99999999999999
-1000
+

Output:
-99999999999999+-1000
Result: -100000000000999
```
```
Input:
-999asdfasdfasdf
-1000
+

Output:
Exception caught: Invalid input: contains non-digit character
```

```
Input:
-999462583462656234560234656203465463574236523478563284765
-1000
-

Output:
-999462583462656234560234656203465463574236523478563284765--1000
Result: -999462583462656234560234656203465463574236523478563283765
```

```
Input:
123456789
-123456789
*

Output:
123456789*-123456789
Result: -15241578750190521
```

```
Input:
0
+0
>=

Output:
0>=0
Result: 1
```

```
Input:
12434234
-

Output:
12434234
Result: -12434234
```

```
Input:
123456789
987654321
=

Output:
num1:123456789  num2:987654321
operation: num1 = num2
num1:987654321  num2:987654321
```