# C++ SUMMARY 

### Declarations
```cpp
int a[10];                      // Array of 10 ints (a[0] through a[9])
int a[] = {0,1,2};              // Initialized array (or a[3]={0,1,2}; )
int a[2][2] = {{1,2},{4,5}};    // Array of array of ints
char s[] = "hello";             // String (6 elements including '\0')
string s = "Hello"              // Creates string object with value "Hello"
int* p;                     	// p is a pointer to (address of) int
char* s = "hello";              // s points to unnamed array containing "hello"
void* p = nullptr;              // Address of untyped memory (nullptr is 0)
int& r = x;                     // r is a reference to (alias of) int x

enum class Color {Red,Blue};    // Color is a strict type with values Red and Blue
Color x = Color::Red;           // Assign Color x to red
typedef String char*;           // String s; means char* s;
const int c = 3;                // Constants must be initialized, cannot assign to
const int* p = a;               // Contents of p (elements of a) are constant
int* const p = a;               // p (but not contents) are constant
const int* const p = a;         // Both p and its contents are constant
```

### STORAGE Classes
```cpp
int x;                      // Auto (memory exists only while in scope)
static int x;               // Global lifetime even if local scope
extern int x;               // Information only, declared elsewhere (rare)
```

### Functions
```cpp
int f(int x, int y);    // f is a function taking 2 ints and returning int
inline f();             // Optimize for speed
```
```cpp
int main()  { statements... }     // or
int main(int argc, char* argv[]) { statements... } // or
int main(int argc, char** argv) { statements... }
```
`argv[]` (argument vector) is an array of `argc` (argument count) strings from the command line.
By convention, `main` returns status `0` if successful, `1` or higher for errors.

Functions with different parameters may have the same name (overloading). Operators except `::` `.` `.*` `?:` may be overloaded.

### Expressions
Operators are grouped by precedence, highest first. Unary operators and assignment evaluate right to left. All
others are left to right.

```cpp
t.x                        // Member x of struct or class t
p->x                       // Member x of struct or class pointed to by p
typeid(x)                  // Type of x

~x                          // Bitwise complement of x
x << y                      // x shifted y bits to left (x * pow(2, y))
x >> y                      // x shifted y bits to right (x / pow(2, y))

&x                          // Address of x
*p                          // Contents of address p
new T(x, y)                 // Address of a T initialized with x, y
new T[x]                    // Address of allocated n-element array of T
delete p                    // Destroy and free object at address p
delete[] p                  // Destroy and free array of objects at p

throw x                     // Throw exception, aborts if not caught
```
> T = type, e.g. int.

### `fstream` (File I/O)
```cpp
ifstream f1("filename");    // Open text file for reading

if (f1)                     // Test if open and input available
    f1 >> x;                // Read object from file

f1.get(s);                  // Read char or line
f1.getline(s, n);           // Read line into string s[n]
ofstream f2("filename");    // Open file for writing
```

### `string` (Variable sized character array)
```cpp
string s1, s2="hello";    // Create two strings
s1.size(), s2.size();     // Number of characters: 0, 5
s1 += s2 + ' ' + "world"; // Concatenation
s1 == "hello world"       // Comparison, also <, >, !=, etc.
s1[0];                    // element at index 0 of s1 = 'h'
s1.c_str();               // Convert to const char*
s1 = to_string(12.05);    // Converts number to string
getline(cin, s);          // Read line ending in '\n'
```

### `vector` (Variable sized array/stack with built in memory allocation)
```cpp
vector<int> a(10);        // a[0]..a[9] are int (default size is 0)
vector<int> b{1,2,3};     // Create vector with values 1,2,3
a.size();                 // Number of elements (10)
a.push_back(3);           // Increase size to 11, a[10]=3
a.back()=4;               // change a[10]=4;
a.pop_back();             // Decrease size by 1, remove last element
a.front();                // first element a[0];
a[20]=1;                  // Crash: not bounds checked
a.at(20)=1;               // Like a[20] but throws out_of_range()

vector<int> b(a.begin(), a.end());  // b is copy of a
```

### `set` (store unique elements)
```cpp
set<int> s;               // Set of integers
s.insert(123);            // Add element to set
if (s.find(123) != s.end()) // Search for an element
    s.erase(123);
cout << s.size();         // Number of elements in set
```

### `algorithm`
```cpp
min(x, y); max(x, y);           // Smaller/larger of x, y (any type defining <)
swap(x, y);                     // Exchange values of variables x and y
sort(a, a+n);                   // Sort array a[0]..a[n-1] by <
sort(a.begin(), a.end());       // Sort vector or deque
reverse(a.begin(), a.end());    // Reverse vector or deque
```

---
### Pointer vs. reference

**References** 				 | **Pointers**
-----------------------------------------|----------------
Must be initialized when it it's created.| Can be initialized any time.
Once initialized, we cannot reinitialize.| Can be reinitialized any number of time.
Can never have a NULL reference.	 | Can be NULL.
Automatically dereferenced.		 | `*` is used to dereference.

---
## 1.0 C++ Classes
### 1.1 Class Syntax
#### 1.1.1 Class Declaration (`.h` file)
Here's a simple class representing a polygon, a shape with any number of sides. The class *declaration* typically goes in the header file, which has the extension `.h`. The *declaration* gives the class name, any classes it may extend, declares the members and methods, and declares which members/methods are public, private, or protected.

```cpp
// File: polygon.h
#include <string>

class Polygon {
// Private members and methods are only accessible via methods in the class definition
private:
    int num_sides;    	// Number of sides
// Protected members and methods are only accessible in the class definition or by classes who extend this class
protected:
    string name;   // Name of the polygon

// Public members and methods are accessible to anyone who creates an instance of the class
public:
    Polygon(const int num_sides, const std::string & name); // Constructors
    // This constructor takes the number of sides and name as arguments

    // Getters and Setters
    int GetNumSides(void) const;
    void SetNumSides(const int num_sides);
    string& GetName(void) const;
    void SetName(const string & name);
};
```

#### 1.1.2 Class Definition (`.cpp` file)
The class *definition* typically goes in the `.cpp` file. The *definition* extends the declaration by providing an actual implementation of whatever it is that you're building.

```cpp
// File: polygon.cpp
#include <string>
#include "polygon.h"    // Obtains the class declaration

// Constructor
// You must scope the method definitions with the class name (Polygon::)
Polygon::Polygon(const int num_sides, const string & name) {
    this->num_sides = num_sides;    // 'this' is a pointer to the instance of the class. 
    // Members are accessed via the -> operator
    this->name = name;	// we use 'this->' to avoid shadowing the member variable since the argument shares the same name
}

// Get the number of sides
int Polygon::GetNumSides(void) const {	// The 'const' here tells the compiler that you guarantee that you won't modify the object when this function is called. This allows it to perform optimizations that it otherwise may not be able to do.
    return this->num_sides;
}

// Set the number of sides
void Polygon::SetNumSides(const int num_sides) {this->num_sides = num_sides;}

// Get the name
string& Polygon::GetName(void) const {return this->name;}

// Set the name
void Polygon::SetName(const std::string& name) {this->name = name;}
```

> NOTE: Regarding the use of `this->` in a class definition, there are places where it's strictly necessary for readability, e.g. when your method parameter shares the exact same name as a member variable, you use `this->` to avoid what's called shadowing. However, some prefer to always use `this->` explicitly regardless of whether it's necessary. 

* How do I refer to a field when a method argument has the same name? Use `this`: a pointer to the current instance.

> `a->b = (*a).b`

#### 1.1.3 Class Utilization (Another `.cpp` file)
```cpp
// File: main.cpp
#include <string>
#include <iostream>
#include "Polygon.h"    // Obtains the class declaration

int main(int argc, char * argv[]) {
    // Create a polygon with 4 sides and the name "Rectangle"
    Polygon polygon = Polygon(4, "Rectangle");

    // Prints: "Rectangle has 4 sides"
    cout << polygon.GetName() << " has " << polygon.GetNumSides() << " sides"<<endl;

    // Change number of sides to 3 and rename to "Triangle"
    polygon.SetNumSides(3);
    polygon.SetName("Triangle");
}
```

#### 1.1.4 Getters and Setters
A shortcut often used for Getters/Setters is to define them in the class declaration (`.h`) file as follows:
```cpp
// File: car.h
#include <string>

class Car {
private:
    int year;
    string make;

public:
    int GetYear(void) const { return this->year; }
    void SetYear(const int year) { this->year = year; }
    string& GetMake(void) const { return this->make; }
    void SetMake(const std::string& make) { this->make = make; }
};
```

> If you have getters and setters for all of your members, you may want to reconsider the design of your class. Could a variable be set once in the constructor and left const thereafter? Does it need to be modified at all? Is it set somewhere else in another method, perhaps even indirectly?

### 1.2 Inheritance
A class can extend another class, meaning that the new class inherits all of the data from the other class, and can also override its methods, add new members, etc. Inheritance is the key feature required for polymorphism.

**Example:** the class `Rectangle` can inherit from the class `Polygon`. You would then say that a `Rectangle` extends from a `Polygon`, or that class `Rectangle` is a sub-class of `Polygon`. In plain English, this means that a `Rectangle` is a more specialized version of a `Polygon`. Thus, all rectangles are polygons, but not all polygons are rectangles.

#### 1.2.1 `Rectangle` Declaration (`.h` file)
```cpp
// File: rectangle.h
#include <string>       // Explicitly include the string header, even though polygon.h also includes it
#include "polygon.h"	// You must include the declaration in order to extend the class

/* We extend from Polygon by using the colon (:) and specifying which type of inheritance
will be used (public inheritance, in this case) */
class Rectangle : public Polygon {
private:
    int length;
    int width;
    // 'num_sides' and 'name' are already inherited from Polygon

public:
    // Constructors
    explicit Rectangle(const string &name);
    Rectangle(const string& name, const int length, const int width);

    // Getters and Setters
    const int GetLength(void) const { return this->length; }
    void SetLength(const int) { this->length = length; }
    const int GetWidth(void) const { return this->width; }
    void SetWidth(const int) { this->width = width; }
    // NOTE: getters/setters for 'num_sides' and 'name' are already inherited from Polygon

    const int Area(void) const;
};
```

> NOTE: The inheritance access specifier (`public`, `protected`, or `private`) is used to determine the type of inheritance. If this is omitted then `private` inheritance is used by default. **Public inheritance is by far the most common type of inheritance**.

#### 1.2.2 `Rectangle` Definition (`.cpp` file)
```cpp
// File: rectangle.cpp
#include "rectangle.h"	// Only need to include 'Rectangle', since 'Polygon' is included in 'rectangle.h'

// This constructor calls the superclass (Polygon) constructor and sets the name and number of sides to '4', and then sets the length and width.
Rectangle::Rectangle(const string& name, const int length, const int width) : Polygon(4, name) {
    this->length = length;
    this->width = width;
}

// This constructor calls the superclass (Polygon) constructor, but sets the length and width to a constant value
// The explicit keyword is used to restrict the use of the constructor.
explicit Rectangle::Rectangle(const string &name) : Polygon(4, name) {
    this->length = 1;
    this->width = 1;
}

// Compute the area of the rectangle
int Rectangle::Area(void) const {
    return length*width;
}
```

#### 1.2.3 `Rectangle` Utilization (Another `.cpp` file)
```cpp
// File: main.cpp
#include <iostream>
#include "Rectangle.h"

int main(int argc, char* argv[]) {
    Rectangle rectangle = Rectangle("Square", 6, 6);
    // Prints "Square has 4 sides, and an area of 36"
    cout<<rectangle.GetName()<<" has "<<rectangle.GetNumSides()<<" sides, and an area of "<<rectangle.Area();
}
```

### 1.3 Class Polymorphism
Polymorphism describes a system in which a common interface is used to manipulate objects of different types. In essence various classes can inherit from a common interface through which they make certain guarantees about which methods/variables are available for use. By adhering to this common interface, one can use a pointer to an object of the base interface type to call the methods of any number of extending classes. The `virtual` keyword is used to ensure runtime polymorphism for class methods.

#### 1.3.1 Motivation
Considering a shape to be any 3 or more sided polygon from which we can compute certain attributes (like the shape's area), let's extend from it to create a rectangle class from which we can set the length/width and a circle class in which you can set the radius. **In both cases, we want to be able to compute the area of the shape.**

```cpp
// File: shape.h
#include <cmath> // M_PI constant

class Shape {//....};

class Rectangle : public Shape {
private:
    double length;
    double width;

public:
    // Constructor using a member initializer list instead of assignment in the method body
    Rectangle(const double w, const double l) : width(w), length(l) {}
    // Compute the area of a rectangle
    double Area(void) const {
        return length * width;
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    explicit Circle(double r) : radius(r) {}
    // Compute the area of a circle
    double Area(void) const {
        return M_PI*radius*radius;  // pi*r^2
    }
};
```

So, we have our two classes, `Rectangle` and `Circle`, but in this case inheriting from `Shape` isn't really buying us anything. To make use of polymorphism we need to pull the common `Area()` method into the base class as follows, by using virtual methods.

#### 1.3.2 Virtual Methods
Imagine you want to have a pointer to a shape with which you want to compute the area of that shape. E.g. you want to hold shapes in some sort of data structure, but you don't want to limit yourself to just rectangles or just circles; you want to support all objects that call themselves a 'Shape'. Something like:

```cpp
Rectangle rectangle(2.0, 5.0);  // params = length, width
Circle circle(1.0);             // param = radius

// Point to the rectangle
Shape* a_shape = &rectangle;

a_shape->Area();  // Returns 10.0 (2*5)

// Point to the circle
Shape* b_shape = &circle;
b_shape->Area();  // Returns 3.14... (pi*1^2)
```

The way to achieve this is to use the `virtual` keyword on the base class methods, which specifies that when a pointer to a base class invokes the method of an object that it points to, it should determine, at runtime, the correct method to invoke. That is, when `a_shape` points to a `Rectangle` it invokes `Rectangle::Area()` and if `b_shape` points to a `Circle` it invokes `Circle::Area()`.

Virtual methods are employed as follows:
```cpp
#include <cmath>

class Shape {
public:
    virtual ~Area() {} // Virtual destructor (VERY IMPORTANT, SEE NOTE BELOW)

    // **Virtual area method**
    virtual double Area() const { return 0.0; }
};

class Rectangle : public Shape {
private:
    double length;
    double width;

public:
    Rectangle(double w, double l) : width(w), length(l) {}

    // Override the Shape::Area() method with an implementation specific to Rectangle
    double Area() const override {
        return length * width;
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    explicit Circle(double t) : radius(r) {}
    
    // Override the Shape::Area() method with an implementation specific to Circle
    double Area() const override {
        return M_PI * radius * radius; // pi*r^2
    }
};
```

> NOTE: It is very important that a default virtual destructor was included after adding the virtual `Area()` method to the base class. Whenever a base class includes even a single virtual method, it must include a virtual destructor so that the correct destructor(s) are called in the correct order when the object is eventually deleted.

This is called runtime polymorphism because the decision of which implementation of the `Area()` method to use is determined during program execution based on the type that the base is pointing at. It is implemented using the virtual table mechanism. 

In the example above, if a class extends from `Shape` but doesn't include an override of `Area()` then calling the `Area()` method will invoke the base class method which (in the implementation above) returns `0.0`. In some cases, you may want to **enforce** that sub-classes implement this method. This is done by not providing a default implementation, thus making it what is called a *pure virtual* method.

```cpp
class Shape {
public:
    virtual ~Area() {}
    virtual double Area() const = 0;
};
```

In general a class with only pure virtual methods and a virtual destructor is called an *abstract class* or *interface* and is typically named as such (e.g. `ShapeInterface`). An interface class guarantees that all extending classes implement a specific method with a specific method signature.

### Special Methods
#### Constructor and Destructor
All classes have at least one constructor and a destructor, even if they are not explicitly defined. The constructor and destructor assist in managing the lifetime of the object. The *constructor* is invoked when an object is created and the *destructor* is invoked when an object is destroyed (either by going out of scope or explicitly using `delete`). The constructor establishes a class invariant, a set of assertions guaranteed to be true during the lifetime of the object, which is then removed when the destructor is called. If a constructor with parameters is defined, the default constructor is no longer available – Without a default constructor, we can’t declare arrays without initializing.

* *Constructor method has the same name as the class, and are automatically run when the object is created*

* *Destructor method has the same name as the class with the addition of a (~) in front. Destructor methods are run when the object is deleted, and are typically used to clean up after a object. E.g. when the object uses a pointer.*

---
##### Use of `explicit` in Constructors
The `explicit` keyword should be used in single-argument constructors to avoid a situation in which the constructor is implicitly invoked when a single argument is given in place of an object. Consider the following `Array` class:

```cpp
class Array {
private:
    int size;

public:
    // Constructor
    Array(int size) {
        this->size = size;
    }

    ~Array() {} // Destructor

    // Print the contents of the array
    Print(const Array& array) {
        // ...
    }
};
```

The following is now legal but ambiguous:
```cpp
Array array = 12345;
```

It ends up being the equivalent of this:
```cpp
Array array = Array(12345);
```

Perhaps that's okay, but what about the following:
```cpp
array.Print(12345);
```
That's now legal, compileable code, but what does it mean? It is extremely unclear to the user.

To fix this, declare the single-argument `Array` constructor as `explicit`:
```cpp
class Array {
    int size;
    
public:
    explicit Array(int size) {
        this->size = size;
    }
    // ...
};
```

Now you can only use the print method as follows:
```cpp
array.Print(Array(12345));
```
and the previous `array.Print(12345)` is now a syntax error.

##### Member Initializer Lists
Member initializer lists allow you to initialize member variables in the definition of a method. This turns out to provide
some performance benefits for class-type member variables, since a call to the default constructor is avoided.

```cpp
class Car {
private:
    int year;
    int miles;
    std::string make;

public:
    Car(const int year, const int miles, const std::string & make) : year(year), miles(miles), make(make) {}
};
```

Using the initializer list is basically the same as the following more verbose constructor implementation.

```cpp
Car(const int year, const int miles, const std::string & make) {
    this->year = year;
    this->miles = miles;
    this->make = make;
}
```

#### `new` and `delete`
The `new` and `delete` operators (and their array counterparts, `new[]` and `delete[]`) are operators used to dynamically allocate memory for objects. When manually allocating memory dynamically, it is the responsibility of the programmer to manage the memory and properly delete objects that have been allocated.

#### Copy Constructor and Copy Assignment
Copy constructors and copy assigment operators allow one object to be constructed or assigned a copy of another object directly:
```cpp
Foo a(10);
Foo b(a);   	// (1): Copy via constructor
Foo c = a;	// (2): Copy via assignment operator
```

This is accomplished by supplying a copy constructor and an assigment operator overload, both of which have a special syntax
where they accept a const reference to an object of their same type.

```cpp
class Foo {
private:
    int data;

public:
    Foo() : data(0) {} 		// Default (no argument) constructor

    explicit Foo(const int v) : data(v) {} 	// Single argument constructor

    Foo(const Foo& f) : data(f.data) {} 	// Copy constructor

    Foo& operator=(const Foo& f) { 	// Copy assignment operator
        data = f.data;
        return *this;
    }
};
```

> The compiler will always provide a default constructor, a default copy constructor, and a default copy assignment operator, so for simple cases you will not have to implement them yourself.

Every time a data element is sent as a `by value` (i.e. not by reference or pointer) the copy constructor is used automatically. Copy constructors accepts one parameter: a reference to a object of the class it belongs to. The task of the copy constructor is to transfer data from the parameters object to the `this` object. If the data is just basic types and no pointers, then there is no need to create a copy constructor. All other cases create one!


#### 1.4.4 Move Constructor and Move Assignment (special)
Sometimes instead of performing a copy you instead wish to completely move data from one object to another. This requires the use of a move constructor and move assignement operator.

```cpp
class Movable {
private:
    Foo* data_ptr;

public:
    Movable(Foo data) : data_ptr(new Foo(data)) {}

    // Move constructor
    Movable(Movable&& m) {
        data_ptr = m.data_ptr; 	// Point to the other object's data
        m.data_ptr = nullptr;  	// Remove the other object's data pointer by setting it to nullptr
    }
    
    Movable& operator=(Movable&& m) { // Move assignment operator
        data_ptr = m.data_ptr;
        m.data_ptr = nullptr;
        return *this;
    }
    ~Movable() { delete data_ptr; }
};
```

The move constructor and assignment operator can be used as follows:
```cpp
Movable Bar() { // ... }

int main() {
    Movable a(Bar());       // Using the move constructor
    Movable b = Bar();		// Using the move assignment operator
}
```

Since `Bar()` creates an object that won't be used elsewhere and is deleted after the call, we can use the move constructor or move assignment operator to move the data to our object. A programming idiom called 'copy and swap' makes use of the move constructor and can be a useful idiom.

---
### 1.5 Operator Overloading
Operators such as `+`, `-`, `*`, etc. can be overloaded to provide a clear syntactic meaning to your own classes. E.g., when working with linear algebra you can overload the `+` operator to perform an element-wise addition of two vectors. Here's a brief example using complex numbers that allows you to use the `+` and `-` operators to easily add and subtract two complex numbers. There are two main ways to do operator overloading. The first is using normal member functions. The second uses the `friend` keyword and non-member methods that have access to the private member variables of the class.

Using normal member functions (requires a getter method for the member variables):

```cpp
// File: complex.h
class Complex {
private:
    double r = 0.0; // Real part, defaults to 0.0
    double i = 0.0; // Imaginary part, defaults to 0.0

public:
    Complex(const double r, const double i) : r(r), i(i) {}

    // Accessor methods
    double GetReal(void) const { return r; }
    double GetImaginary(void) const { return i; }

    // + Operator
    Complex operator+(const Complex& a, const Complex& b) {
        return Complex(a.GetReal() + b.GetReal(), a.GetImaginary() + b.GetImaginary());
    }

    // - Operator
    Complex operator-(const Complex& a, const Complex& b) {
        return Complex(a.GetReal() - b.GetReal(), a.GetImaginary() - b.GetImaginary());
    }
};
```

**Using `friend` methods:**

```cpp
// File: complex.h
class Complex {
private:
    double r = 0.0; // Real part, defaults to 0.0
    double i = 0.0; // Imaginary part, defaults to 0.0

public:
    Complex(const double r, const double i) : r(r), i(i) {}

    // + Operator (declaration only)
    friend Complex operator+(const Complex& a, const Complex& b);

    // - Operator (declaration only)
    friend Complex operator-(const Complex& a, const Complex& b);
};

// These are NOT member functions!
/* They can also be defined inside the class body but leaving them outside
	is a clearer reminder that they are not part of the class */

Complex operator+(const Complex& a, const Complex & b) {
    return Complex(a.r + b.r, a.i + b.i);
}

Complex operator-(const Complex& a, const Complex& b) {
    return Complex(a.r - b.r, a.i - b.i);
}
```

In either case, the new operators can be used as follows:
```cpp
int main() {
    Complex a(1, 2);    //  1 + 2i
    Complex b(5, 3);    //  5 + 3i
    Complex c = a + b;	//  6 + 5i
    Complex d = a - b;	// -4 - 1i
}
```

It's also often useful to overload the output stream operator to provide a custom output string displaying the object's
internal state in a human-readable format. This is done by overloading the `<<` operator and requires using the `<iostream>`
functionality.

```cpp
#include <iostream>

class Complex {
public:
    friend ostream& operator<<(ostream& os, const Complex& c);
};

// Definition
// Again, this is NOT a member function!
ostream& operator<<(ostream& os, const Complex& c) {
    os << c.r << " + " << c.i << "i";
    return os;
}

int main() {
    Complex a {1, 2};
    Complex b {5, 3};
    cout << a;     // Prints: 1 + 2i
    cout << a + b; // Prints: 6 + 5i
}
```

---
### 1.6 Templates
Templates are a very powerful abstraction allowing you to generate compile-time methods/classes/etc. for any number of types while writing only one implementation. Say you have a method that adds two floating point number together, and another to add two integers together:

```cpp
double Add(const double a, const double b) {return a + b;}
int Add(const int a, const int b) {return a + b;}
```

That's great, but since both floating point numbers and integers implement the `+` operator you can use a template to instead write one generic implementation of a method that can operate on doubles, ints, floats, and (in this case) any other type that implements the `+` operator. A simple templatized version of `Add` would look something like this:

```cpp
template <typename T>   // T becomes whatever type is used at compile-time
T Add(const T& a, const T& b) {
    return a + b;       // The type T must support the + operator
}

// Usages
int main() {
    Add<int>(3, 5);         // int version
    Add<double>(3.2, 5.8);  // double
    Add(3.45f, 5.0f);	    // we leave off the <float> here, since it can deduce the type from the context
    Complex a {1, 2};	    // Custom class
    Complex b {5, 3};
    Add(a, b);	            // Works because we added support for the + operator!
}
```

In this simple example the compiler would generate four different methods, one for each type. Templating allows you to write more concise and modular code at the expense of generating a larger executable. Templates are especially useful to create class templates. Class templates must be completely defined in a single header file.

```cpp
// File: storage.h
template <typename T>      // 'typename' is synonymous with 'class'!
class Container {
private:
    T data;
public:
    explicit Container(const T& d) : data(d) {}
};

// Usage
int main() {
    Container<int> a(1);
    Container<float> b(10.0f);
    Container<Container<int>> c(a);
}
```
-----
## 2.0 General C++ Syntax
### 2.1 Namespaces
To avoid symbol names conflicting with one another you can use namespaces to logically separate symbol names in to broad categories. Namespaces are an inherent feature of C++; when you create a class and refer to a method as `ClassName::Method()` you are essentially using a namespace feature intrinsic to classes. For a brief namespace example, suppose that you have two data structures, both of which implement a `Node` class. In the following code, namespaces are used to allow the compiler to distinguish between the two types.

```cpp
// File: list.h
namespace list {
template <typename T>
    struct Node {
        Node* next;
        Node* prev;
        T data;
    };
}; // namespace
```

```cpp
// File: main.cpp
#include "list.h"

int main() {
    list::Node<int> a;
};
```

The standard C++ library uses the namespace `std`, e.g. `std::cout`, `std::string`, `std::endl`, etc. While you can use a `using namespace foo;` directive to address symbols directly in the `foo` namespace without prefixing the `foo::` qualifier, this is generally considered bad practice as it pollutes the global namespace and sort of undermines the point of using namespaces in the first place.

```cpp
using namespace std;
cout << "Hello, World" << endl;    // <--- BAD!: pollutes the global namespace
```

```cpp
std::cout << "Hello, World" << std::endl;   // <--- GOOD: It's clear that you're using symbols from the standard namespace
```

---
### 2.2 References and Pointers 
A **pointer** variable stores the address of whatever it is pointing to. You can think of pointers as essentially storing a link to another piece of data. You can access the data that the pointer points to with the `->` operator, or dereference it with the `*` operator.

**References** are more akin to an alias. References cannot be `NULL` or `nullptr`, and references cannot be reassigned to reference something else after they have been created. Additionally, references do not take up extra memory; they share the same address as whatever they reference to. References cannot have multiple levels of indirection (pointers can),
and there is no reference arithmetic like there is for pointers. You can access the underlying data of a reference directly by using the reference itself: that is, if it's a reference to an integer it can be used as an integer. If it's a reference to a class you can access the class members directly with the `.` operator.

Although pointers are incredibly powerful, references are generally much safer, especially when passing objects to methods using pass-by-reference. It is very common in C++ code to pass an object as a `const` reference (if the data should be unmutable within the method) or a non-const reference rather than a raw pointer.

<img src="https://github.com/deivyka/OOP4200/blob/master/Exams/cpp_pics/pointer.jpg" alt="drawing" width="450"/>

In the following code, assume a 32-bit system, in which case the size of a pointer variable is 4 bytes, and that the stack grows towards higher memory addresses.

```cpp
// Pointers
int a = 10;             // Ends up at memory address '0x2A000084', for example
int b = 20;             // Ends up at memory address '0x2A000088'
int* ptr = nullptr;     /* ptr is a separate variable whose type is 'pointer to int' and whose 
                           value has been initialized to '0x00000000'*/

printf("ptr = %p\n");   // Prints: 0x0
ptr = &a;               // The value of ptr is now the address of the variable 'a'
cout << p << endl;      // Prints: 0x2a000084
cout << *p << endl;     // Prints: 10
ptr = &b;               // The value of ptr is now the address of the variable 'b'
cout << p << endl;      // Prints: 0x2a000088
cout << *p << endl;     // Prints: 20
```

```cpp
// References
int a = 10;                 // Ends up at memory address '0x2A000084', for example
int b = 20;                 // Ends up at memory address '0x2A000088'
int& ref_a = a;             // ref_a is an alias of (reference to) the variable a
int& ref_b = b;             // ref_b is an alias of (reference to) the variable b
cout << ref_a << endl;      // Prints: 10
cout << ref_b << endl;      // Prints: 20
cout << &ref_a << endl;     // Prints: 0x2a000084
cout << &ref_b << endl;     // Prints: 0x2a000088
ref_a = b;                  // SETS THE VALUE OF 'a' TO THE VALUE OF 'b'.
cout << ref_a << endl;      // Prints: 20
cout << a << endl;          // ALSO PRINTS: 20 !
int& ref_c;                 // ERROR! References must be initialized at their declaration
```

Perhaps the most widely used aspect of references is to pass objects by reference (sometimes constant reference) to a method. To avoid hammering the stack with large objects when you pass them by value it is nearly always preferrable to pass by reference, which is the term used when using either a reference *or* a pointer. Using a reference allows you to pass any size object by reference, while still allowing you to access the object directly.

```cpp
// Pass by reference using a const reference
void Foo(const Bar& bar) {
    int a = bar.GetValue();
    if (bar.SomeMethod()) { } // ... 
    bar.SetValue(10);   // ERROR! Cannot modify a const reference!
}

// Pass by reference using a non-const reference
void Foo(Bar& bar) {
    int a = bar.GetValue();
    if (bar.SomeMethod()) { } // ...
    bar.SetValue(10);   // Modifies 'bar' and thus whatever 'bar' references
}
```

**By passing an object by reference using a reference instead of a pointer you:**
* Don't need to check for `NULL` or `nullptr` since references cannot be null
* Can access the referenced object's data directly instead of using the `->` operator or dereferencing a pointer
* Make it clearer which parameters are meant to be *input* parameters and which are meant to be *output* parameters by using
  `const` to denote strictly input parameters
* Gain the benefits of both passing by value and passing by reference since you don't need to use a lot of memory on the stack for your object

Thus, passing by reference using a `const` reference is essentially the same as passing by value, but you avoid copying the object onto the stack. Passing by reference using a non-const reference is essentially the same as passing by reference using a pointer, but you are guaranteed that it is not null and it's as if the pointer is effectively dereferenced.

---
### Cstring (just in case, *it was mentioned in a lecture*)
CString is neither a C nor a C++ type. It appears to be a Microsoft invention that is essentially an alternative to `std::string`:

CString objects can grow as a result of concatenation operations. CString objects follow "value semantics." Think of a CString object as an actual string, not as a pointer to a string. You can freely substitute CString objects for const char* and LPCTSTR function arguments. A conversion operator gives direct access to the string's characters as a read-only array of characters (a C-style string).

I recommend ignoring it, so that:
* (a) people know what you are talking about;
* (b) your code is portable;
* (c) you are writing C++ that everybody can rationalise about according to the worldwide-accepted ISO C++ standard that many, many people spend many, many hours arguing about for this express purpose (y'know, as opposed to a few guys in a room in one company's office).

It will only be available when you are programming with Microsoft Visual C++, which is substantially limiting.

---
### 2.3 Linked lists
A linked list is made up of many nodes which are connected in nature. Every node is mainly divided into two parts, one part holds the data and the other part is connected to a different node. Each node contains a data member and a link to another node. The last node doesn’t point to any other node and just stores NULL.
```cpp
//--------------------------------------------------------------
// Node structs contain data and a pointer to the next node.
struct node { 
    int data;
    node* next; // pointer to next node
};

// ** if we have access to the first node then we can access any node of the linked list **
//--------------------------------------------------------------
// LinkedList is a list of singly-linked nodes.
class LinkedList {
private:
    // We store the first node in ‘head’ and the last node in ‘tail’. 
    node* head;
    node* tail;
    int listLength;
/* 
	the most important part of a linked list is to always keep the track of the 
	first node (head) because access to the first node means access to the entire list.
*/

public:
    // Default Constructor creates head and tail node.
    LinkedList() {
        head = NULL; // NULL since our list is empty
        tail = NULL;
    }   
    ~LinkedList(){} // Destructor de-allocates memory used by the list.
    
    void addNode(int n) {
        node* tmp = new node;  /* We are allocating the space required for a node by the new operator. 
                                Now, ‘tmp’ points to a node (or space allocated for the node). */
        tmp->data = n; // We are giving a value to the ‘data’ of ‘tmp’ as passed to the function.
        tmp->next = NULL; // point to null
 
        if (head == NULL) { // If there is no list yet, our current node(tmp) will be the ‘head’.
            head = tmp;
            tail = tmp;     // node(tmp) will also be the last element 
        }
        else { // we have a list
            tail->next = tmp;   // add new node(tmp) to end of list (after the tail)
            // "the old tail points to node(tmp)"
            tail = tail->next;  // our new node(tmp) is the tail now, the tail points to 0x0
        }
    }   
    /* if ‘a’ is a node then a->next is the node next to the ‘a’-node 
	(the pointer storing the address of the next node is named ‘next’)*/
};

int main() {
    LinkedList a;
    a.addNode(1);
    a.addNode(2);
}
```

### 2.8 Memory
Memory in your C++ program is divided into two parts:
* The **stack** − All variables declared inside the function will take up memory from the stack. 
* The **heap** − This is unused memory of the program and can be used to allocate the memory dynamically when program runs.

Many times, you are not aware in advance how much memory you will need to store particular information in a defined variable and the size of required memory can be determined at run time. You can allocate memory at run time within the heap for the variable of a given type using a special operator in C++ which returns the address of the space allocated. This operator is called 'new' operator. If you are not in need of dynamically allocated memory anymore, you can use 'delete' operator, which de-allocates memory that was previously allocated by new operator.

-----
## ASSIGNMENTS from Canvas :christmas_tree:
> Not Travelling Salesman

#### Create a program that reads a text string with two numbers 
and a operator and prints the result.

```cpp
int main() {
    int num1, num2 = 0;
    char op;
    cout<< "Enter two numbers with an operator between: ";
    cin>> num1 >> op >> num2;
    if (!cin) { // check for invalid input.
        cout<<"Only numbers please"<<endl;
    }
    switch (op) {
        case '+':
            cout << num1 << op << num2 << " = " << num1+num2;
            break;
        case '-': ... case '*': ...
        case '/':
            if (num2 == 0) { cout << "Don't divide by zero!"; }
            else
                cout<<endl<< "The answer to " << num1 << op << num2 
                << " is " << (double) num1/num2 << endl;
            break;
        default:
            break;
    }
    return 0;
}
```

#### Program that reads a text string with multiple numbers 
and operators and prints the result.

```cpp
class calculator {
public:
    double num1, num2, num3, res = 0.0;
    char op1, op2;
    void input() {
        cout << "Enter numbers with operators between: ";
        cin >> num1 >> op1 >> num2 >> op2 >> num3;
        if ((op1 == '/' && num2 == 0) || (op2 == '/' && num3 == 0))
            cout << "You can't divide by zero" << endl;
        else if ((op2 == '*' || op2 == '/') && (op1 == '-' || op1 == '+')) {
            switch (op2) {
                case '*':
                    res = num2*num3;
                    break;
                case '/': ...
                case '%':
                    res = (int)num2 % (int)num3;
                    break;
                default:
                    break;
            }
            switch (op1) {
                case '+':
                    res = num1+res;
                    break;
                case '-': ...
                default:
                    break;
            }
        }
        else {
            switch (op1) {
                case '+':
                    res = num1+num2;
                    break;
                case '-': ... case '*': ... case '/': ...
                default:
                    break;
            }
            switch (op2) {
                case '+':
                    res = res+num3;
                    break;
                case '-': ... case '*': ... case '/': ...
                default:
                    break;
            }
        }
    }
    void display() {
        if (num3 == '\0') {
            cout << num1 << op1 << num2 << " = " << res;
        }
        else cout << num1 << op1 << num2 << op2 << num3 << " = " << res;
    }
};

int main() {
    calculator Calc;
    Calc.input();
    Calc.display();
}
```

#### `Tokenizer` - Program that reads a text string with multiple numbers 
and operators and prints the result. But now it should be possible, among other things, to use () around partial expressions and the program must deal with arbitrary number of parameters. It is also advantageous to add some other operators %, ^ (power) etc. A natural extension is also to create the program so that the text string can be entered at the start of the program from the command line.

```cpp
int no_errors = 0;
double error(const char* s) {
    no_errors++;
    std::cerr << "error: " << s << '\n';
    return 1;
}

enum Token_val {
    name, number, end, PLUS='+', MINUS='-', mul='*',
    DIV='/', print=';', assign='=', LP='(' ,RP=')',
    MOD='%', power = '^'
};

// Token: sequence of chars, (kind, value) pairs: i.e. (number, 3)
class Token {
public:
    char kind;
    double value; // for numbers
    Token(char ch): kind(ch), value(0) {}
    Token(char ch, double val): kind(ch), value(val) {}
};

class Token_stream {
public:
    Token_stream(); // constructor
    Token get();
    void putback(Token curr_token);
private:
    bool full; // token in buffer?
    Token buffer;
};

Token_stream::Token_stream():full(false),buffer(0){}; // default constructor

void Token_stream::putback(Token curr_token) {
    if (full) error("putback() into full buffer");
    buffer = curr_token;
    full = true;
}

Token Token_stream::get() { // read chars from cin and compose tokens
    if (full) { // token in buffer
        full = false;   // read from cin
        return buffer; // return token from buffer
    }
    char ch;
    std::cin >> ch;
    switch (ch) {
        case ';':   // print
        case 'q':   // quit
        case '*': case '/': case '+': case '-':
        case '(': case ')': case '=': case '%':
        case '^':             return Token(ch);
        case '0': case '1': case '2': case '3':
        case '4': case '5': case '6': case '7':
        case '8': case '9': case '.': {
            std::cin.putback(ch); // put digit back into input stream
            double val;
            std::cin >> val;
            return Token(number,val);
        }
        default:
            error("Bad token\n");
    }
    return false;
}

Token_stream ts;
double expression();

/* Parsing (bottom-up)
 4) Expression: must be a term or end with a term
        Term
        Expression '+' term
        Expression '-' term
 3) Term: must be a primary or end with a primary
        Primary
        Term '*' primary
        Term '/' primary
        Term '%' primary
 2) Primary: a number or '(' followed by an expression followed by ')'
        Number
        '(' expression')'
 1) Number:
        floating-point-literal
 */

/* e.g. 45 + 11 * 7
 45: number -> primary -> term -> expression followed by '+', 11=term: (expression+term=45+11)
 11: number -> primary -> term followed by '*', 7=primary: (term * primary = 11 * 7)
 45+11*7 is an expression where 3)(11*7) will be evaluated before the addition 4)45+(11*7) 
 */

double primary() { // handles numbers and parentheses, calls expression().
    Token curr_token = ts.get(); // get token
    switch (curr_token.kind) {
        case number: {
            return curr_token.value; //return number
        }
        case MINUS:
            return -primary();
        case LP: {  // handle << '(' expression ')' >>
            auto e = expression();
            curr_token = ts.get();
            if (curr_token.kind != RP) error("')' missing\n");
            return e;
        }
        default:
            error("Primary expected!\n");
    }
    return false;
}

// multiplication and division has higher precedence than addition and subtraction.
double term() { // handles '*', '/' and '%'. calls primary
    double left = primary();
    Token curr_token = ts.get(); // get next token
    while(true) {
        switch (curr_token.kind) {
                //  Term '*' primary
            case mul:
                left *= term();
                curr_token = ts.get();
                break;  
            case MOD: {
                auto d = term();
                int a=left;
                int b=d;
                left = a%b;
                curr_token = ts.get();
                break;
            }
            case power: // use pow not xor
                left = pow(left,term());
                curr_token = ts.get();
                break;
                
            case DIV:
                if (auto d = term()) {
                    left /= d;
                    curr_token = ts.get();
                    break;
                }
                error("do not divide by 0...\n");
            default:
                ts.putback(curr_token);
                return left;
        }
    }
}
// add and subtract
double expression() {
    double left = term(); // evaluate a Term
    Token curr_token = ts.get(); // get next token
    while (true) {
        switch (curr_token.kind) { // check which kind of token it is.
            case PLUS:
                left += term();
                curr_token = ts.get();
                break;
            case MINUS:
                left -= term();
                curr_token = ts.get();
                break;
            default:
                ts.putback(curr_token); // put token back into token stream
                return left; // return final answer.
        }
    }
}

int main() {
    double val = 0.0;
    try {
        while (std::cin) {
            std::cout << "Enter expression: \n";
            Token curr_token = ts.get();
            if(curr_token.kind == 'q') break;
            if(curr_token.kind == ';') {
                std::cout<<"=" << val << std::endl;
            }
            else {
                ts.putback(curr_token);
                }
            val = expression();
            }
        }
    catch (std::exception &e) {
        std::cerr<<"E: "<<e.what()<<'\n';
        return 1;
    }
}
```

#### Create class `Student` that stores name, age and what degree they are on.
The constructor the must be able to accept information to initialise the object, and the constructor must print this to the screen : "Create a Student: <name>, <age>, <Degree>". The destructior must print the following message to the screen: "Deleted: : <name>, <age>, <Degree>".

```cpp
class Student {
private:
    std::string Name;
    int Age;
    std::string Degree;
public:
    Student();  //-Default constructor
    Student(std::string, int, std::string); //-Overloaded constructor
    ~Student(); //-Destructor
    
    //-Accessors (const = not modifiable)
    std::string getName() const;    //-return name
    int getAge() const;             //-return age
    std::string getDegree() const;  //-return degree
    
    //-Mutators (modifiable)
    void setName();     //-modify name
    void setAge();      //-modify age
    void setDegree();   //-modify degree
    
    void printData();
};

//-Default constructor (:: = 'scope resolution')
Student::Student() {
    std::cout << "Create a student: <name>, <age>, <degree> \n";
    Name = "John Doe";
    Age = -1;
    Degree = "Other degree";
}
//-Overloaded constructor
Student::Student(std::string n, int a, std::string d) {
    std::cout << "Create a student: <name>, <age>, <degree> \n";
    Name = n;
    Age = a;
    Degree = d;
}
Student::~Student() {
    std::cout << "Deleted student: "<< Name <<", "  //-Destructor
    << Age <<", "<< Degree << std::endl;
}
void Student::printData() {
    std::cout <<"Created a student: "<< Name <<", " 
    << Age <<", "<< Degree << std::endl;
}

std::string Student::getName() const {return Name;}
int Student::getAge() const {return Age;}
std::string Student::getDegree() const {return Degree;}

void Student::setName() {
    std::string n;
    std::cout<<"Enter name: ";
    std::cin>>n;
    Name = n;
}
void Student::setAge() {
    int a;
    std::cout<<"Enter age: ";
    std::cin>>a;
    Age = a;
}
void Student::setDegree() {
    std::string d;
    std::cout<<"Enter degree: ";
    std::cin>>d;
    Degree = d;
}

int main() {
    Student stud2;
    stud2.setName();
    stud2.setAge();
    stud2.setDegree();
    stud2.printData();
}
```

#### Create table with:
Size three(3) that stores objects of the type Student.

```cpp
class Student { }; // same as before 
Student::Student() {} // same as before 
Student::Student(std::string n, int a, std::string d) { } // same as before
Student::~Student() {}

std::string Student::getName() const {return Name;}
int Student::getAge() const {return Age;}
std::string Student::getDegree() const {return Degree;}

void fillVec(std::vector<Student>& new_students){
    std::string n, d;
    int a;
    std::cout<<"How many students? ";
    int size;
    std::cin>>size;    
    for (int i=0; i<size; i++) {
        std::cout<<"Student("<<i+1<<") name: ";
        std::cin>>n;
        std::cout<<"Student("<<i+1<<") age: ";
        std::cin>>a;
        std::cout<<"Student("<<i+1<<") degree: ";
        std::cin>>d;
        Student newStud(n,a,d);
        new_students.push_back(newStud);
    }
}
void printVec(const std::vector<Student>& new_students) {
    for (int i=0; i<new_students.size(); i++) {
        std::cout   <<"Created a student: "<<new_students[i].getName()
                    <<", "<<new_students[i].getAge()
                    <<", "<<new_students[i].getDegree()<< std::endl;
    }
}

int main() {
    std::vector<Student> students;
    fillVec(students);
    printVec(students);
}
```

### Create table with:
Size three(3) that stores objects of the type pointer to Student.
 
```cpp
class Student { }; // same as before

Student::Student() {  } // same as before
Student::Student(std::string n, int a, std::string d) {  } // same as before
Student::~Student() {}
std::string Student::getName() const {return Name;} // ..... same as before 

void fillVec(std::vector<Student*>& new_Vec_students) {
    Student* p_students = NULL;
    //... same as before 
    for (int i=0; i<size; i++) {
        //... same as before 
        p_students = new Student(n,a,d);
        new_Vec_students.push_back(p_students);
    }
}

// a->b =(*a).b, access member through pointer
void printVec(const std::vector<Student*> new_students) {
    for (int i=0; i<new_students.size(); i++) {
        std::cout<<"Created a student: "<<new_students[i]->getName()
        <<", "<<new_students[i]->getAge()
        <<", "<<new_students[i]->getDegree()<< std::endl;
        std::cout<<std::endl;
    }
}

static void cleanUP(std::vector<Student*>& students) {
    for (std::vector<Student*>::iterator pObj = students.begin();
            pObj!=students.end(); ++pObj) {
        delete *pObj;
    }
    for (int i=0; i<students.size(); ++i) {
        std::cout<<"Deleting: "<<students[i]->getName()
        <<", "<<students[i]->getAge()
        <<", "<<students[i]->getDegree()<< std::endl;
    }
    students.clear();
}

int main() {
    std::vector<Student*> students;
    students.reserve(3);
    fillVec(students);
    printVec(students);
    cleanUP(students);
}
```

### Create a linked list of student objects.
[Data|ptr]->[Data|ptr]->[Data|ptr]->Nullptr

```cpp
class StudentNode {
public:
    StudentNode();  //-Default constructor
    StudentNode(std::string, int, std::string); //-Overloaded constructor
    ~StudentNode(); //-Destructor
        
    std::string Name;
    int Age;
    std::string Degree;
    StudentNode* next;
    friend class StudentLink;  
    /* friend class: a class whose members have access to 
        the private members of another class. */
};

class StudentLink {
private:
    StudentNode* head; // point to head
public:
    StudentLink();  //-Default constructor
    StudentLink(std::string, int, std::string); //-Overloaded constructor
    ~StudentLink(); //-Destructor
   
    void addData(std::string, int, std::string);
    void print();
};

//-Default constructor (:: = 'scope resolution')
StudentNode::StudentNode() {
    Name = "John Doe";
    Age = -1;
    Degree = "Other degree";
}
//-Overloaded constructor
StudentNode::StudentNode(std::string n, int a, std::string d) {
    Name = n;
    Age = a;
    Degree = d;
}
StudentNode::~StudentNode() {std::cout<<"Node deleted";} //-Destructor

StudentLink::StudentLink() {head = NULL;}
StudentLink::~StudentLink() {
    std::cout<<"\nList deleted\n";
}
void StudentLink::addData(string Name, int Age, std::string Degree) {
    StudentNode* Snode = new StudentNode();
    Snode->Name = Name;
    Snode->Age = Age;
    Snode->Degree = Degree;
    Snode->next = this->head;
    this->head = Snode;
}
void StudentLink::print() {
    StudentNode* head = this->head;
    while (head) {
        std::cout<<" -> ["<<head->Name<<", "
        << head->Age <<", "<<head->Degree<<"]";
        head = head->next;
    }
}
static void setValues(StudentLink *list) {
    std::string n, d;
    int a;
    std::cout<<"How many students? ";
    int size;
    std::cin>>size;
    for (int i=0; i<size; ++i) {
        cout<<"Student("<<i+1<<") name: ";   cin>>n;
        cout<<"Student("<<i+1<<") age: ";    cin>>a;
        cout<<"Student("<<i+1<<") degree: "; cin>>d;
        list->addData(n, a, d);
    }
}

int main() {
    StudentLink* list = new StudentLink();
    setValues(list);
    list->print();
    delete list;
}
```
### Student class, static
We add a static data element to the Student class to store the number of students objects in existence. Then create a function(not method) called `Print()` that accepts a Student object as a 'pass by value' transfer. We make sure that all constructor (including copy constructors) keeps track of number of objects and that the destructor does the same. We make a `PrintNumberOfStudents()` method that prints out number of student objects.
```cpp
// Curiously recurring template pattern
template <typename T>
struct counter {
    static int students_created;
    static int students_alive;
    counter() {
        ++students_created;
        ++students_alive;
    }
    counter(const counter&) {
        ++students_created;
        ++students_alive;
    }
protected: // Protected members are accessible in the class that defines them and in classes that inherit from that class.
    ~counter(){
        --students_alive;
    }
};
template <typename T> int counter<T>::students_created(0);
template <typename T> int counter<T>::students_alive(0);

//------------------------------------------------------
//class Student derives from a class template instantiation using Student itself as template argument.
class Student : counter<Student> {// same as before };

Student::Student(std::string n, int a, std::string d) {} // same as before 
std::string Student::getName() const {return Name;}     // ....(get set) same as before 
void fillVec(std::vector<Student>& new_students) {} // same as before 
void printVec(const std::vector<Student>& new_students) { } // same as before

void PrintNumberOfStudents(const std::vector<Student>& students){
    std::cout<<"\nNumber of student objects created = "           
             <<counter<Student>::students_created<<std::endl;
    std::cout<<"\nNumber of student objects alive = "
             <<counter<Student>::students_alive<<std::endl;
}

int main() {
    std::vector<Student> students;
    fillVec(students);
    printVec(students);
    PrintNumberOfStudents(students);
    students.clear(); //Removes all elements from the vector, leaving the container with a size of 0.
    PrintNumberOfStudents(students);
}
```

### Create class Human that can store the data name og age.
Create two classes, Student and Professor, with the added data: ECTS (for Student) and papers (for Professors).
Constructor calls the constructor in the base class and use that for initialising the class.

```cpp
class Human {
private:
    std::string Name;
    int Age;
public:
    Human() { cout<<"Creating default Human"<<endl;}
    Human(std::string n, int a) : Name(n), Age(a) { cout<<"Creating overloaded Human"<<endl;}
    
    std::string getName() const {return Name;}
    int getAge() const {return Age;}
    void setName(std::string n) {Name = n;}
    void setAge(int a) {Age = a;}
    
    virtual void printHuman() {
        std::cout<<"Name: "<<Name<<std::endl
        <<"Age: "<<Age<<std::endl;
    }
};
//------------------------------------
class Student : public Human {
private:
    int ECTS;
public:
    Student(std::string Name, int Age, int e) : Human(Name, Age) {
        ECTS = e;
        std::cout<<"Creating overloaded Student"<<std::endl;
    }
    int getECTS() const {return ECTS;}
    void printStudent() {
        Human::printHuman();
        std::cout<<"ECTS: "<<ECTS<<std::endl;
    }
};
//------------------------------------
class Professor : public Human {
private:
    int Papers;
public:
    Professor(std::string Name, int Age, int P) : Human(Name, Age) {
        Papers = P;
        std::cout<<"Creating overloaded Professor"<<std::endl;
    }
    int getPapers() const {return Papers;}
    void printProfessor() {
        Human::printHuman();
        std::cout<<"Papers: "<<Papers<<std::endl;
    }
};

int main() {
    Student stu("Putin",20,300);
    stu.printStudent();
    
 //alternative.
 //Student stu("Student",20,300);
 //Student* s_p = &stu;
 //s_p->printStudent();
 
    Professor pro("Prof.",30,50);
    pro.printProfessor();
    return 0;
}
```

#### Create a class SecretAgent where the access to class Human is private.
Add the data number (007 or similar) include this get and set methods, verify that these can be used in the main(), while the others can not.

```cpp
class Human {
private:
    std::string Name;
    int Age;
public:
    Human() { cout<<"Creating default Human"<<std::endl; }
    Human(std::string n, int a) {
        Name = n;
        Age = a;
        std::cout<<"Creating overloaded Human"<<std::endl;
    }
    
    std::string getName() const {return Name;}
    int getAge() const {return Age;}
    void setName() {
        std::string n;
        Name = n;
    }
    void setAge() {
        int a = 0;
        Age = a;
    }
    virtual void printHuman() {
        std::cout<<"Name: "<<Name<<std::endl <<"Age: "<< Age << std::endl;
    }
};

class SecretAgent : private Human {
private:
    std::string agentNr;
public:    
    SecretAgent() {
    //Name = " "; //- private member of human
    //Age = 0;    //- private member of human
        agentNr = " ";
        std::cout<<"Creating default Agent"<<std::endl;
    }
    SecretAgent(std::string n, int a, std::string a_nr) {
    //Name = n; //- private member of human
    //Age = a;  //- private member of human
        agentNr = a_nr;
        std::cout<<"Creating overloaded Agent"<<std::endl;
    } 
    std::string getAgentNr () const {return agentNr;}
    void setAgentNr() {
        std::string a_nr = "007";
        agentNr = a_nr;
    }    
    void printAgent() {
        Human::printHuman();
        std::cout<<"Agent: "<<agentNr<<std::endl;
    }
};

int main() {
    SecretAgent james;
    james.setAgentNr();
    james.printAgent();
    SecretAgent S("Stalin",40,"008");
    S.printAgent(); // only the agentNr will be printed.
}
```
### template - swap
You can swap the value of two objects of the class/type string. As long as your types support copying (via copy constructor and copy assignment operator), the default swap implementation will let objects of your types be swapped without your having to do any special work to support it. However, the default swap implementation may not thrill you. It involves copying three objects: a to temp, b to a, and temp to b. For some types, none of these copies are really necessary. For such types, the default swap puts you on the fast track to the slow lane. Foremost among such types are those consisting primarily of a pointer to another type that contains the real data. 

```cpp
class abc {
public:
	abc();
	abc(std::string);
	~abc(){;}	
	std::string getString() const;
private:
	std::string str;
};

abc::abc(std::string s) {str = s;}
std::string abc::getString() const {return str;}

template <class X>
void Swap(X& a, X& b) {
    X temp;
    // pass by value needs a copy constructor
    // pass by reference doesn't need a copy constructor
    temp = a;   // temp gets address of a
    a = b;      // a gets address of b
    b = temp;   // b gets address of temp (=a)
}

int main() {
    int nI = 10, nJ = 2;
    char c1 = 'B', c2 = 'A';
    float f1 = 0.0, f2 = -1.0;
    std::string s1 = "Hei";
    std::string s2 = "Hallo";
    const char* Cstr1 = "Chei";
    const char* Cstr2 = "Challo";

/*
    char s1[32]="abc", s2[32]="def";
    char* s1p = s1;
    char* s2p = s2;
    cout<<s1p<<" "<<s2p<<endl; //print before swap
    Swap(s1p, s2p);
    cout<<s1p<<" "<<s2p<<endl; //print after swap
s1p now points to s2[0]='d', and s2p points to s1[0]='a'.

A CString can not have a new value assigned to it after it is declared. 
Therefore we have to declare the CString as a pointer to a char.
    char* str = "abc"; 
This creates an array containing your string + a terminating null character ('\0'). 
The address of the first element in the array will be placed in the pointer.

*/
    abc a("hei");
    abc b("hallo");
    Swap(nI, nJ); // ok
    Swap(c1, c2); // ok
    Swap(f1, f2); // ok
    Swap(s1, s2); // ok
    Swap(Cstr1, Cstr2); // ok   
    Swap(a,b); // ok
    std::cout<<a.getString()<<" " <<b.getString();
    return 0;
}
```

### Implement some mathematical operations by using templates:

```cpp
// **GetMax**
template <typename T> // class = typename
 T GetMax (T a, T b) {
     return (a>b ? a:b); // (condition ? value_if_true : value_if_false)
 }
int i=1, j=2, k;
char x='a',y='f',z;
k = GetMax(i, j); // int GetMax (int a, int b);
z = GetMax(x, y); // char GetMax (char a, char b); 
```

```cpp
#include <cmath>

template <typename T>
T myAbs(T x) { return (x*((x>0)-(x<0))); } //similar to abs(x)

template <typename T>
T myAdd(T x, T y) {return (x + y);}

template <typename T>
T myPow(T x, int y) {return pow(x, y);}

int main(int argc, const char * argv[]) {
   /* What happens if we have two string-objects s1 "hei” and  s2 "hallo":
    myAbs(s1); // doesnt work because of abs()
    myAdd(s1,s2); //  --> = heihallo
    myPow(s2,2); // doesnt work because of pow() */
    std::string s1 = "hei";
    std::string s2 = "hallo";  
    std::cout<<"myAbs: "<<myAbs(1)<<std::endl;
    std::cout<<"myAdd: "<<myAdd(s1, s2)<<std::endl;
    std::cout<<"myPow: "<<myPow(4, 2)<<std::endl;
}
```

####  Exceptions
We create a class ZeroException that inherits from the exception-class in STL. We let it have a public attribute 'teller' that contains information about what the divider attempted to divide by 0. Then we create a function `float divide(int numerator, int divisor);` that verifies that the divisor is not 0 before an answer is attempted. If the divisor is 0 then the ZeroException should be generated. Next we create a function `void testDivisor(void);` that runs in an infinite loop and tries to divide a counting number by random numbers from 0 to 100. This function should also catch ZeroExceptions, and write how many times the division managed to run without generating a divide by zero.

* **`try`-block**: The code which can throw/cause an exception is kept inside a try block. Then, when the code leads to an error, that error/exception will get caught inside the catch block.

* **`catch`-block**: Catch the error and handle the exception condition. We can have multiple catch blocks to handle different types of exception and perform different actions when the exceptions occur. e.g., we can display descriptive messages to explain why any particular excpetion occured.

* **`throw` statement**: Throw exceptions to exception handler i.e. it is used to communicate information about error. 
A throw expression accepts one parameter and that parameter is passed to handler. A throw statement is used when we explicitly want an exception to occur, then we can use throw statement to throw or generate that exception.

```cpp
class ZeroException : public std::exception {
public:
	ZeroException() {}
	ZeroException(int);
	~ZeroException(){;}
  	int getTeller() const {return teller;}
    void setTeller(int t) {teller = t;}
	int teller;	// what the divider attempted to divide by zero.
};

ZeroException::ZeroException(int t) : teller(t){}

float divide(int numerator, int divisor) {
	if (divisor == 0) {
		ZeroException e;
		e.setTeller(numerator);
		throw e; // throw exception
	}
	return (numerator/divisor);
}
void testDivisor(void) {
	for (int i=1 ;; i++) { // infinite loop
		try { divide(i, rand()%100); }
		catch (const ZeroException& e) {
			std::cout<<"Divided "<< i <<" times without generating a divide by zero."<<std::endl;
			std::cout<<"Got divided: "<<e.getTeller()<<" by zero. "<<std::endl;
			exit(1);
		}
	}
}

int main() {
	testDivisor();
}
```
---
### 2x2 matrix multiplication
```cpp
//  2x2 matrix multiplication with following specifications
/*
  |2 3| |4 5| = |(2,3)*(4,4) (2,3)*(5,5)|
  |2 3| |4 5|   |(2,3)*(4,4) (2,3)*(5,5)|
              = |(2*4+3*4) (2*5+3*5)| = |(20) (25)|
                |(2*4+3*4) (2*5+3*5)|   |(20) (25)|
*/

class Matrix {
private:
  std::vector<std::vector<double> > mat;
  unsigned m, n;
public:
  Matrix(unsigned _m, unsigned _n, const double& _init1, const double& _init2);
  Matrix(const Matrix& rhs);
  virtual ~Matrix(){}

  // Operator overloading, for "standard" mathematical matrix operations
  Matrix& operator=(const Matrix& rhs);

  // Matrix mathematical operations
  Matrix operator*(const Matrix& rhs);
  Matrix& operator*=(const Matrix& rhs);

  Matrix operator*(const double& rhs); // Matrix/scalar operations
  std::vector<double> operator*(const std::vector<double>& rhs); // Matrix/vector operations

  // Access the individual elements
  double& operator()(const unsigned& row, const unsigned& col);
  const double& operator()(const unsigned& row, const unsigned& col) const;
  
  // Access the row and column sizes
  unsigned get_m() const;
  unsigned get_n() const;
};

// Parameter Constructor
Matrix::Matrix(unsigned _m, unsigned _n, const double& _init1, const double& _init2) {
  mat.resize(_m, std::vector<double>(_n, _init1));
  for (unsigned i=0; i<_m-1; i++) {
    for (unsigned j=0; j<_n-1; j++) {
      mat[i][j] = _init1;     // [0 0]
      mat[i][j+1] = _init2;   // [0 1]
      mat[i+1][j] = _init1;   // [1 0]
      mat[i+1][j+1] = _init2; // [1 1]
    }
  }
  m = _m;
  n = _n;
}
// Copy Constructor
Matrix::Matrix(const Matrix& rhs) {
  mat = rhs.mat;
  m = rhs.get_m();
  n = rhs.get_n();
}
// Assignment Operator
Matrix& Matrix::operator=(const Matrix& rhs) {
  if (&rhs == this)
    return *this;
  unsigned new_m = rhs.get_m();
  unsigned new_n = rhs.get_n();
  mat.resize(new_m);
  for (unsigned i=0; i<mat.size(); i++) {
    mat[i].resize(new_n);
  }
  for (unsigned i=0; i<new_m; i++) {
    for (unsigned j=0; j<new_n; j++) {
      mat[i][j] = rhs(i, j);
    }
  }
  m = new_m;
  n = new_n;
  return *this;
}
// Left multiplication of this matrix and another
Matrix Matrix::operator*(const Matrix& rhs) {
  unsigned m = rhs.get_m();
  unsigned n = rhs.get_n();
  Matrix result(m, n, 0.0, 0.0);
  for (unsigned i=0; i<m; i++) {
    for (unsigned j=0; j<n; j++) {
      for (unsigned k=0; k<m; k++) {
        result(i,j) += this->mat[i][k] * rhs(k,j);
      }
    }
  }
  return result;
}
// Cumulative left multiplication of this matrix and another
Matrix& Matrix::operator*=(const Matrix& rhs) {
  Matrix result = (*this) * rhs;
  (*this) = result;
  return *this;
}
// Matrix/scalar multiplication
Matrix Matrix::operator*(const double& rhs) {
  Matrix result(m, n, 0.0, 0.0);
  for (unsigned i=0; i<m; i++) {
    for (unsigned j=0; j<n; j++) {
      result(i,j) = this->mat[i][j] * rhs;
    }
  }
  return result;
}
// Multiply a matrix with a vector
std::vector<double> Matrix::operator*(const std::vector<double>& rhs) {
  std::vector<double> result(rhs.size(), 0.0);
  for (unsigned i=0; i<m; i++) {
    for (unsigned j=0; j<n; j++) {
      result[i] = this->mat[i][j] * rhs[j];
    }
  }
  return result;
}
// Access the individual elements
double& Matrix::operator()(const unsigned& row, const unsigned& col) {
  return this->mat[row][col];
}
// Access the individual elements (const)
const double& Matrix::operator()(const unsigned& row, const unsigned& col) const {
  return this->mat[row][col];
}
// Get the number of rows of the matrix
unsigned Matrix::get_m() const {
  return this->m;
}
// Get the number of columns of the matrix
unsigned Matrix::get_n() const {
    return this->n;
}
void show(const Matrix& mat) {
    for (int i=0; i<mat.get_m(); i++) {
        for (int j=0; j<mat.get_n(); j++) {
            std::cout << mat(i,j) << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main(int argc, char const *argv[]) {
    Matrix mat1(2, 2, 2, 3);
    Matrix mat2(2, 2, 4, 5);
    show(mat1);
    show(mat2);
    Matrix mat3 = mat1 * mat2;
    show(mat3);
}
```
---
### Template stack
```cpp
template <class CElement>
class CStack {
private:
    CElement m_Array[10];
    int m_nTOS;
public:
    CStack();
    void Push( CElement e );
    CElement Pop();
};

template <class CElement> CStack<CElement>::CStack() {
	memclr( m_Array, sizeof(m_Array) );
	m_nTOS = 0;
}
template <class CElement> void CStack<CElement>::Push(CElement e) {
    if (m_nTOS == 10)
        return;
    m_Array[m_nTOS++] = e;
}
template <class CElement> CElement CStack<CElement>::Pop() {
	if ( m_nTOS > 0 ) m_nTOS--;
	return m_Array[m_nTOS];
}

int main() {
    CStack<int>	IntStack;
    CStack<char> CharStack;
    IntStack.Push(1);
    IntStack.Push(2);
    cout << IntStack.Pop() << IntStack.Pop()<< IntStack.Pop() << endl;
    CharStack.Push('A');
    CharStack.Push('B');
    cout<<CharStack.Pop()<<CharStack.Pop()<< CharStack.Pop() << endl;
}
```
