
void menu()
{ 
  playDHT();
  if(state <= 3) {
  display.println(F("   Motor control"));
  display.println(F("   reset Motorstep"));
  display.println(F("   change stepmode"));
  }
    switch (state)
    {
        case 1 : display.setCursor(0,8); break;
        case 2 : display.setCursor(0,16); break;
        case 3 : display.setCursor(0,24); break;
        
        case 4 : 
        isMoving = true;
        display.setCursor(0,8);
        display.println(F("   Motor control"));
        display.print(F("   SPD : ")); display.print(Speed); 
        display.print(F(" (")); display.print(speedmode); display.println(F(")"));
        display.print(F("   Position : ")); display.println(currentPosition);
          break;
        
        case 5:
        display.setCursor(0,12);
        display.println(F("   reset Motorstep"));
        display.println(F("   RESET TO 250000"));
          break;
        
//        case 6:
//        display.println(F("   change stepmode"));
//        display.setCursor(2,16);
//        display.println(F(" 1, 2, 4, 8, 16, 32 "));
//        display.print("    STEPMODE : ");
//        display.print(stepmode);
//          break;
        case 6:
        display.setCursor(0,12);
        display.println(F("   change stepmode"));
        display.print("    STEPMODE : ");
        display.print(stepmode);
          break;
    }
  if(state<=3) display.print(" >");
}

void motorControl()
{
  float step__ = 32 / stepmode;
  short stp = step__ * mult;
  
  setspeed();
  display.setCursor(0,24);
    if(now[0]==0&& currentPosition + stp <= 600000 ) {stepper.rotate(1.8*mult); currentPosition += stp;}
    else if(currentPosition + stp > 600000) display.print("H");
    
    if(now[1]==0&& currentPosition - stp >= 3000 ) {stepper.rotate(-1.8*mult); currentPosition -= stp;}
    else if(currentPosition - stp < 3000) display.print("L");
    
    if(S[2] && speedmode < 5) speedmode += 1;
    if(S[3] && speedmode > 1) speedmode -= 1;
    else if(S[3] && speedmode == 1) state-=3;
}

void setspeed()
{
  display.setCursor(0,16);
  if(nowRPM < 15) nowRPM = 15;
  else if(nowRPM > 180) nowRPM = 180;
  switch(speedmode)
  {
    case 1:
    mult = 1;
    stepper.setRPM(nowRPM);
        break;

    case 2:
    mult = 5;
      break;

    case 3:
    mult = 20;
    stepper.setRPM(nowRPM+60);
      break;

    case 4:
    mult = 50;
    stepper.setRPM(nowRPM+90);
      break;

    case 5:
    mult = 100;
    stepper.setRPM(nowRPM+150);
      break;

  }
}

