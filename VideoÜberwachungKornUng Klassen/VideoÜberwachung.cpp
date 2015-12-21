#include "VideoÜberwachung.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include <sstream>
using namespace cv;
using namespace std;

//Class Videoüberwachung
//Variablen Deklaration
const string path = "C:\\Users\\Viki\\Dropbox\\KevVic\\AVPRG\\Projekt\\Micro-dance_2.wmv";			//Pfad für das Testvideo 1
const string path2 = "C:\\Users\\Viki\\Dropbox\\KevVic\\AVPRG\\Projekt\\PCRaum.wmv";					//Pfad für das Testvideo 2
const string path3 = "C:\\Users\\Viki\\Dropbox\\KevVic\\AVPRG\\Projekt\\Zimmer.wmv";					//Pfad für das Testvideo 2
int alarmGroesse;					//Int Variable für die Größe eines Objektes(in Pixeln), ab welche der Alarm ausgelöst wird

//Methode zur Initialisierung
void VideoÜberwachung::initialize(int videoOrCam){
	if(videoOrCam == 1){										//je nachdem, ob zu Beginn des Programmes der Videoablauf oder Kamerablauf gewählt wurde wird der input gewählt
		videoCapture.open(path);								//Es wird Videofile 1 abgespielt
	}
	else if(videoOrCam == 2){
		videoCapture.open(path2);								//Es wird Videofile 2 abgespielt
	}
	else if(videoOrCam == 3){
		videoCapture.open(path3);								//Es wird Videofile 3 abgespielt
	}
	else if(videoOrCam == 4){
		videoCapture.open(0);									//Es wird von der Webcam aufgenommen
	}
	widthVideo = videoCapture.get(CV_CAP_PROP_FRAME_WIDTH);		//Breite des geladenen Videos in die Int Variable: widthVideo speichern
	heightVideo = videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT);	//Höhe des geladenen Videos in die Int Variable: heightVideo speichern

	orVideoF = Mat(heightVideo, widthVideo, CV_8UC3);			//Mat Objekt für orVideoF in RGB erstellen
	greyVideoF = Mat(heightVideo, widthVideo, CV_8UC1);			//Mat Objekt für greyVideoF in Binär erstellen

	firstVideoFGrey = Mat(heightVideo, widthVideo, CV_8UC1);	//Mat Objekt für firstVideoFGrey in Binär erstellen

	binaryMaskF = Mat(heightVideo, widthVideo, CV_8UC1);		//Mat Objekt für binaryMaskF in Binär erstellen

	binaryMaskCopy = Mat(heightVideo, widthVideo, CV_8UC1);		//Mat Objekt für binaryMaskCopy in Binär erstellen

	maskMedianBlur = Mat(heightVideo, widthVideo, CV_8UC1);		//Mat Objekt für maskMedianBlur in Binär erstellen
	maskOpened = Mat(heightVideo, widthVideo, CV_8UC1);			//Mat Objekt für maskOpened in Binär erstellen
	maskClosed = Mat(heightVideo, widthVideo, CV_8UC1);			//Mat Objekt für maskClosed in Binär erstellen
	copyOfMask = Mat(heightVideo, widthVideo, CV_8UC1);			//Mat Objekt für copyOfMask in Binär erstellen
	contoursAndBoundingRect = Mat(heightVideo, widthVideo, CV_8UC3);

	frameCounter = 0;											//

}

//Methode setzt die Alarmgrösse
void VideoÜberwachung::setAlarmGroesse(int aGroesse){
	alarmGroesse = aGroesse;
}

//Methode gibt die Alarmgrösse zurück
int VideoÜberwachung::getAlarmGroesse(){
	return alarmGroesse;
}

//Methode zum Starten der Videos
 void VideoÜberwachung::startVideo(){
		cvtColor(orVideoF, greyVideoF, CV_BGR2GRAY);							//Originalvideo wird in grau konvertiert und in greyVideoF gespeichert
		
		//Erstes Graustufen Frame in eigenes Mat Objekt kopieren
		frameCounter++;															//VideoFrame wird hochgezählt
		if(frameCounter == 1){														
			greyVideoF.copyTo(firstVideoFGrey);									//Der erste graue Videoframe wird gespeichert		
		}

		//Berechnet pixelweise den Unterschied zwischen den Bildern des aktuellen grauen Videoframes 
		//und den 1. grauen Videoframe: greySubF = abs(greyVideoF - firstVideoFGrey)
		absdiff(greyVideoF, firstVideoFGrey, greySubF);

		//Schwarz-Weiß Maske vom ganzen Video erzeugen mit threshold
		double thresh = 22;
		int maxValue = 255; 
		threshold(greySubF,binaryMaskF,thresh,maxValue,THRESH_BINARY);
		
		//Zunächst Vordergrund von binaryMaskF vergrößern mit Closing 
		//Closing
		dilate(binaryMaskF, maskClosed,MORPH_RECT); 
		erode(maskClosed, maskClosed,MORPH_RECT);

		//Median Blur von closedMask
		medianBlur(maskClosed, maskMedianBlur, 5); //ksize (last) must be odd and greater than 3

		//Opening von maskMedianBlur
		erode(maskMedianBlur, maskOpened,MORPH_RECT);
		dilate(maskOpened, maskOpened,MORPH_RECT); 

		//Aufruf von findContours zerstört das Originalbild, d.h. vorher Kopie erstellen:
		maskOpened.copyTo(copyOfMask);
		
		//Originalvideo in contoursAndBoundingRect kopieren
		orVideoF.copyTo(contoursAndBoundingRect);
}
