//g++ suaviza.cpp -o suaviza `pkg-config --cflags --libs opencv`

#include <iostream>
#include <math.h>
#include <algorithm>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace std;
using namespace cv;

Mat mediana(Mat img){

 	int pixel[9];
 	
 	for (int j = 1; j<img.rows-1; j++){
    	for (int i = 1; i<img.cols-1; i++){
    		
    		pixel[0] = img.at<uchar>(j-1,i-1);
    		pixel[1] = img.at<uchar>(j-1,i);
    		pixel[2] = img.at<uchar>(j-1,i+1);
    		pixel[3] = img.at<uchar>(j,i-1);
    		pixel[4] = img.at<uchar>(j,i);
    		pixel[5] = img.at<uchar>(j,i+1);
    		pixel[6] = img.at<uchar>(j+1,i-1);
    		pixel[7] = img.at<uchar>(j+1,i);
    		pixel[8] = img.at<uchar>(j+1,i+1);

    		sort(pixel, pixel+9);

    		img.at<uchar>(j,i) = pixel[4];

    	}
    }	

 	return img;
}

Mat media(Mat img){
 	
 	int pixel;

 	for (int j = 0; j<img.rows-1; j++){
    	for (int i = 0; i<img.cols-1; i++){
    		
    		pixel = (img.at<uchar>(j-1,i-1) + img.at<uchar>(j-1,i) + img.at<uchar>(j-1,i+1) 
    				+ img.at<uchar>(j,i-1) + img.at<uchar>(j,i) + img.at<uchar>(j,i+1) 
    				+ img.at<uchar>(j+1,i-1) + img.at<uchar>(j+1,i) + img.at<uchar>(j+1,i+1))/9;

    		img.at<uchar>(j,i) = pixel;

    	}
    }	

 	return img;
}

Mat gaussiano(Mat img){

	Mat imgGaussiano = img.clone();

	int mat[5][5] = {
					{1, 4, 7, 4, 1},
			        {4, 16, 26, 16, 4},
			        {7, 26, 41, 26, 7},
			        {4, 16, 26, 16, 4},
			        {1, 4, 7, 4, 1}
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

			imgGaussiano.at<uchar>(i,j) = pixel/273;
		}
	}

	return imgGaussiano;
}

int main(){

	Mat img = imread("lena.jpg" , CV_LOAD_IMAGE_GRAYSCALE);  

	Mat input1 = img.clone();
	Mat input2 = img.clone();
	Mat input3 = img.clone();

	Mat imgMedia;
	Mat imgMediana;
	Mat imgGaussiano;

	if(!img.data) {
		cout <<  "Não foi possivel abrir a imagem" << endl ;
		return -1;
	}
	
	imgMedia = media(input1);
	imgMediana = mediana(input2);
	imgGaussiano = gaussiano(input3);

	imshow("Imagem Original", img);
	imshow("Media", imgMedia);
	imshow("Mediana", imgMediana);
	imshow("Gaussiano", imgGaussiano);

	waitKey(0);

	return 0;
}
