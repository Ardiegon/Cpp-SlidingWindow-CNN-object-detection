#include <iostream>
#include <opencv2/opencv.hpp>
#include "point/point.hpp"
#include "obdet/obdet.hpp"


using namespace std;

int main(){
    cv::Mat img = cv::imread("../src/lion.jpg", cv::IMREAD_COLOR);
    cout<< (int)img.cols << " " << (int)img.rows << " " << floor(100*(2/3)) << endl;
    odt::SampleTemplate templ(&img, 100, 100 ,3);
    odt::ImgSamples swindow(templ);
    swindow.calculateFactors();
    int how_many = swindow.generateSamples(1); // here we have problem.
    cv::imshow("Lion", img);
    cv::waitKey(0);
    return 0;
}

    // cv::resize(img, img, cv::Size(cv::Size(100,100)), 0, 0, CV_INTER_LINEAR);
    // cv::imshow("Lion2", img);
    // cout<< (int)img.cols << " " << (int)img.rows << endl;
    // cv::resize(img, img, cv::Size(cv::Size(100*(2.0/3.0),100*(2.0/3.0))), 0, 0, CV_INTER_LINEAR);
    // cout<< (int)img.cols << " " << (int)img.rows << endl;
    // cv::imshow("Lion3", img);

    // odt::SampleTemplate st(&img, 300, 300);
    // odt::Sample s1(st, 300, 0, 1);
    // odt::Sample s2(st, 0, 0, 1);
    // odt::Sample s3(st, 900, 500, 2);
    // cv::imshow("Lion", img);
    // cv::imshow("lin1", s1.get_Mat());
    // cv::imshow("lin2", s2.get_Mat());
    // cv::imshow("lin3", s3.get_Mat());
    // cv::imshow("Lion", img);
    // cv::imshow("lin", newimg);
    // cv::imshow("roi", img(roi));
    // cout<< (int)newimg.cols << " " << (int)newimg.rows << endl;