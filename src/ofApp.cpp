#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // Background Image
    photo.load("photo.jpg");
    
    for (int i = 0; i < 16; i++) {
        string name = "movie/m";
        name.append(ofToString(i));
        name.append(".mp4");
        cellMovies[i].load(name);
        cellMovies[i].setLoopState(OF_LOOP_NORMAL);
    }
    
    for (int i = 0; i < 300; i++) {
        string name = "photo/m";
        name.append(ofToString(i));
        name.append(".jpg");
        cellPhotos[i].load(name);
        
        ofPixels & pixels = cellPhotos[i].getPixels();
        int vidWidth = pixels.getWidth();
        int vidHeight = pixels.getHeight();
        int nChannels = pixels.getNumChannels();
        
        int sumR = 0;
        int sumG = 0;
        int sumB = 0;
        
        int numOfPoint = 0;
        
        for (int k = (vidWidth / 5); k < vidWidth; k+=(vidWidth / 5)){
            for (int j = (vidWidth / 5); j < vidHeight; j+=(vidHeight / 5)){
                unsigned char r = pixels[(j * vidWidth + k) * nChannels];
                unsigned char g = pixels[(j * vidWidth + k) * nChannels + 1];
                unsigned char b = pixels[(j * vidWidth + k) * nChannels + 2];
                sumR += r;
                sumG += g;
                sumB += b;
                numOfPoint++;
            }
        }
        
        cellPhotoColors[i].r = sumR/numOfPoint;
        cellPhotoColors[i].g = sumG/numOfPoint;
        cellPhotoColors[i].b = sumB/numOfPoint;
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofLog(OF_LOG_NOTICE) << "rowValue: " << rowValue;
    ofLog(OF_LOG_NOTICE) << "degree: " << degree;
    
    rowValue *= (cos(degree*pi/180)+1)/2;
    
    animateRowValue = rowValue + 1;
    degree+=0.02;
    
    ofBackground(255);
    for (int i = 0; i < 16; i++) {
        cellMovies[i].nextFrame();
        
        if (!cellMovies[i].isFrameNew()) {
            cellMovies[i].setFrame(0);
        }
        cellMovies[i].update();
        ofPixels & pixels = cellMovies[i].getPixels();
        int vidWidth = pixels.getWidth();
        int vidHeight = pixels.getHeight();
        int nChannels = pixels.getNumChannels();
        
        int sumR = 0;
        int sumG = 0;
        int sumB = 0;
        
        int numOfPoint = 0;
        
        for (int k = (vidWidth / 5); k < vidWidth; k+=(vidWidth / 5)){
            for (int j = (vidWidth / 5); j < vidHeight; j+=(vidHeight / 5)){
                unsigned char r = pixels[(j * vidWidth + k) * nChannels];
                unsigned char g = pixels[(j * vidWidth + k) * nChannels + 1];
                unsigned char b = pixels[(j * vidWidth + k) * nChannels + 2];
                sumR += r;
                sumG += g;
                sumB += b;
                numOfPoint++;
            }
        }
        
        cellMovieColors[i].r = sumR/numOfPoint;
        cellMovieColors[i].g = sumG/numOfPoint;
        cellMovieColors[i].b = sumB/numOfPoint;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255);
    
    int w = photo.getWidth();
    int h = photo.getHeight();
    int cellWidth = w/numOfRow;
    int cellHeight = h/numOfRow;
    
    ofPixels & pixels = photo.getPixels();
    
    for(int y = 0; y < h; y+=cellHeight) {
        for(int x = 0; x < w; x+=cellWidth) {
            int index = (y * w + x) * 3;
            unsigned char r = pixels[index];
            unsigned char g = pixels[index+1];
            unsigned char b = pixels[index+2];
            ofSetColor(r, g, b);
            ofDrawRectangle(x * animateRowValue-animateRowValue*w/2+w/2 + cellWidth*animateRowValue/2, y * animateRowValue - animateRowValue*h/2+h/2 + cellHeight*animateRowValue/2, cellWidth * animateRowValue, cellHeight * animateRowValue);
            
            int bgBrightness = r + g + b;
            
            unsigned int diff = 0;
            unsigned int oldDiff = 256;
            int minDiffCellNum = 0;
            
            for (int i = 0; i < 16; i++) {
                int cellBrigtness = cellMovieColors[i].r + cellMovieColors[i].g + cellMovieColors[i].b;
                diff = abs(bgBrightness - cellBrigtness);
                if (diff < oldDiff) {
                    minDiffCellNum = i;
                    oldDiff = diff;
                }
            }
            
            // threshold if you use photo
            if (diff < 1000) {
                
                ofSetColor(255);
                cellMovies[minDiffCellNum].draw(x * animateRowValue-animateRowValue*w/2+w/2 + cellWidth*animateRowValue/2, y * animateRowValue-animateRowValue*h/2+h/2 + cellHeight*animateRowValue/2, cellWidth * animateRowValue, cellHeight * animateRowValue);
            } else {
                
                for (int j = 0; j < 300; j++) {
                    int cellPhotoBrigtness = cellPhotoColors[j].r + cellPhotoColors[j].g + cellPhotoColors[j].b;
                    diff = abs(bgBrightness - cellPhotoBrigtness);
                    if (diff < oldDiff) {
                        minDiffCellNum = j;
                        oldDiff = diff;
                    }
                }
                
                ofSetColor(255);
                cellPhotos[minDiffCellNum].draw(x * animateRowValue-animateRowValue*w/2+w/2 + cellWidth*animateRowValue/2, y * animateRowValue - animateRowValue * h / 2 + h / 2 + cellHeight*animateRowValue/2, cellWidth * animateRowValue, cellHeight * animateRowValue);
             }
            
        }
    }
    
    // Export image
    screenshot.grabScreen(0, 0 , ofGetWidth(), ofGetHeight());
    string name = "screenshot/screenshot";
    name.append(ofToString(ofGetFrameNum()));
    name.append(".png");
    screenshot.save(name);
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
