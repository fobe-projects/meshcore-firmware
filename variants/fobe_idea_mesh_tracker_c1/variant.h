#ifndef _FOBE_IDEA_MESH_TRACKER_C1_H_
#define _FOBE_IDEA_MESH_TRACKER_C1_H_

/** Master clock frequency */
#define VARIANT_MCK (64000000ul)

#define USE_LFXO    // Board uses 32khz crystal for LF

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "WVariant.h"

#define PINS_COUNT               (48)
#define NUM_DIGITAL_PINS         (48)
#define NUM_ANALOG_INPUTS        (1)
#define NUM_ANALOG_OUTPUTS       (0)

// LEDs
#define PIN_LED                  (32 + 11)
#define LED_BLUE                 (-1) // Disable annoying flashing caused by Bluefruit
#define LED_BUILTIN              PIN_LED
#define P_LORA_TX_LED            PIN_LED
#define LED_STATE_ON             0

// Buttons
#define PIN_BUTTON1              (32 + 0) // Menu / User Button
#define PIN_USER_BTN             PIN_BUTTON1

// Buzzer
#define PIN_BUZZER               (0 + 14) // Buzzer pin (defined per firmware type)

#define VBAT_ENABLE              (-1)

// Analog pins
#define PIN_VBAT_READ            (0 + 5)
#define AREF_VOLTAGE             (3.0F)
#define ADC_MULTIPLIER           (1.73F)
#define ADC_RESOLUTION           (12)

// Serial interfaces
#define PIN_SERIAL1_RX           (0 + 12)
#define PIN_SERIAL1_TX           (32 + 9)

// SPI Interfaces
#define SPI_INTERFACES_COUNT     (1)

#define PIN_SPI_MISO             (0 + 24)
#define PIN_SPI_MOSI             (0 + 22)
#define PIN_SPI_SCK              (0 + 20)

// Lora Pins
#define P_LORA_SCLK              PIN_SPI_SCK
#define P_LORA_MISO              PIN_SPI_MISO
#define P_LORA_MOSI              PIN_SPI_MOSI
#define P_LORA_DIO_1             (0 + 17)
#define P_LORA_RESET             (0 + 13)
#define P_LORA_BUSY              (0 + 15)
#define P_LORA_NSS               (32 + 8)
#define SX126X_ANT_SW            (0 + 11)
#define SX126X_RXEN              RADIOLIB_NC
#define SX126X_TXEN              RADIOLIB_NC
#define SX126X_DIO2_AS_RF_SWITCH true
#define SX126X_DIO3_TCXO_VOLTAGE (1.8f)

// Wire Interfaces
#define WIRE_INTERFACES_COUNT    (2)

#define PIN_WIRE_SDA             (0 + 7)
#define PIN_WIRE_SCL             (0 + 27)
#define PIN_WIRE1_SDA            (32 + 14)
#define PIN_WIRE1_SCL            (32 + 10)
#define I2C_NO_RESCAN
#define DISPLAY_ADDRESS 0x3D // SSD1306 OLED I2C address

// GPS L76KB
#define GPS_BAUDRATE    9600
#define PIN_GPS_TX      PIN_SERIAL1_RX
#define PIN_GPS_RX      PIN_SERIAL1_TX
#define PIN_GPS_STANDBY (0 + 6)
#define PIN_GPS_EN      (0 + 26)

#define PIN_PWR_EN      (0 + 16)

#endif