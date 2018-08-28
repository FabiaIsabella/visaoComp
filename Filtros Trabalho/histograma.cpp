//g++ histograma.cpp -o histograma `pkg-config --cflags --libs opencv`

#include <iostream>
#include <math.h>
#include <algorithm>
#include <fstream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace std;
using namespace cv;

int main(int argc, char** argv){

  String imageName;
  if(argc > 1) imageName = argv[1];

  Mat img = imread(imageName, CV_LOAD_IMAGE_GRAYSCALE);
	//Mat img = imread("cameraman.jpg", CV_LOAD_IMAGE_GRAYSCALE); 
   
   //	imshow("img", img);

   	int hist_w = 512; 
   	int hist_h = 256;

    Mat img2 = img.clone();

    int hist[256] = {};
    int histEqual[256] = {};

    int pixel;

    for(int i = 0; i< img.rows; i++){
    	for(int j = 0; j< img.cols; j++){
    		pixel = img.at<uchar>(i,j);
    		hist[pixel] = hist[pixel]+ 1;		
    	}
    }


    ofstream file;
    file.open ("histograma.txt");
    //gnuplot plot "histograma.txt" w l

   //salva os dados do histograma em um arquivo; 
    for(int i = 0; i<256; i++){
    	file << i << " "<< hist[i] << endl;
    }

    file.close();

    equalizeHist(img, img2);

    for(int i = 0; i< img.rows; i++){
      for(int j = 0; j< img.cols; j++){
        pixel = img2.at<uchar>(i,j);
        histEqual[pixel] = histEqual[pixel]+ 1;   
      }
    }

    ofstream file2;
    file2.open ("histogramaEqualizado.txt");
    //gnuplot plot "histogramaEqualizado.txt" w l

   //salva os dados do histograma em um arquivo; 
    for(int i = 0; i<256; i++){
      file2 << i << " "<< histEqual[i] << endl;
    }

    file2.close();

    //imshow("Equalizada", img2);


  imwrite("output/histo.jpg",img);
  imwrite("output/equalizada.jpg",img2);

   	waitKey(0);
   	return 0;

}