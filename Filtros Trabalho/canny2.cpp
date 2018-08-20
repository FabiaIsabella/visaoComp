#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <math.h>  

#define PI 3.14159265

using namespace std;
using namespace cv;


void canny(Mat im, int blur = 1, int highThreshold = 91, int lowThreshold = 31){

	Mat im2, im3;

	int width = im.cols;
	int height = im.rows;

	int pixel;
	
	Mat magX = Mat(im);
    Mat magY = Mat(im);

    Mat grad = Mat(im);
    Mat theta = Mat(im);
    Mat thetaQ = Mat(im);

	int vertical[3][3]={
					{1, 0, -1},
			        {2, 0, -2},
			        {1, 0, -1}
  			       };

    int horizontal[3][3] = {
					{-1, -2, -1},
        			{0, 0, 0},
        			{1, 2, 1}
    		       };


	GaussianBlur(im, im2, Size(7, 7), 0, 0);
	
	Sobel(im2, magX, CV_32F, 1, 0);
    Sobel(im2, magY, CV_32F, 0, 1);

    imshow("magx",magX);
    imshow("magy",magY);
	 
	Mat grad_x, grad_y;

    convertScaleAbs(magX, grad_x);
    convertScaleAbs(magY, grad_y);
    
    int gy, gx;
    for(int i = 0; i < width; i++){
			for(int j = 0; j < height; j++){
				
				gx = grad_x.at<uchar>(i,j);
				gy = grad_y.at<uchar>(i,j);

				grad.at<uchar>(i,j) =(sqrt((gx*gx) + (gy*gy)));
				
				double param = gy/gx;
			
				theta.at<uchar>(i,j) = atan(param)*180/PI;
				thetaQ.at<uchar>(i,j) = cvRound(theta.at<uchar>(i,j)  * (5/PI) + 5)%5;
				
				//cout << grad[i][j] << endl;
			}	
		}


    //![display]
    imshow("gradiente", grad);

	//Non-maximum suppression

	Mat gradSup = Mat(grad);


	for(int r=0; r< height; r++){
		for(int c=0; c < width; c++){
			
			//Suppress pixels at the image edge
			if(r == 0 || r == height-1 || c == 0 || c == width - 1){
				gradSup.at<uchar>(r,c)=0;
				continue;
			}
			
			int tq = thetaQ.at<uchar>(r,c) % 4;
 
			if(tq == 0){
				if(grad.at<uchar>(r,c) <= grad.at<uchar>(r,c-1) || grad.at<uchar>(r,c) <= grad.at<uchar>(r,c+1))
					gradSup.at<uchar>(r,c)=0;
			}
				
			if(tq == 1){
				if(grad.at<uchar>(r,c) <= grad.at<uchar>(r-1,c+1) || grad.at<uchar>(r,c) <= grad.at<uchar>(r+1,c-1))
					gradSup.at<uchar>(r,c) = 0;
			}
				
			if(tq == 2){
				if(grad.at<uchar>(r,c) <= grad.at<uchar>(r-1,c) || grad.at<uchar>(r,c) <= grad.at<uchar>(r+1,c))
					gradSup.at<uchar>(r,c) = 0;
			}
				
			if(tq == 3){
				if(grad.at<uchar>(r,c) <= grad.at<uchar>(r-1,c-1) || grad.at<uchar>(r,c) <= grad.at<uchar>(r+1,c+1))
					gradSup.at<uchar>(r,c) = 0;
			}

			int p = gradSup.at<uchar>(r,c);
			im.at<uchar>(r,c) = p;
		}		
	}
	
	/*int p;
	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			p = gradSup[i][j];
 			if(p >= highThreshold)
 				p = 255;
 			else if(p < lowThreshold) p = 0;
 			else if(p > lowThreshold && p < highThreshold) p=255;

			im.at<uchar>(i,j) = p;
		}
	}
 */


/*
#Double threshold
	strongEdges = (gradSup > highThreshold)
 
	#Strong has value 2, weak has value 1
	thresholdedEdges = np.array(strongEdges, dtype=np.uint8) + (gradSup > lowThreshold)
 
	#Tracing edges with hysteresis	
	#Find weak edge pixels near strong edge pixels
	finalEdges = strongEdges.copy()
	currentPixels = []
	for r in range(1, im.shape[0]-1):
		for c in range(1, im.shape[1]-1):	
			if thresholdedEdges[r, c] != 1:
				continue #Not a weak pixel
 
			#Get 3x3 patch	
			localPatch = thresholdedEdges[r-1:r+2,c-1:c+2]
			patchMax = localPatch.max()
			if patchMax == 2:
				currentPixels.append((r, c))
				finalEdges[r, c] = 1
 
	#Extend strong edges based on current pixels
	while len(currentPixels) > 0:
		newPix = []
		for r, c in currentPixels:
			for dr in range(-1, 2):
				for dc in range(-1, 2):
					if dr == 0 and dc == 0: continue
					r2 = r+dr
					c2 = c+dc
					if thresholdedEdges[r2, c2] == 1 and finalEdges[r2, c2] == 0:
						#Copy this weak pixel to final result
						newPix.append((r2, c2))
						finalEdges[r2, c2] = 1
		currentPixels = newPix
*/
	imshow("teste",gradSup);
	waitKey(0);
}

int main(){

	Mat img = imread("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	canny(img);
	
	return 0;
}
