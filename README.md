# String<sub>v2.0</sub>

Full rewrite of this simple modern String class / library. Incompatible with v1.0 which can be found [here](https://github.com/lionkor/legacy-1.0).

**The v2.0 is not fully done yet**

## Major features

### `String::format`
A static method allowing for simple and fast formatting. Allows any type `T` with an overload to `ostream& operator(ostream&, T)` to be formatted into the String correctly.
Because of this, it also supports all primitive types.

Examples: 

```cpp
const char* name = "Dave";
const int age = 35;
String test = String::format("Name: ", name, ", Age: ", age);
// -> "Name: Dave, City: New York, Age: 35"
```

If your type correctly overloads `ostream& operator(ostream&, T)`, you can pass your type to `String::format`.

You can pass a `String::Format` instance to set formatting options similar to `std::ios::fmtflags`. This allows setting precision, base, width, fill, etc.

Example:
```cpp
String::Format fmt;
fmt.precision    = 3;
fmt.width        = 10;
fmt.alignment    = String::Format::Align::Right;
String my_string = String::format(fmt, 3.53214, " |", fmt, 5.2436, " |");
std::cout << my_string << std::endl;
```
will output:
```
        3.53 |      5.24 |
```

## How to use

1. clone this repository (recursively)
2. switch to the `rewrite` branch
3. include `String.h` and add `String.cpp` to your source files (for an example look at `CMakeLists.txt`)

## FAQ

### Is `std::string` not good?

`std::string` is very good. Still, I always thought its interface was very inconsistent, using iterators here and indices there, and following very few std library conventions.
`String` is supposed to allow for more Python- or C#-like string interactions, making it feel more like a primitive type than a complicated container, yet also supporting it being treated just like a normal `std::vector`.

TL;DR: I just want a string that gives me an iterator when I call `String::find` and has intuitive methods like `.replace` and `.split`.

### Why `std::vector`?
I **don't** like `std::string`, I **do** like `std::vector`. 

### Where did open issues go?

Closed, since the code that was responsible for them was nuked. 
