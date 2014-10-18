#include <jni.h>
#include <memory>
#include "game/Application.hpp"
#include "platform/android/JniObject.hpp"
#include "base/Log.hpp"

Application app;

extern "C" {

	JNIEXPORT void JNICALL Java_com_openglgame_MainActivity_onSurfaceCreated(JNIEnv * env, jclass cls) {
		app.load();
	}
	 
	JNIEXPORT void JNICALL Java_com_openglgame_MainActivity_onSurfaceChanged(JNIEnv * env, jclass cls, jint width, jint height) {

	}
	 
	JNIEXPORT void JNICALL Java_com_openglgame_MainActivity_onDrawFrame(JNIEnv * env, jclass cls, jdouble dt) {
		app.update(dt);
	}

	jint JNI_OnLoad(JavaVM *vm, void *reserved)
	{
		LogDebug("JNI_OnLoad");
		Jni::get().setJava(vm);
	    return JNI_VERSION_1_4;
	}

}