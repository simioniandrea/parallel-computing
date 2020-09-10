#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

void equalization(Mat image, int equalized[], int *yuv_vector)
{
    int index = 0;
    for(int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {


            int Y = equalized[yuv_vector[index]];  // edit Y channel with equalized vector 
            int U = yuv_vector[index+1];
            int V = yuv_vector[index+2];
            
            // reconvert from YUV to RGB
            unsigned char R = (unsigned char)max(0, min(255,(int)(Y + 1.4075 * (V - 128))));
            unsigned char G = (unsigned char)max(0, min(255,(int)(Y - 0.3455 * (U - 128) - (0.7169 * (V - 128)))));
            unsigned char B = (unsigned char)max(0, min(255,(int)(Y + 1.7790 * (U - 128))));

            Vec3b intensity = image.at<Vec3b>(i,j);

            intensity.val[0] = R;
            intensity.val[1] = G;
            intensity.val[2] = B;

            image.at<Vec3b>(i,j) = intensity;

            index = index + 3;
        }
    }
}