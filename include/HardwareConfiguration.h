/**
 * @file HardwareConfiguration.h
 * @author Christoph Honal
 * @brief Defines configuration macros for pin mapping
 * @version 0.1
 * @date 2020-05-30
 */

#define TARGET_VARIANT_NAME  "CHRZwatch Unknown"
#define PIN_VIBRATION        LED2
#define PIN_BUTTON1          BUTTON1
#define PIN_BUTTON2          BUTTON2
#define PIN_BATTERY          P0_3
#define PIN_CHARGE           BUTTON3
#define PIN_LCD_CS           P0_11
#define PIN_LCD_RESET        P0_12
#define PIN_LCD_DC           P0_13 
#define PIN_LCD_SCL          P0_14 
#define PIN_LCD_SDA          P0_15
#define PIN_LCD_BL           P0_4
#define PIN_LCD_PWR          P0_30

#if defined(TARGET_VARIANT_I6HRC)
#   define TARGET_VARIANT_NAME  "CHRZwatch I6HRC"
#   define PIN_VIBRATION        P0_25
#   define PIN_BUTTON1          P0_26
#   define PIN_BUTTON2          P0_27
#   define PIN_BATTERY          P0_28
#   define PIN_CHARGE           P0_24
#elif defined(TARGET_VARIANT_NRF52_DK)
#   define TARGET_VARIANT_NAME  "CHRZwatch NRF52_DK"
#   define PIN_VIBRATION_INVERT 1
#endif