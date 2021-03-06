/*
AnalogButton_Combos
Version 0.1

Connection more then one button to a single analog pin. Utilizing
software debounce to prevent registering multiple button press
while allow for 2 button combos to be registered.  

The Circuit:
  Most other analog buttons circuits call for the resistors to be
  lined up in series from ground. The analog pin and each button
  connect off one of the resistors. My cuicuit requires that the
  resistors tie in from +5 to the buttons. The buttons all connect
  to the analog pin which is tied to ground threw a 1k resistor as
  seen in the diagram below. 
 
         Analog pin 5
            |
Ground--1K--|--------|--------|-------|-------|
            |        |        |       |       |
           btn1     btn2     btn3    btn4    btn5
            |        |        |       |       |
         220 Ohm  390 Ohm  680 Ohm   2.2K    4.7K
            |--------|--------|-------|-------|-- +5V
            
Created By: Michael Pilcher
February 24, 2010

*/
int j = 1; // integer used in scanning the array designating column number
//2-dimensional array for asigning the buttons and there high and low values
int Button[15][3] = {{1, 838, 839}, // button 1
                     {2, 608, 609}, // button 2
                     {3, 733, 734}, // button 3
                     {4, 320, 321}, // button 4
                     {5, 173, 174}, // button 5
                     {6, 896, 897}, // button 1 + button 2
                     {7, 877, 878}, // button 1 + button 3
                     {8, 851, 852}, // button 1 + button 4
                     {9, 844, 845}, // button 1 + button 5
                     {10, 821, 822}, // button 2 + button 3
                     {11, 769, 770}, // button 2 + button 4
                     {12, 753, 754}, // button 2 + button 5
                     {13, 674, 675}, // button 3 + button 4
                     {14, 643, 644}, // button 3 + button 5
                     {19, 408, 409}}; // button 4 + button 5
                   
int analogpin = 5; // analog pin to read the buttons
int label = 0;  // for reporting the button label
int counter = 0; // how many times we have seen new value
long time = 0;  // the last time the output pin was sampled
int debounce_count = 50; // number of millis/samples to consider before declaring a debounced input
int current_state = 0;  // the debounced input value
int ButtonVal;

void setup()
{
  Serial.begin(9600); 

}

void loop()
{
   // If we have gone on to the next millisecond
  if (millis() != time)
  {
    // check analog pin for the button value and save it to ButtonVal
    ButtonVal = analogRead(analogpin);
  //   Serial.print("valor: "); Serial.println(ButtonVal);
    if(ButtonVal == current_state && counter >0)
    { 
      counter--;
    }
    if(ButtonVal != current_state)
    {
      counter++;
    }
    // If ButtonVal has shown the same value for long enough let's switch it
    if (counter >= debounce_count)
    {
      counter = 0;
      current_state = ButtonVal;
      //Checks which button or button combo has been pressed
      if (ButtonVal > 0)
      {
        ButtonCheck();
      }
    }
    time = millis();
  }
}

void ButtonCheck()
{
  // loop for scanning the button array.
  for(int i = 0; i <= 15; i++)
  {
    // checks the ButtonVal against the high and low vales in the array
    if(ButtonVal >= Button[i][j] && ButtonVal <= Button[i][j+1])
    {
      // stores the button number to a variable
      label = Button[i][0];
      Action();      
    }
  }
}

void Action()
{
  if(label == 1)
  {
    Serial.println("Up Button");
  }
  if(label == 2)
  {
    Serial.println("Down Button");
  }
  if(label == 3)
  { 
    Serial.println("Left Button");
  }
  if(label == 4)
  {
    Serial.println("Right Button");
  }
  if(label == 5)
  {
    Serial.println("Action Button #1");
  }
  if(label == 6)
  {
    Serial.println("Action Button #2");
  }
  if(label == 8)
  {
    Serial.println("Left and Up Buttons");
  }
  if(label == 9)
  {
    Serial.println("Right and Up Buttons");
  }
  if(label == 12)
  {
    Serial.println("Left and Down Buttons");
  }
  if(label == 13)
  {
    Serial.println("Right and Down Buttons");
  }
  if(label == 14)
  {
    Serial.println("Action Buttons #1 and #2");
  }    
       
  //Serial.println("Button =:");
  //Serial.println(label);
  //delay(200);
  
  
}



