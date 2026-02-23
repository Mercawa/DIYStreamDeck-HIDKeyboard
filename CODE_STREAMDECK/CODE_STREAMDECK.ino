#include <Keyboard.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN   A1
#define LED_COUNT 8

const uint8_t buttonPins[12] = {
  2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 14, 15
};

const uint8_t keyMap[12] = {
  KEY_F13, KEY_F14, KEY_F15, KEY_F16,
  KEY_F17, KEY_F18, KEY_F19, KEY_F20,
  KEY_F21, KEY_F22, KEY_F23, KEY_F24
};

#define BTN_F24_INDEX 11

Adafruit_NeoPixel leds(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// ---------------- ESTADO ----------------
uint8_t ledMode = 0;
unsigned long modeHoldStart = 0;
bool modeChanging = false;

unsigned long lastLedUpdate = 0;
uint16_t hueBase = 0;

// rainbow
uint8_t rainbowSpeedMode = 1; // 0 lento, 1 medio, 2 rápido
const uint16_t rainbowSpeedValues[3] = { 300, 700, 1200 };

// reactivo
bool rippleActive = false;
int rippleStep = 0;
unsigned long rippleTimer = 0;
uint16_t rippleHue = 0;

// ---------------- SETUP ----------------
void setup() {
  Keyboard.begin();

  for (int i = 0; i < 12; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  leds.begin();
  leds.setBrightness(255);
  leds.clear();
  leds.show();
}

// ---------------- LOOP ----------------
void loop() {
  handleButtons();
  handleModeChange();
  updateLEDs();
}

// ---------------- BOTONES ----------------
void handleButtons() {
  for (int i = 0; i < 12; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {

      // F24 PARA VARIAR VELOCIDAD
      if (i == BTN_F24_INDEX && ledMode == 0) {
        rainbowSpeedMode = (rainbowSpeedMode + 1) % 3;
        delay(200); // antirebote velocidad
      }

      Keyboard.write(keyMap[i]);

      if (ledMode == 4) startRipple();

      delay(150);
    }
  }
}

// ---------------- CAMBIO DE MODO ----------------
void handleModeChange() {
  if (digitalRead(buttonPins[0]) == LOW && digitalRead(buttonPins[1]) == LOW) {
    if (!modeChanging) {
      modeHoldStart = millis();
      modeChanging = true;
    }
    if (millis() - modeHoldStart > 3000) {
      ledMode = (ledMode + 1) % 5;
      modeChanging = false;
      leds.clear();
    }
  } else {
    modeChanging = false;
  }
}

// ---------------- LED ----------------
void updateLEDs() {
  switch (ledMode) {
    case 0: rainbowFast(); break;
    case 1: breathingColors(); break;
    case 2: greenPulse(); break;
    case 3: solidGreen(); break;
    case 4: rippleEffect(); break;
  }
}

// ---------------- COLOR ----------------
uint32_t correctedColor(uint8_t r, uint8_t g, uint8_t b) {
  r = min(255, r * 1.3);
  g = min(255, g * 1.0);
  b = min(255, b * 1.2);
  return leds.gamma32(leds.Color(r, g, b));
}

// ================= MODOS =================

// RAIMBOW
void rainbowFast() {
  if (millis() - lastLedUpdate > 15) {
    lastLedUpdate = millis();

    for (int i = 0; i < LED_COUNT; i++) {
      uint16_t h = hueBase + (i * 65536 / LED_COUNT);
      leds.setPixelColor(i,
        leds.gamma32(leds.ColorHSV(h, 255, 255)));
    }
    leds.show();

    hueBase += rainbowSpeedValues[rainbowSpeedMode];
  }
}

// BREATHING
void breathingColors() {
  static int breath = 0;
  static int dir = 1;
  static uint16_t hue = 0;

  if (millis() - lastLedUpdate > 18) {
    lastLedUpdate = millis();

    // respiración
    breath += dir;
    if (breath >= 100 || breath <= 0) dir *= -1;

    // brillo respirado
    leds.setBrightness(map(breath, 0, 100, 80, 255));

    // cambio color
    hue += 120;   // probá entre 80 y 200 si querés ajustar

    for (int i = 0; i < LED_COUNT; i++) {
      leds.setPixelColor(
        i,
        leds.gamma32(leds.ColorHSV(hue, 255, 255))
      );
    }

    leds.show();
  }
}
// Pulso verde
void greenPulse() {
  static int pulse = 0;
  static int dir = 1;

  if (millis() - lastLedUpdate > 20) {
    lastLedUpdate = millis();

    pulse += dir;
    if (pulse >= 100 || pulse <= 0) dir *= -1;

    uint8_t g = map(pulse, 0, 100, 80, 255);

    for (int i = 0; i < LED_COUNT; i++) {
      leds.setPixelColor(i, correctedColor(0, g, 0));
    }
    leds.show();
  }
}

// Verde fijo
void solidGreen() {
  leds.setBrightness(255);
  for (int i = 0; i < LED_COUNT; i++) {
    leds.setPixelColor(i, correctedColor(0, 255, 0));
  }
  leds.show();
}

// Reactivo
void startRipple() {
  rippleActive = true;
  rippleStep = 0;
  rippleTimer = millis();
  rippleHue += random(2000, 12000);
}

void rippleEffect() {
  if (!rippleActive) {
    for (int i = 0; i < LED_COUNT; i++) {
      leds.setPixelColor(i, correctedColor(0, 40, 0));
    }
    leds.show();
    return;
  }

  if (millis() - rippleTimer > 50) {
    rippleTimer = millis();
    leds.clear();

    int center = LED_COUNT / 2;

    if (center - rippleStep >= 0)
      leds.setPixelColor(center - rippleStep,
        leds.gamma32(leds.ColorHSV(rippleHue, 255, 255)));

    if (center + rippleStep < LED_COUNT)
      leds.setPixelColor(center + rippleStep,
        leds.gamma32(leds.ColorHSV(rippleHue, 255, 255)));

    leds.show();
    rippleStep++;

    if (rippleStep > center) rippleActive = false;
  }
}