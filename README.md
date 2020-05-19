# String<sub>v2.0</sub>

Full rewrite branch of this simple modern String class / library. Incompatible with v1.0.

## Major changes from String<sub>v1.0</sub>

* Fully ABI / API **in**compatible with previous versions (basically a new library).
* No more small string optimization, for now.
* More standard-similar behaviour, with proper iterators doing most of the work.
* Well tested.
* No longer null-terminated.
* `<algorithm>` used for most operations, and thus also fully compatible with algorithms from the std library.
* no longer a buildable library. 
* not a single line of code reused, everything from scratch.

## How to use

1. clone this repository
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
