#include <jni.h>
#include <string>
#include "LabelLocalizer.h"

#include <android/log.h>
#include <android/bitmap.h>

#define  LOG_TAG    "labelparser"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

extern "C"
JNIEXPORT void JNICALL
Java_com_lab_1in_1the_1pocket_totalcheque_MainActivity_getPriceTagInfo(
        JNIEnv *env,
        jobject obj,
        jobject bitmap) {

    AndroidBitmapInfo  info;
    void*              pixels;
    int                ret;

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

    uint16_t *data = (uint16_t *)pixels;

    // process
    cv::Mat image = cv::Mat(info.height, info.width, CV_8UC4, pixels);

    AndroidBitmap_unlockPixels(env, bitmap);

    return;
}