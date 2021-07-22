#include "obdet.hpp"
#include <iostream>
#include <cmath>

using namespace odt;

SampleTemplate::SampleTemplate() {mImage = nullptr;};

SampleTemplate::SampleTemplate(cv::Mat* _mImage, int _lenx, int _leny, int _accuracy): 
    mImage(_mImage), lenx(_lenx), leny(_leny), accuracy(_accuracy) {};

SampleTemplate::SampleTemplate(SampleTemplate &stemp):
    mImage(stemp.get_mImage()), lenx(stemp.get_lenx()), 
    leny(stemp.get_leny()), accuracy(stemp.get_accuracy()) {};

cv::Mat* SampleTemplate::get_mImage(){
    return mImage;
}

int SampleTemplate::get_lenx(){
    return lenx;
}

int SampleTemplate::get_leny(){
    return leny;
}

int SampleTemplate::get_accuracy(){
    return accuracy;
}

bool SampleTemplate::isInitialized(){
    return mImage == nullptr;
}