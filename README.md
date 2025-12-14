# Coding with Adruino

## 0. Setup

Starting a new `sketch` will result in the following code:

<div style="text-align:center;">
    <img src="include/sketch_example.png" style="width:50%">
</div>

Pressing the `check` icon will result in doing a `Verify` of the code. This will lead to an error without changing anything:

<div style="text-align:center;">
    <img src="include/error_sketch_example.png" style="width:30%">
</div>

To remove this error, it's necessary to chose a defined micro controller from:

> Tools -> Board: "ESP32 Family Device" -> esp32 -> ESP32C6 Dev Module

<div style="text-align:center;">
    <img src="include/board_selection.png" style="width:80%">
</div>

Now code can be written and if the sketch is compilable, it can be `uploaded` to the board by pressing on the arrow.

## 1. Layout of the ESP32-C6 Super Mini

The physical layout of the micro controller can be seen in the following image:

<div style="text-align:center;">
    <img src="include/nyFRvmgzB4-500.webp" style="width:40%">
</div>

- The Battery LED always blinks while being pluged in
- The Status LED turns on, if `BOOT` mode is enabled
    - The boot mode can be accesed by pressing and holding the left button `BOOT` and pressing the `RST`-button afterwards. Leave the boot mode by pressing `RST` once.
- The WS2812 LED can be programmed by using the `#include <Adafruit_NeoPixel.h>` library

An actual layout of every pin is given in the following image:

<div style="text-align:center;">
    <img src="include/uGIogYTad2-1000.webp" style="width:100%">
</div>
