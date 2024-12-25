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
    VERSION        1.0.0
    GIT_REPOSITORY "https://github.com/Curve/eraser"
  )
  ```

* Using FetchContent
  ```cmake
  include(FetchContent)

  FetchContent_Declare(eraser GIT_REPOSITORY "https://github.com/Curve/eraser" GIT_TAG v1.0.0)
  FetchContent_MakeAvailable(eraser)

  target_link_libraries(<target> cr::eraser)
  ```

## 

## 📖 Examples

https://github.com/Curve/eraser/blob/88b77e7adc77a4ba4b598fd34cd4acc497b3fbfd/tests/erased.cpp#L45-L63
https://github.com/Curve/eraser/blob/88b77e7adc77a4ba4b598fd34cd4acc497b3fbfd/tests/erased.cpp#L67-L85
