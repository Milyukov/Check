#include "PriceTagLocalizer.h"
#include "TextRecognizer.h"
#include "dirent.h"
INITIALIZE_EASYLOGGINGPP

using namespace preprocessing;

int main() {
    try {

        DIR *dir;
        struct dirent *ent;
        std::string path = "/home/gleb/Документы/Check/PriceTagParserLib/build/photos/";
        if ((dir = opendir (path.c_str())) != NULL) {
            /* print all the files and directories within directory */
            while ((ent = readdir (dir)) != NULL) {
                if (std::strcmp(ent->d_name, ".") == 0 || std::strcmp(ent->d_name, "..") == 0) continue;
                printf ("%s\n", ent->d_name);
                cv::Mat image = cv::imread(path + std::string(ent->d_name));
                // preprocessing
                OrientationCorrector *corrector = OrientationCorrector::createOrientationCorrector(OrientationCorrectorId::HistogramId);
                image = corrector->correct(image);

                // localizing
                PriceTagLocalizer* priceTagLocalizer = PriceTagLocalizer::createPriceTagLocalizer(PriceTagLocalizerId::SimplePriceTagLocalizerId);
                priceTagLocalizer->localize(image);
                std::string filename = "visualized_" + std::string(ent->d_name);
                cv::imwrite(path + filename, priceTagLocalizer->visualize(image));
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
                    words.clear();
                }
                image.release();
                delete textDetector;
                delete textRecognizer;
                delete corrector;
                delete priceTagLocalizer;
                //cv::Mat resultingImage = localizer->visualize(image);
                //cv::imshow("Detected regions of interest", resultingImage);
            }
            closedir (dir);
        } else {
            /* could not open directory */
            perror ("Error!");
            return EXIT_FAILURE;
        }
    }
    catch (cv::Exception e) {
        std::cout << "!!!\n";
        std::cout << e.what() << std::endl;
    }
	return 0;
}
