# C++
- [introduction](#introduction)
- [containers](#containers)
  - [sequence](#sequence)
  - [associative](#associative)
  - [unordered associative](#unordered-associative)
- [object oriented programming](#object-oriented-programming)
  - [move semantics](#move-semantics)
  - [inheritance](#inheritance)
  - [polymorphism](#polymorphism)
- [file \& string stream](#file--string-stream)
- [memory](#memory)
- [pointers](#pointers)
- [templates](#templates)
- [error handling](#error-handling)
- [misc](#misc)
  - [cpp core guidelines](#cpp-core-guidelines)
  - [standard template library](#standard-template-library)

## links  <!-- omit from toc -->
- [[lectures] modern C++](https://www.ipb.uni-bonn.de/teaching/modern-cpp/)
- [spiral rule](https://riptutorial.com/c/example/18833/using-the-right-left-or-spiral-rule-to-decipher-c-declaration)

## todo  <!-- omit from toc -->
- [cpp core guidelines](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#main)
- [lost art of struct packing](http://www.catb.org/esr/structure-packing/)
- [memory order](https://en.cppreference.com/w/c/atomic/memory_order)
- [mix C & C++](https://isocpp.org/wiki/faq/mixing-c-and-cpp#:~:text=Just%20declare%20the%20C%20function,int)
- [structure packing](http://www.catb.org/esr/structure-packing/)
- [efficient c++](https://embeddedgurus.com/stack-overflow/category/efficient-cc/)
- [add other containers](https://en.cppreference.com/w/cpp/container)
- template uses
- STL
- OOPs concepts
- [MSVC init memory](https://stackoverflow.com/questions/127386/what-are-the-debug-memory-fill-patterns-in-visual-studio-c-and-windows)
- atomics & memory ordering
- [templates FAQ](https://isocpp.org/wiki/faq/templates)

## todo list  <!-- omit from toc -->
- Basics and Fundamentals:
  - Syntax and language features
  - Variables, data types, and type conversions
  - Control flow (if-else, loops, switch statements)
  - Functions and parameter passing
- Object-Oriented Programming (OOP):
  - Classes and objects
  - Inheritance, polymorphism, and encapsulation
  - Constructors and destructors
  - Overloading and overriding
- Standard Template Library (STL):
  - Containers (vectors, lists, sets, maps, etc.)
  - Iterators and algorithms (sorting, searching, etc.)
  - Smart pointers (unique_ptr, shared_ptr)
  - Exception handling
- Memory Management:
  - Stack vs. heap memory
  - Dynamic memory allocation (new, delete)
  - Memory leaks and resource management
  - RAII (Resource Acquisition Is Initialization)
- Operator Overloading:
  - Unary and binary operators
  - Assignment operators
  - Stream insertion and extraction operators
  - Comparison operators
- Templates and Generic Programming:
  - Function templates
  - Class templates
  - Template specialization
  - Template metaprogramming
- Advanced Concepts:
  - Lambdas and functional programming
  - Multithreading and concurrency
  - File I/O and streams
  - Exception safety and error handling

## introduction
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
- **example: GCC compiler flags:**
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
  __DATE__        // May 16 2022
  __TIME__        // 09:42:38
  __FILE__        // C:\workspace\code\src\main.cpp
  __LINE__        // 23
  #pragma once    // include file only once
  #error message  // preproc error
  ```
  continuation (`\`), stringize (`#`) & token pasting (`##`) operators
  ```cpp
  #define macroFunc(a, b) printf("val"#a " : %d, val"#b " : %d\n", \
                                val##a, val##b)

  int main(void)
  {
      int val1 = 40;
      int val2 = 30;
      macroFunc(2, 1);  // val2 : 30, val1 : 40
      return 0;
  }
  ```
- **`auto`:** is a placeholder type that will be replaced later by the compiler  
for a variable placeholder replaced typically by deduction from an initializer
  ```cpp
  auto var = 13;     // int
  auto var = 13.0f;  // float
  auto var = 13.0;   // double

  auto a = 0, b = 3.14;  // error: inconsistent types for a and b
  ```
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
  #define setBit(num, idx)   (num |= (0x1 << idx))     // num |= 1 << idx;
  #define clearBit(num, idx) (num &= ~(0x1 << idx))    // num &= ~(1 << idx);
  #define flipBit(num, idx)  (num ^= (0x1 << idx))     // num ^= 1 << idx;
  ```
- **ranged for loop:** uses iterators to loop over collection/container
  ```cpp
  std::vector<int> vec{0, 1, 5};

  // for(const auto& value : container)
  for (auto n : vec)
  {
      std::cout << n << " ";    // 0 1 5
  }
  ```
- **example:infinite loop:**
  ```cpp
  for (;;)     // K&R style, no warning
  while (1)    // readable but compiler warning for condition always true
  ```  
  **example: while loop typo:** so always put rvalue first (`while (0 == i)`), single `=` will give compilation error
  ```cpp
  while (i = 0)     // set i then use i as condition (0 here)
  while (i == 0)    // use (i == 0) condition
  ```
- **break:** exit loop  
**continue:** skip to next iteration
  ```cpp
  do
  {
      ...
      break;    // break without returning
      ...
  } while (0)
  ...
  return 0;
  ```
- **goto:** dont use it unless you want to break out of nested loops without returning from the function to run some code
  ```cpp
  int foo()
  {
      for (int i = 0; i < 100; i++)
      {
          for (int j = 0; j < 100; j++)
          {
              if (i * j > 1000)
              {
                  goto done;    // break out of both loops
              }
          }
      }

  done:
      cleanup();

      return 0;
  }
  ```
- **function:**
  ```cpp
  // declaration (interface)
  void printSum(int a, int b);

  // definition (implementation)
  void printSum(int a, int b) { std::cout << a + b << std::endl; }
  ```
  - **overloading:** pick from all function with same name but different arguments (not return type), picked at compile-time
    ```cpp
    void printSum(int a, int b);
    void printSum(double a, double b);
    ```
  - **default arguments:** only in declaration, after mandatory arguments
    ```cpp
    int printSum(int a, int b, int c = 0, int d = 0);
    ```
- **argument passing:** use pass-by-reference (pointer or reference) to prevent copying of large objects, const reference to prevent copy & modification  
![](./media/cplusplus/pass_by_reference_vs_value.gif)

- **library:** logically connected multiple object files
  - **static:** part of final executable after linking  
  faster but takes lot of space (`*.a`)
    ```sh
    ar rcs lib.a module1.o module2.o
    # rcs: replace, create, sort
    # c: create library
    # r: replace old files within library (if already exists)
    # s: create sorted index of library
    ```
  - **dynamic:** exists as a separate file outside the executable, is loaded at run-time  
  slower but can be copied (`*.so`)
    ```sh
    gcc -c -fPIC main.c -o main.o
    gcc -shared main.o -o libmain.so
    ```

## containers
- **iterator:** used to point at the memory addresses of containers (similar to a pointer), allows quick navigation through containers
![](./media/cplusplus/iterator.png)
  ```cpp
  T::iterator
  *itr           // current element
  ++itr          // next element
  ```  

### sequence
- **sequence containers:** data structures that can be accessed sequentially
- **string:**
  ```cpp
  #include <string>
  std::string str;

  +                         // concatenate operator
  pos = str.find(substr)    // find substring pos
  str.empty()               // check empty
  str.size()                // size
  str.data()                // underlying C array
  str.c_str()               // NULL terminated string
  str[i]                    // access
  str.at(i)                 // access with bounds checking
  str.front()               // first char, back()
  str.clear()               // clear string
  str.push_back(val)        // add val (as char) at end, pop_back()
  str.reserve(size)         // reserve size (prevent frequent mem alloc)
  str.shrink_to_fit()       // dealloc unused mem
  ```
- **array:** static contiguous array
  ```cpp
  #include <array>
  std::array<T, size> arr;

  arr.fill(value)    // assign value all elements
  // same as earlier: empty, size, data, c_str() [i], at(i), front, clear & iterators
  ```
- **vector:** dynamic contiguous array
  ```cpp
  #include <vector>
  std::vector<T> vec;

  // same as earlier: empty, size, data, c_str(), [i], at(i), front, clear, push_back, reserve, shrink_to_fit & iterators
  ```l
- **deque:** double-ended queue, basically a two-sided vector with non contiguous mem
  ```cpp
  #include <deque>
  std::deque<T> dq;

  dq.push_front(val)    // add val at beginning, popfront()
  // same as earlier: empty, size, [i], at(i), front, clear, push_back, shrink_to_fit & iterators
  ```

### associative
- **associative containers:** sorted data structures that can be quickly searched
- **pair:**
  ```cpp
  #include <utility>
  std::pair<T1, T2> pr;
  pr = std::make_pair(val1, val2)    // create pair
  pr.first                           // first element, second
  ```
- **map:** collection of key-value pairs which is sorted by unique keys  
anything with a defined less-than operator (`<`) can be used as key
  ```cpp
  #include <map>
  std::map<keyT, valT> mp;
  mp[key] = val;                             // insert/assign
  <posItr, bool> = mp.insert({key, val});    // insert value if not exists
  posItr = mp.find(key);                     // find element, (posItr == mp.end()) if not present
  if (mp.count(key) > 0)                     // check if key present, 0/1 for map
  // empty, size, at(key), clear & iterators
  ```

### unordered associative
- **unordered associative containers:** unsorted hashed data structures that can be quickly searched
- **unordered map:** similar to map but unsorted, instead organized into buckets based on hash of its key
  ```cpp
  #include <unordered_map>
  std::unordered_map<keyT, valT> ump;
  // [key], at(key), insert, find, count, empty, size, clear & iterators
  ```

## object oriented programming
- **namespace:** helps avoid name conflicts and helps group project into logical modules  
use `using std::cout;` instead of `using namespace std;` especially in headers
- **nameless namespace:** local to translation unit, like global static but can also take user defined types  
useful if same variable names reused in multiple files
  ```cpp
  namespace
  {
  const int SIZE = 100;
  }
  ```
- **encapsulation:** bundle data and methods into easy-to-use units
- **class:** to encapsulate data along with methods to process them, `this` used as pointer to current object
  ```cpp
  class someClass
  {
    public:
      someClass() {}     // constructor, atleast one
      ~someClass() {}    // destructor, exactly one
      // if no constructor/destructor, default one generated

      someClass(int a, int b) : num_a_(a), num_b_(b) {}    // initializer list, can initialize const members
      bool operator<(const someClass &other) {}            // operator overload
      someFunc() const {}                                  // const correctness (should not change object), const reference object needs this
      someFunc() {}                                        // function overload (because const missing)
      static void someStaticFunc() {}                      // static member function
      static int some_num;                                 // static member variable
      static int getNumA(){};                              // getter/accessor (setter/mutator)

    protected:
      int num_x_ = 0;

    private:    // default access specifier
      int num_a_ = 0;
      int num_b_ = 0;

      // friend, give another class/function access to private & protected
      friend class anotherClass;                  // friend class
      friend int add(someClass, anotherClass);    // friend function
  };
  ```
  `{ }` used instead of `( )` for argument type checking
  ```cpp
  someClass var_0;               // default constructor
  someClass var_1(10, 11);       // custom constructor
  someClass var_2{10, 11};       // custom constructor with argument type checking
  someClass var_3 = {10, 11};    // same as var_2
  ```
- **access specifiers/modifiers:** define how the members (variables & functions/methods) of a class can be accessed
  - **`public`:** accessible outside the class
  - **`protected`:** inaccessible outside the class
  - **`private`:** inaccessible outside the class but can be accessed in inherited classes
- **static variable:** exists once per class (not per object) and shared across all (base & derived class) objects, must be defined in source (not header) file  
example: count number of objects of a class
  ```cpp
  class countedClass
  {
      countedClass() { countedClass::count++; }
      ~countedClass() { countedClass::count--; }

      static int count;
  }
  ```
  **static function:** doesn't need an object to call, object required only when private members accessed, must be defined in source file
  ```cpp
  // static member function call
  someClass::staticFunc(args);
  ```
- **struct:** is a `class` where everything is `public`  
**braced initialization:** struct members should be uninitialized for this
  ```cpp
  struct someStruct
  {
      int a;
      string b;
  };

  void printStruct(someStruct& s)
  {
      cout << s.a << s.b << endl;
  }

  int main()
  {
      printStruct({10, "world"});    // braced initialization
      return 0;
  }
  ```
  **padding:** align members to natural address boundaries (usually processor word size)  
  **packing:** prevent padding  
  **bitfields:** specify the size (in bits) of the structure and union members  
  if bitfields used then pointer not possible since member sizes are (typically) smaller than granularity allowed by pointers (`char`)
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
- **resource acquisition is initialization (RAII):** resource allocation/acquisition/initialization is done by the constructor, while resource deallocation/release/deinitialization is done by the destructor
- **forward declaration:**
  ```cpp
  class someClass1;    // forward declaration
  class someClass2;    // forward declaration

  class someClass1
  {
      friend int sum(someClass1, someClass2);    //  error without forward declaration (someClass2 undefined)
  };

  class someClass2
  {
      friend int sum(someClass1, someClass2);
  };
  ```

### move semantics
- **lvalue:** occupies memory  
**rvalue:** everything else, defined using `&&`
- `std::move` converts lvalue to rvalue by transfering ownership so don't access a moved variable (undefined by cpp standard)  
performance better than copying but worse than passing by reference
  ```cpp
  int b = std::move(a);    // memory transferred to b
  ```
- **copy/move constructor/assignment operator:** move constructor/assignment operator used to take ownership of another object
  ```cpp
  myClass(myClass &other) {}                // copy constructor
  myClass &operator=(myClass &other) {}     // copy assignment operator

  myClass(myClass &&other) {}               // move constructor
  myClass &operator=(myClass &&other) {}    // move assignment operator
  ```
  ```cpp
  myClass a;                   // default constructor
  myClass b(a);                // copy constructor
  myClass c = a;               // copy constructor
  a = b;                       // copy assign operator

  myClass b(std::move(a));     // move constructor
  myClass c = std::move(b);    // move constructor
  a = std::move(b);            // move assign operator
  ```
- **`delete`:** to disallow certain functions
  ```cpp
  class someClass
  {
  public:
      int someFunc(int num) {}
      int someFunc(double size) = delete;
  }
  ```
- **rule of all or nothing:** define all 6 special functions (destructor + constructor + above 4) or define none  
if none defined `default` functions used, for something that cannot be moved (like `const`), move falls back to a copy and move marked as `delete`
  ```cpp
  myClass() = default;                 // autogenerated functions, may use shallow copy
  myClass(myClass &other) = delete;    // compilation error if called
  ```

### inheritance
- **inheritance:** inherit public & protected data & functions from another class  
separate 6 special functions & private members
  ```cpp
  class rectangleClass
  {
  public:
      rectangleClass(int w, int h) : width_(w), height_(h) {}

  protected:
      int width_;
      int height_;
  };

  class squareClass : public rectangleClass    // default private
  {
  public:
      squareClass(size) : rectangleClass(size, size) {}
  };
  ```
  - **`public`:** public & protected from base maintain their access specifier
  - **`protected`:** both will be  protected in derived class
  -  **`private`:** both will be private in derived class
- **composition:** combining simpler objects to make more complex ones  
inheritance is `is a` relationship, example: square is a rectangle  
composition is `has a` relationship, example: car has a wheel (& other objects)

### polymorphism
- **polymorphism:** ability to present same interface for differing underlying implementations, inherited classes may have different functionality but share a common interface
  - **compile-time:** function & operator overloading
  - **run-time:** function overriding, used for generic class references
    ```cpp
    derivedClass1 a;
    derivedClass2 b;
    baseClass& c = a;    // can be generic reference for derivedClass1 or derivedClass2
    ```
- **function overriding:** `virtual` function in base class can be overridden in derived class  
same function prototype in both base & derived, so need to check which function needs to be called in virtual table (extra cycles)
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
      // c11:     void print2() override {}
      // older:   virtual void print2() {}
  };

  int main()
  {
      derivedClass b;
      b.print1();    // print1 baseClass
      b.print2();    // print2 derivedClass
                     // but without virtual: print2 baseClass
      return 0;
  }
  ```
- **pure virtual function:** no base implementation, used to force all derived classes to override the function
  ```cpp
  virtual myFunc() = 0;
  ```
  **abstract class:** class with atleast one pure virtual function, cannot create object of this class  
**interface:** class with only pure virtual functions & no data members

## file & string stream
- **fstream:** read/write file
  ```cpp
  #include <fstream>
  std::fstream file(string& filename, Mode std::ios_base::mode);
  ```
  ```cpp
  // modes
  in        // for reading
  out       // for writing
  binary    // in binary mode
  app       // append output
  ate       // seek to EOF when opened
  trunc     // overwrite existing file
  ```
  **`ifstream`:** file stream with default mode `in`  
**`ofstream`:** file stream with default mode `out`
- **example: read line by line:**
  ```cpp
  while (getline(ifstream, string))
  {
      // process line
  }
  ```
- **example: write binary data:**
  ```cpp
  std::ofstream output_file("output.bin", ios_base::out | ios_base::binary);
  output_file.write(reinterpret_cast<char*>(data), sizeof(data));
  ```
- **example: read regular columns:** every line should have same number of columns
  ```cpp
  // 1   one     0.1
  // 2   two     0.2
  // 3   three   0.3

  int a;
  string b;
  float c;

  std::ifstream input_file("input_data.txt", ios_base::in);

  while (input_file >> a >> b >> c)    // read values
  {
      std::cout << a << b << c << std::endl;    // print values in same order
  }
  ```
- **sstream:** allows a string to be treated like a stream
  ```cpp
  #include <sstream>

  // create string
  std::stringstream out_sstream;
  out_sstream << "pi " << 3.14;
  std::string str_out = out_sstream.str();
  std::cout << str_out << std::endl;    // pi 3.14

  // reset sstream string
  out_sstream.str("");

  // parse string
  std::stringstream in_sstream(str_out);
  std::string str;
  float val;
  in_sstream >> str >> val;    // str: "pi" & val: 3.14
  ```

## memory
- **type qualifiers:**
  - **const:** read-only
  - **volatile:** value might be changed by something beyond the program (so not cached)  
  use `const volatile` for read-only status register
  - **restrict:** optimization hint to compiler that during its lifetime no other pointer will be used to access the same memory  
  not part of C++ standard but most compilers support it
  - **atomic:** read-modify-write operators guaranteed in single instruction, free from data races
    ```cpp
    #include <iostream>
    #include <sstream>
    #ifdef __STDC_NO_ATOMICS__
        #error no atomics
    #endif

    _Atomic const int *p1;     // pointer to atomic const int
    const atomic_int *p2;      // same
    const _Atomic(int) *p3;    // same
    ```
- **storage class specifier:**
  - **auto:** default
  - **register:** hint to compiler to place it in processor's register
  - **static:** local static variable keeps its value between invocations, global static variable/function local to translation unit (but prefer)
  - **extern:** used for external linkages, only mention specifier for declaration & keep it in a header, cross checking takes place between translation units
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
    printf("%d\n", g_val);          // 77
    printf("%d\n", increment());    // 78
    ```
  - **mutable:** C++ only, to allow a particular data member of const object to be modified, example: mutexes
- **1s complement:** invert all bits  
**2s complement:** add 1 to 1s complement
  ```cpp
  00011001    //  25
  11100110    //     (1s complement)
  11100111    // -25 (2s complement)
  ```
- **integer representation:** negative numbers stored as 2s complement  
**signed:** `-2^(n-1)` to `2^(n-1) - 1`  
**unsigned:** `0` to `2^(n) - 1`  
**integer promotion:** `signed` promoted to `unsigned` when mixed
  ```cpp
  unsigned int a = 6;
  int b = -20;
  (a + b > 6) ? printf(">6") : printf("<=6");    // >6
  ```
  **sign extension:** preserving sign while increasing number of bits of a binary number
  ```cpp
  1001 0110              //  8 bit (-106)
  1111 1111 1001 0110    // 16 bit (-106)
  ```
  both `128` & `-128` have same 8-bit 2s complement (`10000000`), so `-128` assumed since all bit-patterns with MSB (sign bit) set are negative
- **float representation (IEEE 754):** single precision `1 + 8 + 23`, double precision `1 + 1 + 53`  
![](./media/cplusplus/IEEE754.png)
  ```cpp
  263.3                             // floating number
  100000111.0100110011...           // binary
  1.000001110100110011... x 2^8     // scientific notation, true_exponent = 8
                                    // 1 is invisible leading bit
  sign = 0
  exp = 8 + 127 = 10000111          // exponent = true_exponent + bias
                                    // bias = 2^(exp_bits-1)-1
  mant = 00000111010011001100110    // bits after leading bit

  0 10000111 00000111010011001100110
  ```
- **endianness:** order in which a sequence of bytes is stored in computer memory
  ```cpp
  value:          0x12345678
  big endian:     12, 34, 56, 78  // most significant byte at smallest memory address
  little endian:  78, 56, 34, 12  // least significant byte at smallest memory address
  ```
- **swap endianness:**
  ```cpp
  uint32_t num = 9;
  uint32_t b0, b1, b2, b3;
  uint32_t res;

  b0 = (num & 0x000000ff) << 24u;
  b1 = (num & 0x0000ff00) << 8u;
  b2 = (num & 0x00ff0000) >> 8u;
  b3 = (num & 0xff000000) >> 24u;

  res = b0 | b1 | b2 | b3;
  ```
- **memory layout:** each of the six different segments stores different parts of code and have their own read & write permissions  
![](./media/cplusplus/memory_layout.png)
  - **text:** read only instructions  
  `.rodata` read only const global data
  - **data:** initialized `global` & `static` variables (but `static` functions will be in text section)
  - **bss (b​lock started by symbol):** uninitialized `global` & `static` variables, only size mentioned in executable, allocated after program load and initialized with 0 after allocation
  - **heap:** dynamically allocated during runtime, `std::bad_alloc` error if out of heap  
  **memory leak:** heap not dealloced or address lost (pointer reassigned)  
  **dangling pointer:** pointing to dealloced memory  
  **wild pointer:** pointing to random address
    ```cpp
    float* f_ptr = new float[num];    // allocate array
    delete[] f_ptr;                   // delete array
    ```
  - **stack:** simple last-in-first-out (LIFO) structure that stores local variables, function arguments & inheritance virtual function table  
  **stack pointer:** keeps track of top of the stack  
  **stack overflow:** program attempts to use more memory than is available on stack, usually due to deep/infinite recursion leading to stack shortage  
  **stack frame:** function data (return addr, args, local vars) pushed onto stack  
  example: on ARM first 4 args stored `r0` to `r3`  
  `ebp` (frame pointer) is used to backup `esp` (stack pointer), while `esp` is being modified by the current function  
  ![](./media/cplusplus/stack.png)
- **segmentation fault:** occurs when a program attempts to access a memory location it does not have permission to access or access differently than it is supposed to (like write to read-only location)
- **shallow copying:** just copy pointer not the underlying data (used in default copy constructor/assignment operator)  
can lead to dangling pointer when object shallow copied  
**deep copying:** create new pointers and copy data into it

## pointers
- **pointer vs reference:**
  - own memory vs alias
  - no init required vs init in declaration
  - can reassign vs cannot
  - can be NULL vs cannot
  - indirection (levels of pointers) vs single level
  - can apply arithmetic operations vs cannot
  - can store in vector/array vs cannot
- **arrow operator:** `obj->myFunc()` is same as `(*obj).myFunc()`
- **pointer polymorphism:** used for strategy pattern
  ```cpp
  derivedClass a;
  baseClass *b = &a;
  ```
- **const pointers:**
  ```cpp
  // read right to left
  const int *         // pointer to int that is const
  int *const          // const pointer to int
  const int *const    // const pointer to int that is const
  ```
- **smart pointer:** wrapper class over a raw pointer that owns heap memory and manages its lifetime, when the object is destroyed it frees the memory as well
  ```cpp
  #include <memory>
  sPtr.get();    // get raw pointer
  ```
  - **unique:** can be moved but cannot be copied, memory always owned by single unique pointer
    ```cpp
    auto uPtr = std::unique_ptr<myType>(new myType);          // default constructor
    auto uPtr = std::unique_ptr<myType>(new myType(args));    // custom constructor
    auto uPtr = std::make_unique<myType>(args);               // C++14
    ```
  - **shared:** `std::shared_ptr`, can be copied, `usage_count` incremented/decremented when copied/destructed, memory freed when `usage_count == 0`
    ```cpp
    auto sPtr = std::shared_ptr<myType>(new myType);          // default constructor
    auto sPtr = std::shared_ptr<myType>(new myType(args));    // custom constructor
    auto sPtr = std::make_shared<myType>(args);               // C++11
    sPtr.use_count();                                         // return usage_count
    sPtr.reset(ptr);                                          // decrease usage_count
    ```
    ```cpp
    class A
    {
    public:
        A(int a) { std ::cout << "alive" << std::endl; }
        ~A() { std ::cout << "dead" << std::endl; }
    };

    int main()
    {
        // equivalent to std::shared_ptr<A>(new A(10));
        auto a_ptr = std ::make_shared<A>(10);              // alive
        std ::cout << a_ptr.use_count() << std ::endl;      // 1
        {
            auto b_ptr = a_ptr;                             // alive
            std ::cout << a_ptr.use_count() << std ::endl;  // 2
        }
        std ::cout << "main scope\n";
        std ::cout << a_ptr.use_count() << std ::endl;      // 1

        return 0;                                           // dead
    }
    ```
- **example: smart pointer with local variable:** both stack & smart pointer will try to dealloc that memory leading to error
  ```cpp
      int a = 0;
      auto a_ptr = std ::unique_ptr<int>(&a);
      return 0;    // *** Error in `file ': free (): invalid pointer: 0 x00007fff30a9a7bc ***
  ```
- **example: smart pointer polymorphism:** good way of using smart pointer
  ```cpp
  std::vector<unique_ptr<baseClass>> vec;

  // first method: "new derivedClass" passed to constructor of unique_ptr
  vec.push_back(new derivedClass);

  // second method: need to move (default is copy)
  auto var = unique_ptr<derivedClass>(new derivedClass);
  vec.push_back(std::move(var));

  return 0;    // both dealloced
  ```
- **type casting:** converting expression of given type into another type
  - **implicit:** change types without changing the value, happens automatically, lower data type converted to higher type
    ```cpp
    short a = 1024;
    int b = 5;
    b = a;    // implicit conversion
    ```
  - **explicit:** force type conversion, two types
    ```cpp
    float a = 1.2;
    int b = (int)a + 1;    // C-like notation explicit conversion
    int c = int(a) + 1;    // functional C-like explicit conversion
    ```
    ```cpp
    unsigned char u = (unsigned char)(-9);    // same bit pattern (2s complement), 247
    ```
- **type casting operators:**
  ```cpp
    // newType new_var = static_cast<newType>(var);
    static_cast         // compile-time implicit conversion
    const_cast          // remove const from const ref of non-const variable
    reinterpret_cast    // reinterpret bytes of one type as another type
    dynamic_cast        // runtime conversion of derivedClass pointer to baseClass pointer, nullptr if failed
    ```
- **function pointer:** stores the address of a function
  ```cpp
  int foo(int);       // function
  int *foo(int);      // function returning int*
  int (*foo)(int);    // function pointer, by changing precedence using ()
  ```
  ```cpp
  int foo(int arg)
  {
      printf("foo %d\n", arg);

      return arg;
  }

  int main()
  {
      int (*func_ptr)(int);
      func_ptr = &foo;
      int ret = (*func_ptr)(10);    // foo 10

      // OR
      func_ptr = foo;
      int ret = func_ptr(20);       // foo 20

      printf("ret %d\n", ret);      // ret 20

      return 0;
  }
  ```
- **spiral/right-left rule:**
  ```
  read these symbols as:
  *          pointer of                      - always on left side
  []         array of                        - always on right side
  ()         function returning/expecting    - always on right side

  step1: find the identifier, this is the starting point
  step2: look at symbols on the right of identifier, continue until you run out of symbols or hit `)`
  step3: look at the symbols to the left of identifier, continue until you run out of symbols ot hit `(`
  step4: repeat step 2 & 3 still complete declaration is formed
  ```
  ```cpp
  int *p[];

  int *p[];            // step1
      ^                // p is

  int *p[];            // step2, cant move right
        ^^             // p is array of

  int *p[];            // step3
      ^                // p is array of pointer to

  int *p[];            // step3
  ^^^                  // p is array of pointer to int
  ```
  ```cpp
  int *(*func())();

  int *(*func())();    // step1
         ^^^^          // func is

  int *(*func())();    // step2, cant move right
             ^^        // func is function returning

  int *(*func())();    // step3, cant move left
        ^              // func is function returning pointer to

  int *(*func())();    // step2, cant move right
                ^^     // func is function returning pointer to function returning

  int *(*func())();    // step3
      ^                // func is function returning pointer to function returning pointer to

  int *(*func())();    // step3
  ^^^                  // func is function returning pointer to function returning pointer to int
  ```
  ```cpp
  int (*(*foo)(char*,double))[9][20];

  // without arguments or array sizes
  int (*(*foo)())[][];

  // foo is pointer to function expecting (char*, double) and 
  // returning pointer to 2D array (size 9X20) of int
  ```
  ```cpp
  int i;             // an int
  int *p;            // an int pointer (ptr to an int)
  int a[];           // an array of ints
  int f();           // a function returning an int
  int **pp;          // a pointer to an int pointer (ptr to a ptr to an int)
  int (*pa)[];       // a pointer to an array of ints
  int (*pf)();       // a pointer to a function returning an int
  int *ap[];         // an array of int pointers (array of ptrs to ints)
  int aa[][];        // an array of arrays of ints
  int *fp();         // a function returning an int pointer
  int ***ppp;        // a pointer to a pointer to an int pointer
  int (**ppa)[];     // a pointer to a pointer to an array of ints
  int (**ppf)();     // a pointer to a pointer to a function returning an int
  int *(*pap)[];     // a pointer to an array of int pointers
  int (*paa)[][];    // a pointer to an array of arrays of ints
  int *(*pfp)();     // a pointer to a function returning an int pointer
  int **app[];       // an array of pointers to int pointers
  int (*apa[])[];    // an array of pointers to arrays of ints
  int (*apf[])();    // an array of pointers to functions returning an int
  int *aap[][];      // an array of arrays of int pointers
  int aaa[][][];     // an array of arrays of arrays of int
  int **fpp();       // a function returning a pointer to an int pointer
  int (*fpa())[];    // a function returning a pointer to an array of ints
  int (*fpf())();    // a function returning a pointer to a function returning an int
  ```

## templates
- **generic programming:** separate algorithms from data type
- **templates:** compile-time type-independent/generic algorithms (`<T>` macro expanded), no definition till expansion is done (else linker error)  
**template function:** can use any type that is copy constructable, assignable & defined by the time template compiled (custom classes)
  ```cpp
  template <typename T>    // can use typename or class keyword
  T func1(const T &arg1)
  {
  }

  func(10);       // type inferred by compiler
  func<int>();    // explicit type (in case data type cannot be determined by compiler)
  ```
  **template class:** used for meta programming (programs that modify programs), compiler generates objects based on types we passed
  ```cpp
  template <typename T>
  class myClass
  {
  public:
      myClass(const T &var) : var_(var){};

  private:
      T var_;
  }

  myClass<int> my_object(10);
  ```
- **specialization:** different template function/class implementation for a specific type
  ```cpp
  template <typename T>    // generic
  T func()
  {
  }

  template <>              // specialized
  int func()
  {
  }

  func<int>();             // specialized
  func<double>();          // generic
  ```
- **where to keep template:** a template is a pattern that the compiler uses to generate a family of classes or functions, so for the compiler to generate the code it must see both the template definition (not just declaration) and the specific types/whatever used to fill-in the template, so keep declaration & definition in a header & include it

## error handling
- **exception:** thrown when there is an error, constructor of exception receives a string error message, use `what()` to get exception string
  - `logic_error`
  - `invalid_argument`
  - `domain_error`: not defined for certain domain
  - `length_error`: exceeds max size
  - `out_of_range`: access out of bounds
  - `runtime_error`
  - `range_error`: requested operation doesn't make mathematical sense in the domain considered, example: `sqrqt(negative_number)` in real domain
  - `overflow_error`/`underflow_error`: result exceeds capacity of underlying type
- `try` ⟶ `throw` ⟶ `catch`
  ```cpp
  #include <stdexcept>

  void someFunc(void)
  {
      if (badEvent)
      {
          string msg = "error string";
          throw runtime_error(msg);
      }
  }

  try
  {
      x = someFunc(a, b, c);  // throws exception
  }
  catch (runtime_error &exp)
  {
      cerr << "runtime error: " << exp.what() << endl;
  }
  catch (logic_error &exp)
  {
      cerr << "logic error: " << exp.what() << endl;
  }
  catch (exception &exp)  // generic
  {
      cerr << "some exception: " << exp.what() << endl;
  }
  catch (...)  // catch everything
  {
      cerr << "unknown exception" << endl;
  }
  ```

## misc
- **using:** create type aliases, `using newType = oldType;`, similar to `typedef`, creates local alias if used within function scope
  ```cpp
  using image3f = image<float, 3>;
  using vector3d = double[3];  // not possible using `typedef`
  ```
- **why typedef over macro:**
  ```cpp
  #define type1 struct s *
  typedef struct s *type2;

  type1 a, b;  // "a" pointer-to struct but "b" just struct
  type2 c, d;  // both "c" & "d" pointer
  ```
- **name mangling:** encoding of function/variable names so linker can separate common names (overloading, namespaces)  
to link C code use:
  ```cpp
  extern "C"
  {
      ....
  }
  ```
- **maximum munch rule:** compiler bites off biggest legal chunk
  ```cpp
  c = a+++b;  // a++ + b
  ```
- **format specifiers:**
  ```cpp
  %c  // char
  %s  // string
  %i  // int
  %u  // uint
  %o  // unsigned octal
  %x  // unsigned hex
  %e  // exponent notation
  %f  // float
  %g  // selects shorter of %f & %e, no trailing 0s
  %p  // pointer
  ```
- **data type constants**
  ```cpp
  0x  // hex
  0   // oct
  U   // uint
  L   // long int, UL
  LL  // long long int, ULL
  F   // float
  ```
- **enum:** assign names to integral constants, by default starts with 0
  - **unscoped:** can implicitly convert
  - **scoped:** implicit conversion leads to error, use `static_cast` if required
  ```cpp
  enum uFoo  // unscoped
  {
      a,
      b,
      c = 1,
      d = b + c
  };

  enum class sFoo  // scoped
  {
      a,
      b,
      c = 1,
      d = b + c
  };

  int enumValue = uFoo::a;  // implicit conversion
  int enumValue = sFoo::a;  // error
  ```
- **union:** different variables of different types in same memory location  
use when member variables are used in either-or but never both fashion
  ```cpp
  union unn
  {
      int i;
      char c;
  };
  ```
- **typedef struct:**
  ```cpp
  typedef struct S_
  {
      int x;
  } S;

  // same as
  struct S_
  {
      int x;
  };
  typedef struct S_ S;
  ```
- **nested struct/union:**
  ```cpp
  typedef struct image
  {
      struct coordinate
      {
          int x;
          int y;
      };
      struct coordinate pos;
  } image;
  ```
- **lambdas:** function declared without name
  ```cpp
  auto plus_one = [](const int value) { return value + 1; };
  ```
- **functor** class that acts like a function, done by overloading `operator ()`
  ```cpp
  struct plusOne
  {
      int operator()(const int value) const { return value + 1; }
  };

  int main()
  {
      plusOne plus_one;
      assert(plus_one(2) == 3);

      return 0;
  }
  ```

### cpp core guidelines
- **basics:**
  ```cpp
  int some_random_var;  // snake case
  int some-random-var;  // kebab case
  int someRandomVar;    // camel case
  int SomeRandomVar;    // pascal case
  ```
- **naming:**
  ```cpp
  // snake_case: variables
  int some_var;
  // CAPITALIZED_SNAKE_CASE: constants & macros
  const int SOME_CONSTANT_VAR = 10;
  // camelCase: functions & classes
  int someFunction(void);
  ```

### standard template library
- STL
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