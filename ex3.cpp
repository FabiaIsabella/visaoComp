//g++ ex3.cpp -o ex3 `pkg-config --cflags --libs opencv`

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>

using namespace std;
using namespace cv;
 

int main(){
 
	VideoCapture cap(0); 

	if(!cap.isOpened()){
		cout << "Erro ao abrir o video" << endl;
		return -1;
	}

	while(1){

		Mat frame, frame2;
		cap >> frame;
	
		if (!frame.data) break;
		
		//escala de cinza
		cvtColor(frame, frame, CV_BGR2GRAY);

		frame2 = frame +100;
		
		imshow("Frame", frame);
		imshow("Frame 2", frame2);

		char c=(char)waitKey(25);
		if(c==27) break;
	}


	return 0;
}
