#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <sys/time.h>
#include <sys/stat.h>
#include "histogram.cpp"
#include "equalization.cpp"
#include <fstream>




using namespace std;
using namespace cv;


int main(){

    // Paths to save the resized and equalized test images
    const char *test_dir_path = "../resizedTestImage";
    string _p = string(test_dir_path);

    const char *result_dir = "../eq";
    string _l = string(result_dir);
    ifstream h(_l);
    if (!h.good()){
        mkdir(result_dir, 0777);
    }

    // Path to save the files for speedup calculation
    // Reminder: resizing the original image is required for this analysis
    const char *speed_up = "../speedup";
    string _i = string(speed_up);
    ifstream k(_i);
    if (!k.good()){
        mkdir(speed_up, 0777);
    }

    // Load images from directory
    vector<String> fn;
    // Take the images from the directory. Use .jpg format
    glob("../img/*.jpg", fn, false);
    size_t count = fn.size();

    // Resize dimension vector, 0 is referred to the original size of images. Use the second vector to avoid resizing
    vector<int> image_sizes = {0,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000};
    //vector<int> image_sizes = {0}
    size_t g = image_sizes.size();

    // Txt file to save result
    ofstream out("../eq/sequential_times.txt");

    // Start equalization
    for (int i=0; i<count; i++) {

        string img_name = to_string(i);
        ofstream spt("../speedup/sequential_times_for_speedup"  + img_name +".txt");

        for (int j = 0; j < g; j++) {
            // Image reading
            Mat image = imread(fn[i]);
            if (j>0) {

                //We used these functions to varying the size of the same size
                resize(image, image, Size(image_sizes[j],image_sizes[j]));
                //imshow("Original Image", image);

                // If resizing is set, check if the directory "resizedtestImage"  is already created
                // Otherwise create it
                ifstream f(test_dir_path);
                if (f.good() == false){
                    mkdir(test_dir_path,0777);
                }
                imwrite(_p+"/"+img_name+ "_" + to_string(image_sizes[j]) + "x" + to_string(image_sizes[j]) + ".jpg", image);
            }
            struct timeval start, end;
            gettimeofday(&start, NULL);

            // For big image dimension is required to allocate array for avoid the segmentation fault
            int *yuv_vector = new int[image.rows * image.cols * 3];

            // Making the histogram
            int histogram[256];
            make_histogram(image, histogram, yuv_vector);

            // Making the equalized histogram
            int equalized[256];

            cumulative_hist(histogram, equalized, image.cols, image.rows);

            equalization(image, equalized, yuv_vector);

            gettimeofday(&end, NULL);
            double elapsed_time = ((end.tv_sec - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
            string width = to_string(image.cols);
            string height = to_string(image.rows);

            //save result
            cout << "current size" << width << "x" << height << endl;
            cout << elapsed_time << endl;
            string _t = to_string(elapsed_time);
            out << "image" << img_name << " "<< width << "x" << height << endl;
            out << _t << endl;
            if (j>0){
                spt << _t << endl;
            }


            // Display equalized image
            //resize(image, image, Size(500,500));
            //imshow("Equalized Image", image);
            imwrite("../eq/test_" + img_name + "_" + width + "x" + height + ".jpg", image);
            //waitKey(0);
        }

    }
    return 0;
}
