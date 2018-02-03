#pragma once

#include "ofMain.h"
#include "cParticles.hpp"
#include "cAttractor.hpp"
#include "cRepeller.hpp"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "ofxIO.h"
#include "ofxSerial.h"

#define NUM_PARTICLES 10000
#define PORT 12345

//----------------------Class to handle serial data.

class SerialMessage
{
public:
    SerialMessage(): fade(0)
    {
    }
    
    SerialMessage(const std::string& _message,
                  const std::string& _exception,
                  int _fade):
    message(_message),
    exception(_exception),
    fade(_fade)
    {
    }
    
    std::string message;
    std::string exception;
    int fade;
};

//------------------------------------------------------

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    bool debug;

    
    //-----------Particle Code
    struct Gravity{
        ofVec2f up;
        ofVec2f down;
    };
    
    Gravity gravity;
    ofVec2f wind;

    vector<cParticles> particles;
    cAttractor a, b;
    vector<cAttractor> originals;
    vector<cAttractor> distractors;
    
    
    //---------GUI Stuff (old, shouldn't be used).
    
//    ofxFloatSlider windS_;
//    ofxFloatSlider gravS_;
//    ofxFloatSlider oMass_;
//    ofxFloatSlider clamp_;
//    ofxPanel gui;
    
    //Stuff to handle effects
    float windS_ = 0.0f;
    float gravS_ = 0.0f;
    float oMass_ = 0.0f;
    float clamp_ = 0.0f;
    
    //----------Kinect Code
    struct Person{
        int pid;
        
        double depth;
        double prevDepth;
        double depthDelta;
        
    };
    
    vector<Person> people;
    
    ofxOscReceiver receiver;
    int current_message_string;
    
    //----------------Serial stuff below.
    
    void onSerialBuffer(const ofx::IO::SerialBufferEventArgs& args);
    void onSerialError(const ofx::IO::SerialBufferErrorEventArgs& args);
    
    ofx::IO::BufferedSerialDevice device;
    
    std::vector<SerialMessage> serialMessages;
    
    struct Pot{
        int value;
    };
    
    struct Button{
        int state, lastState;
    };
    
    Pot pot0, pot1, pot2, pot3;
    Button b0, b1, b2, b3, b4, b5, b6, b7;
    
    void randomTrigger();

};
