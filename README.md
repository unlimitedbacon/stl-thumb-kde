stl-thumb-kde
=============

This is the KDE / KIO plugin for [stl-thumb](https://github.com/unlimitedbacon/stl-thumb).

Build Instructions
------------------

1. First you will need to build `stl-thumb`, which this project uses as a library.
    ```
    git checkout https://github.com/unlimitedbacon/stl-thumb.git
    cd stl-thumb
    cargo build --release
    ```
2. Then you can build the plugin.
    ```
    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make
    ```
3. And install it for testing.
    ```
    sudo make install
    ```