#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //from 72 dpi to 90 mm printed object
    ofSetWindowShape(255, 255);
    w = ofGetWidth();
    h = ofGetHeight();
    //file naming var for svg saving
    addNum = 0;
    //to make the outer circle really percise for cutting lol
    ofSetCircleResolution(200);
}

//--------------------------------------------------------------
void ofApp::update(){
    t= ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    ofPushMatrix();
    ofTranslate(w/2, h/2);
    ofSetColor(255);
    ofNoFill();
    /*
    //basic time based controllers for form finding
     
    //radius options for outside flower and inside flower
    a1 =   ofMap(sin(t), -1, 1, 50, 100);
    a2 =   ofMap(sin(t), -1, 1, 2, 10);
    b1 =   ofMap(sin(t), -1, 1, 20, 50);
    b2 =   ofMap(sin(t), -1, 1, 5, 30);
     
    //param 4 for sideFlower (determines if and how the amplitude changes through the line
    float jAdd = ofMap(sin(t), -1, 1, 0.1, 0.3);
     
    //set these to midi or osc for live

     */
    
    ofSetColor(0, 255, 0);
    //drawSideFlower(radiusFlower, radiusPetals, sampleFrequency, amplitudeChange, lineLength)
    drawSideFlowers(70, 5, 0.1, 0.1, 5);
   // jAdd = ofMap(sin(t),1,-1,0.1,0.5);
    drawSideFlowers(40, 15, 0.1, 0.3, 2);
    
    //center and edge
    ofSetColor(255, 0, 0);
    ofDrawCircle(0, 0, 255/2);
    ofPopMatrix();
    ofDrawCircle(w/2, 15, 3);

    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key =='g'){
        ofBeginSaveScreenAsSVG("snowflake" + to_string(addNum) + to_string((int)t) + ".svg");
        addNum++;
        
        //was printing out the settings of the images I liked to pursue those interations
        //e.g. could then hold the a constant while changing b to find new shapes
        /*
         cout<< "a1 " << a1 << endl;
         //etc
         */
    }
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    int addNum = 0;
    if (key =='g'){
        ofEndSaveScreenAsSVG();
        
    }
}

//--------------------------------------------------------------
//side stem flowers
/*
    r1, r2 : outer circle radius and radius of circles drawn on the outer circle, respectively
    freq   : how often we sample from outer circle (i.e. how many subcircles
    jAdd   : how does the amplitude grow over time (note: can hard set j const and jAdd zero)
    l      : sets length of the lines
 
*/
void ofApp::drawSideFlowers(float r1, float r2, float freq, float jAdd, float l){
    
    //setup the outer circle, ie the main ring
    ofPoint center(0, 0);
    ofPolyline outerCircle;
    outerCircle.arc(center, r1, r1, 0, 360, false, 100);
    //outerCircle.draw();
    
    //cycle around the outer circle and setup the "petals"
    //note deg is actually a percentage but named this way is clearer to me
    
    for (float deg = 0; deg <= 1; deg += freq){
        //ofDrawCircle(outerCircle.getPointAtPercent(deg), 20);
        ofPolyline subCircle;
        subCircle.arc(outerCircle.getPointAtPercent(deg), r2, r2, 0, 360, false, 100);
        //subCircle.draw();
        
        //cycle around each petal, called subcircle
        //draw a sin function along x=0 of from the point on the circle along the normal vector
        for (float subDeg = 0; subDeg < 1; subDeg += freq){
            
            //only use 0 and then rotate the matrix around each circle to get all sample points
            ofVec3f normalPt = subCircle.getNormalAtIndexInterpolated(subCircle.getIndexAtPercent(0)) * 100;
            ofVec3f subCirclePt = subCircle.getPointAtPercent(0);
            ofVec3f endPt = (subCirclePt - normalPt/l);
            
            ofPushMatrix();
            
            //roate by percentage of the circle (ofRotate takes value in degrees)
            ofRotate(subDeg * 360);
            
            //take a pt along the x between the circle and the end and give it a value along the sin fxn
            //making two mirrored lines to get the double helix look
            float j = 0;
            for (int i = subCirclePt.x; i < endPt.x; i++){
                float y = j * sin(i * 0.3) - endPt.y;
                line1.addVertex(i, y);
                line2.addVertex(i, -y);
                j += jAdd;
                
            }
            
            line1.draw();
            line2.draw();
            
            ofPopMatrix();
            
            line1.clear();
            line2.clear();
        }
    }
    
}

//--------------------------------------------------------------

//uuu write tranform fxns to learn
//


// float y = sin(i) - endPt.y;
 //float x = i * cos(angle) - sin(angle) * sin(i); //f(t) = x
 //float y=sin(i) + cos(i)*sin(i) - endPt.y;
// float y = sin(i) - endPt.y;
 //float x = i * cos(angle) - sin(angle) * sin(i); //f(t) = x
