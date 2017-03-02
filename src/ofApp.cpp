#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
//	This example demonstrates what Audio Unit parameters
//	are and how to change them
	
//	Parameters are user-controllable variables on an Audio
//	Unit which you can change in real time. For example, a
//	Mixer audio unit typically has parameters for volume,
//	panning, etc. These are the parameters that you are
//	changing with ofxAudioUnitMixer's setPan() and
//	setInputVolume() functions.
	
//	However, there are a huge number of parameters that Audio
//	Units make available, and ofxAudioUnit can't make convienient
//	functions for all of them. This example shows you how to
//	programmatically set Audio Unit parameters on the fly.
	
//	These are the audio units we'll use:
	
//	AUVarispeed - let's you change the playback speed of audio
//	going through it, while simultaneously changing the pitch
//	(like slowing down and speeding up a record)
	
    varispeed.setup(kAudioUnitType_FormatConverter, kAudioUnitSubType_Varispeed);
    
	
//	AULowPass - a lowpass filter which cuts off high frequencies
//	at a user-controllable cutoff point
	
	lowpass.setup(kAudioUnitType_Effect, kAudioUnitSubType_LowPassFilter);
	
    
    reverb.setup(kAudioUnitType_Effect, kAudioUnitSubType_MatrixReverb);//NC
    delay.setup(kAudioUnitType_Effect, kAudioUnitSubType_Delay);//NC

    
//	We'll also use an ofxAudioUnitFilePlayer to generate audio,
//	an ofxAudioUnitTap to extract the waveform, and an output
//	to send the resulting audio to your speakers
	
	//filePlayer.connectTo(varispeed).connectTo(lowpass).connectTo(tap).connectTo(output);
    
    filePlayer1.connectTo(varispeed).connectTo(lowpass).connectTo(delay).connectTo(reverb).connectTo(tap).connectTo(output);
	
//	First, we'll set the lowpass's resonance setting. All of the
//	Apple-manufactured Audio Units have parameter constants defined
//	which follow a particular naming pattern. The two lowpass
//	parameters are kLowPassParam_Resonance and
//	kLowPassParam_CutoffFrequency.
	
//	The easiest way to find the parameters for your Audio Unit
//	are to type kNameOfYourUnit and let Xcode's auto-complete
//	show you what's available. You can also see all of the parameters
//	defined in <AudioUnit/AudioUnitParameters.h>. It is a good idea
//	to read this header file anyway, as it'll tell you what values 
//	these parameters are expecting. One way to get information
//	on the parameter you want to change is to type it, then Cmd-click
//	on it to take you to its entry in AudioUnitParameters.h
	
//	You set parameters by using the function AudioUnitSetParameter().
//	This function expects a few arguments :

//	inUnit - An AudioUnit struct. You can get this from an ofxAudioUnit
//	by calling getUnit() on it
//	inID - The parameter you want to change
//	inScope - The scope the parameter applies to. This is usually
//	the Global scope. Try the Input or Ouput scope if Global doesn't
//	work.
//	inElement - The bus you're changing the parameter on. For Global
//	params, it's always 0
//	inValue - The value you're setting the parameter to.
//	inBufferOffsetFrames - If you want to set the parameter in the
//	future, give this an offset in terms of samples (eg. 44100 for
//	1 second). Usually you want this to be 0.
	
//	Here, we're setting the lowpass's resonance to 10
	
	AudioUnitSetParameter(lowpass, kLowPassParam_Resonance, kAudioUnitScope_Global, 0, 10, 0);
    
    
    
    AudioUnitSetParameter(reverb, kReverbParam_LargeDelay, kAudioUnitScope_Global,0,0.1,0 );
    
    AudioUnitSetParameter(delay, kDelayParam_Feedback, kAudioUnitScope_Global,0,80,0 );


	
//	If you're using a 3rd party unit (i.e. one that's not made by Apple)
//	you'll need to retrieve and set parameters by finding their parameter
//	ID (which is effectively just an index). This call will print a
//	unit's parameter list to the console.
	
    //lowpass.printParameterList();
    delay.printParameterList();
	
//	You can also save the state of an Audio Unit's parameters as a
//	preset file. Saving / Loading a preset file is done like this:

//	varispeed.saveCustomPreset("MyPreset");
//	varispeed.loadCustomPreset("MyPreset");
	
//	These functions will look for or create a preset file with the extension
//	".aupreset" in your app's data folder.
	
//	You can also create .aupreset files in Garageband and other DAWs.
//	Usually, these are stored in ~/Library/Audio/Presets/
	
	output.start();
	
    filePlayer1.setFile(ofFilePath::getAbsolutePath("gong2.wav"));
	
	
	ofSetVerticalSync(true);
    
    ofSetBackgroundColor(255);
    ofSetCircleResolution(100);
    ofSetBackgroundAuto(false);
    
    int numX = ofGetWidth() / 10;
    int numY = ofGetHeight() / 10;
    
    mouseHasClicked=false;

}

//--------------------------------------------------------------
void ofApp::update(){
	tap.getLeftWaveform(waveform, ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::draw(){

    // GRID BACKGROUND
    
    
    int numX = ofGetWidth() / 10;
    int numY = ofGetHeight() / 10;
    
    output2.setColor(0xEEEEEE);
    
    for(int y = 0; y < numY; y++){
        output2.line(0, y * 10, ofGetWidth(), y * 10);
    }
    
    for(int x = 0; x < numX; x++){
        output2.line(x * 10, 0, x * 10, ofGetHeight() );
    }
    
    
    //--------------------
    
    
    
	/*ofBackground(40);
	ofSetColor(255);
	waveform.draw();
	ofDrawBitmapString("Press 'f' to show the file player", ofPoint(40,20));
	
	ofSetColor(255, 125, 50);
	ofDrawCircle(20, ofGetMouseY(), 15, 0);
	ofDrawBitmapString("|\nFilter\nFrequency\n|", ofPoint(40, ofGetHeight()/2));
	
	ofSetColor(20, 255, 150);
	ofDrawCircle(ofGetMouseX(), ofGetHeight() - 20, 15, 0);
	ofDrawBitmapString("<- Playback Speed ->", ofPoint(ofGetWidth()/2 - 100, ofGetHeight() - 40)); */
    
    
    //we don't save this to eps - just info for the app
    
    ofFill();
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetHexColor(0x000000);
    ofDrawRectangle( 60, 30, 170, 140);
    
    //some text to explain whats what
    ofSetHexColor(0xDDDDDD);
    ofDrawBitmapString("THE SCRIBBLETONE", 75, 60);
    ofDrawBitmapString("mouse to doodle,\nswitch numbers to \nexplore sounds, \n'c' key to clear.", 75, 90);
    ofDrawBitmapString("_ by SOUJANYAA ", 75, 150);
    
    
    ////mousedrawy
    
    if( pts.size() > 0 ){
        
        int numPts = pts.size();
        
        output2.setColor(0x0088EE);
        output2.noFill();
        output2.beginShape();
        
        //catmull curves create nice smooth curves between points
        //so actually a lower resolution creates a smoother line
        //and reduce the number of poiints in our eps file.
        int rescaleRes = 8;
        
        for(int i = 0; i < numPts; i++){
            
            //we need to draw the first and last point
            //twice for a catmull curve
            if(i == 0 || i == numPts -1){
                output2.curveVertex(pts[i].x, pts[i].y);
            }
            
            if(i % rescaleRes == 0) output2.curveVertex(pts[i].x, pts[i].y);
        }
        
        output2.endShape();
    }
    
    //_______
    ofSetColor(255,0,0);
    ofNoFill();
    if(mouseHasClicked){
        ofDrawCircle(mousePoint, 10);
    }
    //-------
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == 'f') filePlayer1.showUI();
    if(key == 'c'){
        pts.clear();
        output.stop();
        ofBackground(255);
        mouseHasClicked=false;
    
        
    }
    if(key == '0'){
        filePlayer1.setFile(ofFilePath::getAbsolutePath("gong2.wav"));
    }
    
    if(key == '1'){
        filePlayer1.setFile(ofFilePath::getAbsolutePath("brahms.wav"));
    }
    if(key == '2'){
        filePlayer1.setFile(ofFilePath::getAbsolutePath("baccha.mp3"));
    }
    if(key == '3'){
        filePlayer1.setFile(ofFilePath::getAbsolutePath("crickets.wav"));
    }
    if(key == '4'){
        filePlayer1.setFile(ofFilePath::getAbsolutePath("sea.wav"));
    }
    if(key == '5'){
        filePlayer1.setFile(ofFilePath::getAbsolutePath("forests.wav"));
    }
    if(key == '6'){
        filePlayer1.setFile(ofFilePath::getAbsolutePath("hbd.wav"));
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    
    //GRID
    
    //we add a new point to our line
    pts.push_back(ofPoint());
    int last = pts.size()-1;
    
    pts[last].x = x;
    pts[last].y = y;
    

    mousePoint.x = mouseX;
    mousePoint.y = mouseY;
    
    //	The varispeed has an adjustable playback rate. Setting
    //	it to 1 means a normal playback speed. Anything higher
    //	or lower speeds it up or slows it down accordingly.
    
    float newSpeed = ofMap(x, 0, ofGetWidth(), 0.01, 2, true);
    
    AudioUnitSetParameter(varispeed,
                          kVarispeedParam_PlaybackRate,
                          kAudioUnitScope_Global,
                          0,
                          newSpeed,
                          0);
    
    //float newCutoff = ofMap(y, 0, ofGetHeight(), 10, 6900);
    //float myReverbValue = ofMap(y,0, ofGetHeight(), 0.001, 0.1);
    
    float delayFeedback = ofMap(y,0, ofGetHeight(), 0, 80);
    
    /*AudioUnitSetParameter(lowpass,
     kLowPassParam_CutoffFrequency,
     kAudioUnitScope_Global,
     0,
     newCutoff,
     0);*/
    
    
    //AudioUnitSetParameter(reverb, kReverbParam_LargeDelay, kAudioUnitScope_Global,0,myReverbValue,0 );
    
    AudioUnitSetParameter(delay,kDelayParam_Feedback, kAudioUnitScope_Global,0,delayFeedback,0 );
    
    
//    //GRID
//    
//    //we add a new point to our line
//    pts.push_back(ofPoint());
//    int last = pts.size()-1;
//    
//    pts[last].x = x;
//    pts[last].y = y;
    

    
    
}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    filePlayer1.play();
    output.start();
    
    pts.clear();
    mouseHasClicked=true;
}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){}
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){}
//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){}
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){}
