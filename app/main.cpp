#include <iostream>
#include <opencv2/opencv.hpp>
#include "obdet/obdet.hpp"


using namespace std;

int main(int argc, char* argv[]){
    // cout<<"Argc: " << argc << endl;
    // for(int i = 0; i<argc; i++){
    //     cout << argv[i] << endl;
    // }
    cv::Mat img = cv::imread("../src/lion.jpg", cv::IMREAD_COLOR);
    cv::Mat img_template = cv::imread("../src/lion.jpg", cv::IMREAD_COLOR);
    odt::SampleTemplate templ(&img, 300, 300 ,3);
    odt::ImgSamples swindow(templ);
    swindow.calculateFactors();
    swindow.generateSamples(5);
    odt::TemplateMatch tm(&swindow, img_template);
    cv::imshow("Lion", img);
    cv::imshow("Template", img_template);
    cv::imshow("Result", tm.findBestSample().showOnImage());
    cv::imshow("What", swindow.get_samples()[0].makeHistBGR()[0]);  

    cv::waitKey(0);
    return 0;
}