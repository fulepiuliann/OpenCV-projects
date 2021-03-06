#include "stdafx.h"

#include "opencv2/opencv.hpp"		
#include "opencv2/objdetect.hpp"		
#include "opencv2/highgui.hpp"		
#include "opencv2/imgproc.hpp"		

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;


/** @function main */
int main()
{
	CascadeClassifier face_classifier, eyes_classifier;
	if
		(!face_classifier.load("C:/Users/robi/Desktop/opencv/sources/data/haarcascades/haarcascade_frontalface_alt2.xml")) {
		cout << "Nu s-a deschis!" << endl;
		getchar();
		return 0;
	}
	if
		(!eyes_classifier.load("C:/Users/robi/Desktop/opencv/sources/data/haarcascades/haarcascade_eye.xml")) {
		cout << "Nu s-a deschis!" << endl;
		getchar();
		return 0;
	}
	VideoCapture cap;
	if (!cap.open(0))
	{
		cout << "Nu s-a deschis camera!" << endl;
		getchar();
		return 0;
	}
	Mat img;
	Mat	gray_img;
	vector<Rect> face, eyes;
	while (1)
	{
		cap >> img;
		cvtColor(img, gray_img, CV_BGR2GRAY);
		equalizeHist(gray_img, gray_img);
		face_classifier.detectMultiScale(gray_img, face, 1.1, 3, CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING, cvSize(300, 300));
		for (int i = 0; i < face.size(); i++)
		{
			Point pt1(face[i].x + face[i].width, face[i].y + face[i].height);
			Point pt2(face[i].x, face[i].y);

			Mat faceROI = gray_img(face[i]);
			eyes_classifier.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
			for (size_t j = 0; j< eyes.size(); j++)
			{
				Point center(face[i].x + eyes[j].x + eyes[j].width*0.5, face[i].y + eyes[j].y + eyes[j].height*0.5);
				int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
				circle(img, center, radius, Scalar(255, 0, 0), 2, 8, 0);
			}
			rectangle(img, pt1, pt2, cvScalar(255, 255, 0), 2, 8, 0);
		}

		// print the output
		imshow("Proiect Roboti Inteligenti", img);

		int tasta = waitKey(1);
		if (tasta == 27)
			break;
	}
	return 0;
}
