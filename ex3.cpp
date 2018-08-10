//g++ ex3.cpp -o ex3 `pkg-config --cflags --libs opencv`

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>

using namespace std;
using namespace cv;
 

int main(){
 
	VideoCapture cap(0); 

	Mat img;

	int height, width;

	if(!cap.isOpened()){
		cout << "Erro ao abrir o video" << endl;
		return -1;
	}

	cap.read(img);
	
	imshow("Primeiro Frame", img);

	width = img.cols;
	height = img.rows;
	
	for(int i = 0; i<width; i++){
		for(int j = 0; j<height; j++){
			
			// RGB
			// se r+100 > 255 entao r = 255 senao r = r+100
			img.at<Vec3b>(i,j)[0] = ((img.at<Vec3b>(i,j)[0]+100) > 255) ? 255 : img.at<Vec3b>(i,j)[0]+100;
			img.at<Vec3b>(i,j)[1] = ((img.at<Vec3b>(i,j)[1]+100) > 255) ? 255 : img.at<Vec3b>(i,j)[1]+100;
			img.at<Vec3b>(i,j)[2] = ((img.at<Vec3b>(i,j)[2]+100) > 255) ? 255 : img.at<Vec3b>(i,j)[2]+100;

			//cout << "RGB= " <<"["<<(int)img.at<Vec3b>(i,j)[0]<<","<<(int)img.at<Vec3b>(i,j)[1]<<","<<(int)img.at<Vec3b>(i,j)[0]<<"]"<<endl;
		}	
	}

	imwrite("ex3.jpg",img);

	imshow("Primeiro Frame'", img);

	waitKey(0);

	/*while(1){

		Mat frame;
		// Capture frame-by-frame
		cap >> frame;
	
		// If the frame is empty, break immediately
		if (frame.empty()) break;
		
		//escala de cinza
		cvtColor(frame, frame, CV_BGR2GRAY);

		// Display the resulting frame
		imshow("Frame", frame);

		// Press  ESC on keyboard to exit
		char c=(char)waitKey(25);
		if(c==27) break;
	}

	// When everything done, release the video capture object
	cap.release();

	// Closes all the frames
	destroyAllWindows(); */

	return 0;
}
