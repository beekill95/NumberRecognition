#ifndef MNISTLOADER_H
#define MNISTLOADER_H

// read MNIST data into double vector, OpenCV Mat, or Armadillo mat
// free to use this code for any purpose
// author : Eric Yuan
// my blog: http://eric-yuan.me/
// part of this code is stolen from http://compvisionlab.wordpress.com/

#include "opencv2/core/core.hpp"

#include <string>
#include <vector>

void read_Mnist(const std::string& filename, std::vector<std::vector<float> > &vec);
void read_Mnist(const std::string& filename, std::vector<cv::Mat> &vec);

void read_Mnist_Label(const std::string& filename, std::vector<float> &vec);

/**
* Sample code
*/
//int main()
//{
//    string filename = "mnist/t10k-images-idx3-ubyte";
//    int number_of_images = 10000;
//    int image_size = 28 * 28;


//    //read MNIST iamge into Armadillo mat vector
//    vector<arma::mat> vec;
//    read_Mnist(filename, vec);
//    cout<<vec.size()<<endl;
//    cout<<vec[0].size()<<endl;
//    cout<<vec[0]<<endl;

//    //read MNIST iamge into OpenCV Mat vector
//    vector<cv::Mat> vec;
//    read_Mnist(filename, vec);
//    cout<<vec.size()<<endl;
//    imshow("1st", vec[0]);
//    waitKey();

//    //read MNIST iamge into double vector
//    vector<vector<double> > vec;
//    read_Mnist(filename, vec);
//    cout<<vec.size()<<endl;
//    cout<<vec[0].size()<<endl;


//    string filename = "mnist/t10k-labels-idx1-ubyte";
//    int number_of_images = 10000;


//    //read MNIST label into double vector
//    vector<double> vec(number_of_images);
//    read_Mnist_Label(filename, vec);
//    cout<<vec.size()<<endl;

//    //read MNIST label into armadillo colvec
//    //if you want rowvec, just use .t()
//    arma::colvec vec = arma::zeros<arma::colvec>(number_of_images);
//    read_Mnist_Label(filename, vec);
//    cout<<vec.size()<<endl;
//    return 0;
//}

#endif // MNISTLOADER_H
