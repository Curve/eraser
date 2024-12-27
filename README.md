<div align="center">
    <img src="assets/logo.svg" height="312">
</div>

<br/>

<p align="center">
    A C++20 type-erasure library that supports interfaces
</p>

<hr/>

## 👋 Introduction

_Eraser_ is an easy, customizable, C++20 type-erasure library that supports user defined interfaces.   

## 📦 Installation

* Using [CPM](https://github.com/cpm-cmake/CPM.cmake)
  ```cmake
  CPMFindPackage(
    NAME           eraser
    VERSION        2.0.0
    GIT_REPOSITORY "https://github.com/Curve/eraser"
  )
  ```

* Using FetchContent
  ```cmake
  include(FetchContent)

  FetchContent_Declare(eraser GIT_REPOSITORY "https://github.com/Curve/eraser" GIT_TAG v2.0.0)
  FetchContent_MakeAvailable(eraser)

  target_link_libraries(<target> cr::eraser)
  ```

## 

## 📖 Examples

Given two classes `erase_me` and `erase_me_too`:

https://github.com/Curve/eraser/blob/b61dc0f00541ad2ffd37e83c69b6e5d1e0b726b4/tests/classes.hpp#L5-L37

There are two ways to "erase" them:

...the normal approach:

https://github.com/Curve/eraser/blob/b61dc0f00541ad2ffd37e83c69b6e5d1e0b726b4/tests/erased.cpp#L13-L22
https://github.com/Curve/eraser/blob/b61dc0f00541ad2ffd37e83c69b6e5d1e0b726b4/tests/erased.cpp#L27-L36

... or the experimental/"hacky" approach:

https://github.com/Curve/eraser/blob/b61dc0f00541ad2ffd37e83c69b6e5d1e0b726b4/tests/deduce.cpp#L9-L20
https://github.com/Curve/eraser/blob/b61dc0f00541ad2ffd37e83c69b6e5d1e0b726b4/tests/deduce.cpp#L29-L38

---

While the "hacky" approach might look more pleasing, you should prefer to use the normal approach.
As the name implies, the hacky approach relies on friend injection which allows one to do stateful meta-programming, which is _technically_ not _legal_ C++, however, all three major compilers support it.

## ⭐ Credits 

- [[boost-ext/te]](https://github.com/boost-ext/te): Inspiration for the `experimental` interface.
