#include "TextRecognizer.h"

SimpleTextDetector::SimpleTextDetector() {

}

SimpleTextDetector::~SimpleTextDetector() {

}

TextDetector* TextDetector::createTextDetector(TextDetectorId id) {
    TextDetector *detector;
    switch (id) {
        case SimpleTextDetectorId:
            detector = new SimpleTextDetector();
            break;
        default:
            assert(false);
    }
    return detector;
}

void SimpleTextDetector::detect(cv::Mat area) {

}

TextRecognizer* TextRecognizer::createTextRecognizer(TextRecognizerId id) {
    TextRecognizer *recognizer;
    return recognizer;
}