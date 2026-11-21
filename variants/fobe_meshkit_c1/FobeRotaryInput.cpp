#include "FobeRotaryInput.h"

#if defined(PIN_ROTARY_A) && defined(PIN_ROTARY_B)

// Gray-code transition table, index = (prev << 2) | current.
// 0 = no movement or an invalid (bounced) transition, +/-1 = one quadrature step.
static const int8_t QUAD_TABLE[16] = {
   0, -1,  1,  0,
   1,  0,  0, -1,
  -1,  0,  0,  1,
   0,  1, -1,  0
};

// A full detent on this encoder is four quadrature steps.
#define STEPS_PER_DETENT  4
#define MIN_EVENT_GAP_MS  5

static inline uint8_t read_state() {
  return (uint8_t)((digitalRead(PIN_ROTARY_A) << 1) | digitalRead(PIN_ROTARY_B));
}

bool FobeRotaryInput::begin() {
  pinMode(PIN_ROTARY_A, INPUT_PULLUP);
  pinMode(PIN_ROTARY_B, INPUT_PULLUP);
  delay(2);   // let the pull-ups settle before sampling the idle state
  _prev = read_state();
  _accum = 0;
  _last_event_ms = 0;
  _ready = true;
  return true;
}

RotaryInputEvent FobeRotaryInput::poll() {
  if (!_ready) begin();

  uint8_t cur = read_state();
  if (cur == _prev) return RotaryInputEvent::None;

  _accum += QUAD_TABLE[(_prev << 2) | cur];
  _prev = cur;

  if (_accum >= STEPS_PER_DETENT || _accum <= -STEPS_PER_DETENT) {
    bool forward = (_accum > 0);
    _accum = 0;

    uint32_t now = millis();
    if (now - _last_event_ms < MIN_EVENT_GAP_MS) return RotaryInputEvent::None;
    _last_event_ms = now;

#ifdef ROTARY_INPUT_REVERSED
    forward = !forward;
#endif
    return forward ? RotaryInputEvent::Next : RotaryInputEvent::Prev;
  }
  return RotaryInputEvent::None;
}

#else

bool FobeRotaryInput::begin() { return false; }
RotaryInputEvent FobeRotaryInput::poll() { return RotaryInputEvent::None; }

#endif
