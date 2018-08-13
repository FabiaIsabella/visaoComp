//g++ histoGray.cpp -o gray `pkg-config --cflags --libs opencv`

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>

using namespace std;
using namespace cv;

//histograma de uma imagem em escala de cinza
void histogramaGray(string const& nome, Mat img){

	int histSize = 256; 
	float range[] = {0, 255};
	const float *ranges[] = {range};
	
	Mat hist;
	calcHist( &img, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false );
	
	double total;
	total = img.rows * img.cols;
	for( int h = 0; h < histSize; h++ ){
		float binVal = hist.at<float>(h);
	        //cout<<" "<<binVal;
	}

	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound( (double) hist_w/histSize );

	Mat histImage( hist_h, hist_w, CV_8UC1, Scalar( 0,0,0) );
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

	for( int i = 1; i < histSize; i++ ){
		line(histImage, Point( bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1)) ), Point( bin_w*(i), hist_h - cvRound(hist.at<float>(i)) ),Scalar( 255, 0, 0), 2, 8, 0);
	}

	imshow(nome, histImage);
	
}

int main(){
	Mat img, img2;
	
        img=imread("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);

        imshow("Imagem", img);	
	histogramaGray("Histograma Imagem", img);

	equalizeHist(img, img2);

	imshow("Imagem Equalizada", img2);
	histogramaGray("Histograma Imagem Equalizada", img2);
	
	waitKey(0);    
	return 0;
}
