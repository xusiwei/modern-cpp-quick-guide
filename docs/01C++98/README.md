# C++98 Review

language and library features review

---

## basic features

* basic types
* control follows
* composite types

---

## basic type

* `char`, `short`, `int`, `long`, `char*`, `void*`...
* `sizeof(long)`, `long long`, `"%lld"` ?
* limits of fundamental integral types(`<limits.h>`)
* characteristics of floating-point types(`<float.h>`)
* platform indepent int types(`<stdint.h>`) (C++11)

---

## control follows

* if/else
* swtich/case
	* break
* for/while/do-while
	* break
	* continue
* try/catch/throw
	* catch all, `catch(...)`
	* rethrow, `throw;`
	* no exception declaration, `throw()`

demo: [cxx98exception-handling.cpp](../../demos/cxx98-exception-handling.cpp)

---

## advanced features

* namespace
* constructor/destructor
* operator overloading
* object oriented programming(OOP)
* template and generic programming(GP)
* virtual and exception(RTTI)
