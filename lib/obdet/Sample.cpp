#include "obdet.hpp"
#include <iostream>
#include <cmath>

using namespace odt;
Sample::Sample() {};

Sample::Sample(SampleTemplate& _st, int _corx, int _cory, double _factor):
    SampleTemplate(_st), corx(_corx), cory(_cory), factor(_factor) {};

cv::Mat Sample::get_Mat(){
    int x = static_cast<int>(mImage->cols*factor); int y = static_cast<int>(mImage->rows*factor);
    cv::Mat mat(x, y, CV_8UC3);
    cv::resize(*mImage, mat, cv::Size(), factor, factor, CV_INTER_LINEAR);
    cv::Rect roi(corx, cory, lenx, leny);
    cv::Mat result;
    result = mat(roi);
    return result;
}

cv::Mat Sample::showOnImage(ShowType s){
    cv::Mat bimage;
    cv::Point pt1, pt2;
    bimage = mImage->clone();
    switch(s)
    {
        case ShowType::RAW:        
        cv::resize(bimage, bimage, cv::Size(), factor, factor, CV_INTER_LINEAR);
        pt1 = cv::Point(corx, cory);
        pt2 = cv::Point(corx+lenx-1, cory+leny-1);
        cv::rectangle(bimage, pt1, pt2, cv::Scalar(0, 0, 255));
        break;

        case ShowType::NORMALIZED:
        pt1 = cv::Point(static_cast<int>(corx/factor), static_cast<int>(cory/factor));
        pt2 = cv::Point(static_cast<int>(corx/factor+lenx/factor-1), static_cast<int>(cory/factor+leny/factor-1));
        cv::rectangle(bimage, pt1, pt2, cv::Scalar(0, 0, 255));
        break;
    }
    return bimage;

}

vector<cv::Mat> Sample::makeHistBGR(){
    vector<cv::Mat> hist;
    vector<cv::Mat> channels;
    cv::split(get_Mat(), channels);
    int histSize = 256;
    float range[] = { 0, 256 };
    const float* histRange[] = { range };
    bool uniform = true, accumulate = false;
    cv::Mat b_hist, g_hist, r_hist;
    hist.push_back(b_hist); hist.push_back(g_hist); hist.push_back(r_hist);
    calcHist( &channels[0], 1, 0, cv::Mat(), hist[0], 1, &histSize, histRange, uniform, accumulate );
    calcHist( &channels[1], 1, 0, cv::Mat(), hist[1], 1, &histSize, histRange, uniform, accumulate );
    calcHist( &channels[2], 1, 0, cv::Mat(), hist[2], 1, &histSize, histRange, uniform, accumulate );
    return hist;
}

int Sample::get_corx(){
    return corx;
}

int Sample::get_cory(){
    return cory;
}

double Sample::get_factor(){
    return factor;
}