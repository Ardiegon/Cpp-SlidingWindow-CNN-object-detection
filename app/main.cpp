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
    cout<< (int)img.cols << " " << (int)img.rows << " " << floor(100*(2/3)) << endl;
    odt::SampleTemplate templ(&img, 100, 100 ,6);
    odt::ImgSamples swindow(templ);
    swindow.calculateFactors();
    int how_many = swindow.generateSamples(5); 
    cv::imshow("Lion", img);
    cv::imshow("Sample219700", swindow.get_samples()[219700].showOnImage());
    cv::imshow("What", swindow.get_samples()[0].makeHistBGR()[0]);  
    cv::imshow("Lion2", img);

    float sum = 0;
    for(int i = 0; i< 256; i++){
    sum += swindow.get_samples()[0].makeHistBGR()[0].at<float>(i);
    }
    cout << "Sum: " << sum << endl;

    cv::waitKey(0);
    return 0;
}