#include "AS5600.h"
#include "Wire.h"
#include <Joystick.h>

AS5600 as5600;

const int DEBUG_MODE_PIN = 15;
const int PADDLE_RIGHT = 0;
const int PADDLE_LEFT = 1;

int32_t wheel_range = 270 / AS5600_RAW_TO_DEGREES;
int32_t zero_angle;

int paddle_right_position = 0;
int paddle_left_position = 0;

int32_t reset_start;
int8_t reset_triggered = 0;
int8_t paddles_held = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(DEBUG_MODE_PIN, INPUT_PULLUP);
  pinMode(PADDLE_RIGHT, INPUT_PULLUP);
  pinMode(PADDLE_LEFT, INPUT_PULLUP);

  Serial.begin(115200);
  Joystick.begin();

  // Initialize AS5600
  as5600.begin(4);
  as5600.setDirection(AS5600_CLOCK_WISE);
  // Breaks if missing for some reason
  as5600.isConnected();

  // Set zero position
  zero_angle = as5600.getCumulativePosition();
}

void loop() {
  int32_t degrees = as5600.getCumulativePosition() - zero_angle;
  int32_t limited = constrain(degrees, -wheel_range / 2, wheel_range / 2);

  // if (!digitalRead(PADDLE_RIGHT)) {
  //   Joystick.button(1, true);
  // } else {
  //   Joystick.button(1, false);
  // }

  // if (!digitalRead(PADDLE_LEFT)) {
  //   Joystick.button(2, true);
  // } else {
  //   Joystick.button(2, false);
  // }

  // Zero wheel position by holding both paddles for 3s
  if (!digitalRead(PADDLE_RIGHT) && !digitalRead(PADDLE_LEFT)) {
    if (paddles_held == 0) {
      paddles_held = 1;
      reset_start = millis();
    } else {
      int32_t elapsed = millis() - reset_start;
      if (elapsed > 3000 && reset_triggered == 0) {
        reset_triggered = 1;
        // Flash LED
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        // Zero wheel position
        zero_angle = as5600.getCumulativePosition();
      }
    }
  } else {
    if (paddles_held == 1) {
      paddles_held = 0;
      reset_triggered = 0;
    }
  }

  // Virtual accelerator pedal
  if (!digitalRead(PADDLE_RIGHT)) {
    paddle_right_position += 2;
  } else {
    paddle_right_position -= 10;
  }
  paddle_right_position = constrain(paddle_right_position, 0, 1023);
  Joystick.Y(paddle_right_position);

  // Virtual brake pedal
  if (!digitalRead(PADDLE_LEFT)) {
    paddle_left_position += 5;
  } else {
    paddle_left_position -= 10;
  }
  paddle_left_position = constrain(paddle_left_position, 0, 1023);
  Joystick.Z(paddle_left_position);

  if (digitalRead(DEBUG_MODE_PIN)) {
    // Map degrees to joystick
    int16_t target = map(limited, -wheel_range / 2, wheel_range / 2, 0, 1023);
    Joystick.X(target);
  } else {
    Serial.print(zero_angle);
    Serial.print("\t");
    Serial.print(degrees);
    Serial.print("\t");
    Serial.print(limited);
    Serial.println();
  }
}
