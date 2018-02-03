#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //-----------------OSC + Kinect
    receiver.setup(PORT);
    
    //-----------------Particle Setup
    for(int i = 0; i < NUM_PARTICLES; i++){
        cParticles tP;
        tP.setup(ofVec2f(ofRandomWidth(), ofGetHeight()/2), ofRandomuf());
        particles.push_back(tP);
    }
    
    a.setup(ofVec2f(ofGetWidth()/2, 20), 200.0);
    b.setup(ofVec2f(ofGetWidth()/2, ofGetHeight() - 20), 200.0);
    
    //These attract the particles back to the centre.
    for(int i = 0; i < 10; i++){
        cAttractor a;
        a.setup(ofVec2f(ofRandomWidth(), ofGetHeight()/2), 100.0);
        originals.push_back(a);
    }
    
    //These will add variation to the particle movement
    for(int i = 0; i < 10; i++){
        cAttractor d;
        d.setup(ofVec2f(ofRandomWidth(), ofRandomHeight()), ofRandom(50, 200));
        distractors.push_back(d);
    }
    
    //Buttons!
    buttons.resize(8);
    for(int i = 0; i<buttons.size(); i++){
        buttons[i].state = 0;
        buttons[i].lastState = -1;
    }
    
    
    //------------------GUI
    /*
     gui.setup();
     gui.add(windS_.setup("wind", 0.001, .00001, .001));
     gui.add(gravS_.setup("gravity", .0001, 0.0001, .001));
     gui.add(oMass_.setup("centre nass", 100, 75, 200));
     gui.add(clamp_.setup("clamp", 300, 150, 500));
     */
    
    //---------------------Serial
    std::vector<ofx::IO::SerialDeviceInfo> devicesInfo = ofx::IO::SerialDeviceUtils::listDevices();
    
    ofLogNotice("ofApp::setup") << "Connected Devices: ";
    
    for (std::size_t i = 0; i < devicesInfo.size(); ++i)
    {
        ofLogNotice("ofApp::setup") << "\t" << devicesInfo[i];
    }
    
    if (!devicesInfo.empty())
    {
        // Connect to the first matching device.
        bool success = device.setup(devicesInfo[0], 9600);
        
        if(success)
        {
            device.registerAllEvents(this);
            ofLogNotice("ofApp::setup") << "Successfully setup " << devicesInfo[0];
        }
        else
        {
            ofLogNotice("ofApp::setup") << "Unable to setup " << devicesInfo[0];
        }
    }
    else
    {
        ofLogNotice("ofApp::setup") << "No devices connected.";
    }
    
    //---------------------General OF setup
    ofSetBackgroundColor(0);
    
    debug = true;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //-------------------Serial.
    
    auto iter = serialMessages.begin();
    
    // Cycle through each of our messages and delete those that have expired.
    while (iter != serialMessages.end()){
        iter->fade -= 1;
        
        if (iter->fade < 0){
            iter = serialMessages.erase(iter);
        } else {
            int value = ofToInt(iter->message);
            
            if(value>0 && value<1001){
                pot0.value = ofMap(value, 0, 1000, 0, 1000);
                //cout<<"pot0: " << pot0.value << endl;
            }
            
            else if(value>1000 && value<2001){
                pot1.value = ofMap(value, 1001, 2000, 0, 1000);
                //cout<<"pot1: " << pot1.value << endl;
            }
            
            else if(value>2000 && value<3001){
                pot2.value = ofMap(value, 2001, 3000, 0, 1000);
                //cout<<"pot2: " << pot2.value << endl;
            }
            
            else if(value>3000 && value<4001){
                pot3.value = ofMap(value, 3001, 4000, 0, 1000);
                //cout<<"pot3: " << pot3.value << endl;
            }
            
            else if(value == 4001) buttons[0].state = 1;
            else if(value == 4002) buttons[0].state = 0;
            
            else if(value == 4003) buttons[1].state = 1;
            else if(value == 4004) buttons[1].state = 0;
            
            else if(value == 4005) buttons[2].state = 1;
            else if(value == 4006) buttons[2].state = 0;
            
            else if(value == 4007) buttons[3].state = 1;
            else if(value == 4008) buttons[3].state = 0;
            
            else if(value == 4009) buttons[4].state = 1;
            else if(value == 4010) buttons[4].state = 0;
            
            else if(value == 4011) buttons[5].state = 1;
            else if(value == 4012) buttons[5].state = 0;
            
            else if(value == 4013) buttons[6].state = 1;
            else if(value == 4014) buttons[6].state = 0;
            
            else if(value == 4015) buttons[7].state = 1;
            else if(value == 4016) buttons[7].state = 0;
            
            else {
                //do nothing?
                //cout <<"other value: " << value << endl;
            }
            
            
            if (!iter->exception.empty()){
                std::cout << "error?!" << std::endl;
            }
            ++iter;
        }
    }
    
    //Let's use the data gotten from the serial to actually do stuff :)
    
    windS_ = ofMap(pot0.value, 0, 1000, 0.0001, 0.001);
    gravS_ = ofMap(pot1.value, 0, 1000, 0.0001, 0.001);
    oMass_ = ofMap(pot2.value, 0, 1000, 75, 200);
    clamp_ = ofMap(pot3.value, 0, 1000, 150, 500);
    
    //Buttons...//TODO: Put these nicely in a vector, this is so hacky o.O
    
    for(int i=0; i<buttons.size(); i++){
        if(buttons[i].state != buttons[i].lastState){
            switch(i){
                case 0:
                    randomTrigger();
                    break;
                case 1:
                    for(auto &d : distractors){
                        d.resetMass(50, 200);
                    }
                    break;
                case 2:
                    for(auto &o : originals){
                        o.resetPosX();
                    }
                    break;
                case 3:
                    for(auto &d : distractors){
                        d.resetPos();
                    }
                    break;
                case 4:
                    randomTrigger();
                    break;
                case 5:
                    randomTrigger();
                    break;
                case 6:
                    randomTrigger();
                    break;
                case 7:
                    randomTrigger();
                    break;
            }
            buttons[i].lastState = buttons[i].state;
        }
    }
    
    /*
    if(b0.state != b0.lastState){
        randomTrigger();
        b0.lastState = b0.state;
        cout << "B0 Changed!" << endl;
    }
    
    if(b1.state != b1.lastState){
        randomTrigger();
        b1.lastState = b1.state;
        cout << "B1 Changed!" << endl;
        
    }
    
    if(b2.state != b2.lastState){
        randomTrigger();
        b2.lastState = b2.state;
        cout << "B2 Changed!" << endl;
        
    }
    
    if(b3.state != b3.lastState){
        randomTrigger();
        b3.lastState = b3.state;
        cout << "B3 Changed!" << endl;
        
    }
    
    if(b4.state != b4.lastState){
        randomTrigger();
        b4.lastState = b4.state;
        cout << "B4 Changed!" << endl;
        
    }
    
    if(b5.state != b5.lastState){
        randomTrigger();
        b5.lastState = b5.state;
        cout << "B5 Changed!" << endl;
        
    }
    
    if(b6.state != b6.lastState){
        randomTrigger();
        b6.lastState = b6.state;
        cout << "B6 Changed!" << endl;
        
    }
    
    if(b7.state != b7.lastState){
        randomTrigger();
        b7.lastState = b7.state;
        cout << "B7 Changed!" << endl;
        
    }
     */
    
    //Also trigger randomly once in a while...
    int rT = ofRandom(10000);
    if(rT<100){
        randomTrigger();
    }
    
    //--------------------OSC + Kinect
    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        auto message = m.getAddress();
        
        //check for the messages! :)
        if(message == "/TSPS/personEntered/"){
            //cout<<"enter message"<<endl;
            
            //setup a new person
            Person one;
            one.pid = m.getArgAsInt32(0);
            one.depth = m.getArgAsFloat(7);
            one.prevDepth = one.depth;
            one.depthDelta = 0.0f;
            
            //cout<<m.getArgAsFloat(7)<<endl;
            
            people.push_back(one);
        }
        
        if(message == "/TSPS/personUpdated/"){
            //update the person!
            
            for(int i = 0; i<people.size(); i++){
                if(m.getArgAsInt32(0) == people[i].pid){
                    people[i].depth = m.getArgAsFloat(7);
                    people[i].depthDelta = fabs(people[i].depth - people[i].prevDepth);
                    if (people[i].depthDelta < 0.00001f) people[i].depthDelta = 0.0;
                    people[i].prevDepth = people[i].depth;
                }
            }
        }
        
        if(message == "/TSPS/scene"){
            //nothing to do with the scene message.
        }
        
        if(message == "/TSPS/personWillLeave/"){
            //remove the person from the vector!
            
            int index = -1;
            
            for(int i = 0; i<people.size(); i++){
                if(m.getArgAsInt32(0) == people[i].pid){
                    index = i;
                }
            }
            
            if (index > -1) people.erase(people.begin() + index);
        }
        
        else{
            //cout<<"unknown and the message is " << message << endl;
        }
    }
    
    
    //--------------------Particle Update
    
    wind = ofVec2f(windS_ * sin(ofDegToRad(float(ofGetFrameNum())/50.0)), 0.0);
    gravity.up = ofVec2f(0.0, -gravS_);
    gravity.down = ofVec2f(0.0, gravS_);
    
    for(auto &o : originals){
        o.mass = oMass_;
    }
    
    for(auto p = particles.begin(); p!= particles.end(); ++p){
        
        if(ofGetFrameNum()%30<15){
            if((a.mass > 0) && (p->id == 0)){
                ofVec2f aForce = a.attract(*p);
                p->applyForce(ofVec2f(aForce.x/4.0, aForce.y));
            }
            
            if((b.mass > 0) && (p->id == 1)){
                ofVec2f bForce = b.attract(*p);
                p->applyForce(ofVec2f(bForce.x/4.0, bForce.y));
            }
            
            
        } else {
            
            if((p->position.y < ofGetHeight()/2 - 50) || (p->position.y > ofGetHeight()/2 + 50)){
                for(auto &o : originals){
                    ofVec2f orig = o.attract(*p);
                    p->applyForce(ofVec2f(0, orig.y));
                }
                
                for(auto &d : distractors){
                    ofVec2f force = d.attract(*p);
                    p->applyForce(ofVec2f(0, force.y));
                }
            }
        }
        
        if (p->id == 0){
            p->applyForce(gravity.up);
            p->applyForce(wind);
            if(p->position.y > ofGetHeight()/2) p->velocity.y = 0.0f;
        }
        if (p->id == 1){
            p->applyForce(gravity.down);
            p->applyForce(-wind);
            if(p->position.y < ofGetHeight()/2) p->velocity.y = 0.0f;
        }
        
        p->update();
        
        if(p->isAlive == false){
            particles.erase(p);
        }
        
    }
    
    if(particles.size()<NUM_PARTICLES){
        int size = NUM_PARTICLES - particles.size();
        for(int i = 0; i<size; i++){
            cParticles tP;
            tP.setup(ofVec2f(ofRandomWidth(), ofGetHeight()/2), ofRandomuf());
            particles.push_back(tP);
        }
    }
    
    
    //-----------Kinect - > Attractors
    //...............................................................
    //Old code to work with only one person.
    /*
    if(people.size() == 1){
        
        if(people[0].depthDelta > 0.0001f){
            a.mass += 2.0;
            b.mass += 2.0;
        } else {
            a.mass -= 10.0;
            b.mass -= 10.0;
        }
        
        a.mass = ofClamp(a.mass, 0.0, clamp_);
        b.mass = ofClamp(b.mass, 0.0, clamp_);
    }
    */
    //...............................................................
    
    double totalDelta = 0.0f;
    
    if(people.size()>0){
    for(int i=0; i<people.size(); i++){
        totalDelta += people[i].depthDelta;
    }
    
    double averageDelta = totalDelta/float(people.size());
    
    cout << "Total number of people: " << people.size() << " Average Delta: " << averageDelta << endl;
        
        if(averageDelta>0.00001f){
            a.mass += 0.5f;
            b.mass += 0.5f;
        } else {
            a.mass -= 10.0;
            b.mass -= 10.0;
        }
    }
    
    a.mass = ofClamp(a.mass, 0.0, clamp_);
    b.mass = ofClamp(b.mass, 0.0, clamp_);
    
    if((people.size() == 0) && (a.mass>0)){
        a.mass -= 25.0;
        b.mass -= 25.0;
    }
    
}

//--------------------------------------------------------------
void ofApp::randomTrigger(){
    int random = int(ofRandom(4));
    
    if(random == 0){
        
        for(auto &o : originals){
            o.resetPosX();
        }
        
    }
    
    else if(random == 1){
        
        for(auto &d : distractors){
            d.resetPos();
        }
        
    }
    
    else {
        //do nothing :)
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //gui.draw();
    
    //-----------------Particle Draw
    for(auto p = particles.begin(); p!= particles.end(); ++p){
        p->draw();
    }
    
    
    //------------------Debug Draws;
    if(debug == true){
        ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), ofGetWidth() - 75, 15);
        a.draw();
        b.draw();
        
        for(auto &o : originals){
            o.draw();
        }
        
        for(auto &d : distractors){
            d.draw();
        }
        
        //gui.draw();
        ofDrawBitmapStringHighlight(ofToString(pot0.value), 15, 15);
        ofDrawBitmapStringHighlight(ofToString(pot1.value), 45, 15);
        ofDrawBitmapStringHighlight(ofToString(pot2.value), 75, 15);
        ofDrawBitmapStringHighlight(ofToString(pot3.value), 105, 15);
        
        ofDrawBitmapStringHighlight(ofToString(buttons[0].state), 15, 30);
        ofDrawBitmapStringHighlight(ofToString(buttons[1].state), 45, 30);
        ofDrawBitmapStringHighlight(ofToString(buttons[2].state), 75, 30);
        ofDrawBitmapStringHighlight(ofToString(buttons[3].state), 105, 30);
        ofDrawBitmapStringHighlight(ofToString(buttons[4].state), 15, 45);
        ofDrawBitmapStringHighlight(ofToString(buttons[5].state), 45, 45);
        ofDrawBitmapStringHighlight(ofToString(buttons[6].state), 75, 45);
        ofDrawBitmapStringHighlight(ofToString(buttons[7].state), 105, 45);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
}

//--------------------------------------------------------------
void ofApp::onSerialBuffer(const ofx::IO::SerialBufferEventArgs& args)
{
    // Buffers will show up here when the marker character is found.
    SerialMessage message(args.getBuffer().toString(), "", 500);
    serialMessages.push_back(message);
}

//---------------------------------------------------------------
void ofApp::onSerialError(const ofx::IO::SerialBufferErrorEventArgs& args)
{
    // Errors and their corresponding buffer (if any) will show up here.
    SerialMessage message(args.getBuffer().toString(),
                          args.getException().displayText(),
                          500);
    serialMessages.push_back(message);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if(key == ' '){
        debug = !debug;
    }
    
    if(key == '1'){
        for(auto &d : distractors){
            d.resetPos();
        }
    }
    
    if(key == '2'){
        for(auto &o : originals){
            o.resetPosX();
        }
    }
    
    
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
    
    a.position = ofVec2f(ofGetWidth()/2, 0 + 20);
    b.position = ofVec2f(ofGetWidth()/2, ofGetHeight() - 20);
    
    
    for(int i = 0; i < originals.size(); i++){
        float spacing = ofGetWidth()/float(originals.size());
        originals[i].position.x = ofRandomWidth();
        originals[i].position.y = ofGetHeight()/2.0;
        
        distractors[i].position = ofVec2f(ofRandomWidth(), ofRandomHeight());
    }
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
