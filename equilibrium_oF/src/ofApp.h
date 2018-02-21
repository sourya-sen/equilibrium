#pragma once

#include "ofMain.h"
#include "cParticles.hpp"
#include "cAttractor.hpp"
#include "cRepeller.hpp"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "ofxIO.h"
#include "ofxSerial.h"
#include "ofxMaxim.h"

#define NUM_PARTICLES 10000
#define PORT 12345
#define FFTSIZE 1024

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
    //Button b0, b1, b2, b3, b4, b5, b6, b7;
    
    vector<Button> buttons;
    
    void randomTrigger();
    
    float sizeModifier;
    
    //-----------Audio stuff below.
    void audioOut(float * output, int bufferSize, int nChannels);
    int bufferSize, sampleRate;
    
    vector<float> frequencyTable = {261.63, 293.66, 328.63, 349.23, 392.00, 440.00, 493.88, 523.25};
    vector<float> masterTable = {261.63, 293.66, 328.63, 349.23, 392.00, 440.00, 493.88, 523.25};
    
    //Global Maximillian stuff
    maxiClock clock;
    
    //...1
    float frequencyOne;
    maxiOsc oscillatorOne;
    maxiOsc modulatorOne;
    maxiEnv envOne;
    maxiFFT fftOne;
    double volumeOne;
    double oneOut;
    
    int ratioOne;
    int indexOne;
    int attackOne;
    int releaseOne;
    
    
    //...2
    float frequencyTwo;
    maxiOsc oscillatorTwo;
    maxiOsc modulatorTwo;
    maxiEnv envTwo;
    maxiFFT fftTwo;
    double volumeTwo;
    double twoOut;
    
    int ratioTwo;
    int indexTwo;
    int attackTwo;
    int releaseTwo;
    
    float playFreqOne, playFreqTwo;
    
    //IFFT
    maxiIFFT ifft;
    float convoMag[FFTSIZE];
    float convoPha[FFTSIZE];
    float *cmPointer, *cpPointer;
    double ifftOutput;
    double filterOutput;
    
    double masterFrequency;
    
    ofMutex waveformMutex;
    
    maxiFilter filter;
    float mixLevel;

};
