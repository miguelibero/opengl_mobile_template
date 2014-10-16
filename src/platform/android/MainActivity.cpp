#include <jni.h>
#include <memory>
#include "game/Application.hpp"

Application app;
 
JNIEXPORT void JNICALL Java_MainActivity_onSurfaceCreated(JNIEnv * env, jclass cls) {
	app.load();
}
 
JNIEXPORT void JNICALL Java_MainActivity_onSurfaceChanged(JNIEnv * env, jclass cls, jint width, jint height) {

}
 
JNIEXPORT void JNICALL Java_MainActivity_onDrawFrame(JNIEnv * env, jclass cls) {
	double dt = 0;
	app.update(dt);
}