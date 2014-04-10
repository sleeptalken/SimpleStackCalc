/* -------------------------------------------------------------------
SIMPLE STACK CALCULATOR

Author: William Christian
File: ssc.cc
Date: 03/19/2014
Class: CPSC5135U
Simple Stack Calculator is a Reverse Polish Notation Calculator
for rational numbers.
** -----------------------------------------------------------------*/
#include <iomanip>
#include <cstdlib>
#include <iostream>

using namespace std;

/* -------------------------------------------------------------------
Class Stack

Class Stack implements a stack with methods pop, push, top, empty,
full, and overloads operator <<.
** -----------------------------------------------------------------*/
template<class TYPE,int size>
class Stack {
	private:
		int stackIndexVar;
		TYPE data[size];
    public:
		Stack(void);
		void push(TYPE x);
		void pop();
		TYPE top();
		bool empty();
		bool full();
		int stackIndex();
		TYPE getData(int x);
		template<class Q,int size1>
		friend ostream& operator<<(ostream&, const Stack<Q,size1>&);	
};

/* -------------------------------------------------------------------

** -----------------------------------------------------------------*/
template<class TYPE,int size>
Stack<TYPE,size>::Stack(void) {
    int i;
    stackIndexVar = 0;
}

/* -------------------------------------------------------------------
Method push() is a method that takes a parameter with a certain type
and pushes it onto the stack, returning void.
** -----------------------------------------------------------------*/
template<class TYPE,int size>
void Stack<TYPE,size>::push(TYPE x) {
    if(full()) {
        return;
    }
	else {
		data[stackIndexVar++]=x;
    }
    return;
}

/* -------------------------------------------------------------------
Method top() is a method that takes no parameters and returns the data
at the top of the stack.
** -----------------------------------------------------------------*/
template<class TYPE,int size>
TYPE Stack<TYPE,size>::top() {
	int y = stackIndexVar - 1;
    return data[y];
}

/* -------------------------------------------------------------------
Method pop() is a method that takes no parameters and removes the data
on the top of the stack, returning void.
** -----------------------------------------------------------------*/
template<class TYPE,int size>
void Stack<TYPE,size>::pop() {
	if(empty()) {
    }
	else {
		data[--stackIndexVar];
	}
}

/* -------------------------------------------------------------------
Method empty() is a method that takes no parameters and returns true 
if the stack index is 0, false if not. Basically, it will return true 
if the stack is empty, false if it is not.
** -----------------------------------------------------------------*/
template<class TYPE,int size>
bool Stack<TYPE,size>::empty() {
	if(stackIndexVar<=0) {
        return true;
    }
	else {
		return false;
	}
}

/* -------------------------------------------------------------------
Method full() is a method that takes no parameters and returns true if 
the stack index is equal to the size, false if not. Basically, it will
return true if the stack is full, false if it is not.
** -----------------------------------------------------------------*/
template<class TYPE,int size>
bool Stack<TYPE,size>::full() {
	if(stackIndexVar>=size) {
        return true;
    }
	else {
		return false;
	}
}

/* -------------------------------------------------------------------
Method stackIndex() is a method that takes no parameters and returns
the stack index. This is needed to access the private variable
stackIndexVar.
** -----------------------------------------------------------------*/
template<class TYPE,int size>
int Stack<TYPE,size>::stackIndex() {
	return stackIndexVar;
}

/* -------------------------------------------------------------------
Method getData() is a method that passes x and returns the data at that
index in the stack.
** -----------------------------------------------------------------*/
template<class TYPE,int size>
TYPE Stack<TYPE,size>::getData(int x) {
	return data[x];
}

/* -------------------------------------------------------------------
This "method" overloads the ostream operator to return all of the
data in the stack separated by a newline character
** -----------------------------------------------------------------*/
template<class TYPE,int size>
ostream& operator<<(ostream& os, const Stack<TYPE,size>& s) {
	for(int i=(s.stackIndexVar - 1); i >= 0; i--) {
		os << s.data[i] << "\n";
	}
}

/* -------------------------------------------------------------------
Class RationalNumber is a class that overloads +, -, *, /, <, <=, >, >=,
==, !=, <<, and >> operators to invoke them specifically on a rational
number, defined with a numerator and a denominator.
** -----------------------------------------------------------------*/
class RationalNumber {
	public:
		RationalNumber();
		RationalNumber(int numerator, int denominator = 1);
		friend RationalNumber operator+(const RationalNumber&,const RationalNumber&);
		friend RationalNumber operator-(const RationalNumber&,const RationalNumber&);
		friend RationalNumber operator*(const RationalNumber&,const RationalNumber&);
		friend RationalNumber operator/(const RationalNumber&,const RationalNumber&);
		friend bool operator<(const RationalNumber&,const RationalNumber&);
		friend bool operator<=(const RationalNumber&,const RationalNumber&);
		friend bool operator>(const RationalNumber&,const RationalNumber&);
		friend bool operator>=(const RationalNumber&,const RationalNumber&);
		friend bool operator==(const RationalNumber&,const RationalNumber&);
		friend bool operator!=(const RationalNumber&,const RationalNumber&);
		friend ostream& operator <<(ostream&,const RationalNumber&); 
		friend istream& operator >>(istream&,RationalNumber&);
	
		int n;
		int d;
};

/* -------------------------------------------------------------------
Initializes a stack called myStack of type RationalNumber and size 32 
as per instructions
** -----------------------------------------------------------------*/
Stack<RationalNumber,32> myStack;

void normalize(int &n, int &d);

RationalNumber::RationalNumber(int numer, int denom) {
	normalize(numer, denom);
	n = numer;
	d = denom;
}

RationalNumber::RationalNumber():n(), d(1){}

/* -------------------------------------------------------------------
Overloads the + operator and passes two RationalNumbers: the numerator
and denominator. The operator will now replace the top two entries of
the stack with their sum.
** -----------------------------------------------------------------*/
RationalNumber operator +(const RationalNumber& locaNumer, const RationalNumber& localNum) {
	int numer = locaNumer.n * localNum.d + locaNumer.d * localNum.n;
	int denom = locaNumer.d * localNum.d;
	normalize(numer, denom);
	RationalNumber local(numer, denom);
	myStack.pop();
	myStack.pop();
	myStack.push(local);
	return myStack.top();
}

/* -------------------------------------------------------------------
Overloads the - operator and passes two RationalNumbers: the numerator
and denominator. The operator will now take the top entry and subtract
it from the next item down and the top two stack entries will be
replaced with the result.
** -----------------------------------------------------------------*/
RationalNumber operator -(const RationalNumber& locaNumer, const RationalNumber& localNum) {
	int numer = locaNumer.n * localNum.d - locaNumer.d * localNum.n;
	int denom = locaNumer.d * localNum.d;
	normalize(numer, denom);
	RationalNumber local (numer, denom);
	myStack.pop();
	myStack.pop();
	myStack.push(local);
	return myStack.top();
}

/* -------------------------------------------------------------------
Overloads the * operator and passes two RationalNumbers: the numerator
and denominator. The operator will now replace the top two entries of
the stack with their product.
** -----------------------------------------------------------------*/
RationalNumber operator *(const RationalNumber& locaNumer,const RationalNumber& localNum) {
	RationalNumber product;
	int numer = locaNumer.n * localNum.n;
	int denom = locaNumer.d * localNum.d;
	normalize(numer, denom);
	product = RationalNumber(numer, denom);
	myStack.pop();
	myStack.pop();
	myStack.push(product);
	return myStack.top();
}

/* -------------------------------------------------------------------
Overloads the / operator and passes two RationalNumbers: the numerator
and denominator. The operator will now replace the top two entries of
the stack with their quotient.
** -----------------------------------------------------------------*/
RationalNumber operator/(const RationalNumber& locaNumer,const RationalNumber& localNum) {
	RationalNumber quotient;
	int numer = locaNumer.n * localNum.d;
	int denom = locaNumer.d * localNum.n;
	normalize(numer, denom);
	quotient = RationalNumber(numer, denom);
	myStack.pop();
	myStack.pop();
	myStack.push(quotient);
	return myStack.top();
}

/* -------------------------------------------------------------------
Overloads the >> operator and sets the instream to the localNum 
parameter.
** -----------------------------------------------------------------*/
istream& operator >>(istream& in, RationalNumber& localNum) {
	char ch;
	in >> localNum.n;
}

/* -------------------------------------------------------------------
Overloads the << operator and sets the ostream to the localnum parameter
if the denominator is equal to 1. If not, it will put a '/' between the
numerator and denominator.
** -----------------------------------------------------------------*/
ostream& operator <<(ostream& out,const RationalNumber& localNum) { 
	if(localNum.d == 1) 
	{
		out << localNum.n;
	}
	else
	{
		out << localNum.n << '/' << localNum.d;
	}
}

/* -------------------------------------------------------------------
Overloads the < operator and returns the comparison between the 
1st numerator/denominator parameter and the 2nd numerator/denominator.
** -----------------------------------------------------------------*/
bool operator <(const RationalNumber& locaNumer,const RationalNumber& localNum) { 
	return locaNumer.n * localNum.d < localNum.n * locaNumer.d;
}

/* -------------------------------------------------------------------
Overloads the <= operator and returns the comparison between the 
1st numerator/denominator parameter and the 2nd numerator/denominator.
** -----------------------------------------------------------------*/
bool operator <=(const RationalNumber& locaNumer, const RationalNumber& localNum) { 
	return locaNumer.n * localNum.d <= localNum.n * locaNumer.d;
}

/* -------------------------------------------------------------------
Overloads the > operator and returns the comparison between the 
1st numerator/denominator parameter and the 2nd numerator/denominator.
** -----------------------------------------------------------------*/
bool operator >(const RationalNumber& locaNumer, const RationalNumber& localNum) { 
	return locaNumer.n * localNum.d > localNum.n * locaNumer.d;
}

/* -------------------------------------------------------------------
Overloads the >= operator and returns the comparison between the 
1st numerator/denominator parameter and the 2nd numerator/denominator.
** -----------------------------------------------------------------*/
bool operator >=(const RationalNumber& locaNumer, const RationalNumber& localNum) { 
	return locaNumer.n * localNum.d >= localNum.n * locaNumer.d;
}

/* -------------------------------------------------------------------
Overloads the == operator and returns the comparison between the 
1st numerator/denominator parameter and the 2nd numerator/denominator.
** -----------------------------------------------------------------*/
bool operator ==(const RationalNumber& locaNumer, const RationalNumber& localNum) { 
	return locaNumer.n * localNum.d == localNum.n * locaNumer.d;
}

/* -------------------------------------------------------------------
Overloads the != operator and returns the comparison between the 
1st numerator/denominator parameter and the 2nd numerator/denominator.
** -----------------------------------------------------------------*/
bool operator !=(const RationalNumber& locaNumer, const RationalNumber& localNum) { 
	return locaNumer.n * localNum.d != localNum.n * locaNumer.d;
}

/* -------------------------------------------------------------------
Method normalize is a method that takes two integer parameters and 
simplifies them and deciphers if the denominator is equal to 0.
** -----------------------------------------------------------------*/
void normalize(int& n, int& d) {
	if (d == 0) {
		d = 1;
	}
	int largest; 
	largest = n > d ? n : d;
	int gcd = 0;

	for ( int loop = 2; loop <= largest; loop++ )

	if ( n % loop == 0 && d % loop == 0 ) {
		gcd = loop;
	}

	if (gcd != 0) {
		n /= gcd;
		d /= gcd;
	}

} 

/* -------------------------------------------------------------------
The main method runs a while loop that continually allows the user to
feed in numbers and operators. It tests for negatives in numerator or
denominator or both, denominator or numerator of 0, attempt to
divide by 0, and any attempt to manipulate an empty or full stack.
** -----------------------------------------------------------------*/

int main() {
/* -------------------------------------------------------------------
Instantiation of all methods needed for main()
** -----------------------------------------------------------------*/
	bool running = true;
	RationalNumber number, x, q, r;
	char myOperator;
	string myInput = "";
	int checker = 0;
/* -------------------------------------------------------------------
The while loop continually feeds the user input into a initialized
string. If the length of the string is greater than 1, than that means
there is more than just an 'operator' and will cycle through the string
via for loop and at() functions and find out if the user has input a 
fraction. If so, it will set a mySwitch variable to 1 for later use.
** -----------------------------------------------------------------*/
	while(running) {
		int fracLength = 0;
		int checker = 0;
		int newNumer = 0;
		int newDenom = 0;
		int mySwitch = 0;
		cin >> myInput;
		myOperator = myInput.at(0);
		if(myInput.length() > 1) {
			for(int i = 0; i <= (myInput.length() - 1); i++)
			{
				if(myInput.at(i) == '/')
				{
					mySwitch = 1;
					break;
				}
				fracLength++;
			}
		}
		
/* -------------------------------------------------------------------
If the user inputs a fraction then it will test if the numerator is 
negative by checking if the index at 0 is equal to '-'. If so, it will
cast the input substring from 0 to fracLength by using the .c_str() 
and atoi(), then multiply that outcome by -1 to account for the 
negative input. The same idea is used if the denominator is negative.
** -----------------------------------------------------------------*/
		if(mySwitch == 1) {
			if(myInput.at(0) == '-') {
				newNumer = atoi(myInput.substr(0,fracLength).c_str()) * -1;
				newNumer = newNumer * -1;
				fracLength++;
				myOperator = myInput.at(1);
				checker++;
			}
			else {
				newNumer = atoi(myInput.substr(0,fracLength).c_str());
				fracLength++;
			}
			if(myInput.at(fracLength) == '-') {
				newDenom = atoi(myInput.substr(fracLength,myInput.length()-1).c_str());
				newDenom = newDenom * -1;
				newNumer = newNumer * -1;
				checker++;
			}
			else {
				newDenom = atoi(myInput.substr(fracLength,myInput.length()-1).c_str());
			}
			if(checker == 2) {
				number.n = newNumer;
				number.d = newDenom;
			}
			else {
				number.n = newNumer;
				number.d = newDenom;
				mySwitch = 2;
			}
		}
		else
		{
			if(myInput.length() > 1) {
				if(myInput.at(0) == '-') {
					newNumer = atoi(myInput.c_str()) * -1;
					newNumer = newNumer * -1;
					myOperator = myInput.at(1);
				}
				else {
					newNumer = atoi(myInput.c_str());
				}
				number.n = newNumer;
				number.d = 1;
			}
			else {
				number = atoi(myInput.c_str());
			}
		}
		
/* -------------------------------------------------------------------
This long set of switch statements checks the first index of the input
and deciphers if it is equal to different cases for the different
operations. All the operations check for error exceptions as stated
in the comments section of the class declaration.

Please refer to this chart to decide what the operations do:
OPERATION       PURPOSE
p				Prints the current top entry on the stack (but leaves 
				it on the stack).
P				Pops the stack.
f				Prints the entire stack starting with the top entry 
				(useful for debugging).
c				Pops all items off the stack (i.e., clears the stack).
d				Duplicates the top entry on the stack.
r				Reverses the top two entries on the stack.
+				Replaces the top 2 entries with their sum.
-				The top entry is subtracted from the next item down 
				and the top two 
				stack entries replaced with the result.
*				Replaces the top 2 entries with their product.
/				The top entry is divided into the next item down 
				and the top two stack entries replaced with the result.
** -----------------------------------------------------------------*/
		switch(myOperator) {
			case '+':
				if(myStack.stackIndex() < 2) {
					cout << "StackUnderflow: Attempt to manipulate items from a stack without at least 2 numbers.\n";
					break;
				}
				else {
					x = myStack.getData(myStack.stackIndex() - 2) + myStack.getData(myStack.stackIndex() - 1);
					break;
				}
			case '-':
				if(myStack.stackIndex() < 2) {
					cout << "StackUnderflow: Attempt to manipulate items from a stack without at least 2 numbers.\n";
					break;
				}
				else {
					x = myStack.getData(myStack.stackIndex() - 2) - myStack.getData(myStack.stackIndex() - 1);
					break;
				}
			case '*':
				if(myStack.stackIndex() < 2) {
					cout << "StackUnderflow: Attempt to manipulate items from a stack without at least 2 numbers.\n";
					break;
				}
				else {
					x = myStack.getData(myStack.stackIndex() - 2) * myStack.getData(myStack.stackIndex() - 1);
					break;
				}
			case '/':
				if(myStack.stackIndex() < 2) {
					cout << "StackUnderflow: Attempt to manipulate items from a stack without at least 2 numbers.\n";
					break;
				}
				else {
					if(myStack.getData(myStack.stackIndex() - 2) == 0) {
						cout << "DivisionByZero: Attempt to divide a number by 0\n";
						break;
					}
					else if(myStack.getData(myStack.stackIndex() - 1) == 0) {
						x = 0 / myStack.getData(myStack.stackIndex() - 1);
						break;
					}
					else {
						x = myStack.getData(myStack.stackIndex() - 2) / myStack.getData(myStack.stackIndex() - 1);
						break;
					}
				}
			case 'p':
				if(myStack.empty()) {
					cout << "StackUnderflow: The stack is empty.\n";
					break;
				}
				else {
					cout << myStack.top() << "\n";
					break;
				}
			case 'P':
				if(myStack.empty()) {
					cout << "StackUnderflow: Attempt to pop items from an empty stack.\n";
					break;
				}
				else {
					myStack.pop();
					break;
				}
			case 'f':
				if(myStack.empty()) {
					cout << "StackUnderflow: Attempt to print items from an empty stack.\n";
					break;
				}
				else {
					cout << myStack;
					break;
				}
			case 'c':
				if(myStack.empty()) {
					cout << "StackUnderflow: Attempt to clear items from an already empty stack.\n";
					break;
				}
				else {
					for(int i=myStack.stackIndex(); i >= 0; i--) {
						myStack.pop();
					}
					break;
				}
			case 'd':
				myStack.push(myStack.top());
				break;
			case 'r':
				if(myStack.empty()) {
					cout << "StackUnderflow: Attempt to reverse items from an empty stack.\n";
					break;
				}
				else {
					q = myStack.top();
					myStack.pop();
					r = myStack.top();
					myStack.pop();
					myStack.push(q);
					myStack.push(r);
					break;
				}
			//USEFUL FOR EXITING THE WHILE LOOP WHILE TESTING!!!!!
			/*case '.':
				running = false;
				break;*/
			default:
				if(number.d == 0) {
					cout << "UndefinedRational: Denominator of input 0.\n";
					break;
				}
				else {
					if(myStack.stackIndex() >= 32) {
						cout << "StackOverflow: Attempt to push more items onto the stack than it can hold.\n";
						break;
					}
					else {
						myStack.push(number);
						break;
					}
				}
		}
	}
	return 0;
}