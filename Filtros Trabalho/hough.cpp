//g++ hough.cpp -o hough `pkg-config --cflags --libs opencv`

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>

using namespace cv;
using namespace std;


void houghLines(Mat img){

	Mat output;

	vector<Vec2f> lines;

	cvtColor(img, output, CV_GRAY2BGR);

	int lowThreshold = 30; 
	int highThreshold = 90;

	blur(img, img, Size(3,3));

	//imshow("Blur", img);

    Canny(img, img, lowThreshold, highThreshold, 3);

  //  imshow("Canny", img);

    HoughLines(img, lines, 1, CV_PI/180, 100);

    for( size_t i = 0; i < lines.size(); i++ ){
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000*(-b));
		pt1.y = cvRound(y0 + 1000*(a));
		pt2.x = cvRound(x0 - 1000*(-b));
		pt2.y = cvRound(y0 - 1000*(a));
		line(output, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
	}

    imshow("HoughLines", output);

}

void houghCircle(Mat img){
	Mat img2;

	cvtColor(img, img2, CV_GRAY2BGR);

	int lowThreshold = 30; 
	int highThreshold = 90;

	vector<Vec3f> circles;

	GaussianBlur(img, img, Size(9, 9), 2, 2 );

	//imagem open.jpg
    //HoughCircles(img, circles, CV_HOUGH_GRADIENT, 1, img.rows/16, 100, 100, 10, 85);

	//imagem moedas.jpg
    HoughCircles(img, circles, CV_HOUGH_GRADIENT, 1, img.rows/8, 50, 100, 10, 200);

	for( size_t i = 0; i < circles.size(); i++ ){
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
	    int radius = cvRound(circles[i][2]);
	    circle(img2, center, 3, Scalar(0,255,0), -1, 8, 0 );
	    circle(img2, center, radius, Scalar(0,0,255), 3, 8, 0 );
	}

	imshow("HoughCircle", img2);
}

int main(){

	Mat img = imread("xadrez.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat img2 = imread("moedas.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	if(img.empty()){
		cout << "Erro na leitura da imagem!" << endl;
		return -1;
	}

	houghLines(img);
	houghCircle(img2);

	waitKey(0);

	return 0;
}