#ifndef SNNFUNCTION
#define SNNFUNCTION

#include <cmath>
#include "snndata.h"

// Activation Functions and their Derivatives
#define sigmoid_func(sum) ((snn_type) (1.0 / (1.0 + exp(-sum))))
#define sigmoid_deri_func(input) ((snn_type) (input * (1.0 - input)))

// cost function
#define softmax_func(curr, sum) ((snn_type) (exp(curr) / sum))

#define mean_square_error_func(target, output) ((snn_type) (0.5 * (target - output) * (target - output)))
#define mean_square_error_deri_func(target, output) ((snn_type) (output - target))

#define cross_entropy_func(target, output) ((snn_type) ((target == (snn_type) 0) ? 0 : -(target * log(output))))
#define cross_entropy_deri_func(target, output) ((snn_type) (output - target))

// other functions
#define mean_absolute_error_func(target, output) ((snn_type) fabs(target - output))

#endif // SNNFUNCTION

