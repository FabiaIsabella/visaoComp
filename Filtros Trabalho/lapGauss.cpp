//g++ lapGauss.cpp -o lapGauss `pkg-config --cflags --libs opencv`

#include <iostream>
#include <math.h>
#include <algorithm>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace std;
using namespace cv;


Mat lapGauss(Mat img){

	Mat imgLaplacianoGaussiana = img.clone();

	int mat[5][5] = {
					{0, 0, -1, 0, 0},
			        {0, -1, -2, -1, 0},
			        {-1, -2, 16, -2, -1},
			        {0, -1, -2, -1, 0},
			        {0, 0, -1, 0, 0}
  			       };

  	int gx, gy;
    int pixel;

    for(int i = 0; i< img.rows; i++){
    	for(int j = 0; j< img.cols; j++){
			pixel = 0;
    		
    		for(int x =0; x<5; x++){
    			for(int y=0; y<5; y++){
    				int px = i + (x - 2);
    				int py = j + (y - 2);

    				pixel = pixel + mat[x][y] * img.at<uchar>(px,py);
    			}
    		}
    		
    		if(pixel < 0) pixel = 0;
    		if(pixel > 255) pixel = 255;

			imgLaplacianoGaussiana.at<uchar>(i,j) = pixel;
		}
	}

	 for(int i = 0; i< img.rows; i++){
    	for(int j = 0; j< img.cols; j++){
    		if(imgLaplacianoGaussiana.at<uchar>(i,j) > 200) imgLaplacianoGaussiana.at<uchar>(i,j) = 255;
    		else imgLaplacianoGaussiana.at<uchar>(i,j) = 0;
    	}
    }

	return imgLaplacianoGaussiana;

}

int main(){

	Mat img = imread("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);  

	Mat input1 = img.clone();

	Mat imgLaplacianoGaussiana;

	if(!img.data) {
		cout <<  "Não foi possivel abrir a imagem" << endl ;
		return -1;
	}

	imgLaplacianoGaussiana = lapGauss(input1);

	imshow("Laplaciano da Gaussiana", imgLaplacianoGaussiana);

	waitKey(0);

	return 0;
}
