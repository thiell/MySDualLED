
void setup()
{
  metric = getControllerConfig().isMetric;

#if defined LED1_CONTROL
  pinMode(MosLED1_PIN, OUTPUT);
  //Fetch the last light state from the eeprom
  currentLED1level = loadState(EEPROM_LED1_LEVEL);
#if defined MY_DEBUG
  Serial.print(F("LED1 eeprom state: "));
  Serial.print(currentLED1level > 0 ? F("ON, ") : F("OFF, "));
  Serial.print(currentLED1level);
  Serial.println(F("%"));
#endif
  analogWrite(MosLED1_PIN, currentLED1level * 2.55 );
#endif

#if defined LED2_CONTROL
  pinMode(MosLED2_PIN, OUTPUT);
  //Fetch the last light state from the eeprom
  currentLED2level = loadState(EEPROM_LED2_LEVEL);
#if defined MY_DEBUG
  Serial.print(F("LED2 eeprom state: "));
  Serial.print(currentLED2level > 0 ? F("ON, ") : F("OFF, "));
  Serial.print(currentLED2level);
  Serial.println(F("%"));
#endif
  analogWrite(MosLED2_PIN, currentLED2level * 2.55 );
#endif

#if defined SW1
  // Setup the button
  pinMode(SW1_PIN, INPUT);
#ifdef SW1_CLICK
  // After setting up the button, setup debouncer
  debouncerSW1.attach(SW1_PIN);
  debouncerSW1.interval(5);
  oldSW1Val = debouncerSW1.read();
#else
  // Regular ON/OFF switch
  oldSW1Val = digitalRead(SW1_PIN);
#endif
#endif

#if defined SW2
  // Setup the button
  pinMode(SW2_PIN, INPUT);
#ifdef SW1_CLICK
  // After setting up the button, setup debouncer
  debouncerSW2.attach(SW2_PIN);
  debouncerSW2.interval(5);
  oldSW2Val = debouncerSW2.read();
#else
  // Regular ON/OFF switch
  oldSW2Val = digitalRead(SW2_PIN);
#endif
#endif

  Serial.println(F("Node ready to receive messages"));
}
