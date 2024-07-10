# table of contents  <!-- omit from toc -->
- [introduction](#introduction)
- [object oriented programming](#object-oriented-programming)
- [file \& string stream](#file--string-stream)
- [memory](#memory)
- [pointers](#pointers)
- [templates](#templates)
- [exceptions](#exceptions)
- [misc](#misc)
- [STL](#stl)
- [containers](#containers)

# links  <!-- omit from toc -->
- [[lectures] modern C++](https://www.ipb.uni-bonn.de/teaching/modern-cpp/)
- [compiler explorer](https://godbolt.org/)
- [spiral rule](https://riptutorial.com/c/example/18833/using-the-right-left-or-spiral-rule-to-decipher-c-declaration)
- [bit manipulation](https://www.hackerearth.com/practice/basic-programming/bit-manipulation/basics-of-bit-manipulation/tutorial/)
- [why avoid `goto`](https://smartbear.com/blog/goto-still-has-a-place-in-modern-programming-no-re/)
- [`++i` vs `i++`](https://stackoverflow.com/questions/24901/is-there-a-performance-difference-between-i-and-i-in-c)
- [why `emplace_back`](https://stackoverflow.com/questions/43596430/push-back-vs-emplace-back-to-a-stdvectorstdstring)
- [`std::move` for primitives](https://stackoverflow.com/questions/27888873/copy-vs-stdmove-for-ints)
- [`std::move` without assignment](https://stackoverflow.com/questions/62642804/what-happens-when-stdmove-is-called-without-assignment)
- [why `virtual` (early vs late binding)](https://stackoverflow.com/questions/2391679/why-do-we-need-virtual-functions-in-c)
- [why `override`](https://stackoverflow.com/questions/18198314/what-is-the-override-keyword-in-c-used-for)
- [mixing `signed` & `unsigned`](https://stackoverflow.com/questions/19446888/adding-signed-and-unsigned-int)
- [IEEE754 conversion](https://www.youtube.com/watch?v=8afbTaA-gOQ&pp=ygUIaWVlZSA3NTQ%3D)
- [storage specifiers, linkage, storage duration](https://en.cppreference.com/w/cpp/language/storage_duration)
- [2D pointer](https://c-faq.com/aryptr/dynmuldimary.html)

# todo  <!-- omit from toc -->
- [cpp core guidelines](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#main)
- [lost art of struct packing](http://www.catb.org/esr/structure-packing/)
- [memory order](https://en.cppreference.com/w/c/atomic/memory_order)
- [mix C & C++](https://isocpp.org/wiki/faq/mixing-c-and-cpp#:~:text=Just%20declare%20the%20C%20function,int)
- [structure packing](http://www.catb.org/esr/structure-packing/)
- [efficient c++](https://embeddedgurus.com/stack-overflow/category/efficient-cc/)
- template uses
- STL
- OOPs concepts
- [MSVC init memory](https://stackoverflow.com/questions/127386/what-are-the-debug-memory-fill-patterns-in-visual-studio-c-and-windows)
- atomics & memory ordering
- [templates FAQ](https://isocpp.org/wiki/faq/templates)
- why static initialized to 0
- double pointer access
- stack canary
- [copy-and-swap idiom](https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom) ([video](https://www.youtube.com/watch?v=7LxepUEcXA4))
- friend functions
- [zero overhead principle](https://github.com/baderouaich/the-zero-overhead-principle)
- [embedded C questions](https://rmbconsulting.us/publications/a-c-test-the-0x10-best-questions-for-would-be-embedded-programmers/)

# introduction
- *within C++ there is a much smaller & cleaner language struggling to get out*
- **standard I/O channels:** are preconnected input & output communication channels between a computer program and its environment when it begins execution  
one input channel: standard input `cin` and two output channels: standard output (`cout`) & standard error (`cerr`)  
`stdin`, `stdout` & `stderr` streams are identified by the file descriptors 0, 1 & 2 in linux
  ```cpp
  // C++
  std::cout << "out log" << std::endl;  // endl: endline

  // C
  fprintf(stderr, "error log");
  ```
- **command line arguments:** to pass arguments define `main()` to receive number of arguments (`int argc`) & list of arguments (`char const *argv[]`)
  ```cpp
  // ./exe_main command line arguments

  int main(int argc, char const *argv[])
  {
      // argc == 4
      // argv[] == {"exe_main", "command", "line", "arguments"}
  }
  ```
- **compilation process:** transforms a human-readable code into a machine-readable format  
![](./media/cplusplus/compilation_stages.png)
  - **preprocessor:** all statements beginning with `#` are processed  
  tasks include comments removal, file inclusion, macros expansion & conditional expansion
  - **compiler:** converts pre-processed intermediate file (`*.i`) into an assembly file (`*.s`) having low-level assembly instructions
  - **assembler:** converts assembly code into machine-readable object (binary/hex) code (`*.o`)
  - **linker:** combines the object files with other necessary libraries & modules (object files) to create an executable file (`*.exe/*.out`)  
  ensures that necessary functions & variables referenced from different modules are correctly connected
- **example: GCC compiler flags:** MSVC flags are similar but instead of `-` uses `/`
  ```sh
  -std=c++11        # set C++ standard
  -Wall             # all warnings
  -Wextra           # extra warnings
  -Werror           # treat warnings as errors
  -O<n>             # optimize for speed
  -Os               # optimize for size
  -Og               # optimize for debuggability
  -ftree-vectorize  # auto vectorization
  -g<n>             # keep debugging symbols
  -pg               # extra profile information (used for gprof)
  -l                # library name
  -L                # library search path
  -I                # include search path
  -D<flag>=<value>  # add preprocessor flag (with value if required)
  -fPIC             # position independent code (suitable for inclusion in shared libs)
                    # example: jumps will be relative instead of absolute
  -c                # compile but don't link
  -save-temps       # save intermediate source files
  ```
- **preprocessor:**
  ```cpp
  #pragma once    // include file only once

  __DATE__        // May 16 2022
  __TIME__        // 09:42:38
  __FILE__        // C:\workspace\code\src\main.cpp
  __LINE__        // 23

  #error message  // preproc error
  ```
  continuation (`\`), stringize (`#`) & token pasting (`#`) operators
  ```cpp
  #define macroFunc(a, b) printf("val"#a " : %d, val"#b " : %d\n", \
                                val#a, val#b)

  int main(void)
  {
      int val1 = 40;
      int val2 = 30;
      macroFunc(2, 1);  // val2 : 30, val1 : 40
      return 0;
  }
  ```
  **variadic macros:** all the tokens in the argument list after the last named argument will replace the identifier `__VA_ARGS__` in the macro body wherever it appears
  ```cpp
  #define PRINT(str, ...) \
    printf(str "\n", __VA_ARGS__);  // append new line to format string then place arguments
  ```
- **declaration:** introduces an identifier and describes its type, this is what the compiler needs to accept references to that identifier  
**definition:** actually instantiates/implements this identifier, this is what the linker needs in order to link references to those entities
  ```cpp
  // declaration
  extern int bar;
  extern int g(int, int);
  double f(int, double);
  class foo;

  // definition
  int bar;
  int g(int lhs, int rhs) { return lhs * rhs; }
  double f(int i, double d) { return i + d; }
  class foo
  {
  };
  ```
- **variable shadowing:** a variable declared in some specific scope takes precedence over a variable with the same name declared in an outer scope
- **`auto`:** is a placeholder type that will be replaced later by the compiler  
for a variable placeholder replaced typically by deduction from an initializer
  ```cpp
  auto var = 13;     // int
  auto var = 13.0f;  // float
  auto var = 13.0;   // double

  auto a = 0, b = 3.14;  // error: inconsistent types for a and b
  ```
- **reference:** is an alias (alternative name) for an existing variable declared using `&`  
whatever happens to a reference happens to variable & vice-versa, yields performance gain as references avoid copying data
- **`++i` vs `i++`:** post-increment could be slower since a copy of the old value copy needs to be saved for later use  
but modern compilers will optimize it if `i` is a primitive data type (like `int`)  
if `i` is  a class then temp will involve calling a copy ctor which can be expensive
- **bitwise operators:** variants of AND (`&&`), OR (`||`) & NOT (`!`)
  ```
  A      = 0011 1100
  B      = 0000 1101
  -----------------
  A & B  = 0000 1100  AND
  A | B  = 0011 1101  OR
  A ^ B  = 0011 0001  XOR
  ~A     = 1100 0011  NOT
  A << 2 = 1111 0000  RSH
  A >> 2 = 0000 1111  LSH
  ```
- **example: XOR number swap:**
  ```cpp
  x = x ^ y;  // x == x ^ y
  y = x ^ y;  // y == (x ^ y) ^ y ⟶ (y ^ y) ^ x ⟶ 0 ^ x ⟶ x
  x = x ^ y;  // x == (x ^ y) ^ x ⟶ (x ^ x) ^ y ⟶ 0 ^ y ⟶ y
  ```
- **example: bit manipulation:**
  ```cpp
  #define setBit(num, idx)   (num |= (0x1 << idx))
  #define clearBit(num, idx) (num &= ~(0x1 << idx))
  #define flipBit(num, idx)  (num ^= (0x1 << idx))
  ```
- **example: check power of 2:** power-of-2 will have only one bit set and if one is subtracted all lower bits will be set then bitwise AND of these two should result in zero
  ```cpp
  // first part to check if number is zero
  return (x && !(x & (x - 1)));
  ```
- **example: count number of ones:** `n & (n-1)` will remove least significant 1 per iteration
  ```cpp
  while (n)  // run till n equals 0
  {
      n = n & (n - 1);
      count++;          
  }

  // n = 1010
  // 1010 & 1001 ⟶ 1000  second place 1 removed
  // 1000 & 0001 ⟶ 0     fourth place 1 removed
  ```
- use `for` when number of iterations are known else use `while` loop, it easy to form an infinite loop with `while`
- **ranged for loop:** more readable `for` loop for iterating over standard containers (using iterators internally)  
avoids mistakes with indices since container iterator used
  ```cpp
  std::vector<int> vec{0, 1, 5};

  // for (const type& value : container)
  for (const int& n : vec)  // for (int n : vec) if you want to modify
  {
      std::cout << n << " ";  // 0 1 5
  }
  ```
- **`break`:** exit enclosing loop  
**`continue`:** skip to next loop iteration
  ```cpp
  do
  {
      ...
      break;  // break without returning
      ...
  } while (0)
  ...
  return 0;
  ```
- **`goto`:** don't use it unless you want to break out of some complex code without returning because you need to run some cleanup code  
a good rule-of-thumb is to only jump forward & to the end of a block
  ```cpp
  int foo()
  {
      for (int i = 0; i < 100; i++)
      {
          for (int j = 0; j < 100; j++)
          {
              if (i * j > 1000)
              {
                  goto done;  // break out of both loops
              }
          }
      }

  done:
      cleanup();

      return 0;
  }
  ```
- **function overloading:** two or more functions can have the same name but with different parameters  
picked at compile-time based on arguments (return type plays no role)
  ```cpp
  void printSum(int a, int b);
  void printSum(double a, double b);
  ```
- **name mangling:** encoding of function/variable names so linker can separate common names due to overloading/namespaces  
  use `extern "C" { .... }` in C++ when declaring a function that was implemented/compiled in C (name mangling not done)
- **function argument passing:** use pass-by-reference (pointer or reference) to prevent copying of large objects, use `const` reference in function declaration to prevent modification as well  
![](./media/cplusplus/pass_by_reference_vs_value.gif)
- **default argument:** is a value provided in a function declaration (after mandatory arguments) that is automatically assigned by the compiler if the calling function doesn’t provide a value
  ```cpp
  int printSum(int a, int b, int c = 0, int d = 0);
  ```
- **`namespace`:** is a declarative region that provides a scope to the identifiers inside it, used to organize code into logical groups and to prevent name collisions, all identifiers at namespace scope are visible to one another without qualification  
don't add `using namespace std;` or `using std::cout;` in headers  
example: if client code has his own `cout` implementation this can lead to wrong function during overload (especially if arguments match)
- **library:** is a collection of pre-compiled code that can be re-used by programs
  - **static:** is linked directly into the final executable, fast but takes lot of space (`*.a` archive)
    ```sh
    ar rcs lib.a module1.o module2.o
    # rcs: replace, create, sort
    # c: create library
    # r: replace old files within library (if already exists)
    # s: create sorted index of library
    ```
  - **dynamic:** is linked but exists as a separate file that will be loaded at run-time, slower but can be copied (`*.so` shared object)
    ```sh
    gcc -c -fPIC main.c -o main.o
    gcc -shared main.o -o libmain.so
    ```

# object oriented programming
- **object oriented programming:** bind together the data and the functions that operate on them so that no other part of the code can access this data except that function

## encapsulation
- **encapsulation:** binding together the data and the functions that manipulate them  
- **`class`:** is a user-defined data type which holds its own data & function members which can be accessed by creating an instance of that class (object), class is like a blueprint for an object  
use `this` as pointer to current object in class member functions  
pass arguments to parametrized ctor to help initialize the object, if ctor/dtor not defined explicitly then default ones (with no arguments) will be generated  
avoid setters instead set data in ctor
  ```cpp
  class someClass
  {
    public:
      someClass() {}   // constructor (ctor), atleast one, called upon object creation
      ~someClass() {}  // destructor (dtor), exactly one, called upon object destruction

      someClass(int a, int b) : num_a_(a), num_b_(b) {}  // member initializer list
      bool operator<(const someClass &other) {}          // operator overload (no space after operator keyword)
      someFunc() const {}                                // const correctness
      someFunc() {}                                      // function overload because const missing
                                                         // but const object reference will call const one
      static void someStaticFunc() {}                    // static member function
      static int some_num;                               // static member variable
      static int getNumA(){};                            // getter/accessor (setter/mutator)

    private:  // default access specifier
      int num_a_ = 0;
      int num_b_ = 0;

      friend class anotherClass;                // friend class
  };
  ```
- **class access specifiers/modifiers:** defines how the members (variables & functions/methods) of a class can be accessed
  - **`public`:** accessible outside the class
  - **`private`:** inaccessible outside the class
  - **`protected`:** inaccessible outside the class but can be accessed in inherited classes
- **why private default:** *it's better to be properly encapsulated and only open up the things that are needed, as opposed to having everything open by default and having to close it*  
keep data members hidden (private), user should be able to modify data only through provided public interfaces (functions)
- **resource acquisition is initialization (RAII):** resource acquisition (allocation) is done by the ctor while resource release (deallocation) is done by the dtor, holding a resource should be class-invariant and tied to object lifetime  
also known as scope-bound resource management
  ```cpp
  class someClass
  {
    public:
      someClass() { data_ = new someOtherClass; }
      ~someClass()
      {
          delete data_;
          data_ = nullptr;
      }

    private:
      someOtherClass data_;  // default copy ctor will just copy this pointer (shallow copy)
                             // so rule of all or nothing
  };
  ```
- **member initializer list:** to initialize members that cannot be set in body (like `const`) or to call non-default ctor for object members  
const members will be created by the time we reach the scope of the ctor(`{`)
  ```cpp
  class A
  {
    public:
      A() { x = 0; }
      A(int x_) { x = x_; }
      int x;
  };

  class B
  {
    public:
      B() { a.x = 3; }  // A() called first (initialization) then x set (assignment), easier to call a(3) directly
                        // what if default ctor allocated memory or opened files that you don't need
    private:
      A a;
  };
  ```
- **operator overloading:** provides the operator with a special meaning for a data type (like class), compile-time polymorphism (similar to function overloading)  
example: overload `+` operator in string class so that we can concatenate two strings by just using `+`  
example: overload arithmetic operators for complex numbers  
example: implement `<` operator to sort user defined aggregate types using `std::sort`
- **const correctness:** prevent const objects from getting mutated  
a const member function cannot modify the object (else compiler error), declare getters as const functions  
also helps compiler generate more efficient code since it knows the full intent and use of the variable/function
- **`static` variable:** exists once per class (not per object) and shared across all (base & derived class) objects, data allocated in class not in instances so more like a global variable  
**`static` function:** doesn't need an object to call, pass object if you need to access private members  
both are only declared in class declaration so must be explicitly defined outside the class (in source file) using the scope resolution operator (`::`)  
example: count number of objects of a class
  ```cpp
  // header file declaration
  class someClass
  {
    public:
      someClass() { someClass::numInstances++; }
      ~someClass() { someClass::numInstances--; }
      static int numInstances;
      static void printInstances(void);
  };

  // source file definition
  int someClass::numInstances = 0;

  void someClass::printInstances(void)
  {
      std::cout << someClass::numInstances << std::endl;
  }

  // source file usage
  int main()
  {
      someClass a;
      someClass::printInstances();  // 1

      {
          someClass b;
          someClass::printInstances();  // 2
      }

      someClass::printInstances();  // 1

      return 0;
  }
  ```
- **`friend` class:** can access private and protected members of other classes in which it is declared as a friend  
used when you don't want to expose getter/setters to everyone but just to a single class permitting the encapsulation to be wider than own class (private members) or derived class (protected members)  
  ```cpp
  class classB;  // forward declaration 

  class classA
  {
      friend class classB;  // error without forward declaration (classB undefined)

    private:
      int foo_;
  };

  class classB
  {
      int add(classA &a, classB &b) { return a.foo_ + b.bla_; }  // access classA private member

    private:
      int bla_;
  };
  ```
- **`struct`:** is a `class` where members are `public` by default (default `private` in class), use it as a simple data container  
**padding:** adds some empty bytes of memory to aligns members to natural (processor word size) address boundaries  
example: for accessing an entire word in a single cycle 32 bit processor's memory will be split into 4 banks  
if a struct has three `char`s followed by an `int` then without padding `int` would be split into two rows of the banks and processor needs 2 cycles to read it  
![](./media/cplusplus/padding_example.png)  
padding of larger structs also eliminates false sharing by putting each structure on its own cache line  
**packing:** prevent padding (`#pragma pack`), used when CPUs of different architecture need to access the same structure in memory or binary dump  
**bitfields:** specify the size (in bits) of the structure/union members, pointer is not possible since member sizes are (typically) smaller than granularity allowed by pointers (byte addressable)  
used to map hardware registers exposed to memory bit-by-bit
  ```cpp
  typedef struct
  {
      uint8_t a : 4;
      uint8_t b : 4;
  } two_nibbles;

  two_nibbles temp;
  temp.a = 5;
  temp.b = 17;
  printf("%u %u %u\n", sizeof(temp), temp.a, temp.b);    // 1 5 1 (b overflowed)
  ```
- **uniform initialization:** allows usage of a consistent syntax to initialize variables/objects ranging from primitive (built-in) types to aggregates (made up of primitives) by using `{}` to enclose initializer values  
doesn't allow narrowing as well `int i{1.2};` (throws error/warning) so can be used in member initializer list for argument type checking
  ```cpp
  int i;                  // uninitialized built-in type
  int j = 10;             // initialized built-in type
  int k(10);              // initialized built-in type
  int a[] = {1, 2, 3, 4}  // aggregate initialization
  someClass x1;           // default ctor
  someClass x2(1);        // parameterized ctor
  someClass x3 = 3;       // parameterized ctor with single argument
  someClass x4 = x3;      // copy ctor

  // uniform initialization
  int i{};             // initialized built-in type, equals to int i{0};
  int j{10};           // initialized built-in type
  int a[]{1, 2, 3, 4}  // aggregate initialization
  someClass x1{};      // default ctor
  someClass x2{1};     // parameterized ctor;
  someClass x4{x3};    // copy-ctor
  ```
  **braced initialization:** it isn't always necessary to define a ctor for a simple class/struct so objects can be initialized using uniform initialization
  ```cpp
  struct classA
  {
      int station_id;
      time_t time_set;
      double current_temp;
  };

  time_t time_to_set;
  classA cla{45978, time(&time_to_set), 28.9};  // member initialization in order of declaration
                                                // an empty brace initializer does value initialization = {0,0,0}
  ```
- **move semantics:** every expression is a lvalue (occupies memory so can be written on left of `=`) or a rvalue (everything else, explicitly defined using `&&`)  
rvalues denote temporary objects which are destroyed at the next semicolon  
**`std::move`:** converts lvalue to rvalue by moving resources (transferring ownership) from one object to another (instead of copying them) so don't access an already moved variable (undefined by cpp standard)
  ```cpp
    int a;                      // a lvalue
    int &a_ref = a;             // a_ref lvalue
    a          = 2 + 2;         // 2 + 2 rvalue
    int b      = a + 2;         // a + 2 rvalue
    int &&c    = std::move(a);  // c rvalue
  ```
  internally `std::move` doesn't move the passed object by itself, it consists of a cast whose result is used by move assignment operator  
  example: `s` casted to rvalue reference (`std::string &&`) but that result is unused so the object is not actually moved
  ```
  std::string s = "Moving";
  std::move(s);
  ```
  for primitive types move is implemented as a copy, for aggregates performance will be better than copying but worse than passing by reference  
  for a vector move is just equivalent to assigning some internal pointers
  ```cpp
  std::vector<std::string> vec;
  std::string str = "hello";      // temp variable
  vec.push_back(str);             // copy
  vec.push_back(std::move(str));  // move

  std::cout << str << std::endl;  // undefined, prints empty string in MSVC
  ```
- **copy ctor & assignment operator:** ctor called automatically when the object is copied and assignment operator when the object is assigned a new value from a lvalue  
assignment operator return reference to changed object
  ```cpp
  myClass(myClass &other) {}             // copy ctor
  myClass &operator=(myClass &other) {}  // copy assignment operator

  myClass a;      // default ctor
  myClass b(a);   // copy ctor
  myClass c = a;  // copy ctor
  a         = b;  // copy assignment operator
  ```
  **move ctor & assignment operator:** ctor called automatically when the object is moved and assignment operator when the object is assigned a new value from a rvalue  
  both are used to take ownership of another object's resources
  ```cpp
  myClass(myClass &&other) {}             // move ctor
  myClass &operator=(myClass &&other) {}  // move assignment operator

  myClass a;                 // default ctor
  myClass b(std::move(a));   // move ctor
  myClass c = std::move(b);  // move ctor
  a         = std::move(b);  // move assign operator
  ```
- **rule of all or nothing:** try to define none of the six special functions (dtor + ctor + copy/move constr/assignment op), if you must define one of them then define all  
if none defined then compiler generated `default` functions will be used (they may use shallow copy)
  ```cpp
  class myClass
  {
    public:
      myClass()                         = default;
      ~myClass()                        = default;
      myClass(myClass &&var)            = default;
      myClass(const myClass &var)       = default;
      myClass &operator=(myClass &&var) = default;
      myClass &operator=(myClass &var)  = default;
  };
  ```
- **`delete`:** to disable the usage of a class member function (mentioned in class declaration itself), calling such functions lead to compilation error
  ```cpp
  class someClass
  {
    public:
      int someFunc(int num) {}
      int someFunc(double num) = delete;  // without this, someFunc accepts double by converting it to int
  };
  ```
  example: disable copy ctors when only ones instance of the class must be guaranteed  
  example: if a class has a constant data member then compiler marks copy/move ctor/assignment operator as deleted

## inheritance
- **inheritance:** is the capability of a class (child) to inherit/derive data & functions from other classes (parent)  
six special functions & private members will not be inherited from base class
  ```cpp
  class rectangleClass
  {
    public:
      rectangleClass(int w, int h) : width_(w), height_(h) {}

    protected:
      int width_;
      int height_;
  };

  class squareClass : public rectangleClass  // default private
  {
    public:
      squareClass(int size) : rectangleClass(size, size) {}
  };
  ```
- **inheritance modes:**
  - **`public`:** both (base public & protected members) maintain their access specifier
  - **`protected`:** both will be protected in derived class
  - **`private`:** both will be private in derived class
- **composition/containment:** implementing complex objects using simpler or smaller ones  
inheritance is `is a` relationship, example: square is a rectangle  
composition is `has a` relationship, example: car has a wheel (& other objects)
- prefer shallow hierarchies so it is easier to track where a particular member is inherited from  
or use composition instead which makes it easier to hide data that is not required in derived class  
example: include an object of another class as a class member instead of polluting your class by adding (inheriting) all that data & functions

## polymorphism
- **function overriding:** if a function (not data) is `virtual` in base class then it can be overridden in derived class (base class member function shadowing)  
same function prototype in both base & derived classes, so compiler needs to check which function needs to be called in a virtual table (costs extra cycles)  

  ```cpp
  class baseClass
  {
    public:
      void print1()
      {
          std::cout << "print1 baseClass" << std::endl;
          this->print2();
      }

      virtual void print2() { std::cout << "print2 baseClass" << std::endl; }
  };

  class derivedClass : public baseClass
  {
    public:
      void print2() override { std::cout << "print2 derivedClass" << std::endl; }
      // pre-cpp11:   virtual void print2() {}
  };

  int main()
  {
      derivedClass b;
      b.print1();  // print1 baseClass
      b.print2();  // print2 derivedClass
                   // but without virtual: print2 baseClass
      return 0;
  }
  ```
- **`override`:** keyword shows the reader that a particular function is overriding a virtual method of a base class  
compiler also can make sure that you are not altering (redefinition) or adding new methods (overloading) that you think are overrides
  ```cpp
  class base
  {
    public:
      virtual int foo(float x) = 0;
  };

  class derived : public base
  {
    public:
      int foo(float x) override {}  // okay
  };

  class derived2 : public base
  {
    public:
      int foo(int x) override {}  // error: does not override a base class member
  };
  ```
- **overloading vs overriding:** overloading is picking one from all methods with same name but different arguments at compile-time  
overriding is picking from methods with the same name & arguments in different class of same class hierarchy at run-time
- **early binding:** which implementation of the method is used gets decided at compile-time based on the type of the pointer that you call through  
**late binding:** which implementation of the method is used gets decided at run-time based on the type of the pointed-to object (what it was originally constructed as) which might not necessarily be same as the type of the pointer that points to that object  
example: if two classes in a hierarchy have the same function defined, without `virtual` early binding and with `virtual` late binding
  ```cpp
  class baseClass
  {
    public:
      void func1() { std::cout << "baseClass::func1" << std::endl; }
      virtual void func2() { std::cout << "baseClass::func2" << std::endl; }
  };

  class derivedClass : public baseClass
  {
    public:
      void func1() { std::cout << "derivedClass::func1" << std::endl; }  // adding override would result in an error
      void func2() override { std::cout << "derivedClass::func2" << std::endl; }
  };

  int main()
  {

      baseClass *basePtr = new derivedClass();  // constructed as derivedClass but stored as baseClass*

      basePtr->func1();  // baseClass::func1     --> early binding
      basePtr->func2();  // derivedClass::func2  --> late binding

      return 0;
  }
  ```
- **polymorphism:** ability of a function/object to perform in different ways depending on how it is being used
  - **compile-time:** function & operator overloading, early binding
  - **run-time:** function overriding, late binding  
  example: generic class pointer that can work with all children  
  pointer polymorphism preferred (over reference) since pointer can be reassigned
    ```cpp
    derivedClass a;
    derivedClass b;
    baseClass *c = &a;  // can be generic reference for derivedClass1 or derivedClass2
    ```
- **pure virtual function:** in a base class (with function not implemented) can force all derived classes to override that function
  ```cpp
  virtual myFunc() = 0;
  ```
  **abstract class:** are a class which has at-least one pure virtual function, object of this class cannot be created  
  **interface:** special abstract class with only pure virtual functions & no data members

# file & string stream
- **fstream:** read/write file
  ```cpp
  #include <fstream>
  std::fstream file(string &filename, Mode std::ios_base::mode);
  ```
  ```cpp
  // modes
  in      // for reading
  out     // for writing
  binary  // in binary mode
  app     // append output
  ate     // seek to EOF when opened
  trunc   // overwrite existing file
  ```
  **`ifstream`:** fstream with default mode `in`  
**`ofstream`:** fstream with default mode `out`
- **example: read line by line:**
  ```cpp
  std::ifstream input("dummy.txt");  // default mode used

  if (input.is_open())  // check if opening failed
  {
      std::string line;
      while (std::getline(input, line))
      {
          // process line
      }
  }
  ```
- **example: write binary data:**
  ```cpp
  std::ofstream output_file("output.bin", std::ios_base::out | std::ios_base::binary);  // default mode overridden
  output_file.write(reinterpret_cast<char *>(data), sizeof(data));
  ```
- **example: read regular columns:** every line should have same number of columns
  ```cpp
  // 1   one     0.1
  // 2   two     0.2
  // 3   three   0.3

  int a;
  std::string b;
  float c;

  std::ifstream input_file("input_data.txt");

  while (input_file >> a >> b >> c)  // read values
  {
      std::cout << a << b << c << std::endl;  // print values in same order
  }
  ```
- **sstream:** allows a string to be treated like a stream, used to combine different types into a string or vice-versa (break/parse string)
  ```cpp
  #include <sstream>

    // combine into string
    std::stringstream out_sstream;
    out_sstream << "pi " << 3.14;
    std::string str_out = out_sstream.str();
    std::cout << str_out << std::endl;  // pi 3.14

    out_sstream.str("");  // reset sstream string

    // parse string
    std::stringstream in_sstream(str_out);
    std::string str;
    float val;
    in_sstream >> str >> val;  // str: "pi", val: 3.14
  ```

# memory
- **1s complement:** invert all bits  
**2s complement:** add one to 1s complement
  ```cpp
  00011001  //  25
  11100110  //     (1s complement)
  11100111  // -25 (2s complement)
  ```
- **integer representation:** for signed numbers one possible implementation is to use MSB for sign but this permits `+0` & `-0` which is undesirable, so negative numbers stored as 2s complement  
both `128` & `-128` have same 8bit 2s complement (`10000000`), but since all negative numbers have MSB set assume bit-pattern as `-128`  
use fixed-width integer types (like `uint32_t`) from `<stdint.h>`
  - **`signed`:** `-2^(n-1)` to `2^(n-1) - 1`
  - **`unsigned`:** `0` to `2^(n) - 1`
- **sign extension:** increasing number of bits of a binary number while preserving the number's sign & value
  ```cpp
            0000 1010  // uint8_t   (10)
            1111 0110  // uint8_t  (-10)
  1111 1111 1111 1111  // uint16_t (-10)
  ```
- **integer promotion:** is the implicit conversion of a type smaller (lower rank) than integer to `signed int` if it can represent all values of the original type else converted to an `unsigned int`  
example: `0x 80` is first promoted to `0x 80 00 00 00` signed integer (only MSB set) then automatically sign extended (for 64bit) to `0x ff ff ff ff 80 00 00`
  ```cpp
  uint8_t val = 0x80;
  printf("%x \n", val);        // 80

  // incorrect
  uint64_t result1 = val << 24;
  printf("%llx \n", result1);  // ffffffff80000000

  // fixed
  uint64_t result2 = (uint64_t)val << 24;
  printf("%llx \n", result2);  // 80000000
  ```
  same rank signed integer is converted to unsigned when mixed
  ```cpp
  uint32_t a = 6;
  int32_t b  = -20;
  (a + b > 6) ? printf(">6\n") : printf("<=6\n");           // >6
  ((int32_t)a + b > 6) ? printf(">6\n") : printf("<=6\n");  // <=6
  ```
- **float representation (IEEE 754):** single precision `1 + 8 + 23`, double precision `1 + 1 + 53`  
![](./media/cplusplus/IEEE754.png)
  ```cpp
  263.3                           // floating number
  100000111.0100110011...         // binary
  1.000001110100110011... x 2^8   // scientific notation, true_exponent = 8
                                  // 1 is invisible leading bit
  sign = 0
  exp = 8 + 127 = 10000111        // exponent = true_exponent + bias
                                  // bias = 2^(exp_bits - 1) - 1
  frac = 00000111010011001100110  // bits after leading bit (also known as mantissa)

  0 10000111 00000111010011001100110
  ```
- **type qualifiers:** `restrict` not part of C++ standard but most compilers support it, `_Atomic` added in C11, `mutable` C++ only
  - **`const`:** variable (or object) cannot be modified after initialization, compilation error if modification attempted
  - **`volatile`:** variable may be changed by something external to the program at any time so must be re-read from memory every time (don't keep in cache) it is accessed, `const volatile` used for read-only status registers
  - **`restrict`:** is an optimization hint to compiler that during a pointer's lifetime no other pointer will access the same memory  
  - **`_Atomic`:** variable have guaranteed read-modify-write operation in single instruction  
  free from data races so can be used in reentrant functions & again in the ISR that interrupt it
    ```cpp
    #include <stdatomic.h>

    _Atomic int a;  // or _Atomic(int) a;
    ```
  - **`mutable`:** permits modification of the class member (like mutexes) even if the containing object is declared const  
  used to specify that the member does not affect the externally-visible state of the class  
  C++ language grammar treats mutable as a storage-class-specifier but it does not affect storage class or linkage
    ```cpp
    mutable std::mutex m;
    ```
- **linkage:** specifies till where is the visibility of a variable/function name (identifier)
  - **no linkage:** can be referred only in scope it is in
  - **internal linkage:** all scopes in the current translation unit
  - **external linkage:** scopes in the other translation units (accessible through the whole program)
- **storage duration:** is the object's property that defines the rules according to which it is created and destroyed
  - **automatic:** allocated at the beginning of the enclosing code block and dealloced at the end
  - **static:** allocated when the program begins and dealloced when the program ends
  - **thread:** allocated when the thread begins and dealloced when the thread ends
  - **dynamic:** allocated and dealloced upon request (like dynamic memory allocation)
- **storage class specifier:**
  - **no specifier or `auto`:** objects declared at block scope or in function parameter lists with (default) automatic storage duration
  - **`register`:** auto variable with hints to the compiler to place the variable in the processor's register
  - **`static`:** static duration with internal linkage at file scope (global static) and no linkage at block scope (local static)
  - **`extern`:** function/variable is assumed to be available somewhere else (external linkage) and the resolving is deferred to the linker  
  use a header file to contain an extern declaration of the variable then that header is included by the one source file that defines the variable and by all the source files that reference it
    ```cpp
    // header.h
    extern int g_val;
    extern int increment(void);

    // source1.c
    #include "header.h"
    int g_val = 77;
    int increment(void) { return (++g_val); }

    // source2.c
    #include "header.h"
    printf("%d\n", g_val);        // 77
    printf("%d\n", increment());  // 78
    ```
  - **`thread_local`:** indicates that the object has thread storage duration, can be combined with static/extern to specify internal/external linkage, static is implied when thread_local applied to a block scope variable
- **endianness:** order in which bytes within a word is stored/transmitted  
big-endian has most significant byte (big end) data first (smallest address) and little-endian has least significant byte data first  
![](./media/cplusplus/endianness.png)  
**find endianness of system:**
  ```cpp
  int n = 1;
  if (*(char *)&n == 1)  // check most significant byte set
  {
      std::cout << "little endian" << std::endl;
  }
  ```
  **swap endianness:**
  ```cpp
  uint32_t input = 0x12345678;
  uint32_t b0, b1, b2, b3;
  uint32_t output;

  b0 = (input & 0x000000ff) << 24;
  b1 = (input & 0x0000ff00) << 8;
  b2 = (input & 0x00ff0000) >> 8;
  b3 = (input & 0xff000000) >> 24;

  output = b0 | b1 | b2 | b3;

  printf("0x%x", output);  // 0x78563412
  ```
- **memory layout:** each different segment stores different parts of code and have their own read & write permissions  
![](./media/cplusplus/memory_layout.png)
  - **text:** contains executable instructions, usually read-only to prevent accidental modification  
  - **initialized data:** initialized `global` & `static` variables (`static` functions will be in text section)  
  also contains read-only `.rodata` section for static/global constants
  - **uninitialized data:** uninitialized `global` & `static` variables, also known as `bss` (b​lock started by symbol)  
  only size mentioned in executable, allocated & zero-initialized after program load
  - **heap:** for memory allocated at run-time  
  internally use `sbrk` and `brk` system calls to change memory allocation within the heap segment
    ```cpp
    type *ptr = (type *)malloc(size);        // memory allocation
    type *ptr = (type *)calloc(size);        // contiguous allocation, zero-initialization
    type *ptr = (type *)realloc(ptr, size);  // re-allocation
    free(ptr);

    // C++ only
    type *ptr = new type;       // declare variable & allocate for one element
    delete ptr;                 // delete variable
    type *ptr = new type[num];  // allocate array
    delete[] ptr;               // delete array
    ```
    `new` throws `std::bad_alloc` exception if out of heap, to instead get NULL addr use `new (std::nothrow)`
    ```cpp
    int *p = new (std::nothrow) int;

    if (!p)
    {
        std::cout << "mem allocation failed" << std::endl;
    }
    ```
  - **stack:** simple last-in-first-out (LIFO) structure that stores local variables, function arguments & return addr  
  **stack frame:** set of values (return addr, arguments, local variables) pushed onto stack for a function call (on ARM first 4 args stored `r0` to `r3`), stack pointer keeps track of top of the stack  
  `ebp` (frame pointer) is used to backup `esp` (stack pointer), while `esp` is being modified by the current function  
  ![](./media/cplusplus/stack.png)
- **memory leak:** when heap not dealloced or address lost (pointer reassigned)  
compiler throws `double free or corruption` if we try to free memory twice  
**dangling pointer:** points to dealloced memory  
**wild pointer:** pointing to random address, usually due to uninitialized pointer so use `nullptr` for initialization  
**segmentation fault:** occurs when a program attempts to access a memory location it does not have permission to access or access differently than it is supposed to  
example: write to a read-only location, read a `nullptr`  
dereferencing a free-up pointer might not lead to a fault since standard library might be collecting memory deallocs before returning them back to OS  
**stack overflow:** program attempts to use more memory than is available on stack, usually due to deep/infinite recursion leading to stack shortage
- **shallow copying:** just copy pointer not the underlying data (used in default copy ctor/assignment operator)  
can lead to dangling pointer when object shallow copied  
**deep copying:** create new pointers and copy data into it  
shallow copy duplicate as little as possible while deep copy duplicate everything

# pointers
- **pointer:** holds the memory address of another object (variable/function) as its value  
in modern C++ owning memory means being responsible for its cleanup, so raw pointer should never own memory
- **`nullptr`:** implicitly converts to any pointer type (but never an integral type)
- **pointer vs reference:** use references wherever you can (passing parameters), and pointers wherever you must (polymorphic interfaces are `NULL` initialized)
  - own memory vs alias
  - no init required vs init in declaration
  - can reassign vs cannot
  - can be NULL vs cannot
  - indirection (levels of pointers) vs single level
  - can apply arithmetic operations vs cannot
  - can store in vector/array vs cannot
- **address operator (`&`):** returns the address of the variable in memory  
**dereferencing operator (`*`):** returns the value of the variable to which the pointer points to  
**arrow operator (`->`):** to call class/struct members, `obj->myFunc()` is same as `(*obj).myFunc()`
- **example: pointer polymorphism:**
  ```cpp
  std::vector<abstractShapeType *> shapes;
  squareType square;
  triangleType triangle;

  shapes.push_back(square);
  shapes.push_back(triangle);

  for (const auto *shape : shapes)
  {
      shape->print();  // executes respective derivedClass implementation
  }
  ```
- **function pointer:** is a variable that contains the address of a function
  ```cpp
  int foo(int);     // function
  int *foo(int);    // function returning int*
  int (*foo)(int);  // function pointer, by changing precedence using ()
  ```
  ```cpp
  int foo(int arg)
  {
      printf("foo %d\n", arg);

      return arg;
  }

  int main()
  {
      int ret = 0;
      int (*func_ptr)(int);
      func_ptr = &foo;
      ret      = (*func_ptr)(10);  // foo 10

      // OR
      func_ptr = foo;
      ret      = func_ptr(20);  // foo 20

      printf("ret %d\n", ret);  // ret 20

      return 0;
  }
  ```
- **spiral/right-left rule:**
  ```
  read these symbols as:
  *     pointer of                      - always on left side
  []    array of                        - always on right side
  ()    function returning/expecting    - always on right side

  step1: find the identifier, this is the starting point
  step2: look at symbols on the right of identifier, continue until you run out of symbols or hit `)`
  step3: look at the symbols to the left of identifier, continue until you run out of symbols ot hit `(`
  step4: repeat step 2 & 3 still complete declaration is formed
  ```
  ```cpp
  int *p[];

  int *p[];          // step1
      ^              // p is

  int *p[];          // step2, cant move right
        ^^           // p is array of

  int *p[];          // step3
      ^              // p is array of pointer to

  int *p[];          // step3
  ^^^                // p is array of pointer to int
  ```
  ```cpp
  int *(*func())();

  int *(*func())();  // step1
         ^^^^        // func is

  int *(*func())();  // step2, cant move right
             ^^      // func is function returning

  int *(*func())();  // step3, cant move left
        ^            // func is function returning pointer to

  int *(*func())();  // step2, cant move right
                ^^   // func is function returning pointer to function returning

  int *(*func())();  // step3
      ^              // func is function returning pointer to function returning pointer to

  int *(*func())();  // step3
  ^^^                // func is function returning pointer to function returning pointer to int
  ```
  ```cpp
  int (*(*foo)(char*,double))[9][20];

  // without arguments or array sizes
  int (*(*foo)())[][];

  // foo is pointer to function expecting (char*, double) and 
  // returning pointer to 2D array (size 9X20) of int
  ```
  ```cpp
  int i;           // an int
  int *p;          // an int pointer (ptr to an int)
  int a[];         // an array of ints
  int f();         // a function returning an int
  int **pp;        // a pointer to an int pointer (ptr to a ptr to an int)
  int (*pa)[];     // a pointer to an array of ints
  int (*pf)();     // a pointer to a function returning an int
  int *ap[];       // an array of int pointers (array of ptrs to ints)
  int aa[][];      // an array of arrays of ints
  int *fp();       // a function returning an int pointer
  int ***ppp;      // a pointer to a pointer to an int pointer
  int (**ppa)[];   // a pointer to a pointer to an array of ints
  int (**ppf)();   // a pointer to a pointer to a function returning an int
  int *(*pap)[];   // a pointer to an array of int pointers
  int (*paa)[][];  // a pointer to an array of arrays of ints
  int *(*pfp)();   // a pointer to a function returning an int pointer
  int **app[];     // an array of pointers to int pointers
  int (*apa[])[];  // an array of pointers to arrays of ints
  int (*apf[])();  // an array of pointers to functions returning an int
  int *aap[][];    // an array of arrays of int pointers
  int aaa[][][];   // an array of arrays of arrays of int
  int **fpp();     // a function returning a pointer to an int pointer
  int (*fpa())[];  // a function returning a pointer to an array of ints
  int (*fpf())();  // a function returning a pointer to a function returning an int
  ```
- **example: matrix (2D array) as double pointer:** double pointer is a pointer to pointers (array of pointers)  
first allocate pointer array (double pointer) then allocate memory for each element (1D row array)  
![](./media/cplusplus/2d_pointer.png)
  ```cpp
  // method1: non contiguous
  uint8_t **array1 = (uint8_t **)malloc(num_rows * sizeof(uint8_t *));  // or sizeof(*array1)
  for (size_t i = 0; i < num_rows; i++)
      array1[i] = (uint8_t *)malloc(num_cols * sizeof(uint8_t));  // or sizeof(**array1)

  // method2: contiguous
  uint8_t **array2 = (uint8_t **)malloc(num_rows * sizeof(int *));
  array2[0]        = (uint8_t *)malloc(num_rows * num_cols * sizeof(int));
  for (int i = 1; i < num_rows; i++)
      array2[i] = array2[0] + i * num_cols;

  // print matrix
  void printArray2d(uint8_t **arr, size_t num_rows, size_t num_cols)
  {
      for (size_t row = 0; row < num_rows; row++)
      {
          for (size_t col = 0; col < num_cols; col++)
          {
              printf("%u ", arr[row][col]);
          }
          printf("\n");
      }
  }
  ```

## smart pointers
- **smart pointer:** is a wrapper class over a heap memory owning raw pointer and is used to manage its lifetime (memory freed when object destroyed), crucial for the RAII programming idiom  
just create a standard raw pointer then pass that to the smart pointer immediately
  ```cpp
  #include <memory>
  smartPointerType<type> sPtr(new type());  // declaration

  sPtr.get();           // get raw pointer
  sPtr.reset(new_ptr);  // stops using currently-used pointer (freed if not required)
                        // and starts managing new_ptr now instead
  ```
  use `unique_ptr` by default, if multiple objects must share ownership then use `shared_ptr`
  - **`unique_ptr`:** guarantees that memory is always owned by a single unique pointer, can be moved to a new owner but not copied or shared (copy ctor deleted)  
  as fast as raw pointer
    ```cpp
    auto uPtr = std::unique_ptr<myType>(new myType());      // default ctor
    auto uPtr = std::unique_ptr<myType>(new myType(args));  // custom ctor
    ```
  - **`shared_ptr`:** allows you to make a copy of the pointer which will hold the memory until all the pointers holding that memory gets out of scope which is done by maintaining a reference counter (*last one turns off the light*, memory freed when refcount reaches zero)  
  `reset()` revokes the ownership over the memory that the pointer holds (decreases `usage_count`)
    ```cpp
    auto sPtr = std::shared_ptr<myType>(new myType());      // default ctor
    auto sPtr = std::shared_ptr<myType>(new myType(args));  // custom ctor

    sPtr.use_count();  // return usage_count
    ```
  - **`weak_ptr`:** similar to `shared_ptr` but does not affect the refcount, used to observe a `shared_ptr`(like check if still holds the memory or not)
    ```cpp
    class someClass
    {
      public:
        someClass() { std ::cout << "alive" << std::endl; }
        ~someClass() { std ::cout << "dead" << std::endl; }
    };

    int main()
    {
        auto a = std::shared_ptr<someClass>(new someClass());  // alive
        std ::cout << a.use_count() << std ::endl;             // 1
        {
            auto b = a;
            std ::cout << b.use_count() << std ::endl;  // 2
        }
        std ::cout << a.use_count() << std ::endl;  // 1

        auto c = std::weak_ptr<someClass>(a);
        std ::cout << a.use_count() << std ::endl;  // 1

        return 0;
    }  // dead
    ```
- **example: smart pointer with local variable:** both stack & smart pointer will try to dealloc that memory leading to error
  ```cpp
  int main()
  {
      int a      = 0;
      auto a_ptr = std ::unique_ptr<int>(&a);
      return 0;
  }  // error: invalid pointer / double free or corruption
  ```
- **example: smart pointer polymorphism:** good way of using smart pointer
  ```cpp
  std::vector<std::unique_ptr<abstractShape>> shapes;

  // method1: "new derivedClass" passed to ctor of unique_ptr
  shapes.emplace_back(new squareClass);  // note emplaced_back

  // method2: need to move since unique_ptr cannot be copied
  auto var = std::unique_ptr<triangleClass>(new triangleClass);
  shapes.push_back(std::move(var));

  for (const auto &shape : shapes)
  {
      shape->print();  // executes respective derivedClass implementation
  }
  ```
- **type casting:** converting value of given data type into another  
![](./media/cplusplus/typecasting.png)
  - **implicit/automatic:** are done automatically by the compiler, tries to prevent changing the value by up-casting it to highest data type present in the expression
    ```cpp
    short a = 1024;
    int b   = 5;
    b       = a;  // implicit conversion
    ```
    ```cpp
    float a    = 10.5;
    uint32_t b = a;               // decimal dropped
    std::cout << b << std::endl;  // 10
    ```
  - **explicit:** deliberate modification of a variable's data type by the programmer
    - **assignment operator:** also known as forced casting
      ```cpp
      float a = 1.2;
      int b   = (int)a + 1;  // C-like notation
      int c   = int(a) + 1;  // functional C-like notation
      ```
      ```cpp
      unsigned char u = (unsigned char)(-9);  // same bit pattern
      printf("%d \n", u);                     // 247
      ```
    - **cast operator:** has different easily recognizable & searchable (in codebase) notations for different tasks that eliminate unintended errors  
      - **`static_cast`:** can perform all the conversions compile time that can be done implicitly
      - **`dynamic_cast`:** runtime conversion of pointer/reference to classes up/down/sideways along the inheritance hierarchy  
      if failed returns `nullptr` for pointer or throws `std::bad_alloc` for pointers
      - **`reinterpret_cast`:** reinterpret bytes of one type as another type, mainly used to work with bits
      - **`const_cast`:** remove const from const reference of non-const variable
        ```cpp
        int i            = 3;         // non-const variable
        const int &i_ref = i;         // const ref
        std::cout << i << std::endl;  // 3

        int &k = const_cast<int &>(i_ref);
        k      = 4;
        std::cout << i << std::endl;  // 4
        ```
        another usecase is to prevent code duplication
        ```cpp
        const std::string &shorterString(const std::string &s1, const std::string &s2)
        {
            return s1.size() <= s2.size() ? s1 : s2;
        }

        std::string &shorterString(std::string &s1, std::string &s2)
        {
            const std::string &r = shorterString(const_cast<const std::string &>(s1),
                                                 const_cast<const std::string &>(s2));  // add const qualifier to args
            return const_cast<std::string &>(r);  // discard const qualifier
        }
        ```
- **run-time type information (RTTI):** is a mechanism that exposes information stored about each polymorphic object's data type at runtime, this is useful when `dynamic_cast` is used
- **type aliasing:** using the memory of one type as if it were a different type when the memory layout of two types are compatible, compatible types can be converted using `reinterpret_cast`
  ```cpp
  struct point
  {
      int x;
      int y;
  };

  struct location
  {
      int x;
      int y;
  };

  point p{1, 2};
  auto *loc = reinterpret_cast<location *>(&p);
  ```

# templates
- **generic programming:** enables the programmer to write a general algorithm which will work with all data types (separate algorithms from data type)
- **`template`:** enable you to define the operations of a function/function and later specify what types those operations should work on  
**instantiation:** compiler generates concrete functions/classes based on the supplied argument type (`<T>` expanded)  
so for the compiler to generate the code it must see both the template definition (not just declaration) and the specific types used to fill-in the template, so keep declaration & definition in a header then include it in source files
  - **`template` function:** can use any type that is copy constructable, assignable & defined by the time template compiled (custom classes)  
  pass explicit type if compiler is not able to determine the type
    ```cpp
    template <typename T>  // can use typename or class keyword
    T foo(const T &arg1)
    {
    }

    foo(10);     // type inferred by compiler
    foo<int>();  // explicit type
    ```
  - **`template` class:** used for meta-programming in which templates are used to generate temporary source code
    ```cpp
    template <typename T>
    class someClass
    {
      public:
        someClass(const T &var) : var_(var){};

      private:
        T var_;
    };

    someClass<int> my_object(10);
    ```
- **example: get type size in bytes (meta-programming):**
  ```cpp
  template <typename T>
  size_t sizeOf()
  {
      T *a        = nullptr;
      size_t size = (uint8_t *)(a + 1) - (uint8_t *)(a);
      return size;
  }

  std::cout << "int: " << sizeOf<int>() << std::endl;              // int: 4
  std::cout << "someClass: " << sizeOf<someClass>() << std::endl;  // someClass: 16
  ```
- **specialization:** special (different) function/class implementation for a specific type
  ```cpp
  template <typename T>  // generic
  T foo()
  {
      std::cout << "generic" << std::endl;
  }

  template <>  // specialized
  int foo()
  {
      std::cout << "specialized int" << std::endl;
  }

  foo<int>();     // specialized int
  foo<double>();  // generic
  ```

# exceptions
- **`exception`:** provides consistent interface to handle errors through the `throw` expression  
an exception can be caught at any point of the program (`try - catch`) or even thrown further (`throw`)  
ctor of exception receives a string error message as argument which can accessed later using `what()`  
`std::exception` is the base class from which various error types like `logic_error` & `runtime_error` inherit
- **example: `try` ⟶ `throw` ⟶ `catch`:**
  ```cpp
  #include <stdexcept>

  void someFunc(void)
  {
      uint8_t *ptr = nullptr;

      if (nullptr == ptr)
      {
          std::string msg = "null pointer";
          throw std::runtime_error(msg);  // throw
      }
  }

  int main(void)
  {
      try
      {
          someFunc();  // throws exception
      }
      catch (std::runtime_error &exp)
      {
          std::cerr << "runtime error: " << exp.what() << std::endl;  // runtime error: null pointer
      }
      catch (std::logic_error &exp)
      {
          std::cerr << "logic error: " << exp.what() << std::endl;
      }
      catch (std::exception &exp)  // generic
      {
          std::cerr << "exception: " << exp.what() << std::endl;
      }
      catch (...)  // catch everything
      {
          std::cerr << "unknown exception" << std::endl;
      }
  }
  ```

# misc
- **`using` type alias:** similar to `typedef` but compatible with complex types (like templates & arrays)  
creates local alias if used within function scope
  ```cpp
  // not possible with typedef
  using image3f  = image<float, 3>;  // template
  using vector3d = double[3];        // array
  ```
- **why `typedef` over macro:**
  ```cpp
  #define type1 int *
  typedef int *type2;

  type1 a, b;  // "a" pointer but "b" just int
  type2 c, d;  // both "c" & "d" pointer
  ```
- **maximum munch rule:** compiler bites off biggest legal chunk
  ```cpp
  d = ++a+++b++c++;  // ++a + ++b + +c++
  ```
- **format specifiers:** are placeholders to represent data types
  ```cpp
  %c  // char
  %s  // string
  %d  // int
  %u  // uint
  %o  // unsigned octal
  %x  // unsigned hex, %llx 64 bit
  %f  // float, %lf double
  %e  // float exponent notation
  %g  // shorter of %f & %e (no trailing zeroes)
  %p  // pointer
  ```
  C99 has added fixed length integer format specifiers, replace `PRI` with `SCN` for `scanf()`
  ```cpp
  #include <inttypes.h>

  PRId8  // signed
  PRIi8  // unsigned
  PRIx8  // unsigned hex
  ```
- **constant integer literals:**
  ```cpp
  // pre
  0b  // binary
  0x  // hex
  0   // oct

  // post
  U   // uint
  L   // long int, UL
  LL  // long long int, ULL
  F   // float
  ```
  ```cpp
  uint32_t a = 0b10, b = 0x10, c = 052;
  LOG("a %" PRIi32 " b %" PRIi32 " c %" PRIi32, a, b, c);  // a 2 b 16 c 42
  ```
- **`enum`:** user-defined type that consists of a set of named integral constants, by default starts with 0
  - **unscoped:** can implicitly convert to primitives
  - **scoped:** add `class` to create a new scope, implicit conversion leads to error (use `static_cast` if required)
  ```cpp
  enum uFoo  // unscoped
  {
      a,         // 0
      b,         // 1
      c = 1,     // 1
      d = b + c  // 2
  };

  enum class sFoo  // scoped
  {
      a,
      b,
      c = 1,
      d = b + c
  };

  int enumValue = a;        // visible without qualifier, implicit conversion
  int enumValue = sFoo::a;  // sFoo qualifier required, error for conversion
  ```
- **`union`:** is a type consisting of a sequence of members whose storage overlaps  
use when member variables are used in either-or-but-never-both fashion
  ```cpp
  union someUnion  // size 8bytes
  {
      uint32_t a;
      uint8_t b;
      uint64_t c;
  };
  ```
- **`typedef struct`:** used to define an alias for the structure data type
  ```cpp
  typedef struct someStruct_  // someStruct_ not necessary
  {
      int x;
  } someStruct;

  // same as
  struct someStruct_
  {
      int x;
  };
  typedef struct someStruct_ someStruct;
  ```
- **nested `struct`/`union`:** do not repeat anonymous/nameless struct/union member names
  ```cpp
  typedef struct
  {
      union
      {
          struct  // nameless struct
          {
              uint8_t nibble1 : 4;
              uint8_t nibble2 : 4;
          };

          struct
          {
              uint8_t bit0 : 1;
              uint8_t bit1 : 1;
              uint8_t bit2 : 1;
              uint8_t bit3 : 1;
              uint8_t bit4 : 1;
              uint8_t bit5 : 1;
              uint8_t bit6 : 1;
              uint8_t bit7 : 1;
          };

          uint8_t value;
      };
  } byte;
  ```
- **functor (function object)** class/struct that acts like a function by overloading `operator ()`  
**lambdas:** define an anonymous function object right at the location where it's invoked or passed as an argument
  ```cpp
  struct  // functor
  {
      bool operator()(int a, int b) const { return a < b; }
  } customLessFunc;

  std::sort(vec.begin(), vec.end(), customLessFunc);                      // using functor
  std::sort(vec.begin(), vec.end(), [](int a, int b) { return a > b; });  // using lambdas
  ```

# STL

# containers
- **`iterator`:** used to point at the memory addresses of STL containers (similar to a pointer) which allows quick & efficient navigation through any STL container (even unordered ones)  
![](./media/cplusplus/iterator.png)
  ```cpp
  T::iterator itr = container.begin();  // vector<double>::iterator itr;

  T val = *itr;  // current element
  ++itr;         // increment iterator, now points to next element
  ```  

## sequence
- **sequence containers:** data structures that can be accessed sequentially (`O(n)`)
- **`string`:** sequences of characters, better than C-style arrays (which is faster) because this has dynamic size & useful member functions
  ```cpp
  #include <string>
  std::string str;                      // std::string str("hello world");

  +                                     // concatenate operator
  int pos          = str.find(substr);  // find substring pos
  bool is_empty    = str.empty();       // check empty
  int size         = str.size();        // size (doesn't include string end NULL character)
  const char *data = str.data();        // underlying NULL terminated C array, same as c_str()
  char c           = str.at(i);         // access with bounds checking, without check [i]
  str.clear();                          // clear string
  str.push_back(val);                   // add val char at the end, pop_back(), alternate to `emplace_back`
  str.reserve(size);                    // reserve size to prevent frequent memory-allocs
                                        // optional second arg for initializing new elements
  str.shrink_to_fit();                  // dealloc unused memory
  ```
- **`vector`:** dynamic contiguous (so cache-friendly) array
  ```cpp
  #include <vector>
  std::vector<T> vec;                   // std::vector<int> vec{1, 2, 3, 4};

  // empty, size, data, at(i), clear, push_back, reserve, shrink_to_fit
  ```
- **`array`:** static contiguous array
  ```cpp
  #include <array>
  std::array<T, size> arr;              // std::array<int, 4> arr{1, 2, 3, 4};

  arr.fill(value)                       // assign value to all elements
  // empty, size, data, at(i), clear
  ```
- **`deque`:** double-ended queue, basically a two-sided vector with non contiguous mem  
usually implemented as variable size array of fixed size arrays, this makes growing faster than a vector (which requires allocation & copying)
  ```cpp
  #include <deque>
  std::deque<T> dq;                     // std::deque<int> dq{1, 2, 3, 4};

  dq.push_front(val)                    // add element at beginning, popfront()
  // empty, size, at(i), clear, push_back, shrink_to_fit
  // size not provided
  ```
- **why `emplace_back`:** it constructs the object in place with the ctor arguments, while `push_back` will construct a temporary object then copy/move it into the container  
more performant for types with an inefficient move constructor

## associative
- **associative containers:** sorted data structures that can be quickly searched (`O(logn)`)
- **`pair`:** provides a way to store two heterogeneous objects as a single unit
  ```cpp
  #include <utility>
  std::pair<T1, T2> pr;                 // std::pair<int, string> pr(1, "hello");

  pr       = make_pair(val1, val2);     // create pair
  pr.first = val3;                      // modify first element, second
  ```
- **set:** collection of unique keys which is always sorted
  ```cpp
  #include <set>
  std::set<T> st;                       // std::set<T> st{1, 2, 3, 4};

  <posItr, bool> = st.insert(val);      // insert value if not exists
  posItr         = st.find(key);        // find element, (posItr == st.end()) if not present
  if (mp.count(key) > 0)                // number of matching keys (0/1 for set & map)
  // empty, size, clear
  ```
- **`map`:** collection of key-value pairs which is sorted by unique keys  
anything with a defined less-than operator (`<`) can be used as key
  ```cpp
  #include <map>
  std::map<keyT, valT> mp{{1, "hello"}, {2, "world"}};

  mp[key] = val;                        // assign (insert if not present)
  // empty, size, at(key), clear, insert(pair), find, count
  ```
- **`multiset` & `multimap`:** are same as set & map but keys are not unique (duplicates allowed), so `count(key)` can greater than 1  
  defined in same headers as set & map

## unordered associative
- **unordered associative containers:** unsorted  but hashed data structures that can be quickly searched (average `O(1)` but worst case `O(n)`)  
worst case if hash function is producing collision for every insertion into container
- **`unordered_set`, `unordered_map`, `unordered_multiset` & `unordered_multimap`:** same as ordered associate containers with headers: `#include <unordered_set>` & `#include <unordered_map>`

## container adaptors
- **container adaptors:** provide a different interface for sequential containers
- **`stack`:** deque wrapper with functionality of a LIFO data structure by forcing push/pop on one side only
  ```cpp
  #include <stack>
  std::stack<T> stk;                    // new dequeue created
  std::stack<T> stk(dq);                // copy existing deque data (copy ctor)

  T t = stk.top();                      // peek top
  stk.push(val);                        // add value to top of stack, pop()
                                        // pop() doesn't return value so store top() first
  // empty, size
  ```
- **`queue`:** deque wrapper with functionality of a FIFO data structure by forcing push one side and pop on other
  ```cpp
  #include <queue>
  std::queue<T> que;                    // new dequeue created
  std::queue<T> que(dq);                // copy existing deque data (copy ctor)

  T t = que.front();                    // first element, back()
  stk.push(val);                        // add value at the end, pop()
                                        // pop() doesn't return value so store front() first
  // empty, size
  ```
- **`priority_queue`:** vector wrapper which provides `O(1)` (top element) lookup at the expense of `O(logn)` insertion/extraction by taking more effort into how to insert new elements in the underlying vector  
stack & queue based on queue since growing is faster, priority queue uses vector because insertion into sorted vector (data shifts) is faster with contiguous memory (same cache line)
  ```cpp
  #include <queue>
  std::priority_queue<T> pq();          // new vector created & uses less<T> by default
  std::priority_queue<T> pq(compare, vec);  // copy existing vector data (copy ctor)
                                        // for compare function: std::less<T> (largest at top) or std::greater<T>

  // empty, size, top, push, pop
  // push will insert into sorted array
  ```

## functions
- standard template library
  ```cpp
  #include <algorithm>
  flag = std::all_of(startItr, endItr, boolFunc);      // all_of, any_of, none_of
  std::for_each(startItr, endItr, func);               // for_each
  itr = std::find(startItr, endItr, val_or_boolFunc);  // find
  std::fill(startItr, endItr, value);                  // fill
  std::generate(startItr, endItr, func);               // generate
  std::replace(startItr, endItr, old_val, new_val);    // replace
  std::rotate(startItr, new_startItr, endItr);         // rotate
  std::sort(startItr, endItr, operator);               // default std::less<T>, greater<>
  std::reverse(startItr, endItr);                      // reverse
  float sum = std::accumulate(startItr, endItr, initValue, operation); // default: std::plus<T>, (minus, multiplies, divides, modulus)

  #include <stdio.h>
  FILE *fp;
  fp = fopen("filename", "mode");  // r, rb, w, wb, a, ab
  fprintf(fp, char *....);
  fwrite(ptr, size, num_mem, fp);  // fread
  fclose(fp);
  getchar();

  #include <stdlib.h>
  ptr = malloc(size);  // malloc(0) valid pointer, implementation defined
  ptr = calloc(num_mem, size);
  ptr = realloc(ptr, newSize);
  free(ptr);
  abs(val);
  atoi(str);           // string to int
  assert(expr);        // assert if expr false

  #include <string.h>
  size = strlen(string);  // size excluding NULL (\0)
  memcpy(dst, src, size);
  memset(ptr, val, size);

  #include <math.h>
  ceil(num);
  floor(num);
  fabs(num);
  pow(num, power);
  sqrt(num);

  #include <unistd.h>
  sleep(numSeconds);  // usleep(numUSeconds)

  #include <time.h>
  clock_t t;
  t = clock();
  ...
  t = clock() - t;
  double time_taken = ((double)t) / CLOCKS_PER_SEC;
  ```