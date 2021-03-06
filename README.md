# CHRZ Watch Firmware

Custom firmware for the NRF52 based smartwatch I6HRC using the Mbed framework.

## Development setup

Install **Visual Studio Code** and the **PlatformIO** extension. Then use the `i6hrc` env for deployment, or the `nrf52_dk` env for debugging on a NRF52-DK board.

Use `doxygen` or the "Build Documentation" task to generate documentation.

## Modding a I6HRC watch

Solder the SWDCLK and SWDIO testpoints to the unused USB data lines. You might want to fabricate a custom USB to ISP adapter.

### Flashing the watch

Flashing should work with any SWD capable programmer, like for example the **ST-Link V2** (the cheap clones work too). 

If the watch refuses to flash, hangs in low poer mode or is stuck in a bootloop, try connecting to it using **OpenOCD** (http://openocd.org/) while spamming the reset button on your adapter (or short `SWDIO` to `VCC`). This should not be needed during normal flashing and execution.

```
openocd -d2 -f interface/stlink-v2.cfg -c "transport select hla_swd" -f target/nrf52.cfg
```

On a successful connection OpenOCD displays something like "`Info : nrf52.cpu: hardware has 6 breakpoints, 4 watchpoints`". The script `tools/reset.sh` or the task "Reset Target" automates this spamming.

Optinally, open up GDB via telnet and reset the core using `reset halt` via `telnet localhost 4444`.

You can then exit the OpenOCD instance if you want to use a other tool for flashing (e.g. PlatformIO). The core should run normally (or hang at the reset vector if you reset it) and accept SWD connections and flash commands reliably. The PlatformIO flash tool should leave the core in a useable, running state.

## Connecting to a phone

You can use the Android app "**nRF Connect**" (https://play.google.com/store/apps/details?id=no.nordicsemi.android.mcp&hl=en) to test the Bluetooth functions. Sometimes, connecting takes multiple tries.

## Stock firmware

A dump of the stock ROM can be found at `doc/stock_rom_dump.bin` (armv7le) for decompiling (e.g. using **Ghidra**: https://ghidra-sre.org/) or restoring the watch (untested).

## Thanks to and credits

Thanks to *Aaron Christophel* for providing instructions on how to modify the hardware, mapping out the pins and providing some demo Arduino code.

 - https://github.com/atc1441
 - http://atcnetz.blogspot.com/2019/02/arduino-auf-dem-fitness-tracker-dank.html
 - https://www.mikrocontroller.net/topic/467136
 - https://www.youtube.com/watch?v=0Fu-VSuKHEg 

### Library credits:

 - ARM Mbed RTOS and API: https://os.mbed.com/
 - The `CurrentTimeService` module of the `BLE_GATT_Services` library is based on `BLE_CurrentTimeService` by *Takehisa Oneta*: https://os.mbed.com/users/ohneta/code/BLE_CurrentTimeService/
   - Deferred calls in ISR context to EventQueue
   - Added documentation
 - The `Adafruit_ST7735_Mini` library is based on the `Adafruit_ST7735` library by *Andrew Lindsay*: https://platformio.org/lib/show/2150/Adafruit_ST7735, which in turn is a port of a library by Adafruit: https://github.com/adafruit/Adafruit-ST7735-Library
   - Added support for the `R_MINI160x80` display type
   - Added documentation
   - Added an explicit dependency to `Adafruit_GFX` port by *Andrew Lindsay*: https://platformio.org/lib/show/2147/Adafruit_GFX, which is a port of https://github.com/adafruit/Adafruit-GFX-Library
