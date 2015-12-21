#ifndef KALIBRIERUNG_H
#define KALIBRIERUNG_H

class Kalibrierung{
public:
	Kalibrierung();																					//Konstruktor von Kalibrierung
	Vector<Point> runCalibrate(int NoCamArrayLength,Vector<Point> noCamArray, int videoOrCam);		//Startet die Kalibrierung
private:
	Vector<Point> sortNoCamArray(Vector<Point> noCamArray);											//Sortiert das Array, in welches die nicht �berwachten Felder gespeichert sind
	int alarmgroesse;																				//Int Variable f�r die Gr��e eines Objektes(in Pixeln), ab welche der Alarm ausgel�st wird
};
#endif