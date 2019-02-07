float batteryvoltage()
{  
  int valPinBatt;
  float vpin_perc;
  float vbatt;  
  float calc_res;

  
  calc_res = (R1 + R2) / R2;
  valPinBatt = analogRead(PinBatt);
  vpin_perc = map (valPinBatt, 0, 1023, 0, 500);
  //leggerÃ² 1023 quando ho 5 volt sul pin, quindi scalo 0-1023 in 0-500.
  vbatt = vpin_perc * calc_res / 100 ;  
  //ora divido tutto per 100 perchÃ¨ sopra ho scalato da 0 a 500 anzichÃ¨ da 0 a 5V
  return vbatt;
}
