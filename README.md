# String

Full rewrite branch of this simple modern String class / library. 

## Major changes

* Fully ABI / API **in**compatible with previous versions (basically a new library).
* No more small string optimization, for now.
* More standard-similar behaviour, with proper iterators doing most of the work.
* Proper tests.
* No longer null-terminated.
* `<algorithm>` used for most operations.
