//g++ canny.cpp -o canny `pkg-config --cflags --libs opencv`

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>

using namespace std;
using namespace cv;

int main() {
  
	Mat img, img2;
	int height, width, pixel;
	
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

	img = imread("lena.jpg" , CV_LOAD_IMAGE_GRAYSCALE);  
	
	if(!img.data) {
		cout <<  "Não foi possivel abrir a imagem" << endl ;
		return -1;
	}

	width = img.cols;
	height = img.rows;
	

	
    GaussianBlur(img, img2, Size(7, 7), 0, 0);		
	imshow("Gaussian", img2);
	
	//SOBEL
	int grad[width][height];

	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			int gx = 0;
			int gy = 0;
			
			for(int x = 0; x<3; x++){
				for(int y = 0; y <3; y++){
					int px = i + (x -1);
				        int py = j + (y -1);

					pixel = img.at<uchar>(px,py);

					gx = gx + (horizontal[x][y]*pixel);
					gy = gy + (vertical[x][y]*pixel);

				}
			}
			grad[i][j] =(int)(sqrt((gx*gx) + (gy*gy)));
			cout << grad[i][j] <<endl;
		}	
	}
	/*int p;
	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			if(grad[i][j] > 255)
				p = 255;
			else if(grad[i][j] < 0)
				p = 0;
			else
 				p = grad[i][j];
			
			img.at<uchar>(i,j) = p;
		}
	}*/

	//FIM SOBEL

	//imshow("sobel", img);

	//Non-maximum suppression

	int gradSup[width][height];

	memcpy(gradSup,grad,sizeof(grad));
	
	for(int r = 0; r < height; r++){
		for(int c = 0; c < width; c++){
			if(r == 0 || r == im.height-1 || c == 0 || c == width - 1){
				gradSup[r][c] = 0;
				continue;
			}
			
		}
	}

	waitKey(0);

	return 0;
}
