#include <iostream>
#include <math.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace std;
using namespace cv;

#define PI 3.14159265

Mat canny(Mat img, int highThreshold, int lowThreshold){

	Mat sobel = img.clone();

	Mat supress = img.clone();

	Mat imgFinal = img.clone();

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

    int height = img.rows;
    int width = img.cols;

    int grad[height][width];
	int theta[height][width];

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

			grad[i][j] = sqrt((gx*gx) + (gy*gy));
 			if (grad[i][j]> 255) grad[i][j] = 255;
			else if(grad[i][j] < 0) grad[i][j] = 0;

			theta[i][j] = (atan2(gy,gx)/PI) * 180.0;

			sobel.at<uchar>(i,j) = grad[i][j];
		}
	}

	int gradN[height][width];


	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){	

			// 0 degrees
	        if ((theta[i][j] >= -337.5 || theta[i][j] < -22.5) || (theta[i][j] >= 157.5 && theta[i][j] < 202.5)){
	          if(grad[i][j] >= grad[i][j + 1] && grad[i][j] >= grad[i][j - 1])
	            gradN[i][j] = grad[i][j];
	    	}
	        // 45 degrees
	        else if ((theta[i][j] >= -22.5 && theta[i][j] < -67.5) || (theta[i][j] >= 202.5 && theta[i][j] < 247.5)){
	          if(grad[i][j] >= grad[i - 1][j + 1] && grad[i][j] >= grad[i + 1][j - 1])
	            gradN[i][j] = grad[i][j];
	    	}
	        // 90 degrees
	        else if ((theta[i][j] >= -67.5 && theta[i][j] < -112.5) || (theta[i][j] >= 247.5 && theta[i][j] < 292.5)){
	          if(grad[i][j] >= grad[i - 1][j] && grad[i][j] >= grad[i + 1][j])
	            gradN[i][j] = grad[i][j];
	    	}
	        // 135 degrees
	        else if ((theta[i][j] >= -112.5 && theta[i][j] < -157.5) || (theta[i][j] >= 292.5 && theta[i][j] < 337.5)){
	          if(grad[i][j] >= grad[i - 1][j - 1] && grad[i][j] >= grad[i + 1][j + 1])
	            gradN[i][j] = grad[i][j];
	    	} else gradN[i][j] = 0;
	       
			supress.at<uchar>(i,j) = gradN[i][j];
		}
	}

	for(int i=0; i<height; i++){
		for(int j=0; j<width; j++){
			if(gradN[i][j] > highThreshold) 
				imgFinal.at<uchar>(i,j) = 255;
			else if(gradN[i][j] <= lowThreshold) 
				imgFinal.at<uchar>(i,j) = 0;
			/*else{
				int med = (highThreshold + lowThreshold)/2;
				if(gradN[i][j] > med) imgFinal.at<uchar>(i,j) = 255;
				else imgFinal.at<uchar>(i,j) = 0;
			}*/

	    	else if(gradN[i-1][j-1] > highThreshold || gradN[i-1][j] > highThreshold || gradN[i-1][j+1] > highThreshold || 
					gradN[i+1][j-1] > highThreshold || gradN[i+1][j] > highThreshold || gradN[i+1][j+1] > highThreshold || 
					gradN[i][j-1] > highThreshold || gradN[i][j+1] > highThreshold) 
				imgFinal.at<uchar>(i,j) = 255; 
             else imgFinal.at<uchar>(i,j) = 0;
		}
	}

	return imgFinal;
 }

int main()
{

    Mat img = imread("lena.jpg", 0); 
   
   	Mat img2 = img.clone();
   
   	GaussianBlur(img, img2, Size(5, 5), 0, 0);

   	//imshow("GaussianBlur", img2);

	Mat img3 = img.clone();
	img3 = canny(img2, 60, 30);
  
    imshow("Canny", img3);

    waitKey(0);
    return 0;
}
