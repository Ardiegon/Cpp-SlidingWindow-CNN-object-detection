#include "obdet.hpp"
#include <iostream>
#include <cmath>

using namespace odt;
 
TemplateMatch::TemplateMatch(ImgSamples *i, cv::Mat m): image(i), templ(m) {
    normalizeTemplate();
};

void TemplateMatch::normalizeTemplate(){
    cv::resize(templ, templ, cv::Size(image->get_samplet().get_lenx(),image->get_samplet().get_leny()), 0, 0, CV_INTER_LINEAR);
}
