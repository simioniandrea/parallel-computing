#include <omp.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include "histogram.cpp"
#include "equalization.cpp"
#include <fstream>
#include <sys/stat.h>


using namespace std;
using namespace cv;
int main(){

    // For change the threads number
    int n_thread = 8;
    //omp_set_dynamic(0);     // Explicitly disable dynamic teams
    omp_set_num_threads(n_thread); // Use 4 threads for all consecutive parallel regions

    // Paths to save the resized and equalized test images
    const char *test_dir_path = "../resizedtestImage";
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
    vector<cv::String> fn;
    // Take the images from the directory. Use .jpg format
    glob("../img/*.jpg", fn, false);
    size_t count = fn.size();
    // Resize dimension vector, 0 is referred to the original size of images. Use the second vector to avoid resizing
    vector<int> image_sizes = {0,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000};
    //vector<int> image_sizes = {0}
    size_t g = image_sizes.size();
    
    // Txt file to save result
    ofstream out("../eq/parallel_times.txt");
    
    
    // Start equalization
    for (int i=0; i<count; i++)
    {
        string img_name = to_string(i);
        ofstream spt("../speedup/parallel_times_for_speedup"  + img_name +".txt");
        for (int j = 0; j < g; j++) {
            Mat image = imread(fn[i]);
            if (j > 0) {
                resize(image, image, Size(image_sizes[j], image_sizes[j]));
                //imshow("Original Image", image);
                //waitKey(0);
                // If resizing is set, check if the directory "resizedtestImage"  is already created
                // Otherwise create it
                ifstream f(test_dir_path);
                if (!f.good()) {
                    mkdir(test_dir_path, 0777);
                }
                imwrite(_p + "/" + img_name + "_" + to_string(image_sizes[j]) + "x" + to_string(image_sizes[j]) +
                        ".jpg", image);
            }
            double start = omp_get_wtime();

            int *yuv_vector = new int[image.rows * image.cols * 3];

            // Generate the histogram
            int histogram[256];
            make_histogram(image, histogram, yuv_vector);

            // Generate the equalized histogram
            int equalized_h[256];

            cumulative_hist(histogram, equalized_h, image.cols, image.rows);

            equalization(image, equalized_h, yuv_vector);

            double end = omp_get_wtime();

            // Display equalized image
            //Mat image_for_display = image;
            //resize(image_for_display, image_for_display, Size(600, 450)); //in case of loadind different images, show the resized output
            //imshow("Equalized Image", image_for_display);
            string width = to_string(image.cols);
            string height = to_string(image.rows);
            
            
            // Save Result
            cout << "current size" << width << "x" << height << endl;
            cout << end - start << endl;
            string _t = to_string(end - start);
            out << "image" << img_name <<" "<< width << "x" << height << endl;
            out << _t << endl;
            if (j >0){
                spt << _t << endl;
            }
            imwrite("../eq/test_" + img_name + "_" + width + "x" + height + ".jpg",
                    image);
            //waitKey(0);
        }

    }
    return 0;
}
