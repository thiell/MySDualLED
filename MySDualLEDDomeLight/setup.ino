
void setup()
{
  metric = getControllerConfig().isMetric;

  // no specific setup for Dome Light, just fetch the status from
  // the buttons during first loop

#if defined MY_DEBUG
  Serial.println(F("Node ready to receive messages"));
#endif
}
