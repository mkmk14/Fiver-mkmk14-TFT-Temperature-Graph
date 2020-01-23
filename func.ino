void temp_init()
{
  sensors.begin(); 
  Serial.print(F("Locating devices..."));
  Serial.print(F("Found "));
  deviceCount = sensors.getDeviceCount();
  if (deviceCount > 4) deviceCount = 4;
  Serial.print(deviceCount, DEC);
  Serial.println(F(" devices."));
}

void readTemp()
{
  sensors.requestTemperatures();
  for (int i = 0;  i < deviceCount;  i++)
  {
    temp[i] = sensors.getTempCByIndex(i);
    //Serial.print((char)176);
  }
  updateArrays();
}

void fillZero()
{
  for (int i = 0; i < arlen ; i++)
  {
    sen1[i] = 0;
    sen2[i] = 0;
    sen3[i] = 0;
    sen4[i] = 0;
  }
}

void updateArrays()
{
  for (int i = 0; i < (arlen - 1) ; i++)
  {
    sen1[i] = sen1[i + 1];
    sen2[i] = sen2[i + 1];
    sen3[i] = sen3[i + 1];
    sen4[i] = sen4[i + 1];
  }
  sen1[arlen - 1] = temp[0];
  sen2[arlen - 1] = temp[1];
  sen3[arlen - 1] = temp[2];
  sen4[arlen - 1] = temp[3];
}
void update_temp()
{
  if (millis() - tim_temp > 1000)
  {
    tim_temp = millis();
    readTemp();
  }

  if (millis() - tim_disp > 60000L)
  {
    tim_disp = millis();
    updateArrays();
  }
}
void parray()
{
  for (int i = 0; i < arlen ; i++)
  {
    Serial.print(sen1[i]);
    Serial.print(",");
  }
  Serial.println("");
}
