#ifndef MOMENT_H
#define MOMENT_H

#include "histogrambaseddescriptor.h"

class Moment : public HistogramBasedDescriptor
{
private:
    std::vector<int> nthMoments;

public:
    /*
    * count: so luong moment ma muon xuat ra
    * vi du: count = 5 thi se xuat ra moment tu 2 -> 5
    */
    Moment(int count);

    /*
    * moments: nhung moment ma muon xuat ra
    * vi du moments = {1, 3, 5} thi chi tinh moment 1, 3, 5
    */
    Moment(const std::vector<int>& moments);
    ~Moment();

    int getFeatureCount() const override {return nthMoments.size();}
    std::vector<val_type> extractFeature(const cv::Mat &image) const override;
    std::vector<val_type> extractFeature(const val_type* histogram) const override;
};

#endif // MOMENT_H
