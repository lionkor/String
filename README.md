# String
A simple modern String class. `String`, which is **only 24 bytes**, has **small string optimization (SSO)**, uses **variadic templates** for formatting (`String::format`), includes a very lightweight **StringView** friend class, and has some methods `std::string` is desperately missing!

`String` is immutable, but it offers plenty of ways to be constructed, so don't worry!

The idea is that it has a more practical and straightforward interface and enforces some stricter rules, while at the same time giving more method-functionality (as opposed to external functionality enabled through `<algorithm>`). I personally like interfaces that are easy to read while offering high complexity, and that's ultimately the goal. `String` does, of course, include (constant) iterators for all your non-mutating `<algorithm>` needs, as well as a fitting constructor!

By the way, *small string optimization kicks in for strings >23 bytes*!

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
```cpp
String s = String::format("Hello, ", name, '!');
```
This currently only supports primitive types. (More will be added soon!)

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
`StringBuilder::prepend` is incomplete.

### Why?

For learning purposes and as part of my own personal library of code that I use in my projects. This is not supposed to be faster or better in an objective sense than `std::string`. The idea is to develop a String class with an interface that fits my personal coding style. This is not to say that it won't be fast; I just know that it's pretty difficult to ever reach the speed of, say, `std::string`.
Do, however, feel free to suggest any optimizations :)
