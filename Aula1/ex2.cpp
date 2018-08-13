//g++ ex2.cpp -o ex2 `pkg-config --cflags --libs opencv`

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>

using namespace std;
using namespace cv;
 
int main() {
  
	Mat img;
	int height, width;

	img = imread("london.jpg" , CV_LOAD_IMAGE_COLOR);  

	if(!img.data) {
		cout <<  "Não foi possivel abrir a imagem" << endl ;
		return -1;
	}
	
	imshow("Imagem 1", img);
  
	width = img.cols;
	height = img.rows;
	
	for(int i = 0; i<width; i++){
		for(int j = 0; j<height; j++){
			
			// RGB
			// se r+100 > 255 entao r = 255 senao r = r+100
			img.at<Vec3b>(i,j)[0] = ((img.at<Vec3b>(i,j)[0]+100) > 255) ? 255 : img.at<Vec3b>(i,j)[0]+100;
			img.at<Vec3b>(i,j)[1] = ((img.at<Vec3b>(i,j)[1]+100) > 255) ? 255 : img.at<Vec3b>(i,j)[1]+100;
			img.at<Vec3b>(i,j)[2] = ((img.at<Vec3b>(i,j)[2]+100) > 255) ? 255 : img.at<Vec3b>(i,j)[2]+100;

			cout << "RGB= " <<"["<<(int)img.at<Vec3b>(i,j)[0]<<","<<(int)img.at<Vec3b>(i,j)[1]<<","<<(int)img.at<Vec3b>(i,j)[0]<<"]"<<endl;
		}	
	}

	imwrite("ex2.jpg",img);

	imshow("Imagem 2", img);
	  
	waitKey(0);
	return 0;
}
