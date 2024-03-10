stl-thumb-kde
=============

[![Build Status](https://github.com/unlimitedbacon/stl-thumb-kde/actions/workflows/cmake.yml/badge.svg)](https://github.com/unlimitedbacon/stl-thumb-kde/actions/workflows/cmake.yml)

This is the KDE / KIO plugin for [stl-thumb](https://github.com/unlimitedbacon/stl-thumb). It shows previews of `.stl` files in Dolphin and throughout the KDE desktop.

![stl-thumb-kde](https://user-images.githubusercontent.com/3131268/116009004-fe666680-a5cb-11eb-9ecf-cb443120c2d5.png)

## Installation

You will first need to install [stl-thumb](https://github.com/unlimitedbacon/stl-thumb).


Build Instructions
------------------

Build dependencies:
* cmake
* extra-cmake-modules
* qtbase5-dev
* kio-dev

1. Install [stl-thumb](https://github.com/unlimitedbacon/stl-thumb)
2. Then you can build the plugin.
    ```
    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make
    ```
3. And install it for testing (on Debian or Ubuntu).
    ```
    sudo make install
    ```
4. To build a Debian package
    ```
    cpack
    ```
