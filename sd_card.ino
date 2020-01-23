void save_sd()
{
  String data;
  data = String(temp[0]) +","+ String(temp[1]) +","+ String(temp[2]) +","+ String(temp[3]);
  File dataFile = SD.open("sensor.csv", FILE_WRITE);
  if (dataFile) 
  {
    dataFile.println(data);
    dataFile.close();
    //Serial.println(dataString);
  }
  else 
  {
    Serial.println("error opening datalog.txt");
  }
}

void save_data()
{
  if (millis() - tim_sd > sd_save_tim)
  {
    tim_sd = millis();
    save_sd();
  }
}
