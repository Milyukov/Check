#include "GlobalParameters.h"

enum PriceTagLocalizerId { SimplePriceTagLocalizerId = 0 };

namespace preprocessing {
    const std::string TAG = "preprocessing";

    enum OrientationCorrectorId { HistogramId = 0 };
    class OrientationCorrector {
    public:
        virtual cv::Mat correct(cv::Mat image) = 0;
        static OrientationCorrector* createOrientationCorrector(OrientationCorrectorId id);
        virtual ~OrientationCorrector() {};
    };

    class HistogrammOrientationCorrector : public OrientationCorrector {
    public:
        cv::Mat correct(cv::Mat image);
        ~HistogrammOrientationCorrector();
    };

    cv::Mat rgb2gray(cv::Mat image);

    cv::Mat binarize(cv::Mat image);

    cv::Mat removeNoise(cv::Mat image, int kernelSize);

    cv::Mat dilate(cv::Mat image, int kernelSize);

    cv::Mat findMaximalAbsoluteGradientSum(cv::Mat image, cv::Mat regions);

}

class PriceTagLocalizer {
public:
    PriceTagLocalizer() {};
    ~PriceTagLocalizer() {};
    virtual void localize(cv::Mat image) = 0;
    virtual cv::Mat visualize(cv::Mat image) = 0;
    static PriceTagLocalizer* createPriceTagLocalizer(PriceTagLocalizerId id);
    std::vector<cv::Mat> getRegions() {
        return regions;
    };
    //std::vector<cv::Point[2]> getCoordinates() { return coordinates; };

protected:
    //std::vector<cv::Point[2]> coordinates;
    std::vector<cv::Mat> regions;
};

class SimplePriceTagLocalizer : public PriceTagLocalizer {
public:
    SimplePriceTagLocalizer();
    ~SimplePriceTagLocalizer();
    void localize(cv::Mat image);
    cv::Mat visualize(cv::Mat image);
};