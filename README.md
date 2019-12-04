# String
A simple modern String class. `String`, which is **only 24 bytes**, has **small string optimization (SSO)**, uses **variadic templates** for formatting (`String::format`), includes a very lightweight **StringView** friend class, and has some methods `std::string` is desperately missing!

`String` is immutable, but it offers plenty of ways to be constructed, so don't worry!

The idea is that it has a more practical and straightforward interface and enforces some stricter rules, while at the same time giving more method-functionality (as opposed to external functionality enabled through `<algorithm>`). I personally like interfaces that are easy to read while offering high complexity, and that's ultimately the goal. `String` does, of course, include (constant) iterators for all your non-mutating `<algorithm>` needs, as well as a fitting constructor!

By the way, *small string optimization kicks in for strings >23 bytes*!

### Features

* `substring`: Returns a sub-string of the current String. 
* `split`: Splits the string at delimiters and returns a vector of Strings.
* `trimmed`: Returns a copy with all occurances of a char at the start and end of the String removed.
* `startswith`: Returns whether the String starts with a given String.
* `endswith`: Returns whether the String ends with a given String.
* `find`: Returns an iterator to the first occurance of a given character.
* `hexified`: Returns a copy of the string in hex. Example: `abc` gives `616263`.
* `capitalized`: Returns a copy of the String with the first letter capitalized.
* `replaced`: Finds a given substring and returns the String with thta substring replaced with another given substring.
* `to_upper`: Returns a copy of the String in ALL UPPERCASE.
* `to_lower`: Returns a copy of the String in all lowercase.
* `to_printable_only`: Returns a copy of the String which only has the printable characters of the original String.
* `substring_view`: Like `substring`, but is `constexpr` and returns a `StringView`.
* `empty`: Returns whether the String is empty (`""`).
* `equals`: The same as `==`.
* `equals_case_insensitive`: Returns whether the two Strings are equal, while ignoring case sensitiviy.
* `size`: Returns the size of the String.
* *`static`* `format`: Creates a String from an amount of arguments of different types.

### Roadmap

The following will **definitely** need to be done:

- [x] Replace varargs with variadic templates.
- [x] Implement `String::split`.
  - [x] Implement `String::substr` (use `String::substring`).
- [x] Implement `String::trim`.
- [x] Implement small-string-optimization.
- [x] Optimize `StringBuilder::build`.
- [x] Optimize `StringBuilder::append` and `StringBuilder::prepend`.
- [ ] Document the public interface (*Doxygen?*).
- [x] Add Iterator(s), `begin`, `end`.
- [x] ~~Use `std::unique_ptr` for `char[]`.~~ (replaced by SSO)
- [ ] Ensure only valid (printable) types to be passed to HexFormat, OctalFormat, etc.

The following I'm **not so sure** about:

- [ ] `StringBuilder` operators `+=`, `+`, etc.
- [ ] Conversion between `String` and `std::string`.
- [ ] Make `String` use more move semantics in some situations (?).

### How to use

A `String` can be constructed with:

**There are more ctors, but these are the important ones!**

#### `String::String(const char*)`
```cpp
String s("My String!");
```
This method is the easiest for simple strings. For formatting support one of the next options is needed.

#### `String::String(iter, iter)`
```cpp
String s(my_begin_iterator, my_end_iterator);
```
This is useful for creating Strings from pieces of other Strings (this is as close to mutability as it gets in here).

#### `String::format`

There are a few helper templates that can be used to get a lot of the formatting sugar that you're used to from `printf` and the like:

* `HexFormat<>(x)`: Produces Hex formatted output of `x`, comparable to `%x`.
* `OctalFormat<>(x)`: Produces Octal formatted output of `x`, comparable to `%o`.
* `PointerFormat(x)`: Produces Pointer formatted output of `x`, comparable to `%p`. Note that this only supports pointer types to be passed, and thus is not templated. This ensures that intention is clear and being followed.

```cpp
String s = String::format("Hello, ", name, '!');
String s2 = String::format("Hex of 14: ", HexFormat<int>(14));
```

Templates like `HexFormat` aren't functions and serve no purpose outside of `String::format`, as they do not produce any output. They merely serve as a hint to the formatter.

#### `StringBuilder`
```cpp
StringBuilder builder;
builder.append("Version v");
builder.append(MAJOR);
builder.append('.');
builder.append(MINOR);
builder.append('.');
builder.append(PATCH);
String s(std::move(builder.build()));
```
This could of course all be done in one call to `String::format`, but the point is that it allows an iterative approach.

It's also possible to chain together `append` (and `prepend`):
```cpp
StringBuilder sb()
  .append("Hello,")
  .append(' ')
  .append("World!")
  .append(1.0 / 3.0)
.build();
```

### Notes

`StringBuilder::appendf` and `StringBuilder::prependf` were removed for now.

### Why?

For learning purposes and as part of my own personal library of code that I use in my projects. This is not supposed to be faster or better in an objective sense than `std::string`. The idea is to develop a String class with an interface that fits my personal coding style. This is not to say that it won't be fast; I just know that it's pretty difficult to ever reach the speed of, say, `std::string`.
Do, however, feel free to suggest any optimizations :)
