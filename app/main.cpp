#include <iostream>
#include <opencv2/opencv.hpp>
#include "obdet/obdet.hpp"


using namespace std;

int main(){
    cv::Mat img = cv::imread("../src/lion.jpg", cv::IMREAD_COLOR);
    cout<< (int)img.cols << " " << (int)img.rows << " " << floor(100*(2/3)) << endl;
    odt::SampleTemplate templ(&img, 300, 300 ,6);
    odt::ImgSamples swindow(templ);
    swindow.calculateFactors();
    int how_many = swindow.generateSamples(5); 
    cv::imshow("Lion", img);
    cv::imshow("Sample1", swindow.get_samples()[0].showOnImage());
    cv::imshow("Sample1", swindow.get_samples()[10].showOnImage());
    cv::imshow("Sample1", swindow.get_samples()[11].showOnImage());
    cv::imshow("Sample1", swindow.get_samples()[31].showOnImage());


    cv::waitKey(0);
    return 0;
}