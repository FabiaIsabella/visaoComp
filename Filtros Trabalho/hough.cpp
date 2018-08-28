//g++ hough.cpp -o hough `pkg-config --cflags --libs opencv`

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>

using namespace std;
using namespace cv;

int main() {
  
	Mat img;
	int height, width, pixel;

	img = imread("lena.jpg" , CV_LOAD_IMAGE_GRAYSCALE);  

	if(!img.data) {
		cout <<  "Não foi possivel abrir a imagem" << endl ;
		return -1;
	}
	
	Mat gaussian = img.clone();

	Mat canny = img.clone();
   
   	GaussianBlur(img, gaussian, Size(5, 5), 0, 0);

   	Canny(gaussian, canny, 30, 90, 3);

	imshow("Canny", canny);

	waitKey(0);

	return 0;

}