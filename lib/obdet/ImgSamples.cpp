#include "obdet.hpp"
#include <iostream>
#include <cmath>


double odt::factorSpacing(double start, double end, double steps, double x, FactorFunction f){
    double result;
    switch(f){
        case FactorFunction::LINEAR:        result = ((end - start) / steps)*x + start; break;
        case FactorFunction::SQUARE:        result = ((end-start)/(steps*steps))*(x*x) + start; break;
    }
    return result;
}

using namespace odt;
constexpr double max_factor = 10 ;

ImgSamples::ImgSamples(SampleTemplate& _st): samplet(_st) {
    factors = new double[_st.get_accuracy()];
}

ImgSamples::~ImgSamples(){
    delete factors;
}

void ImgSamples::calculateFactors(){
    double a = static_cast<double>(samplet.get_accuracy());
    double min_factor = max(static_cast<double>(samplet.get_lenx())/static_cast<double>(samplet.get_mImage()->cols),static_cast<double>(samplet.get_leny())/static_cast<double>(samplet.get_mImage()->rows));
    for (int i = 0; i < a; i++){
        factors[i] = factorSpacing(min_factor, max_factor, a, i);
    }
}

int ImgSamples::generateSamples(int padding){
    // k - kernel, b - resized, m - main
    double mwidth, mheight, bwidth, bheight, kwidth, kheight; 
    mwidth = samplet.get_mImage()->cols;
    mheight = samplet.get_mImage()->rows;
    kwidth = samplet.get_lenx();
    kheight = samplet.get_leny();

    // Alocate memory, calculate how much.
    int max_samples = 0;
    for(int f = 0; f<samplet.get_accuracy(); f++){
        bheight =  floor(factors[f]*mheight); bwidth = floor(factors[f]*mwidth);
        max_samples += static_cast<int>(ceil((bheight-kheight+1)/padding)*ceil((bwidth-kwidth+1)/padding));
    }
    samples = new Sample[max_samples];
    
    // Make Samples using nested loops (Resized image -> Iter through height -> Iter through width).
    int id_sample = 0;
    for(int f = 0; f<samplet.get_accuracy(); f++){
        double curr_factor = factors[f];
        bheight =  floor(curr_factor*mheight); bwidth = floor(curr_factor*mwidth);
        std::cout<< "\nWindow size: " << bwidth << ":" << bheight << std::endl;  
        for(int prop_y = 0; prop_y<=bheight-kheight; prop_y+=padding){
            for(int prop_x = 0; prop_x<=bwidth-kwidth; prop_x+=padding){
                samples[id_sample] = Sample(samplet, prop_x, prop_y, curr_factor);
                id_sample++;
            }
        }
        std::cout << "Sample amount: " <<id_sample << "/" << max_samples<<endl;
    }
    if (id_sample != max_samples){
        throw "Number of samples is other than calculated!";
    }
    return max_samples;
}

double* ImgSamples::get_factors(){
    return factors;
}

Sample* ImgSamples::get_samples(){
    return samples;
}

SampleTemplate ImgSamples::get_samplet(){
    return samplet;
}