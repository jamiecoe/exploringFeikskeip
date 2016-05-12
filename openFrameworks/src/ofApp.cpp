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
    
    // Initialise sampler player array
    for(int i = 0; i < numOfSamples; i++) {
        maxiSample temp;
        sounds.push_back(temp); // Add sample players to vector array
        isPlaying.push_back(false); // All start off as false
        waves.push_back(0); // All waves start at 0
    }
    
    // Add .wav files to sample players
    for (int i = 1; i < numOfSamples+1; i++) {
        string soundName = "sound" + ofToString(i) + ".wav";
        sounds[i-1].load(ofToDataPath(soundName));
    }
    
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
    
    // For all the sounds
    for (int i = 0; i < sounds.size(); i++) {
        // If the sounds finished playing
        if (sounds[i].finished()) {
            isPlaying[i] = false; // set its playing state to false
            sounds[i].setPosition(0); // set its position back to beginning
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // Pass in gaze coordinates to population
    population.draw(eyeX, eyeY);
    
    // Display 'Feikskeip 3'
    img.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    //Draw a black rectangle which can be used to cover 'Feikskeip 3'
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
            isPlaying[reference] = true; // set its playing state to true
            
            // print its name to console
            string sound = "sound" + ofToString(reference);
            cout<<sound<<endl;

           
            // Increment the sample index
            sampleIndex++;
            
            // If sample index reaches maximum size
            if (sampleIndex == samplePlayerSize) {
                
                // If no one is looking at the screen
                if (eyeX == 0 && eyeY == 0) {
                    // 255 turns on black rectangle to cover image
                    on = 255;
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

        double finalWave = 0;
        
        // If the piece is switched on
        if (on == 0) {
            
            // For all the sounds
            for (int j = 0; j < sounds.size(); j++) {
                // If their play state is on
                if (isPlaying[j]) {
                    // Add their wave to finalWave
                    waves[j] = sounds[j].playOnce();
                    finalWave += waves[j];
                }
            }
        }
        else finalWave = 0; // Else turn volume off
        
        //play finalWave
        output[i*nChannels    ] = finalWave;
        output[i*nChannels + 1] = finalWave;
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
