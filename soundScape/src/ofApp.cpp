#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    sampleRate = 44100;
    bufferSize = 256;
    
    maxiSettings::setup(sampleRate, 2, bufferSize);
    
    clock.setTempo(12);
    clock.setTicksPerBeat(1);
    
    attackOne = 10000;
    releaseOne = 100000;
    ratioOne = 30;
    indexOne = 10;
    
    attackTwo = 1000;
    releaseTwo = 10000;
    
    volumeOne = 1.0;
    volumeTwo = 0.0;
    
    fftOne.setup(FFTSIZE, 512, 256);
    fftTwo.setup(FFTSIZE, 512, 256);
    ifft.setup(FFTSIZE, 512, 256);
    
    envOne.setAttack(attackOne);
    envOne.setDecay(1);
    envOne.setSustain(10);
    envOne.setRelease(releaseOne);
    
    envTwo.setAttack(attackTwo);
    envTwo.setDecay(1);
    envTwo.setSustain(10);
    envTwo.setRelease(releaseTwo);
    
    ofSoundStreamSetup(2, 2, this, sampleRate, bufferSize, 2);
}

//--------------------------------------------------------------
void ofApp::update(){

    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
}

//--------------------------------------------------------------
void ofApp::audioOut(float *output, int bufferSize, int nChannels){
    
    ofScopedLock waveformLock(waveformMutex);
    
    mixLevel = 0.8;
    
    for(int i = 0; i<bufferSize; i++){
        
        clock.ticker();
        
        volumeOne = (envOne.adsr(1, envOne.trigger));
        volumeTwo = (envTwo.adsr(1, envTwo.trigger));
        
        
        if(clock.tick){
            frequencyOne = frequencyTable[ofRandom(frequencyTable.size())]/2.0f;
            frequencyTwo = frequencyTable[ofRandom(frequencyTable.size())]/2.0f;

            envOne.trigger = 1;
            envTwo.trigger = 1;
        } else {
            envOne.trigger = 1;
            envTwo.trigger = 1;
        }
        
        ratioOne = 30 + 15 * sin(ofDegToRad(ofGetFrameNum()/10.0));
        indexOne = 10 + 5 * sin(ofDegToRad(ofGetFrameNum()/100.0));
    
    
        oneOut = oscillatorOne.sinewave(frequencyOne+ (modulatorOne.sinewave(ratioOne*frequencyOne)*indexOne*volumeOne)) * volumeOne;
        
        twoOut = oscillatorTwo.sinewave(frequencyTwo + (modulatorTwo.sinewave(ratioTwo*frequencyTwo)*indexTwo*volumeTwo)) * volumeTwo;
        
        if(fftOne.process(oneOut)) fftOne.magsToDB();
        if(fftTwo.process(twoOut)) fftTwo.magsToDB();
        
        //....................
        
        for(int nBands = 0; nBands<FFTSIZE; nBands++){
            convoMag[nBands] = float(*(fftOne.magnitudes + nBands) * *(fftTwo.magnitudes + nBands));
            convoPha[nBands] = float(*(fftOne.phases + nBands) * *(fftTwo.phases + nBands));
        }
        
        cmPointer = convoMag;
        cpPointer = convoPha;
        
        //....................
        
        ifftOutput = (double)(ifft.process(cmPointer, cpPointer));
        
        double myOutput = oneOut * (1.0 - mixLevel) + ifftOutput * mixLevel;
        
        filterOutput = filter.lores(myOutput, 440, 4);
        
        output[i * nChannels] = filterOutput;
        output[i * nChannels + 1] = filterOutput;
        
        
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
