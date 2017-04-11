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
#if Build_For_ANDROID
#else
    LOG(INFO) << TAG + ": ~HistogrammOrientationCorrector";
#endif
}

cv::Mat preprocessing::rgb2gray(cv::Mat image) {
#if Build_For_ANDROID
#else
    LOG(INFO) << TAG + ": rgb2gray";
#endif
    cv::Mat gray;
    if (image.channels() == 3) {
        cv::cvtColor(image, gray, cv::COLOR_RGB2GRAY);
    }
    return gray;
}

cv::Mat preprocessing::binarize(cv::Mat image) {
#if Build_For_ANDROID
#else
    LOG(INFO) << TAG + ": binarize";
#endif
    cv::Mat binarizedIm;
    cv::threshold(image, binarizedIm, 60, 255, cv::THRESH_BINARY_INV);
    return binarizedIm;
}

cv::Mat preprocessing::dilate(cv::Mat image, int kernelSize) {
#if Build_For_ANDROID
#else
    LOG(INFO) << TAG + ": dilate";
#endif
    // assertion
    cv::Mat dilatedIm;
    cv::Mat kernel(kernelSize, kernelSize, CV_8UC1, cv::Scalar(1));
    cv::dilate(image, dilatedIm, kernel, cv::Point(-1, -1), 3);
    return dilatedIm;
}

cv::Mat preprocessing::removeNoise(cv::Mat image, int kernelSize) {
#if Build_For_ANDROID
#else
    LOG(INFO) << TAG + ": removeNoise";
#endif
    // assertion
    cv::Mat denoisedIm;
    cv::Mat kernel(kernelSize, kernelSize, CV_8UC1, cv::Scalar(1));
    cv::erode(image, denoisedIm, kernel, cv::Point(-1, -1), 3);
    cv::dilate(denoisedIm, denoisedIm, kernel, cv::Point(-1, -1), 3);
    return denoisedIm;
}

cv::Mat preprocessing::findMaximalAbsoluteGradientSum(cv::Mat image, cv::Mat regions) {
#if Build_For_ANDROID
#else
    LOG(INFO) << TAG + ": findMaximalAbsoluteGradientSum";
#endif
    int numberOfRegions, minimum, maximalRegionId = 0;
    double maximum = 0;
    std::vector<double> sumsOfAbsGrad;
    cv::minMaxLoc(regions, 0, &maximum);
    numberOfRegions = (int)maximum;
    maximum = 0;
    cv::Mat gradientMapX, gradientMapY;
    cv::Sobel(image, gradientMapX, CV_64F, 1, 0);
    cv::Sobel(image, gradientMapY, CV_64F, 0, 1);
    cv::Mat gradientAbs(gradientMapX.rows, gradientMapX.cols, gradientMapX.type());
    cv::magnitude(gradientMapX, gradientMapY, gradientAbs);
    for (int regionNumber = 1; regionNumber < numberOfRegions + 1; regionNumber++) {
        //cv::Mat temp = gradientAbs;
        //temp.setTo(cv::Scalar(0), regions != regionNumber);
        sumsOfAbsGrad.push_back(cv::mean(gradientAbs, regions == regionNumber)[0]);
        //std::cout << sumsOfAbsGrad[regionNumber - 1] << std::endl;
        if (sumsOfAbsGrad[regionNumber - 1] > maximum) {
            maximum = sumsOfAbsGrad[regionNumber - 1];
        }
    }
    for (int regionNumber = 1; regionNumber < numberOfRegions + 1; regionNumber++) {
        if (sumsOfAbsGrad[regionNumber - 1] < maximum * 0.4)
            regions.setTo(cv::Scalar(0), regions == regionNumber);
    }
    return regions;
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
#if Build_For_ANDROID
#else
    LOG(INFO) << "localize";
#endif
    cv::Mat mask, gray;
    gray = preprocessing::rgb2gray(image);
    // Binarization
    // Choose threshold
    mask = preprocessing::binarize(gray);
    // Removing of noise
    mask = preprocessing::removeNoise(mask, 5);
    // Dilation
    // Choose kernel size
    mask = preprocessing::dilate(mask, 30);
    // Localization
    // Marker labelling
    cv::Mat markers;
    cv::connectedComponents(mask, markers);
    // Maximal sum of gradient absolute value
    markers = preprocessing::findMaximalAbsoluteGradientSum(gray, markers);
    //
    double maximum;
    cv::minMaxLoc(markers, 0, &maximum);
    int numberOfRegions = (int)maximum;
    for (int regionNumber = 0; regionNumber < numberOfRegions; regionNumber++) {
        cv::Mat region(markers.rows, markers.cols, markers.type(), cv::Scalar(0));
        region.setTo(cv::Scalar(1), markers == regionNumber + 1);
        regions.push_back(region);
    }
    // visualization
    //cv::Mat addition = cv::Mat(image.rows, image.cols, image.type(), cv::Scalar(0, 0, 0));
    //addition.setTo(cv::Scalar(0, 40, 0), markers != 0);
    //image += addition;

    //cv::imwrite("test_seg.jpg", image);

}

cv::Mat SimplePriceTagLocalizer::visualize(cv::Mat image) {
    /*std::vector<cv::Point[2]> coordinates = getCoordinates();
    for (int regionId = 0; regionId < coordinates.size(); regionId++) {
        cv::rectangle(image, coordinates[regionId][0], coordinates[regionId][1], cv::Scalar(0, 255, 0));
    }*/
    return image;
}