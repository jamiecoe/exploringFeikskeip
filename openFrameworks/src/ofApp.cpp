#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    img.load("rebecca1.png"); // load image
    
    mutationRate = 0.1; // mutation rate
    numberOfSquares = 50; // number of SoundSquares
    numOfSamples = 50; // total number of possible audio samples
    samplePlayerSize = 5; // size of sample player sequence
    
    ofSetBackgroundColor(0);
    on = 255; // start the piece switched off
    
    receive.setup(PORT); // OSC receiver setup
    sender.setup(HOST, PORT2); // OSC sender setup
    
    // Population setup
    population.setup(mutationRate, numberOfSquares, numOfSamples);
    // Initial natural selection, generate a new mating pool
    population.naturalSelection();
    // Pick a current SoundSquare from the mating pool
    currentSoundSquare = population.pickOne();
    // Generate a new population from the
    population.generate();
    
    sampleRate 	= 44100; /* Sampling Rate */
    bufferSize	= 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */
    
    // Maxi settings
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    // Set clock to 60bpm
    clock.setTicksPerBeat(1);
    clock.setTempo(60);
    
    // start sample index at 0
    sampleIndex = 0;
    
    // this has to happen at the end of setup - it switches on the DAC
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4);
    
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
    // Check for OSC messages from Python
    while (receive.hasWaitingMessages()) {
        
        ofxOscMessage m;
        receive.getNextMessage(m);
        
        // Extract gaze coordinates
        if (m.getAddress() == "/avXY") {
            eyeX = ofToFloat(m.getArgAsString(0));
            eyeY = ofToFloat(m.getArgAsString(1));
        }
        
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // Pass in gaze coordinates to population
    population.draw(eyeX, eyeY);
    
    // Display 'Feikskeip 3'
    img.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    // Draw a black rectangle which can be used to cover 'Feikskeip 3'
    ofPushStyle();
    ofSetColor(0, on); // on is used to control transparency
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    ofPopStyle();
    
    
    // Circle to display position of gaze coordinates
     ofDrawCircle(eyeX, eyeY, 10, 10);
   
    
    
    
    


}
//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
   
    
    
    for (int i = 0; i < bufferSize; i++){
        
        clock.ticker(); // Starts clock
        
        // Every clock tick
        if (clock.tick) {
            
            // Get audio sample reference at sample index position
            int reference = currentSoundSquare.audioSamples[sampleIndex];
            // Create a string for audio sample name
            string sound = "sound" + ofToString(reference);

            
            // If the piece is switched on
            if (on == 0) {
                
                // Send OSC message to play audio sample
                ofxOscMessage n;
                n.setAddress("/triggerClip");
                n.addStringArg(sound);
                sender.sendMessage(n, false);
                
                // Send OSC message to turn volume on
                ofxOscMessage v;
                v.setAddress("/volume");
                v.addFloatArg(0.85);
                sender.sendMessage(v, false);
            }
           
            // Increment the sample index
            sampleIndex++;
            
            // If sample index reaches maximum size
            if (sampleIndex == samplePlayerSize) {
                
                // If no one is looking at the screen
                if (eyeX == 0 && eyeY == 0) {
                    // 255 turns on black rectangle to cover image
                    on = 255;
                    // Send OSC message to turn off volume
                    ofxOscMessage v;
                    v.setAddress("/volume");
                    v.addFloatArg(0.);
                    sender.sendMessage(v, false);
                }
                // If someone is looking at screen
                else {
                    // 0 turns off black rectangle to reveal image
                    on = 0;
                    // Natural selection
                    population.naturalSelection();
                    // Pick a current SoundSquare from mating pool
                    currentSoundSquare = population.pickOne();
                    // Generate new population from mating pool
                    population.generate();
                }
                
                sampleIndex = 0; // reset index to 0
            }
            
            
        }
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
