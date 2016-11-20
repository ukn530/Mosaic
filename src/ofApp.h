#pragma once

#include "ofMain.h"
#include "ofxGui.h"

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
		
        ofImage screenshot;
    
        // background image
        ofImage photo;
        int numOfRow = 120;
        float animateRowValue = 0;
        float rowValue = 119;
    
        // Number of Movies
        // You have to change this number in .m file, too.
        ofVideoPlayer cellMovies[16];
        ofColor cellMovieColors[16];
    
    
        //Number of Photos
        // You have to change this number in .m file, too.
        ofImage cellPhotos[300];
        ofColor cellPhotoColors[300];
    
        float degree = 0;
};
