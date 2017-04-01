#include "PriceTagLocalizer.h"

preprocessing::OrientationCorrector * preprocessing::OrientationCorrector::createOrientationCorrector(
        OrientationCorrectorId id) {
    OrientationCorrector *corrector;
    switch (id) {
        case HistogramId:
            corrector = new HistogrammOrientationCorrector();
            break;
        default:
            assert(false);
    }
    return corrector;
}

cv::Mat preprocessing::HistogrammOrientationCorrector::correct(cv::Mat image) {
    return image;
}

preprocessing::HistogrammOrientationCorrector::~HistogrammOrientationCorrector() {

}

SimplePriceTagLocalizer::SimplePriceTagLocalizer() {

}

SimplePriceTagLocalizer::~SimplePriceTagLocalizer() {

}

PriceTagLocalizer* PriceTagLocalizer::createPriceTagLocalizer(PriceTagLocalizerId id) {
    PriceTagLocalizer *localizer;
    switch (id) {
        case SimplePriceTagLocalizerId :
            localizer = new SimplePriceTagLocalizer();
            break;
        default:
            assert(false);
    }
    return localizer;
}

void SimplePriceTagLocalizer::localize(cv::Mat image) {

}