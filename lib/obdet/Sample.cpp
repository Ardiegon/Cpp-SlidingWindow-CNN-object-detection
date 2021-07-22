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

int Sample::get_corx(){
    return corx;
}

int Sample::get_cory(){
    return cory;
}

double Sample::get_factor(){
    return factor;
}