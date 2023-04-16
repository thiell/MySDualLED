
void receive(const MyMessage &message) {

  if (message.isAck()) {
#if defined MY_DEBUG
    Serial.println("ACK received");
#endif
  }

#if defined LED1_CONTROL
  else if (((message.sensor == CHILD_ID_LED1)) && (message.type == V_STATUS || message.type == V_PERCENTAGE)) {

    //  Retrieve the power or dim level from the incoming request message
    int requestedLevel = atoi(message.data);

    // Adjust incoming level if this is a V_LIGHT variable update [0 == off, 1 == on]
    requestedLevel *= (message.type == V_STATUS ? 100 : 1);

    // Clip incoming level to valid range of 0 or 100
#if defined LED1_DIMMER
    requestedLevel = requestedLevel > 100 ? 100 : requestedLevel;
    requestedLevel = requestedLevel < 0  ? 0   : requestedLevel;
#else
    requestedLevel = requestedLevel >= 50 ? 100 : requestedLevel;
    requestedLevel = requestedLevel < 50  ? 0   : requestedLevel;
#endif

#if defined MY_DEBUG
    Serial.print(F("Changing LED1 level from "));
    Serial.print(currentLED1level);
    Serial.print(F(" to "));
    Serial.println(requestedLevel);
#endif

    if (requestedLevel > 0) {
      saveLevelState(EEPROM_LED1_LEVEL, requestedLevel);
    }
    analogWrite(MosLED1_PIN, requestedLevel * 2.55 );
    currentLED1level = requestedLevel;

    // Inform the gateway of the current dim level.
    wait(MESSAGEWAIT);
#if defined LED1_DIMMER
    send(msgPercLED1.set(currentLED1level));
#else
    send(msgStatLED1.set(currentLED1level = 100 ? currentLED1level : 0));
#endif
  }
#endif

#if defined LED2_CONTROL
  else if (((message.sensor == CHILD_ID_LED2)) && (message.type == V_STATUS || message.type == V_PERCENTAGE)) {

    //  Retrieve the power or dim level from the incoming request message
    int requestedLevel = atoi(message.data);

    // Adjust incoming level if this is a V_LIGHT variable update [0 == off, 1 == on]
    requestedLevel *= (message.type == V_STATUS ? 100 : 1);

    // Clip incoming level to valid range of 0 to 100
#if defined LED2_DIMMER
    requestedLevel = requestedLevel > 100 ? 100 : requestedLevel;
    requestedLevel = requestedLevel < 0  ? 0   : requestedLevel;
#else
    requestedLevel = requestedLevel >= 50 ? 100 : requestedLevel;
    requestedLevel = requestedLevel < 50  ? 0   : requestedLevel;
#endif

#if defined MY_DEBUG
    Serial.print(F("Changing LED2 level from "));
    Serial.print(currentLED2level);
    Serial.print(F(" to "));
    Serial.println(requestedLevel);
#endif

    if (requestedLevel > 0) {
      saveLevelState(EEPROM_LED2_LEVEL, requestedLevel);
    }
    analogWrite(MosLED2_PIN, requestedLevel * 2.55 );
    currentLED2level = requestedLevel;

    // Inform the gateway of the current dim level.
    wait(MESSAGEWAIT);
#if defined LED2_DIMMER
    send(msgPercLED2.set(currentLED2level));
#else
    send(msgStatLED2.set(currentLED2level = 100 ? currentLED2level : 0));
#endif
  }

  if (currentLED2level > 0) {
    toggleLED = 0;
  } else if (currentLED1level > 0) {
    toggleLED = 2;
  } else {
    toggleLED = 1;
  }
#endif

}
