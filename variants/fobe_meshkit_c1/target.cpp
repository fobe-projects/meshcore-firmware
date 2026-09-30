#include <Arduino.h>
#include "target.h"
#include <helpers/ArduinoHelpers.h>
#include <helpers/sensors/MicroNMEALocationProvider.h>

FobeMeshKitC1Board board;

RADIO_CLASS radio = new Module(P_LORA_NSS, P_LORA_DIO_1, P_LORA_RESET, P_LORA_BUSY, SPI);

WRAPPER_CLASS radio_driver(radio, board);

VolatileRTCClock fallback_clock;
AutoDiscoverRTCClock rtc_clock(fallback_clock);

#ifdef ENV_INCLUDE_GPS
MicroNMEALocationProvider nmea = MicroNMEALocationProvider(Serial1, &rtc_clock);
EnvironmentSensorManager sensors = EnvironmentSensorManager(nmea);
#else
EnvironmentSensorManager sensors = EnvironmentSensorManager();
#endif

#ifdef DISPLAY_CLASS
  DISPLAY_CLASS display;
  MomentaryButton user_btn(PIN_USER_BTN, 1000, true);
  #if defined(PIN_ENCODER_BTN)
    // active-low with internal pull-up, no multi-click so a press reacts at once
    MomentaryButton encoder_btn(PIN_ENCODER_BTN, 1000, true, true, false);
  #endif
#endif

#if defined(UI_HAS_ROTARY_INPUT)
  #include "FobeRotaryInput.h"
  static FobeRotaryInput rotary_input_impl;
  RotaryInput& rotary_input = rotary_input_impl;
#endif

bool radio_init() {
  rtc_clock.begin(Wire);

  return radio.std_init(&SPI);
}

uint32_t radio_get_rng_seed() {
  return radio.random(0x7FFFFFFF);
}

void radio_set_params(float freq, float bw, uint8_t sf, uint8_t cr) {
  radio.setFrequency(freq);
  radio.setSpreadingFactor(sf);
  radio.setBandwidth(bw);
  radio.setCodingRate(cr);
}

void radio_set_tx_power(uint8_t dbm) {
  radio.setOutputPower(dbm);
}

mesh::LocalIdentity radio_new_identity() {
  RadioNoiseListener rng(radio);
  return mesh::LocalIdentity(&rng);  // create new random identity
}
