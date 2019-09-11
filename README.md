# String
A simple modern String class. `String` is not a clone of `std::string`. The idea is that it has a more practical and straightforward interface and enforces some stricter rules.

For example, a `String` cannot be changed once created. Construction happens either through a straighforward constructor or through the helper class `StringBuilder`. This follows the idea of `String` being immutable after creation.

### Roadmap

The following will **definitely** need to be done:

- [x] Use `std::unique_ptr` for `char[]`.
- [ ] Replace varargs with variadic templates.
- [x] Implement `String::split`.
  - [x] Implement `String::substr`.
- [x] Implement `String::trim`.
- [ ] Implement small-string-optimization.
- [ ] Optimize `StringBuilder::build`.
- [ ] Optimize `StringBuilder::append` and `StringBuilder::prepend` (and respective `*f` equivalents).
- [ ] Document the public interface (*Doxygen?*).
- [x] Add Iterator(s), `begin`, `end`.

The following I'm **not so sure** about:

- [ ] `StringBuilder` operators `+=`, `+`, etc.
- [ ] Conversion between `String` and `std::string`.
- [ ] Make `String` use more move semantics in some situations (?).

### How to use

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

~~The project doesn't use any smart pointers, so exceptions will cause memory leaks. Any proposals for how to fix this without using std shared pointers is welcome!~~ *This was not very smart. Both `String` and `StringBuilder` now use `std::unique_ptr`s.* 

### Why?

For learning purposes and as part of my own personal library of code that I use in my projects. This is not supposed to be faster or better in an objective sense than `std::string`. The idea is to develop a String class with an interface that fits my personal coding style. This is not to say that it won't be fast; I just know that it's pretty difficult to ever reach the speed of, say, `std::string`, and it's not the scope of this project to make a String class that will fit every possible use case.
