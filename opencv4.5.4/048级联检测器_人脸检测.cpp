#include "primary.h"
using namespace cv;
const char* cascadeAddr = "D:/opencv4.3.0/opencv/build/etc/haarcascades/";
#include <vector>
void image_cascade_detector_face_detection()
{
	CascadeClassifier face_detector;
	face_detector.load(std::string(cascadeAddr)+"haarcascade_frontalface_default.xml");
	Mat src = imread(imgAddr + "me.jpg"),gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	//imshow("gray", gray);
	equalizeHist(gray,gray);
	//imshow("equalizegray", gray);
	Mat dst;
	std::vector<Rect>faces;
	Size minSize(0, 0), maxSize(0, 0);
	double scaleFactor = 1.1;
	int minNeighbors = 3;
	int flags = 0; 
	face_detector.detectMultiScale(gray, faces,scaleFactor,minNeighbors,flags,minSize,maxSize);
	for (size_t i= 0; i < faces.size(); i++)
	{
		rectangle(src,faces[i],Scalar(0,0,255));
	}
	imshow("src",src);
	waitKey(0);
	destroyAllWindows();
}