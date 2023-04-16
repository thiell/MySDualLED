
void presentation() {

  // Send the Sketch Version Information to the Gateway
  wait(MESSAGEWAIT);
  sendSketchInfo(SN, SV);

#if defined LED1_CONTROL
  String led1Reg = "LED1 " + Location;
  // Register the LED1 as a dimmable light with the gateway
  wait(MESSAGEWAIT);
#if defined LED1_DIMMER
  MyMessage msgPercLED1(CHILD_ID_LED1, V_PERCENTAGE);
  present(CHILD_ID_LED1, S_DIMMER, led1Reg.c_str());
#else
  MyMessage msgPercLED1(CHILD_ID_LED1, V_STATUS);
  present(CHILD_ID_LED1, S_BINARY, led1Reg.c_str());
#endif
#endif

#if defined LED2_CONTROL
  String led2Reg = "LED2 " + Location;
  // Register the LED2 as a dimmable light with the gateway
  wait(MESSAGEWAIT);
#if defined LED2_DIMMER
  MyMessage msgPercLED2(CHILD_ID_LED2, V_PERCENTAGE);
  present(CHILD_ID_LED2, S_DIMMER, led2Reg.c_str());
#else
  MyMessage msgPercLED2(CHILD_ID_LED2, V_STATUS);
  present(CHILD_ID_LED2, S_BINARY, led2Reg.c_str());
#endif
#endif

  // Pull the current status from the controller
#if defined MY_DEBUG
  Serial.println(F("Updating device status from the controller"));
#endif

#if defined LED1_CONTROL
  wait(MESSAGEWAIT);
#if defined LED1_DIMMER
  request(CHILD_ID_LED1, V_PERCENTAGE);
#else
  request(CHILD_ID_LED1, V_STATUS);
#endif
#endif

#if defined LED2_CONTROL
  wait(MESSAGEWAIT);
#if defined LED2_DIMMER
  request(CHILD_ID_LED2, V_PERCENTAGE);
#else
  request(CHILD_ID_LED2, V_STATUS);
#endif
#endif
}
