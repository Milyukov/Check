#include <jni.h>
#include <string>
#include "PriceTagLocalizer.h"
#include "TextRecognizer.h"

#include <android/log.h>
#include <android/bitmap.h>

#define  LOG_TAG    "priceTagParser"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

using namespace preprocessing;

extern "C"
JNIEXPORT void JNICALL
Java_com_lab_1in_1the_1pocket_totalcheque_MainActivity_getPriceTagInfo(
        JNIEnv *env,
        jobject obj,
        jobject bitmap) {

    AndroidBitmapInfo  info;
    void*              pixels;
    int                ret;

    try {

        if ((ret = AndroidBitmap_getInfo(env, bitmap, &info)) < 0) {
            LOGE("AndroidBitmap_getInfo() failed ! error=%d", ret);
            return;
        }

        if (info.format != ANDROID_BITMAP_FORMAT_RGB_565) {
            LOGE("Bitmap format is not RGB_565 !");
            return;
        }

        if ((ret = AndroidBitmap_lockPixels(env, bitmap, &pixels)) < 0) {
            LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
        }

        uint16_t *data = (uint16_t *) pixels;

        // process
        cv::Mat image = cv::Mat(info.height, info.width, CV_8UC4, data);

        // preprocessing
        OrientationCorrector *corrector = OrientationCorrector::createOrientationCorrector(
                OrientationCorrectorId::HistogramId);
        corrector->correct(image);

        // localizing
        PriceTagLocalizer *priceTagLocalizer = PriceTagLocalizer::createPriceTagLocalizer(
                PriceTagLocalizerId::SimplePriceTagLocalizerId);
        priceTagLocalizer->localize(image);
        std::vector<cv::Mat> areas = priceTagLocalizer->getRegions();

        // Text detection and recognition
        TextDetector *textDetector = TextDetector::createTextDetector(
                TextDetectorId::SimpleTextDetectorId);
        TextRecognizer *textRecognizer = TextRecognizer::createTextRecognizer(
                TextRecognizerId::SimpleTextRecognizerId);
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

        AndroidBitmap_unlockPixels(env, bitmap);
    }
    catch (...) {

    }
    return;
}