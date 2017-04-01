#include "GlobalParameters.h"

enum TextDetectorId { SimpleTextDetectorId = 0 };
enum TextRecognizerId { SimpleTextRecognizerId = 0 };

class TextDetector {
public:
    TextDetector() {};
    virtual ~TextDetector() {};
    virtual void detect(cv::Mat area) = 0;

    static TextDetector* createTextDetector(TextDetectorId id);

    std::vector<cv::Mat> getWords() { return words; };
private:
    std::vector<cv::Mat> words;
};

class TextRecognizer {
public:
    virtual ~TextRecognizer() {};
    virtual void recognize(cv::Mat word) = 0;
    static TextRecognizer* createTextRecognizer(TextRecognizerId id);
    std::string getWord() { return word; };
private:
    std::string word;
};

class SimpleTextDetector : public TextDetector {
public:
    SimpleTextDetector();
    ~SimpleTextDetector();
    void detect(cv::Mat area);
};