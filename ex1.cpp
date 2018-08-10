//g++ ex1.cpp -o ex1 `pkg-config --cflags --libs opencv`

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
	
	imshow("Imagem 1", img);
  
	width = img.cols;
	height = img.rows;
	
	for(int i = 0; i<width; i++){
		for(int j = 0; j<height; j++){
			pixel = (int)img.at<uchar>(i,j);

			// se pixel+100 > 255 entao pixel = 255 senao pixel = pixel+100
			pixel = ((pixel+100) > 255) ? 255 : pixel+100;
			
			cout << pixel << endl;		
			
			img.at<uchar>(i,j) = pixel;

		}	
	}
	
        imwrite("ex1.jpg",img);
       	
	imshow("Imagem 2", img);
	  
	waitKey(0);
	return 0;
}
