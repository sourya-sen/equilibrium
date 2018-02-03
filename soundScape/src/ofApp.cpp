#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    sampleRate = 44100;
    bufferSize = 512;
    
    maxiSettings::setup(sampleRate, 2, bufferSize);
    
    clock.setTempo(30);
    clock.setTicksPerBeat(1);
    
    attackOne = 10000;
    releaseOne = 100000;
    ratioOne = 30;
    indexOne = 10;
    
    attackTwo = 1000;
    releaseTwo = 10000;
    
    volumeOne = 1.0;
    volumeTwo = 0.0;
    
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
    
    for(int i = 0; i<bufferSize; i++){
        
        clock.ticker();
        
        volumeOne = (envOne.adsr(1, envOne.trigger));
        volumeTwo = (envTwo.adsr(1, envTwo.trigger));
        
        double myOutput;
        if(clock.tick){
            frequencyOne = frequencyTable[ofRandom(frequencyTable.size())]/2.0f;

            envOne.trigger = 1;
            envTwo.trigger = 1;
        } else {
            envOne.trigger = 0;
            envTwo.trigger = 0;
        }
        
        ratioOne = 30 + 15 * sin(ofDegToRad(ofGetFrameNum()/10.0));
        indexOne = 10 + 5 * sin(ofDegToRad(ofGetFrameNum()/100.0));
    
    
        oneOut = oscillatorOne.sinewave(frequencyOne+ (modulatorOne.sinewave(ratioOne*frequencyOne)*indexOne*volumeOne)) * volumeOne;
        
        double filterOut = filter.lores(oneOut, 80, 2);
        
        output[i * nChannels] = filterOut;
        output[i * nChannels + 1] = filterOut;
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
