#ifndef COMMON_H
#define COMMON_H

#include "mnistloader/mnistloader.h"

#include "preprocessing/preprocessingimage.h"

#include "recognizer/recognizer.h"
#include "recognizer/knearestneighbors.h"
#include "recognizer/neuralnetwork.h"

#include "featureextraction/pixelfeature/pixelfeature.h"
#include "featureextraction/statisticalfeatures/statisticalfeature.h"
#include "featureextraction/featuresetextractor.h"
#include "featureextraction/boundaryfeature/boundaryfeature.h"

#include "validator/validator.h"

#include <string>
#include <vector>
#include <iostream>
#include <cmath>

#include <opencv2/opencv.hpp>

#define IMAGE_COUNT 60000
#define TEST_IMAGE_COUNT 10000
#define SMALL_IMAGE_COUNT 2000


#endif // COMMON_H
