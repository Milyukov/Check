#include "PriceTagLocalizer.h"
#if Build_For_ANDROID
#else
#include "easylogging++.h"
INITIALIZE_EASYLOGGINGPP
#endif

preprocessing::OrientationCorrector * preprocessing::OrientationCorrector::createOrientationCorrector(
        OrientationCorrectorId id) {
#if Build_For_ANDROID
#else
    LOG(INFO) << TAG + ": createOrientationCorrector";
#endif
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

#if Build_For_ANDROID
#else
    LOG(INFO) << TAG + ": correct";
#endif
    return image;
}

preprocessing::HistogrammOrientationCorrector::~HistogrammOrientationCorrector() {

}

SimplePriceTagLocalizer::SimplePriceTagLocalizer() {

}

SimplePriceTagLocalizer::~SimplePriceTagLocalizer() {

}

PriceTagLocalizer* PriceTagLocalizer::createPriceTagLocalizer(PriceTagLocalizerId id) {
#if Build_For_ANDROID
#else
    LOG(INFO) << "createPriceTagLocalizer";
#endif
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