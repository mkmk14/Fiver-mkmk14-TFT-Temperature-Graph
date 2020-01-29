void welcome()
{
  myGLCD.setBackColor(0, 0, 0); // Sets the background color of the area where the text will be printed to black
  myGLCD.setColor(255, 255, 255); // Sets color to white
  myGLCD.setFont(BigFont); // Sets font to big
  myGLCD.print("Temperature Sensor", CENTER, CENTER); // Prints the string on the screen
}

void drawBackButton()
{
  myGLCD.setColor(100, 155, 203);
  myGLCD.fillRoundRect (10, 10, 60, 36);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (10, 10, 60, 36);
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(100, 155, 203);
  myGLCD.print("<-", 18, 15);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.setFont(SmallFont);
  myGLCD.print("Back to Main Menu", 70, 18);
}

void drawMain()
{
  myGLCD.fillScr(255, 255, 255);
  
  myGLCD.setBackColor(255, 255, 255);
  myGLCD.setFont(BigFont);
  myGLCD.setColor(0, 0, 0);
  myGLCD.print("Temperature Sensor", CENTER, 10);

  rect_with_text(20, 40, 155, 120, "Sensor 1");

  rect_with_text(165, 40,300, 120, "Sensor 2");

  rect_with_text(20, 140, 155, 220, "Sensor 3");

  rect_with_text(165, 140, 300, 220, "Sensor 4");
}

void rect_with_text(int x1, int y1, int len, int wid, const char* txt)
{
  myGLCD.setColor(0, 255, 0);
  myGLCD.fillRoundRect (x1, y1, len, wid);
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(0, 255, 0);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print(txt, x1+5, y1+5);
}
void prinMainTemp()
{
  //drawMain();
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(0, 255, 0);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print(String(temp[0]), 60, 85);
  myGLCD.print(String("o"), 92, 81);  
  myGLCD.print(String("C"), 104, 85);

  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(0, 255, 0);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print(String(temp[1]), 200, 85);
  myGLCD.print(String("o"), 232, 81);  
  myGLCD.print(String("C"), 244, 85);
  
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(0, 255, 0);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print(String(temp[2]), 60, 185);
  myGLCD.print(String("o"), 92, 181);  
  myGLCD.print(String("C"), 104, 185);

  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(0, 255, 0);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print(String(temp[3]), 200, 185);
  myGLCD.print(String("o"), 232, 181);  
  myGLCD.print(String("C"), 244, 185);
}
void checkBackButton()
{
  while (myTouch.dataAvailable())
  {
    myTouch.read();
    x = myTouch.getX();
    y = myTouch.getY();
    if (x != -1 && y != -1)
    {
      Serial.print("X:"); Serial.print(x); Serial.print("\tY:"); Serial.println(y);
      if ((x >= 10) && (x <= 60) && (y >= 10) && (y <= 36))
      {
        screen = scr_main;
        drawMain();
        Serial.print("Back button pressed");
        delay(100);     
      }
    }
  }
}
void checkMainButton()
{
  while (myTouch.dataAvailable())
  {
    myTouch.read();
    x = myTouch.getX();
    y = myTouch.getY();
    if (x != -1 && y != -1)
    {
      Serial.print("X:"); Serial.print(x); Serial.print("\tY:"); Serial.println(y);
      if ((x >= 30) && (x <= 150) && (y >= 40) && (y <= 120))
      {
        screen = scr_lu;
        drawBackButton();
        Serial.println("Left up sensor is pressed for graph");
        delay(100);
      }

      if ((x >= 170) && (x <= 290) && (y >= 40) && (y <= 120))
      {
        screen = scr_ru;
        drawBackButton();
        Serial.println("Right up sensor is pressed for graph");
        delay(100);
      }

      if ((x >= 30) && (x <= 150) && (y >= 140) && (y <= 220))
      {
        screen = scr_ld;
        drawBackButton();
        Serial.println("left down sensor is pressed for graph");
        delay(100);
      }

      if ((x >= 170) && (x <= 290) && (y >= 140) && (y <= 220))
      {
        screen = scr_rd;
        drawBackButton();
        Serial.println("Right down sensor is pressed for graph");
        delay(100);
      }
    }
  }
}



void graph_lu()
{
  myGLCD.fillScr(0, 0, 0);
  drawBackButton();
  int y = 0, xi;
  for (int x = 0; x < arlen; x++)
  {
    y = sen1[x];
    xi = arlen - x;
    Graph(myGLCD, xi, y, 10, 210, 280, 180 , arlen, 0, 30, 0, 100, 20, "LU temperature Grapg", "Time", "Temperature", DKGREY, GREEN, BLUE, BLACK, WHITE, display1);
  }
  display1 = true;
}
void graph_ru()
{
  myGLCD.fillScr(0, 0, 0);
  drawBackButton();
  int y = 0, xi;
  for (int x = 0; x < arlen; x++)
  {
    y = sen2[x];
    xi = arlen - x;
    Graph(myGLCD, xi, y, 10, 210, 280, 180 , arlen, 0, 30, 0, 100, 20, "RU temperature Grapg", "Time", "Temperature", DKGREY, GREEN, BLUE, BLACK, WHITE, display2);
  }
  display2 = true;
}
void graph_ld()
{
  myGLCD.fillScr(0, 0, 0);
  drawBackButton();
  int y = 0, xi;
  for (int x = 0; x < arlen; x++)
  {
    y = sen3[x];
    xi = arlen - x;
    Graph(myGLCD, xi, y, 10, 210, 280, 180 , arlen, 0, 30, 0, 100, 20, "LD temperature Grapg", "Time", "Temperature", DKGREY, GREEN, BLUE, BLACK, WHITE, display3);
  }
  display3 = true;
}
void graph_rd()
{
  myGLCD.fillScr(0, 0, 0);
  drawBackButton();
  int y = 0, xi;
  for (int x = 0; x < arlen; x++)
  {
    y = sen4[x];
    xi = arlen - x;
    Graph(myGLCD, xi, y, 10, 210, 280, 180 , arlen, 0, 30, 0, 100, 20, "RD temperature Grapg", "Time", "Temperature", DKGREY, GREEN, BLUE, BLACK, WHITE, display4);
  }
  display4 = true;
}
void Graph(UTFT &d, double x, double y, double gx, double gy, double w, double h, double xlo, double xhi, double xinc, double ylo, double yhi, double yinc, String title, String xlabel, String ylabel, unsigned int gcolor, unsigned int acolor, unsigned int pcolor, unsigned int tcolor, unsigned int bcolor, boolean &redraw) {

  double ydiv, xdiv;
  // initialize old x and old y in order to draw the first point of the graph
  // but save the transformed value
  // note my transform funcition is the same as the map function, except the map uses long and we need doubles
  //static double ox = (x - xlo) * ( w) / (xhi - xlo) + gx;
  //static double oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  double i;
  double temp;
  int rot, newrot;

  if (redraw == true) {

    redraw = false;
    ox = (x - xlo) * ( w) / (xhi - xlo) + gx;
    oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
    // draw y scale
    for ( i = ylo; i <= yhi; i += yinc) {
      // compute the transform
      temp =  (i - ylo) * (gy - h - gy) / (yhi - ylo) + gy;

      if (i == 0) {
        d.setColor(acolor);
        d.drawLine(gx, temp, gx + w, temp);
      }
      else {
        d.setColor(gcolor);
        d.drawLine(gx, temp, gx + w, temp);
      }

      d.setFont(SmallFont);
      d.setBackColor(bcolor);
      d.setColor(tcolor);
      d.print(String(i), gx - 40, temp);
      // precision is default Arduino--this could really use some format control

    }
    // draw x scale
    for (i = xlo; i <= xhi; i += xinc) {

      // compute the transform

      temp =  (i - xlo) * ( w) / (xhi - xlo) + gx;
      if (i == 0) {
        d.setColor(acolor);
        d.drawLine(temp, gy, temp, gy - h);
      }
      else {
        d.setColor(gcolor);
        d.drawLine(temp, gy, temp, gy - h);
      }
      d.setFont(SmallFont);
      d.setBackColor(bcolor);
      d.setColor(tcolor);
      d.print(String(i), temp, gy + 10);
    }

    //now draw the labels
    d.setFont(SmallFont);
    d.setBackColor(bcolor);
    d.setColor(tcolor);
    d.print(title, gx,  gy - h - 30);

    d.setFont(SmallFont);
    d.setBackColor(bcolor);
    d.setColor(tcolor);
    d.print(xlabel, gx,  gy + 20);

    d.setFont(SmallFont);
    d.setBackColor(bcolor);
    d.setColor(tcolor);
    d.print(ylabel, gx - 30,  gy - h - 10);
  }

  //graph drawn now plot the data
  // the entire plotting code are these few lines...
  // recall that ox and oy are initialized as static above
  x =  (x - xlo) * ( w) / (xhi - xlo) + gx;
  y =  (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  d.setColor(pcolor);
  d.drawLine(ox, oy, x, y);
  d.drawLine(ox, oy + 1, x, y + 1);
  d.drawLine(ox, oy - 1, x, y - 1);
  ox = x;
  oy = y;

}
