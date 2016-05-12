#pragma once

#include "ofMain.h"
#include "Population.h"
#include "ofxMaxim.h"
#include "ofxOsc.h"

#define PORT 12345 // Port for communicating with Python

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
        void audioOut(float * output, int bufferSize, int nChannels);
    
    ofImage img; // variable to display 'Feikskeip 3'
    
    int on; // variable that turns piece on and off
    
    ofxOscReceiver receive; // OSC receiver
    
    Population population; // Population object
    float mutationRate; // mutation rate
    int numberOfSquares; // number of SoundSquares
    int numOfSamples; // total number of possible audio samples
    int samplePlayerSize; // size of sample player sequence
    
    float eyeX, eyeY; // variables for the viewer gaze position
    
    maxiClock clock; // clock
    int sampleIndex; // sample index number
    SoundSquare currentSoundSquare; // current SoundSquare
    vector<maxiSample> sounds; // vector array of sounds
    vector<bool> isPlaying; // vector array to check if sounds are playing
    vector<double> waves; // vector array of doubles to add together
    
    int	bufferSize; // buffer size
    int	sampleRate; // sample rate

		
};
