#pragma once


#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "ofxVectorGraphics.h"

class ofApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
    ofxAudioUnit           varispeed;
    ofxAudioUnit           reverb;//NC
    ofxAudioUnit           delay;//NC
	ofxAudioUnit           lowpass;
	ofxAudioUnitFilePlayer filePlayer1;
    
    
	ofxAudioUnitOutput     output;
	ofxAudioUnitTap        tap;
	
	ofPolyline waveform;
    ofxVectorGraphics output2;
    vector <ofPoint> pts;
    ofPoint mousePoint;
    
    
    bool mouseHasClicked;
    
};
