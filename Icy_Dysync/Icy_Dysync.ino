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


    // Get the data of controller
    auto r1 = GamecubeController1.getReport();
    Gamecube_Data_t d = defaultGamecubeData;

    //NEW! Zeros the controller on startup
    d.origin = GamecubeController1.getOrigin();
    //Huge thanks to SeanMombo for debugging/figuring this out!

    //Reporting all buttons, sticks, sliders
    d.report.a = r1.a;
    d.report.b = r1.b;
    //Changes X to report Z button
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

    if (r1.x == 1){
      //This may need a little tweaking
      //If both Nana and Popo jump lower this by one or two
      //If no one jumps raise this by one or two 
      //One way to fix would be to have DPad (Left and right lower and raise the Y Value
      //This way you can set it in game and not have to worry
      d.report.yAxis = 181;
      d.report.xAxis = 128;
      d.report.x = 0;
    }

    
    // Sends the data to the console 
    if (!GamecubeConsole1.write(d))
    {
      delay(100);
    }

    // Enable rumble
    if (d.status.rumble) {
      GamecubeController1.setRumble(true);
    }
    else {
      GamecubeController1.setRumble(false);
    }
  }




  

