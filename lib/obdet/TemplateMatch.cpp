#include "obdet.hpp"
#include <iostream>
#include <cmath>
#include <limits>

using namespace odt;
 
TemplateMatch::TemplateMatch(ImgSamples *i, cv::Mat m): image(i), templ(m) {
    normalizeTemplate();
};

void TemplateMatch::normalizeTemplate(){
    cv::resize(templ, templ, cv::Size(image->get_samplet().get_lenx(),image->get_samplet().get_leny()), 0, 0, CV_INTER_LINEAR);
    vector<cv::Mat> channels;
    cv::split(templ, channels);
    int histSize = 256;
    float range[] = { 0, 256 };
    const float* histRange[] = { range };
    bool uniform = true, accumulate = false;
    cv::Mat b_hist, g_hist, r_hist;
    temp_hist.push_back(b_hist); temp_hist.push_back(g_hist); temp_hist.push_back(r_hist);
    calcHist( &channels[0], 1, 0, cv::Mat(), temp_hist[0], 1, &histSize, histRange, uniform, accumulate );
    calcHist( &channels[1], 1, 0, cv::Mat(), temp_hist[1], 1, &histSize, histRange, uniform, accumulate );
    calcHist( &channels[2], 1, 0, cv::Mat(), temp_hist[2], 1, &histSize, histRange, uniform, accumulate );
};

long int TemplateMatch::calcHistDifference(int id_sample){
    vector<cv::Mat> sample_hist = image->get_samples()[id_sample].makeHistBGR();
    long int difference_sum = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 256; j++){
            difference_sum += static_cast<long int>(pow(sample_hist[i].at<float>(j,0) - temp_hist[i].at<float>(j,0),2));
        }
    }
    return difference_sum;
};

Sample TemplateMatch::findBestSample(){
    int best = 0;
    int nsamples = image->get_nsamples();
    long int best_diff = std::numeric_limits<long int>::max();
    for(int i = 0; i<nsamples; i++){
        long int diff = calcHistDifference(i);
        if(best_diff > diff){
            best = i;
            best_diff = diff;
        }
        if(i%100==0){
            cout << static_cast<float>(i)/static_cast<float>(nsamples) * 100.0 << "%\n";
        }
    }
    return image->get_samples()[best];
};
