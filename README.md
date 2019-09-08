# String
A simple modern String class.

### How to use

`String` is not resizable or editable like `std::string` is. Copying will copy memory and size information.
It's basically a fancy wrapper around a heap-allocated `char*`.

A `String` can be constructed with:

#### `String::String`
```
String s("My String!");
```
This method is the easiest for simple strings. For formatting support one of the next options is needed.

#### `String::format`
```
String s = String::format("Hello, %s!", name);
```
This supports all of printf's formatting features. Resulting formatted strings can be any length.

#### `StringBuilder`
```
StringBuilder builder;
builder.append("Version v");
builder.appendf("%u.%u.%u", MAJOR, MINOR, BUILD);
String s = builder.build();
```
This could of course all be done in one call to `appendf`, but this is for demo only.
This supports all of printf's formatting features. Resulting formatted strings can be any length.

### Notes

The project doesn't use any smart pointers, so exceptions will cause memory leaks. Any proposals for how to fix this without using std shared pointers is welcome!
However, each feature has been tested and `valgrind` does not complain.

### Why?

I needed my own String class so I could add more functionality.
