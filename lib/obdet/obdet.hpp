#ifndef OBDET_H
#define OBDET_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
namespace odt{ // object detection

enum class ShowType { RAW, NORMALIZED };
enum class FactorFunction { LINEAR, SQUARE};

extern double factorSpacing(double, double, double, double, FactorFunction = FactorFunction::SQUARE);
void showHistogram();
class SampleTemplate{
    // Class that holds parameters for future samples.                               
protected:
    cv::Mat *mImage;                                // Pointer to original image                               
    int lenx;                                       // Sample width
    int leny;                                       // Sample height
    int accuracy;                                   // How many resizes we do to original image
public: 
    SampleTemplate();
    SampleTemplate(cv::Mat*, int, int, int = 5);    
    SampleTemplate(SampleTemplate&);                
    cv::Mat* get_mImage(void);
    int get_lenx(void);
    int get_leny(void);
    int get_accuracy(void);
    bool isInitialized();
};

class Sample: private SampleTemplate{
    // Info where to look for our sample in original image
    int corx;
    int cory;
    double factor;
    // First we rescale Linearly original image, then we ROI from coordinates
public:
    Sample();
    Sample(SampleTemplate&, int, int, double);
    int get_corx(void);                             
    int get_cory(void);
    double get_factor(void);
    cv::Mat get_Mat(void);                          // Making Matrix from info
    cv::Mat showOnImage(ShowType = ShowType::NORMALIZED);
    vector<cv::Mat> makeHistBGR();
};

class ImgSamples{
    /*
    Sliding Window implementation. Instead of making small Matrices with data,
    we are making samples in which are written all info to take matrix from it,
    only if needed.
    
    private:
    - SampleTemplate samplet:   Info for making samples.
    - double[] factors:         All of resizes for image, for getting good 
                                position of recognized object.
    - Sample[] samples:         Holds info how to perform specific cut from image.

    public:
    - void calculateFactors():  Using linear function splits resizes beetween minimal 
                                and 10x the image <samplet.get_accuracy()> times.
    - int generateSamples():    Sliding Window. Creates samples in samples table. 
                                Returns number of samples created.
    */
    SampleTemplate samplet;
    double* factors;
    Sample *samples;
    int nsamples;
public:
    ImgSamples(SampleTemplate&);
    ~ImgSamples();
    int generateSamples(int);
    void calculateFactors(void);
    double* get_factors(void);
    Sample* get_samples(void);
    SampleTemplate get_samplet(void);
    int get_nsamples();
};

class ConvLayer{
    int nfilters;
    cv::Mat *kernels;
public:
    cv::Mat* convoluteThrough(cv::Mat&);
};

class TemplateMatch{
    ImgSamples *image;
    cv::Mat templ;
    vector<cv::Mat> temp_hist;
public:
    TemplateMatch(ImgSamples*, cv::Mat);
    void normalizeTemplate();
    long int calcHistDifference(int);
    Sample findBestSample();
};

}
#endif