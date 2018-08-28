//g++ edges.cpp -o edges `pkg-config --cflags --libs opencv`

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

Mat laplaciano(Mat img){

	Mat imgGaussiano = img.clone();


	Mat imgLaplaciano = img.clone();

	int mat[3][3] = {
					{-1, -1, -1},
        			{-1, 8 -1},
        			{-1, -1, -1}
    		       };
    int gx, gy;
    int pixel;

	//imgGaussiano = gaussiano(img);

	GaussianBlur(img, imgGaussiano, Size(3, 3), 0, 0);

    for(int i = 0; i< img.rows; i++){
    	for(int j = 0; j< img.cols; j++){
			pixel = 0;
    		
    		for(int x =0; x<3; x++){
    			for(int y=0; y<3; y++){
    				int px = i + (x - 1);
    				int py = j + (y - 1);

    				pixel = pixel + mat[x][y] * imgGaussiano.at<uchar>(px,py);
    			}
    		}
    		
    		if(pixel < 0) pixel = 0;
    		if(pixel > 255) pixel = 255;

			imgLaplaciano.at<uchar>(i,j) = pixel;
		}
	}


	return imgLaplaciano;
}

Mat laplaciano5(Mat img){

	Mat imgLaplaciano5 = img.clone();

	/*int mat[5][5] = {
					{-1, -1, -1, -1, -1},
			        {-1, -1, -1, -1, -1},
			        {-1, -1, 24, -1, -1},
			        {-1, -1, -1, -1, -1},
			        {-1, -1, -1, -1, -1}
  			       };*/

 	int mat[3][3] = {
					{-1, -1, -1},
        			{-1, 8, -1},
        			{-1, -1, -1}
    		       };

    int gx, gy;
    int pixel;

    for(int i = 0; i< img.rows; i++){
    	for(int j = 0; j< img.cols; j++){
			pixel = 0;
    		
    		for(int x =0; x<3; x++){
    			for(int y=0; y<3; y++){
    				int px = i + (x - 1);
    				int py = j + (y - 1);

    				pixel = pixel + mat[x][y] * img.at<uchar>(px,py);
    			}
    		}

    		//pixel = pixel/8;
    		
    		if(pixel < 0) pixel = 0;
    		if(pixel > 255) pixel = 255;

			imgLaplaciano5.at<uchar>(i,j) = pixel;
		}
	}

	return imgLaplaciano5;
}


int main(int argc, char** argv){

	String imageName;
	if(argc > 1) imageName = argv[1];

  	Mat img = imread(imageName, CV_LOAD_IMAGE_GRAYSCALE);
	//Mat img = imread("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);  

	Mat input1 = img.clone();
	Mat input2 = img.clone();
	Mat input3 = img.clone();
	Mat input4 = img.clone();
	Mat input5 = img.clone();

	Mat imgRoberts;
	Mat imgSobel;
	Mat imgPrewitt; 
	Mat imgLaplaciano;
	Mat imgLaplaciano5;

	if(!img.data) {
		cout <<  "Não foi possivel abrir a imagem" << endl ;
		return -1;
	}
	
	imgRoberts = roberts(input1);
	imgSobel = sobel(input2);
	imgPrewitt = prewitt(input3);
	imgLaplaciano = laplaciano(input4); //laplaciano da gaussiana
	imgLaplaciano5 = laplaciano5(input5);

	
	imwrite("output/cinza.jpg",img);
	imwrite("output/roberts.jpg",imgRoberts);
	imwrite("output/sobel.jpg",imgSobel);
	imwrite("output/prewitt.jpg",imgPrewitt);
	imwrite("output/laplacianoGaussiana.jpg",imgLaplaciano);
	imwrite("output/laplaciano.jpg",imgLaplaciano5);

	//imshow("Imagem Original", img);
	//imshow("Roberts", imgRoberts);
	//imshow("Sobel", imgSobel);
	//imshow("Prewitt", imgPrewitt);
	//imshow("Laplaciano da Gaussiana", imgLaplaciano);
	//imshow("Laplaciano", imgLaplaciano5);

	waitKey(0);

	return 0;
}
