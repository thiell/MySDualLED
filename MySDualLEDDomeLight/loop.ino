
void loop() {

#if defined MY_DEBUG
  unsigned long currentMillis = millis();       // Start timer
#endif

  checkSW1Button();
  checkSW2Button();
}

#if defined SW1

// Regular On/Off switch

void checkSW1Button() {
  byte val = digitalRead(SW1_PIN);
  if (val != oldSW1Val) {
    if (val == HIGH && currentLED1level == 0) {
      // Turn on light. Set the level to last saved dim value
      int saved = loadLevelState(EEPROM_LED1_LEVEL);
      byte newLED1Level = saved > 0 ? saved : 100;
#if defined MY_DEBUG
      Serial.print(F("LED 1 ON new level :"));
      Serial.println(newLED1Level);
#endif
      analogWrite(MosLED1_PIN, newLED1Level * 2.55 );
      send(msgPercLED1.set(newLED1Level), true);
      currentLED1level = newLED1Level;
    } else if (val == LOW && currentLED1level > 0) {
      analogWrite(MosLED1_PIN, 0);
      send(msgPercLED1.set(0), true);
      currentLED1level = 0;
    }
    if (oldSW1Val != -1) // actual change only
      oldSW2Val = -1;    // change in SW1 => force check SW2 status
  }
  oldSW1Val = val;
}
#endif

#if defined SW2

// Regular On/Off switch (SW2)
void checkSW2Button() {
  byte val = digitalRead(SW2_PIN);
  if (val != oldSW2Val) {
    if (val == HIGH && currentLED2level == 0) {
      // Turn on light. Set the level to last saved dim value
      int saved = loadLevelState(EEPROM_LED2_LEVEL);
      byte newLED2Level = saved > 0 ? saved : 100;
#if defined MY_DEBUG
      Serial.print(F("LED 2 ON new level :"));
      Serial.println(newLED2Level);
#endif
      analogWrite(MosLED2_PIN, newLED2Level * 2.55 );
      send(msgPercLED2.set(newLED2Level), true);
      currentLED2level = newLED2Level;
    } else if (val == LOW && currentLED2level > 0) {
      analogWrite(MosLED2_PIN, 0);
      send(msgPercLED2.set(0), true);
      currentLED2level = 0;
    }
    if (oldSW2Val != -1) // actual change only
      oldSW1Val = -1;    // change in SW2 => force check SW1 status
  }
  oldSW2Val = val;
}
#endif
