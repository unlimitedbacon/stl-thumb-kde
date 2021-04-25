stl-thumb-kde
=============

This is the KDE / KIO plugin for [stl-thumb](https://github.com/unlimitedbacon/stl-thumb).

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
