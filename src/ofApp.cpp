#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
  gui = new ofxUISuperCanvas("OFXUI TUTORIAL");
  gui->addSlider("BACKGROUND",0,1,0.5);
  gui->addToggle("T1", false, 44, 44);
  gui->addButton("B1", false, 44, 44);
  
  int ticksPerBuffer = 8; // 8 * 64 = buffer len of 512
  int numInputs = 1;
  ofSoundStreamSetup(2, numInputs, this, 44100, ofxPd::blockSize()*ticksPerBuffer, 3);
  
  if(!pd.init(2, numInputs, 44100, ticksPerBuffer, false)){
        OF_EXIT_APP(1);
  }
  
  pd.start();
  
  Patch patch = pd.openPatch("pd/1Secuencer.pd");
  
  ofAddListener(gui->newGUIEvent, this, &ofApp::guiEvent);
    pd.sendFloat("slider", value);
    pd.sendFloat("metro", cont);
}

//--------------------------------------------------------------
void ofApp::exit()
{
  gui->saveSettings("settings.xml");
  delete gui;
}

//--------------------------------------------------------------
void ofApp::guiEvent(ofxUIEventArgs &e)
{
  string name = e.widget->getName();
  int kind = e.widget->getKind();
    
   if(kind == OFX_UI_WIDGET_TOGGLE){
    
    ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
    val = toggle ->getValue();
    
     if (val==1){
     pd.sendBang("bang");
     }
     if(val==0){
     pd.sendBang("bang2");
     }
    }

  if(name == "BACKGROUND")
  {
    ofxUISlider *slider = e.getSlider();
    value = slider->getScaledValue();
    pd.sendFloat("slider", value);
  }
    
  if (kind == OFX_UI_WIDGET_BUTTON){
    ofxUIButton *button = (ofxUIButton *) e.widget;
    value2 = button->getValue();
    if (value2 == 1){
        cont=cont+1;
        pd.sendFloat("metro", cont);
        cout<<cont<<endl;
    }
  }
}

//--------------------------------------------------------------
void ofApp::playTone(int pitch) {
  pd << StartMessage() << "pitch" << pitch << FinishList("tone") << Bang("tone");
}

//--------------------------------------------------------------
void ofApp::audioReceived(float * input, int bufferSize, int nChannels) {
  pd.audioIn(input, bufferSize, nChannels);
}

//--------------------------------------------------------------
void ofApp::audioRequested(float * output, int bufferSize, int nChannels) {
  pd.audioOut(output, bufferSize, nChannels);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
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
