// single line comment

/*

multi-line comment

Program that multiples two numbers together
*/

#include <iostream> 
//input and output stream

#include <iomanip>
//input and output manipulator

using namespace std;
//std --> standard

int main()
{
//step 1: Create some variables (3)

double num1, num2, result;

//step 2: Put the numbers to use in the multiplication
//        into the variables

//num1 = 1.23;
cout << "Enter a number please. ";
cin >> num1;

//num2 = 6.7;
cout << "Enter another number please. ";
cin >> num2;

//step 3: Mutliply the numbers and save the product

result = num1 * num2;	//result = num2 * num1

//step 4: Display the product

cout << "The product is " << result; //cout is used for output("print" in C++)

return 0;
//number after 'return' statement does not matter
}
