# String v2.0

Full rewrite of this simple modern String class / library. Incompatible with v1.0 which can be found [here](https://github.com/lionkor/String/tree/legacy-1.0).

**The v2.0 is not fully done yet**

## Documentation

Full documentation can be found here: [**Full documentation**](https://lionkor.github.io/String-docs).

## How to use

There are **2** ways to use this library:

### 1 Compile with your project

1. clone this repository (recursively).
2. add `String/include` to your include directories.
3. include `String.h` and add `String/src/String.cpp` to your source files (for an example look at `CMakeLists.txt`).
4. compile with at least `-std=c++17`.

### 2 Compile as library, link (linux/unix)

1. clone this repository (recursively).
2. go into the cloned repository directory.
3. run `cmake && make String`. This will create `libString.a`.
4. add `String/include` to your include directories
5. link against `libString.a`. 
  
   Example with gcc, assuming `String` was cloned into the same directory that main.cpp is in and libString.a has been built: 
   ```bash
   g++ main.cpp -o myprogram -lString -L./String -I./String/include
   ```

## Major features

* `String::format` - Described below.
* `String::split` - Splits the String into parts, using a char or String as delimiter.
* `String::replace` - Replaces all instances of a char or String with another char or String.
* `String::startswith` - Tests whether the String starts with another substring.
* `String::endswith` - Tests whether the String ends with another substring.
* `String::insert` and `String::erase` - Inserts or erases chars or Strings into or from the String.

### String::format
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
String my_string = String::format(".", fmt, 3.53214, " |", fmt, 5.2436, " |");
std::cout << my_string << std::endl;
```
will output:
```
.        3.53 |      5.24 |
```

## FAQ

### How do you run the tests?

After cloning the repo, head into the cloned String directory and run `cmake` and then `make StringTest`. You can then execute `./StringTest`.

### Is `std::string` not good?

`std::string` is very good. Still, I always thought its interface was very inconsistent, using iterators here and indices there, and following very few std library conventions.
`String` is supposed to allow for more Python- or C#-like string interactions, making it feel more like a primitive type than a complicated container, yet also supporting it being treated just like a normal `std::vector`.

TL;DR: I just want a string that gives me an iterator when I call `String::find` and has intuitive methods like `.replace` and `.split`.

### Is it faster / slower than `std::string`?

Generally, it's *probably* slower, as is to be expected at this point in development. Construction is just as fast as `std::string`, for any string long enough so that SSO doesn't kick in for `std::string`. This is not a performance library, it's a convenience library. If you think `std::vector` is fast enough, then this library is probably fast enough.

### How do you convert to `std::string` or `char*`?

Since `String` is not null-terminated, conversion is rather slow.
Options for conversion are, from fastest to slowest:

1. Append `'\0'`, access `String::data()`, do stuff, then `String::erase` the `'\0'`. This is super fast, won't copy any data, and you can just use it like a regular `const char*`. 
  This is only useful if the String is only used by one thread and is not `const`. 
  **Attention:** This will cause huge troubles if you attempt to use the String after adding a `'\0'` *without erasing it again*, as the size will have increased by one (since we treat `'\0'` as a normal character). 
  This is the fastest, but also the most error-prone way. Not recommended.
  
2. Use `String::to_std_string`. This copies the data into a `std::string`, which might be faster than method nr. 3, as this might use SSO. The returned `std::string` is a copy.

3. Use `String::to_c_string`. This allocates a buffer with `new[]`, wraps it in a `std::unique_ptr`, copies the chars into it and returns that `std::unique_ptr`. You can then access the `char*` with `.get()`. This is probably the slowest way, but it will give you back a self-memory-managing buffer, so it's pretty neat. I was thinking about a raw pointer return, but that just *wants* to leak memory. 

### Why `std::vector`?
I **don't** like `std::string`, I **do** like `std::vector`. 

### Where did open issues go?

Closed, since the code that was responsible for them was nuked. 
