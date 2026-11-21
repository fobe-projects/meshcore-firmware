#include <Arduino.h>
#include <Wire.h>

#include "FobeMeshKitC1Board.h"

void FobeMeshKitC1Board::begin() {
  // sets startup_reason and powers up the CC310 CryptoCell
  NRF52Board::begin();

  pinMode(PIN_VBAT_READ, INPUT); // VBAT ADC input
  // Set all button pins to INPUT_PULLUP
  pinMode(PIN_BUTTON1, INPUT_PULLUP_SENSE);
  pinMode(SX126X_ANT_SW, OUTPUT);
  digitalWrite(SX126X_ANT_SW, HIGH);

  #if defined(PIN_WIRE_SDA) && defined(PIN_WIRE_SCL)
    Wire.setPins(PIN_WIRE_SDA, PIN_WIRE_SCL);
  #endif

  Wire.begin();

  #ifdef P_LORA_TX_LED
    pinMode(P_LORA_TX_LED, OUTPUT);
    digitalWrite(P_LORA_TX_LED, HIGH);
  #endif

  delay(10);   // give sx1262 some time to power up
}

void FobeMeshKitC1Board::shutdownPeripherals() {
  // display off, LoRa reset and powered down, GNSS stopped, CC310 closed
  NRF52Board::shutdownPeripherals();

  #ifdef PIN_PWR_EN
    digitalWrite(PIN_PWR_EN, LOW);   // cut the peripheral rail (OLED, GNSS, sensors)
  #endif

  // Re-arm the user button as a wake source. begin() configures it as
  // INPUT_PULLUP_SENSE, but MomentaryButton::begin() later reconfigures the very
  // same pin as a plain INPUT, which clears the SENSE latch. Without this nothing
  // wakes the MCU from SYSTEM_OFF except RESET or re-plugging USB. The internal
  // pull-up is used deliberately, since the external one may sit on the rail that
  // was just switched off above.
  #ifdef PIN_USER_BTN
    nrf_gpio_cfg_sense_input(g_ADigitalPinMap[PIN_USER_BTN],
                             NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
  #endif
}
