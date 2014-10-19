

#define LOG_TAG "OpenGlGame"

#ifdef __ANDROID__

#include <android/log.h>

#define  LogDebug(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LogError(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#endif