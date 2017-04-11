#include "PriceTagLocalizer.h"
#include "TextRecognizer.h"

using namespace preprocessing;

int main() {
    try {
        cv::Mat image = cv::imread("/home/gleb/Документы/Check/PriceTagParserLib/build/Test.jpg");
        // preprocessing
        OrientationCorrector *corrector = OrientationCorrector::createOrientationCorrector(OrientationCorrectorId::HistogramId);
        corrector->correct(image);

        // localizing
        PriceTagLocalizer* priceTagLocalizer = PriceTagLocalizer::createPriceTagLocalizer(PriceTagLocalizerId::SimplePriceTagLocalizerId);
        priceTagLocalizer->localize(image);
        std::vector<cv::Mat> areas = priceTagLocalizer->getRegions();

        // Text detection and recognition
        TextDetector *textDetector = TextDetector::createTextDetector(TextDetectorId::SimpleTextDetectorId);
        TextRecognizer *textRecognizer = TextRecognizer::createTextRecognizer(TextRecognizerId::SimpleTextRecognizerId);
        // for all the regions of interest
        for (int areaNum = 0; areaNum < areas.size(); areaNum++) {
            // detect text
            textDetector->detect(areas[areaNum]);
            // for every word
            std::vector<cv::Mat> words = textDetector->getWords();
            for (int wordNum = 0; wordNum < words.size(); wordNum++) {
                // recognize text
                textRecognizer->recognize(words[wordNum]);
                textRecognizer->getWord();
            }
        }

        //cv::Mat resultingImage = localizer->visualize(image);
        //cv::imshow("Detected regions of interest", resultingImage);
    }
    catch (cv::Exception e) {
        std::cout << "!!!\n";
        std::cout << e.what() << std::endl;
    }
	return 0;
}
