#include <iostream>
#include <opencv2/opencv.hpp>
#include "obdet/obdet.hpp"


using namespace std;

int main(){
    cv::Mat img = cv::imread("../src/lion.jpg", cv::IMREAD_COLOR);
    cout<< (int)img.cols << " " << (int)img.rows << " " << floor(100*(2/3)) << endl;
    odt::SampleTemplate templ(&img, 100, 100 ,3);
    odt::ImgSamples swindow(templ);
    swindow.calculateFactors();
    int how_many = swindow.generateSamples(2); 
    cv::imshow("Lion", img);
    cv::waitKey(0);
    return 0;
}