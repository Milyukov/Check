#include "TextRecognizer.h"

SimpleTextDetector::SimpleTextDetector() {

}

SimpleTextDetector::~SimpleTextDetector() {
    for (int i = 0; i < words.size(); i++) {
        words[i].release();
    }
    words.clear();
}

TextDetector* TextDetector::createTextDetector(TextDetectorId id) {
#if Build_For_ANDROID
#else
    LOG(INFO) << ": createTextDetector";
#endif
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
    TextRecognizer *recognizer = new SimpleTextRecognizer();
    return recognizer;
}