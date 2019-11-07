# Contributing



## What should I know before contributing?

* The main focus of this project is an intuitive and easy-to-use design. 

* Naming conventions are pretty straightforward: Classes, enums, etc. shall be `CamelCase`, anything else shall be `snake_case`. Private and protected member variables shall have the `m_` prefix. A getter for a private or protected variable shall be the variable name without the `m_` (no `get_` prefix). Setters shall have the `set_` prefix. (just look at the code, its really straightforward)

* Choose clear and descritive names with as little abbreviation as possible. 

* `String` is immutable, and this is by design. Any changes going against this idea won't be merged.

## What can I contribute / where can I help?

In general, anything that's on the roadmap in the [readme](https://github.com/lionkor/String/blob/master/README.md). 

In more detail: 

* Any optimization is welcome (as long as it doesn't break something important).

* Any features that operate on the string (akin to `split` and `trim`) are welcome. Keep in mind that they shall not modify the `String` and instead return a new one, or a vector of String, or whatever.

* Useful overloads for existing features are welcome.

* Documentation. Basically every public method needs to be documented at some point.
