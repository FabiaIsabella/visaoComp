#include <iostream>
#include <math.h>
#include <algorithm>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace std;
using namespace cv;

Mat roberts(Mat img){

	Mat roberts = img.clone();

	int vertical[3][3] = {
					{0, 0, -1},
			        {0, 1, 0},
			        {0, 0, 0}
  			       };


	int horizontal[3][3] = {
					{-1, 0, 0},
        			{0, 1, 0},
        			{0, 0, 0}
    		       };
    int gx, gy;
    int grad;

    for(int i = 0; i< img.rows; i++){
    	for(int j = 0; j< img.cols; j++){
			gx = 0;
			gy = 0;
    		
    		for(int x =0; x<3; x++){
    			for(int y=0; y<3; y++){
    				int px = i + (x - 1);
    				int py = j + (y - 1);

    				gx = gx + horizontal[x][y] * img.at<uchar>(px,py);
    				gy = gy + vertical[x][y] * img.at<uchar>(px,py);
    			}
    		}

			grad = sqrt((gx*gx) + (gy*gy));
 			if (grad> 255) grad = 255;
			else if(grad < 0) grad = 0;

			roberts.at<uchar>(i,j) = grad;
		}
	}

	return roberts;
}

Mat sobel(Mat img){

	Mat sobel = img.clone();
	int vertical[3][3] = {
					{1, 0, -1},
			        {2, 0, -2},
			        {1, 0, -1}
  			       };


	int horizontal[3][3] = {
					{-1, -2, -1},
        			{0, 0, 0},
        			{1, 2, 1}
    		       };
    int gx, gy;
    int grad;

    for (int i = 0; i< img.rows; i++){
    	for (int j = 0; j< img.cols; j++){
			gx = 0;
			gy = 0;
    		
    		for(int x =0; x<3; x++){
    			for(int y=0; y<3; y++){
    				int px = i + (x - 1);
    				int py = j + (y - 1);

    				gx = gx + horizontal[x][y] * img.at<uchar>(px,py);
    				gy = gy + vertical[x][y] * img.at<uchar>(px,py);
    			}
    		}

			grad = sqrt((gx*gx) + (gy*gy));
 			if (grad> 255) grad = 255;
			else if(grad < 0) grad = 0;

			sobel.at<uchar>(i,j) = grad;
		}
	}

	return sobel;
}

Mat prewitt(Mat img){

	Mat prewitt = img.clone();

	int vertical[3][3] = {
					{1, 0, -1},
			        {1, 0, -1},
			        {1, 0, -1}
  			       };


	int horizontal[3][3] = {
					{-1, -1, -1},
        			{0, 0, 0},
        			{1, 1, 1}
    		       };
    int gx, gy;
    int grad;

    for(int i = 0; i< img.rows; i++){
    	for(int j = 0; j< img.cols; j++){
			gx = 0;
			gy = 0;
    		
    		for(int x =0; x<3; x++){
    			for(int y=0; y<3; y++){
    				int px = i + (x - 1);
    				int py = j + (y - 1);

    				gx = gx + horizontal[x][y] * img.at<uchar>(px,py);
    				gy = gy + vertical[x][y] * img.at<uchar>(px,py);
    			}
    		}

			grad = sqrt((gx*gx) + (gy*gy));
 			if (grad> 255) grad = 255;
			else if(grad < 0) grad = 0;

			prewitt.at<uchar>(i,j) = grad;
		}
	}

	return prewitt;
}

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

int main(){

	Mat img = imread("lena.jpg" , CV_LOAD_IMAGE_GRAYSCALE);  

	Mat input = img.clone();
	Mat input2 = img.clone();
	Mat input3 = img.clone();
	Mat input4 = img.clone();
	Mat input5 = img.clone();

	Mat imgRoberts;
	Mat imgSobel;
	Mat imgPrewitt; 
	Mat imgMediana;
	Mat imgMedia;


	if(!img.data) {
		cout <<  "Não foi possivel abrir a imagem" << endl ;
		return -1;
	}
	
	imgRoberts = roberts(input);
	imgSobel = sobel(input2);
	imgPrewitt = prewitt(input3);

	imgMediana = mediana(input4);
	imgMedia = media(input5);

	imshow("Imagem Original", img);
	imshow("Roberts", imgRoberts);
	imshow("Sobel", imgSobel);
	imshow("Prewitt", imgPrewitt);
	
	imshow("Mediana", imgMediana);
	imshow("Media", imgMedia);

	waitKey(0);

	return 0;
}
