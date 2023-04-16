
void loop() {

#if defined MY_DEBUG
  unsigned long currentMillis = millis();       // Start timer
#endif

#if defined SW1_CLICK
  // Check if someone has pressed the SW1 button
  checkSW1ButtonClick();
#elif defined SW1
  // Regular On/Off switch SW1
  checkSW1Button();
#endif

#if defined SW2_CLICK
  // Check if someone has pressed the SW2 button
  checkSW2ButtonClick();
#elif defined SW2
  // Regular On/Off switch SW2
  checkSW2Button();
#endif

}

//
// Switch button support
//

#ifdef SW1_CLICK

// Click/press button switch

void checkSW1ButtonClick() {
  debouncerSW1.update();
  byte SW1Val = debouncerSW1.read();

  byte newLED1Level = 0;
  byte newLED2Level = 0;
  
  if (SW1Val != oldSW1Val && SW1Val == HIGH) {
#if defined MY_DEBUG
    Serial.println(F("SW1 pushed"));
#endif

    // LED1
    if (currentLED1level == 0) {
      // Turn on light. Set the level to last saved dim value
      int saved = loadLevelState(EEPROM_LED1_LEVEL);
      newLED1Level = saved > 0 ? saved : 100;
#if defined MY_DEBUG
      Serial.print(F("LED 1 ON new level :"));
      Serial.println(newLED1Level);
#endif
    } else {
      // Turn off light.
      newLED1Level = 0;
#if defined MY_DEBUG
      Serial.print(F("LED 1 OFF new level :"));
      Serial.println(newLED1Level);
#endif
    }
    analogWrite(MosLED1_PIN, newLED1Level * 2.55 );
    send(msgPercLED1.set(newLED1Level), true);
    currentLED1level = newLED1Level;

    // LED 2
    if (currentLED2level == 0) {
      // Turn on light. Set the level to last saved dim value
      int saved = loadLevelState(EEPROM_LED2_LEVEL);
      newLED2Level = saved > 0 ? saved : 100;
#if defined MY_DEBUG
      Serial.print(F("LED 2 ON new level :"));
      Serial.println(newLED2Level);
#endif
    } else {
      // Turn off light.
      newLED2Level = 0;
#if defined MY_DEBUG
      Serial.print(F("LED 2 OFF new level :"));
      Serial.println(newLED2Level);
#endif
    }
    analogWrite(MosLED2_PIN, newLED2Level * 2.55 );
    send(msgPercLED2.set(newLED2Level), true);
    currentLED2level = newLED2Level;
    
  }
  oldSW1Val = SW1Val;
}


#endif

#ifdef SW2_CLICK

// Click/press button switch

void checkSW2ButtonClick() {
  debouncerSW2.update();
  byte SW2Val = debouncerSW2.read();
  byte newLED2Level = 0;
  if (SW2Val != oldSW2Val && SW2Val == HIGH) {
#if defined MY_DEBUG
    Serial.println(F("SW2 pushed"));
#endif
    if (currentLED2level == 0) {
      // Turn on light. Set the level to last saved dim value
      int saved = loadLevelState(EEPROM_LED2_LEVEL);
      newLED2Level = saved > 0 ? saved : 100;
#if defined MY_DEBUG
      Serial.print(F("LED 2 ON new level :"));
      Serial.println(newLED2Level);
#endif
    } else {
      // Turn off light.
      newLED2Level = 0;
#if defined MY_DEBUG
      Serial.print(F("LED 2 OFF new level :"));
      Serial.println(newLED2Level);
#endif
    }
    analogWrite(MosLED2_PIN, newLED2Level * 2.55 );
    send(msgPercLED2.set(newLED2Level), true);
    currentLED2level = newLED2Level;
  }
  oldSW2Val = SW2Val;
}

#elif defined SW2

// Regular On/Off toggle switch (SW2)

void checkSW2Button() {
  byte newLED2Level = 0;
  byte val = digitalRead(SW2_PIN);
  if (val != oldSW2Val) {
#if defined MY_DEBUG
    Serial.print(F("SW2 switched: "));
    Serial.println(val);
#endif
    if (currentLED2level == 0) {
      // Turn on light. Set the level to last saved dim value
      int saved = loadLevelState(EEPROM_LED2_LEVEL);
      newLED2Level = saved > 0 ? saved : 100;
 #if defined MY_DEBUG
      Serial.print(F("LED 1 ON new level :"));
      Serial.println(newLED2Level);
#endif
    } else {
      // Turn off light.
      newLED2Level = 0;
#if defined MY_DEBUG
      Serial.print(F("LED 1 OFF new level :"));
      Serial.println(newLED2Level);
#endif
    }
    analogWrite(MosLED2_PIN, newLED2Level * 2.55 );
    send(msgPercLED2.set(newLED2Level), true);
    currentLED2level = newLED2Level;
  }
  oldSW2Val = val;
}
#endif
