#include "Video‹berwachung.h"
#include "Kalibrierung.h"
#include "‹berwachung.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include <sstream>
using namespace cv;
using namespace std;

int main(){
//Videofile, das abgespielt werden soll in Video‹berwachung.cpp angeben
	Video‹berwachung video‹berwachung;
	int videoOrCam = 0; 
	while(videoOrCam != 1 && videoOrCam != 2 && videoOrCam != 3 && videoOrCam != 4){
		cout<<"Video 1 abspielen (1) Video 2 abspielen (2) Video 3 abspielen (3)" << endl;
		cout << "oder Kamera Input(4)? ";
		cin >> videoOrCam;	
	}
	int NoCamArrayLength = -1;
	while(NoCamArrayLength < 0 || NoCamArrayLength > 5){
		cout<<"Anzahl der nicht Videoueberwachten Felder( 0 bis max. 5): ";
		cin >> NoCamArrayLength;
	}
	NoCamArrayLength = NoCamArrayLength * 2;
	Vector<Point> noCamArray(NoCamArrayLength);
	‹berwachung ¸berwachung;
	Kalibrierung kalibrierung;
	noCamArray = kalibrierung.runCalibrate(NoCamArrayLength, noCamArray, videoOrCam);
	¸berwachung.run‹berwachung(noCamArray, videoOrCam);
	return 0;
}//main