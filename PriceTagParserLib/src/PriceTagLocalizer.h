#include "GlobalParameters.h"

enum PriceTagLocalizerId { SimplePriceTagLocalizerId = 0 };

namespace preprocessing {
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
}

class PriceTagLocalizer {
public:
    PriceTagLocalizer() {};
    virtual ~PriceTagLocalizer() {};
    virtual void localize(cv::Mat image) = 0;
    static PriceTagLocalizer* createPriceTagLocalizer(PriceTagLocalizerId id);
    std::vector<cv::Mat> getRegions() { return regionsOfInterest;};
    std::vector<int[4]> getCoordinates() { return coordinates; };

private:
    std::vector<cv::Mat> regionsOfInterest;
    std::vector<int[4]> coordinates;
};

class SimplePriceTagLocalizer : public PriceTagLocalizer {
public:
    SimplePriceTagLocalizer();
    ~SimplePriceTagLocalizer();
    void localize(cv::Mat image);
};