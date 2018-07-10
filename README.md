# maybe_ptr

Pointer type that acts like a `std::unique_ptr`, but that may or may not actually own its data, and lets the user check at runtime whether it is owned.

It is the moral equivalent of a `std::variant<std::unique_ptr<T>, T*>`, with an interface to get the value of the pointer regardless of whether it owns its underlying data.

It takes some inspiration from [Rust's Copy-On-Write `Cow` type](https://doc.rust-lang.org/std/borrow/enum.Cow.html).

# Basic usage

```lang=cpp
#include <maybe_ptr.h>

int main()
{
  auto owner = make_owner<int>(42); // allocate a new int*
  auto observer = make_observer(owner); // observes the owner ptr
  *owner = 12;
  assert(*observer == 12);
  *observer = 6;
  assert(*owner == 6);
}
```

# Building

The library is header only, hence no building is required. Building requires at least C++14.
You can use the provided CMake file to install the header in a system-wide directory, or to compile the examples.

## Compiling the examples

```
cmake -Dmaybe_ptr_EXAMPLES=ON <src-dir> # from <build-dir>
make
```
The source for the examples can be found in the [examples](examples/) directory
