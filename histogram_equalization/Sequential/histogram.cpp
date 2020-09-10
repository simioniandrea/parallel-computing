#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

void make_histogram(Mat image, int hist[], int *yuv_vector){
// receives the image histogram as formal parameter(int hist[]) and computes the RGB to YUV conversion, updating the Y histogram

    // initialize all intensity values to 0
    for(int i = 0; i < 256; i++){
        hist[i] = 0;
    }

    int index = 0;
    //slide rows and cols
    for(int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++)
        {

            Vec3b intensity = image.at<Vec3b>(i,j); //vector with 3 byte entries, each one for R,G,B respectively

            int R = intensity.val[0]; // R is red
            int G = intensity.val[1]; // G is green
            int B = intensity.val[2]; // B is blue

            // Conversion
            int Y = R * .299000 + G * .587000 + B * .114000; // Y is the luminance level
            int U = R * -.168736 + G * -.331264 + B * .500000 + 128;
            int V = R * .500000 + G * -.418688 + B * -.081312 + 128;

            hist[Y]++;
            // memorize in a column vector all the pixels of the image in RGB format ( the yuv_vector is initialized like rows*cols*3 )
            yuv_vector[index] = Y;
            yuv_vector[index + 1] = U;
            yuv_vector[index + 2] = V;

            index = index +3;
        }
    }
}

void cumulative_hist(int hist[], int equalized[], int cols, int rows)

{
    int cumulative_histogram[256];

    cumulative_histogram[0] = hist[0];

    for(int i = 1; i < 256; i++)
    {
        cumulative_histogram[i] = hist[i] + cumulative_histogram[i-1]; //Computation of cdf

        equalized[i] = (int)(((float)cumulative_histogram[i] - hist[0])/((float)cols * rows - 1)*255); //Normalization of cdf
    }
}
