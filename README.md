# 32Blit RPG Test

[![license](http://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/Blackhawk-TA/32blit-rpg-test/blob/master/LICENSE.md)
![Build](https://github.com/32blit/32blit-boilerplate/workflows/Build/badge.svg)
[![github](https://img.shields.io/github/release/Blackhawk-TA/32blit-rpg-test.svg?color=brightgreen)](https://github.com/Blackhawk-TA/32blit-rpg-test/releases)

This is a project for testing the basic feature implementations required for a rpg on the 32Blit console.

## Build
Linux:
```
mkdir build
cd build
cmake ..
make
```

32blit:
```
mkdir build.stm32
cd stm32
cmake .. -DCMAKE_TOOLCHAIN_FILE="../32blit-sdk/32blit.toolchain"
make rpg-test
```
