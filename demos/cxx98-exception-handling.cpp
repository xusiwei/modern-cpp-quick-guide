#include <exception> // for std::exception
#include <iostream>
#include <math.h>
#include <stdexcept> // for std::runtime_error
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string> // for std::string

using namespace std;

// user defined exception demo
struct Exception : public std::exception {
      public:
	Exception(std::string msg) : message_(msg) {}
	~Exception() throw() {} // no throw
	const char* what() { return message_.c_str(); }

      private:
	std::string message_;
};

double Sqrt(double x)
{
	if (x < 0.0) {
		cout << "x less than zero!\n";
		throw Exception("invalid value, x less than zero!");
	}
	return ::sqrt(x);
}

void test_exception()
{
	puts(__FUNCTION__);
	double x = 2.0, y = 0;
	try {
		y = Sqrt(x);
		cout << "sqrt of " << x << " is " << y << endl;
		x = -2.0;
		y = Sqrt(x);
		cout << "sqrt of " << x << " is " << y << endl;
	} catch (Exception& e) {
		cout << "exception raised: " << e.what() << endl;
	}
}

void throw_exception(int n)
{
	switch (n) {
	case 0:
		throw 0;
	case 1:
		throw "1";
	case 2:
		throw 2.0;
	case 3:
		throw std::string("3");
	case 4:
		throw std::exception();
	default:
		throw Exception("default");
	}
}

void test_catch_all()
{
	puts(__FUNCTION__);
	for (int i = 0; i < 6; i++) {
		try {
			throw_exception(i);
		} catch (Exception& e) {
			cout << "Exception: " << e.what() << endl;
		} catch (std::exception& e) {
			cout << "std::exception: " << e.what() << endl;
		} catch (std::string& s) {
			cout << "std::string: " << s << endl;
		} catch (const char* s) {
			cout << "const char*: " << s << endl;
		} catch (int i) {
			cout << "int: " << i << endl;
		} catch (...) { // catch all
			cout << "unkonw exception throwed" << endl;
		}
	}
}

void test_bad_alloc()
{
	puts(__FUNCTION__);
	for (uint64_t i = 0; i < 64; i++) {
		uint64_t sz = (1ull << i);
		try {
			char* ptr = new char[sz];
			cout << i << "\tnew char[" << sz << "] success!"
			     << endl;
			delete[] ptr;
		} catch (std::exception& e) {
			cout << "exception raised: " << e.what() << endl;
			// throw; // rethrow
			break;
		}
	}
}

void rethow_bad_alloc()
{
	try {
		new char[1uLL << 40];
	} catch (...) {
		throw;
	}
}

void test_rethrow()
{
	puts(__FUNCTION__);
	try {
		rethow_bad_alloc();
	} catch (std::bad_alloc& e) {
		cout << "exception throwed: " << e.what() << endl;
	}
}

// RTTI
void throw_bad_alloc(int n) throw(
    std::bad_alloc) // throw declaration, run crashed
{
	if (n % 2) {
		new char[1uLL << 40];
	}
	throw std::runtime_error("error"); // complie OK
}

void test_throw_declare()
{
	puts(__FUNCTION__);
	for (int i = 0; i < 2; i++) {
		try {
			throw_bad_alloc(i); // check at runtime
		} catch (std::exception& e) {
			cout << e.what() << endl;
		} catch (...) {
			cout << "unkonw exception throwed" << endl;
		}
	}
}

int main()
{
	test_exception();
	test_bad_alloc();
	test_catch_all();
	test_rethrow();

	test_throw_declare();

	return 0;
}
