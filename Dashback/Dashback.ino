/*
  This code utalizes the Nicohood Library and was built off of the Multi-Singleplayer example
  Use this code at your own risk 
  Code Written by Simple Controllers
  Open source meaning its free to modify, share, and improve on.
  Tag me in any creations you make!
  I love seeing what you guys come up with!
*/

#include "Nintendo.h"

// Change this to what you like right now it is on pin 3 and 4
// I personally use 18 and 19 since it is near the bottom of the Arduino 
CGamecubeController GamecubeController1(4);
CGamecubeConsole GamecubeConsole1(3);

// Pin definitions
#define pinLed LED_BUILTIN

//Zeroing the buffer and control stick.  Recommended do not change
  int bufferrr = 0;
  int i = 1;
  int X = 128;


void setup()
{
  // Set up debug led
  pinMode(pinLed, OUTPUT);

}


void loop()
{
    //Just stops the code if no controller is found
    if (!GamecubeController1.read()) {
      delay(100);
      return;
    }


    // Gets the data of controller
    auto r1 = GamecubeController1.getReport();
    Gamecube_Data_t d = defaultGamecubeData;

    //NEW! Zeros the controller on startup
    d.origin = GamecubeController1.getOrigin();
    //Huge thanks to SeanMombo for debugging/figuring this out!

    //Zeros the xAxis in the code
    if (i == 1){
      int X = r1.xAxis;
      i = 0;
    }
    


    //if the x axis is between these two than set buffer to eight
    if (r1.xAxis > X-21 && r1.xAxis < X+21){
      //CHANGE THIS TO 8 IF PLAYING ON DOLPHIN
      bufferrr = 2;
    }


    //Reporting all buttons, sticks, sliders
    d.report.a = r1.a;
    d.report.b = r1.b;
    d.report.x = r1.x;
    d.report.y = r1.y;
    d.report.start = r1.start;
    
    d.report.dleft = r1.dleft;
    d.report.dright = r1.dright;
    d.report.ddown = r1.ddown;
    d.report.dup = r1.dup;
    
    d.report.z = r1.z;
    d.report.r = r1.r;
    d.report.l = r1.l;
    
    d.report.xAxis = r1.xAxis;
    d.report.yAxis = r1.yAxis;
    d.report.cxAxis = r1.cxAxis;
    d.report.cyAxis = r1.cyAxis;
    d.report.left = r1.left;
    d.report.right = r1.right;

    
    //The dashback modification
    if (r1.xAxis < X-22 || r1.xAxis > X+22){
      //Automatically dashes and skips all buffer if you enter running state
      if (r1.xAxis > X+97 || r1.xAxis < X-97){
        d.report.xAxis = r1.xAxis; 
        bufferrr = 0;
      }
      if (bufferrr > 0){
        d.report.xAxis = 128;
        bufferrr = bufferrr - 1;
        //than set xaxis to neutral
      }
      
    }
    
    // Sends the data to the console
    if (!GamecubeConsole1.write(d))
    {
      delay(100);
    }


    if (d.status.rumble) {
      GamecubeController1.setRumble(true);
    }
    else {
      GamecubeController1.setRumble(false);
    }
  }
