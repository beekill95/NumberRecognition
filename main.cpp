#include "mnistloader/mnistloader.h"

#include <string>
#include <vector>
#include <iostream>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    {
        string filename = "data/train-images.idx3-ubyte";
        //read MNIST iamge into OpenCV Mat vector
        std::vector<cv::Mat> vec;
        read_Mnist(filename, vec);
        std::cout << vec.size()<<endl;
        imshow("1st", vec[0]);
        waitKey();
    }

    {
        string filename = "data/train-labels.idx1-ubyte";
        int number_of_images = 60000;

        //read MNIST label into double vector
        vector<double> vec(number_of_images);
        read_Mnist_Label(filename, vec);
        cout<<vec.size()<<endl;

        for (auto it = vec.cbegin(); it != vec.cend(); ++it) {
            cout << '\n' << *it;
        }
    }

    return 0;
}

