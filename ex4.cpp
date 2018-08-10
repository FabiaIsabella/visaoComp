//g++ ex4.cpp -o ex4 `pkg-config --cflags --libs opencv`

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include "dirent.h"

using namespace std;
using namespace cv;
 
int main() {
  
	string input = "input";
	string output = "output";
	int height, width;
	Mat img;
	
	DIR *directory = opendir (input.c_str());
	struct dirent *_dirent = NULL;
	
	if(directory == NULL){
		cout << "Erro ao abrir a pasta" << endl;
		return -1;
	}

	while((_dirent = readdir(directory)) != NULL){
        	string fileName = input + "/" + string(_dirent->d_name);
       		
		img = imread(fileName.c_str());
        	
		if(!img.data){
           		cout << "Erro ao abrir imagem" << endl;
			continue;
        	}
		
		imshow(fileName, img);

		width = img.cols;
		height = img.rows;
	
		for(int i = 0; i<width; i++){
			for(int j = 0; j<height; j++){
			
				// RGB
				// se r+100 > 255 entao r = 255 senao r = r+100
				img.at<Vec3b>(i,j)[0] = ((img.at<Vec3b>(i,j)[0]+100) > 255) ? 255 : img.at<Vec3b>(i,j)[0]+100;
				img.at<Vec3b>(i,j)[1] = ((img.at<Vec3b>(i,j)[1]+100) > 255) ? 255 : img.at<Vec3b>(i,j)[1]+100;
				img.at<Vec3b>(i,j)[2] = ((img.at<Vec3b>(i,j)[2]+100) > 255) ? 255 : img.at<Vec3b>(i,j)[2]+100;
			}	
		}


        	fileName = output + "/" + string(_dirent->d_name);
        	imwrite(fileName.c_str(), img);
    	}
    	
	closedir(directory);	
	waitKey(0);
	
	return 0;
}
