#include <omp.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

void make_histogram(Mat image, int hist[], int *yuv_vector)
// receives the image histogram as formal parameter(int hist[]) and computes the RGB to YUV conversion, updating the Y histogram
{

    // initialize all intensity values to 0
    for (int i = 0; i < 256; i++) {
        hist[i] = 0;
    }


#pragma omp parallel default(shared) // The parallel construct starts a parallel block
    // all variables are shared with all threads
    {
#pragma omp for schedule(static)
            for (int i = 0; i < image.rows; i++) {
                for (int j = 0; j < image.cols; j++) {

                    Vec3b intensity = image.at<Vec3b>(i, j); //vector with 3 byte entries, each one for R,G,B respectively

                    int R = intensity.val[0]; // R is red
                    int G = intensity.val[1]; // G is green
                    int B = intensity.val[2]; // B is blue

                    // Convert from RGB into YUV
                    int Y = R * .299000 + G * .587000 + B * .114000; // Y is the luminous level
                    int U = R * -.168736 + G * -.331264 + B * .500000 + 128;
                    int V = R * .500000 + G * -.418688 + B * -.081312 + 128;

                    hist[Y]++;

                    int index = (i * image.cols + j) * 3;

                    // memorize in a column vector all the pixels of the image in RGB format ( the yuv_vector is initialized like rows*cols*3 )
                    yuv_vector[index] = Y;
                    yuv_vector[index + 1] = U;
                    yuv_vector[index + 2] = V;

                }
            }

    }
}

void cumulative_hist(int histogram[], int equalized[], int cols, int rows)
// compute the cdf(named cumulative_histogram) and normalize it (named equalized)
{

    int cumulative_histogram[256];

    cumulative_histogram[0] = histogram[0];

    // Cumulative_histogram needs to be compute in sequential mode
    for(int i = 1; i < 256; i++)
    {
        cumulative_histogram[i] = histogram[i] + cumulative_histogram[i-1];
    }

    #pragma omp parallel for
        for(int i = 1; i < 256; i++){
            equalized[i] = (int)(((float)cumulative_histogram[i] - histogram[0])/((float)cols * rows - 1)*255);
        }
}
