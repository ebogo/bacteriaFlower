#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		
        void keyReleased(int key);
		/*
         void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
             */
        float t, w, h;
        int addNum;
        
        //side stem flowers
        void drawSideFlowers(float r1, float r2, float freq, float jAdd, float l);
        float a1, a2;
        float b1, b2;
        float jAdd;
        ofPolyline line1, line2;
    
		
};
