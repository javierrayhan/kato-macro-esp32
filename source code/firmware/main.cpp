// ==== Liblary ==== 
#include <Arduino.h>
#include <EEPROM.h>
#include <BleKeyboard.h>
#include <ESP32Encoder.h>
#include "esp32-hal-cpu.h"
#include "keys.h"
#include <esp_sleep.h>

//SET UP
#define DEBUG 1
#define NAME_KEYBOARD "KATO Macro"
#define objKeyboard katoKeys
const char* intro = R"rawliteral(
 ___   _  _______  _______  _______    __   __  _______  _______  ______    _______ 
|   | | ||   _   ||       ||       |  |  |_|  ||   _   ||       ||    _ |  |       |
|   |_| ||  |_|  ||_     _||   _   |  |       ||  |_|  ||       ||   | ||  |   _   |
|      _||       |  |   |  |  | |  |  |       ||       ||       ||   |_||_ |  | |  |
|     |_ |       |  |   |  |  |_|  |  |       ||       ||      _||    __  ||  |_|  |
|    _  ||   _   |  |   |  |       |  | ||_|| ||   _   ||     |_ |   |  | ||       |
|___| |_||__| |__|  |___|  |_______|  |_|   |_||__| |__||_______||___|  |_||_______|

)rawliteral";   

//DEEP SLEEP
#define TIMEOUT_IDLE 180000  
unsigned long lastCheckedTime = 0;

typedef void (*KeyFunction)(BleKeyboard &);                                                                                                                                          
KeyFunction keyFunctions1[] = {
  key_1,
  key_2,
  key_3,
  key_4,
  key_5,
  key_6,
  [](BleKeyboard &k){ k.releaseAll(); },  
  key_0,
};

KeyFunction keyFunctions2[] = {
  key_7,
  key_8,
  key_9,
  key_0,
  key_A,
  key_B,
  [](BleKeyboard &k){ k.releaseAll(); },  
  key_0,
};

KeyFunction keyFunctions3[] = {
  key_C,
  key_D,
  key_E,
  key_F,
  key_G,
  key_H,
  [](BleKeyboard &k){ k.releaseAll(); },
  key_0,
};

KeyFunction keyFunctions4[] = {
  key_I,
  key_J,
  key_K,
  key_L,
  key_M,
  key_N,
  [](BleKeyboard &k){ k.releaseAll(); }, 
  key_0,
};

KeyFunction keyFunctions5[] = {
  key_L,
  key_O,
  key_P,
  key_Q,
  key_R,
  key_S,
  [](BleKeyboard &k){ k.releaseAll(); },  
  key_0,
};

KeyFunction keyFunctions6[] = {
  key_media_previous_track,
  key_media_play_pause,
  key_media_next_track,
  key_media_mute,
  key_media_volume_down,
  key_media_volume_up,
  [](BleKeyboard &k){ k.releaseAll(); },  
  key_0,
};

// KeyFunction keydummy[]{

// };

KeyFunction* keyLayers[] = {
  keyFunctions1,
  keyFunctions2,
  keyFunctions3,
  keyFunctions4,
  keyFunctions5,
  keyFunctions6  
};

//DEBUGGING STATE 
#if DEBUG == 1
  #define debug(x) Serial.print(x)
  #define debugln(x) Serial.println(x)
  #define debugf(...) Serial.printf(__VA_ARGS__)
#else
  #define debug(x) 
  #define debugln(x) 
  #define debugf(...)
#endif

// ==== Hardware Config ====
#define cpuFreq 80

// ==== EEPROM Config ====
#define EEPROM_SIZE 8 
int ledBrightnessEEPROM = 0;
int layerEEPROM = 2;

// ==== Function Declarate ====
void showStatus(const char* statusText); 
void buttonRead();
void updateEncoder();
void setVolumeTarget(uint8_t target);
void setLEDBrightness(uint8_t brightnessPercent);
void layerChanges(int8_t l);
void sleepMode();

// ==== Variable Setup ====

//BUTTON
bool currentState;

//Encoder 
long lastPosition = 0;
int8_t encoderValue = 0;  

//Volume
int8_t lastTarget = 20; 

//BLE Status
bool bleConnected = false;

//LED PWM
uint8_t ledPin = 25;       
uint8_t pwmChannel = 0;    
uint16_t freq = 5000;     
uint8_t resolution = 8;   

uint8_t ledScale = 5;

//LED Recent
int8_t savedBrightness;

//Layer Change
int8_t layer = 1;
bool layerChange = false;

// ==== Setup Pin ====
const int buttonPins[] = {
  4,   // Key 1
  5,   // Key 2
  12,  // Key 3
  13,  // Key 4
  14,  // Key 5
  16,  // Key 6
  17,  // Key 7
  19   // Encoder Button
};

const int numButtons = sizeof(buttonPins) / sizeof(buttonPins[0]);
bool lastButtonState[numButtons] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};

// // Pin encoder
#define clk 26
#define dt 27

// === Liblary Setup ====
BleKeyboard katoKeys(NAME_KEYBOARD, "Exter Labs", 100);  // Name, vendor, battery level (dummy)
ESP32Encoder encoder;

void setup() {
  Serial.begin(115200);
  // Enable wake from GPIO 17 (LOW)
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_4, 0); 
  
  debugln("🔌 [BOOT] Starting up...");
  
  if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0) {
    debug("✨ Wake from GPIO 4");
  } else {
    debugln("🚀 Normal boot");
  }

  // Show Intro
  debugln("\n🎬 Showing intro screen...");
  debug(intro);
  debugln("");

  // Hardware Config
  debugln("⚙️  [CONFIG] Setting CPU frequency...");
  setCpuFrequencyMhz(cpuFreq);

  // EEPROM Init
  debugln("💾 [EEPROM] Initializing...");
  if (!EEPROM.begin(EEPROM_SIZE)) {
    debugln("❌ [EEPROM] Initialization failed!");
    return;
  } else {
    debugln("✅ [EEPROM] Ready.");
  }

  // PWM LED Setup
  debugln("💡 [LED] Setting up PWM...");
  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(ledPin, pwmChannel);

  savedBrightness = EEPROM.read(ledBrightnessEEPROM);
  debug("[LED] Restoring brightness from EEPROM: ");
  debugln(savedBrightness);
  setLEDBrightness(savedBrightness*ledScale);

  // Layer EEPROM
  layer = EEPROM.read(layerEEPROM);
  if(layer < 1){
    layer = 1;
  }
  debug("[LAYER] Restoring Layer from EEPROM: ");
  debugln(layer);

  // BLE Keyboard
  debugln("🧠 [BLE] Initializing BLE Keyboard...");
  katoKeys.begin();

  // Encoder Setup
  debugln("🔁 [ENCODER] Attaching rotary encoder...");
  ESP32Encoder::useInternalWeakPullResistors = puType::up;
  encoder.attachHalfQuad(clk, dt);
  encoder.setCount(encoderValue * 2);  
  lastPosition = encoder.getCount() / 2;

  // Pin PullUps for buttons
  debugln("🔘 [BUTTONS] Setting pin modes...");
  for (int i = 0; i < numButtons; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    debug("[BUTTON] Pin ");
    debug(i);
    debugln(" set to INPUT_PULLUP.");
  }

  // BLE Connection Check
  debugln("📡 [BLE] Waiting for host connection...");
  while (!katoKeys.isConnected()) {
    showStatus("Waiting for connection");
    bleConnected = false;
    sleepMode();
  }

  if (katoKeys.isConnected()) {
    debugln("\n✅ [BLE] Connected to host!");
    bleConnected = true;
    // setLEDBrightness(savedBrightness*ledScale);
    lastCheckedTime = millis(); 
  }
}

void loop() {
  // ==== Handle Input ====
  if (katoKeys.isConnected()) {
    //Connected Status
    if (bleConnected == false){
      debugln("\n[STATUS] Reconnected to host ✅");
      bleConnected = true;
    }

    buttonRead();
    updateEncoder();

    if (!(digitalRead(buttonPins[6]))) {
      setLEDBrightness(savedBrightness*ledScale);
      layerChange = true;
    } if (digitalRead(buttonPins[6])){
      setVolumeTarget(encoderValue);
      layerChange = false;
    }

    lastCheckedTime = millis(); 
  } else if(!katoKeys.isConnected()) {
    showStatus("Host disconnected, retrying to reconnect");
    bleConnected = false;
    sleepMode();
  }

  delay(50); // debounce
}

// ==== Status Debugging ====
void showStatus(const char* statusText) {
  static const char* dots[] = {"   ", ".  ", ".. ", "..."};
  static uint8_t dotIndex = 0;
  static unsigned long lastUpdate = 0;

  if (millis() - lastUpdate >= 500) {
    debug("\r[STATUS] ");
    debug(statusText);
    debug(dots[dotIndex]);
    debug("     "); 
    dotIndex = (dotIndex + 1) % 4;
    lastUpdate = millis();
  }
}

// ==== Button Read ====
void buttonRead(){
  for (int i = 0; i < numButtons; i++) {
    currentState = digitalRead(buttonPins[i]);

    if (lastButtonState[i] == HIGH && currentState == LOW) {
      debugf("📲 Button %d pressed\n", i + 1);
      
      switch (i) {
        case 0: 
          layerChanges(i);
          break;  // Key 1
        case 1: 
          layerChanges(i);
          break;  // Key 2
        case 2: 
          layerChanges(i);
          break;  // Key 3
        case 3: 
          layerChanges(i);
          break;  // Key FN
        case 4: 
          layerChanges(i);
          break;  // Key 4
        case 5: 
          layerChanges(i);
          break;  // Key 5
        case 6: 
          
          break;  // Key 6
        case 7: 
          if (layer >= 1 && layer <= 6) {
            keyLayers[layer - 1][i](objKeyboard);
          }
          break; // Encoder Key
      }
    }
    katoKeys.releaseAll();
    lastButtonState[i] = currentState;
  }
}

// ==== Encoder ====
void updateEncoder() {
  long newPosition = encoder.getCount() / 4;  // Sensitive

  if (newPosition != lastPosition) {
    long delta = newPosition - lastPosition;
    lastPosition = newPosition;

    if (!(digitalRead(buttonPins[6]))){
      savedBrightness += delta;
      if (savedBrightness > 100) savedBrightness = 100;  // Max
      if (savedBrightness < 0) savedBrightness = 0; // Min
      
      debug("\nSaved Brightness: "); 
      debug(savedBrightness);
    } else {
      encoderValue += delta;          // Update Value
      if (encoderValue > 100) encoderValue = 100;  // Max
      if (encoderValue < 0) encoderValue = 0;  // Min

      debug("\nencoderValue: "); 
      debug(encoderValue);
    }
  
  }

  delay(50);
}

// ==== Set Volume ==== 
void setVolumeTarget(uint8_t target) {
  target = constrain(target, 0, 100);
  if (target > lastTarget) { // Increase Volume
      int steps = target - lastTarget;
      for (int i = 0; i < steps; i++) {
        katoKeys.write(KEY_MEDIA_VOLUME_UP);
        delay(5); // debounce
      }
    } else if (target < lastTarget) { // Decrease Volume
      int steps = lastTarget - target;
      for (int i = 0; i < steps; i++) {
        katoKeys.write(KEY_MEDIA_VOLUME_DOWN);
        delay(5); // debounce
      }
    }

  lastTarget = target; 
}

// ==== Brightness Set ====
void setLEDBrightness(uint8_t brightnessPercent) {
  // Clamp brightness between 0-100%
  if (brightnessPercent > 20) brightnessPercent = 20;
  if (brightnessPercent < 0) brightnessPercent = 0;

  // Convert percentage to duty (0-255)
  uint8_t duty = map(brightnessPercent, 0, 100, 0, 255);

  // Set the PWM duty cycle
  ledcWrite(pwmChannel, duty);

  //EEPROM Commit
  if (!(digitalRead(buttonPins[6]))){
    EEPROM.write(ledBrightnessEEPROM, brightnessPercent/ledScale);
    EEPROM.commit();
  } 
}

// ==== Layer change ====
void layerChanges(int8_t l){
  if (layerChange) {
    if (l<6){
      layer = l + 1;  
    } else {
      layer = l; 
    }

    layerChange = false;
    debugf("\n[LAYER] Layer Changed to: %d\n", layer);
  } else {
    if (layer >= 1 && layer <= 6) {
      keyLayers[layer - 1][l](objKeyboard);
    }
  }
  EEPROM.write(layerEEPROM, layer);
  EEPROM.commit();
}

// ==== Sleep Mode ====
void sleepMode(){
  if (millis() - lastCheckedTime >= TIMEOUT_IDLE) {
    debugln("\n💤 No connection for 3 minutes, going to sleep...");
    ledcWrite(pwmChannel, 0);
    delay(100); 
    esp_deep_sleep_start();
  } else {
    delay(100);
  }
}
