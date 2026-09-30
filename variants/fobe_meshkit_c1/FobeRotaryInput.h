#pragma once

#include <Arduino.h>
#include <helpers/ui/RotaryInput.h>

// Rotary encoder on the FoBE Mesh Tracker C1 (F2102).
// Plain 2-bit quadrature decoder on two GPIOs; pin numbers come from variant.h.
class FobeRotaryInput : public RotaryInput {
public:
  bool begin() override;
  RotaryInputEvent poll() override;
  bool isReady() const override { return _ready; }

private:
  bool _ready = false;
  uint8_t _prev = 0;
  int8_t _accum = 0;
  uint32_t _last_event_ms = 0;
};
