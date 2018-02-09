#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"

#define FFTSIZE 1024

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
		
    //Audio init.
    void audioOut(float * output, int bufferSize, int nChannels);
    //void audioIn(float * input, int bufferSize, int nChannels);
    
    int bufferSize;
    int sampleRate;
    
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
