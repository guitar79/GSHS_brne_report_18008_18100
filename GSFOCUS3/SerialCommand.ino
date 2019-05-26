


/**
  process the command we recieved from the client
  command format is <Letter><Space><Integer>
  i.e. A 500 ---- Fast Rewind with 500 steps
*/
void serialCommand(String commandString) 
    {
        //charAt(0) : 그냥 맨 앞에거 가져옴
        char _command = commandString.charAt(0);
         //2번째부터 얻기 시작 //아마 #을 제외하기 위한거 같음
        int _step = commandString.substring(2).toInt(); // toInt() : 문자열을 정수로 변환
        Serial.println(_step);
        String _answer = "";
        long _currentPosition = currentPosition;
        long _newPosition = _currentPosition;
        int _backlashStep;

        switch (_command) 
            {
                case 'A':  // FAST REVERSE "<<"
                case 'a': _newPosition = _currentPosition - ( _step * 2 );
                    currentDirection = "INWARD";
                    break;
                case 'B':  // REVERSE "<"
                case 'b': _newPosition = _currentPosition - _step;
                    currentDirection = "INWARD";
                    break;
                case 'C':  // FORWARD ">"
                case 'c': _newPosition = _currentPosition + _step;
                    currentDirection = "OUTWARD";
                    break;
                case 'D':  // FAST FORWARD ">>"
                case 'd': _newPosition = _currentPosition + ( _step * 2 );
                    currentDirection = "OUTWARD";
                    break;
                    
                case 'E':  // MOVE TO POSITION
                case 'e': _newPosition = _step;
                    break;
                case 'F':  // GET CURRENT POSITION
                case 'f': _answer += _currentPosition;
                    break;
                case 'G':  // SET POSITION TO 0
                case 'g': _newPosition = 0;
                    _currentPosition = 0;
                    currentPosition = 0;
                    break;
//                case 'H':  // SET ACCELERATION
//                case 'h': _newPosition = _currentPosition; // non move command
//                    break;
                case 'I':  // SET SPEED
                    _newPosition = _currentPosition; // non move command
                    Speed = _step;
                    stepper.setRPM(60*Speed/MOTOR_STEPS);
                    nowRPM = 60*Speed/MOTOR_STEPS;
                    _answer += "SET-SPEED:";
                    _answer += _step;
                    break;
                case 'i':  // GET SPEED
                    _newPosition = _currentPosition; // non move command
                    _answer += "GET-SPEED:";
                    _answer += Speed;
                    break;
//                case 'J':  // SET SPEED
//                case 'j':  _newPosition = _currentPosition; // non move command
//                    Speed = _step;
//                    _answer += "SET-SPEED:";
//                    _answer += _step;
//                    break;
                case 'k': // GET TEMPERATURE / HUMIDITY
                    _newPosition = _currentPosition; // non move command
                    humidityTemperatureReport();
                    break;
                case 'L' :
                case 'l' :
                //백리시 스텝 고려 (방향이 바뀔때마다 백리시오차가 발생)
                //https://blog.naver.com/PostView.nhn?blogId=rotho&logNo=140191623251
                //https://m.blog.naver.com/PostView.nhn?blogId=ina_om&logNo=220662187786&proxyReferer=https%3A%2F%2Fwww.google.com%2F
                    backlashStep = _step;
                    _answer += "SET-BACKLASHSTEP:";
                    _answer += _step;
                    break;
//                case 'X':  // GET STATUS - may not be needed (just don't use it)
//                case 'x':
//                    break;
                case 'Z':  // IDENTIFY (GET NAME : just same as default)
                case 'z':  _answer += "EQFOCUSER_STEPPER";
                    break;
                default:
                    _answer += "EQFOCUSER_STEPPER";
                    break;
            }

        if (_newPosition != _currentPosition) 
            {
                if (lastDirection != "NONE") 
                    {
                        if (currentPosition < _newPosition) 
                            {
                                // moving forward
                                currentDirection == "OUTWARD";
                            }
                        if (currentPosition > _newPosition) 
                            {
                                // moving backward
                                currentDirection == "INWARD";
                            }
                            
                        Serial.print(lastDirection); Serial.print(F("===")); Serial.println(currentDirection);
                        //백래시 고려
                        if (lastDirection != currentDirection) 
                            {
                              if (currentDirection == "OUTWARD") _newPosition = _newPosition + backlashStep;
                              if (currentDirection == "INWARD") _newPosition = _newPosition - backlashStep;
                            }
                        else 
                            {
                                _backlashStep = 0;
                            }
                    }

                // a move command was issued
                Serial.print(F("MOVING:"));
                Serial.print(_newPosition);
                Serial.println(F("#"));
                distance = _newPosition - _currentPosition;
                moveTo(_newPosition);
                currentPosition = _newPosition;
                lastDirection = currentDirection;
                _answer += "POSITION:";
                _answer += currentPosition;
            }


        Serial.print(_answer);
        Serial.println(F("#"));
    }

/**
  handler for the serial communicationes
  calls the SerialCommand whenever a new command is received
*/
void serialEvent() 
    {
        while (Serial.available()) 
            {
                char inChar = (char)Serial.read();
                inputString += inChar;
                if (inChar == '\n') 
                    {
                        serialCommand(inputString);
                        inputString = "";
                    }
            }
    }

    
