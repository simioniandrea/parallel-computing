#include <omp.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>



void equalization(Mat image, int equalized[], int *yuv_vector)
{
// edit Y channel with equalized vector and reconvert from YUV to RGB
#pragma omp parallel default(shared)
    {
#pragma omp for schedule(static)
            for (int i = 0; i < image.rows; i++) {
                for (int j = 0; j < image.cols; j++) {

                    int index = (i * image.cols + j) * 3;

                    int Y = equalized[yuv_vector[index]];
                    int U = yuv_vector[index + 1];
                    int V = yuv_vector[index + 2];

                    //Conversion
                    unsigned char R = (unsigned char) max(0, min(255, (int) (Y + 1.4075 * (V - 128))));
                    unsigned char G = (unsigned char) max(0, min(255, (int) (Y - 0.3455 * (U - 128) - (0.7169 * (V - 128)))));
                    unsigned char B = (unsigned char) max(0, min(255, (int) (Y + 1.7790 * (U - 128))));

                    Vec3b intensity = image.at<Vec3b>(i, j);

                    intensity.val[0] = R;
                    intensity.val[1] = G;
                    intensity.val[2] = B;

                    image.at<Vec3b>(i, j) = intensity;
                }
            }

    }
}
