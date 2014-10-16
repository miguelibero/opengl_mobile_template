
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

public class MainActivity extends Cocos2dxActivity
{
	private GLSurfaceView glSurfaceView;
	private boolean rendererSet;


	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);

		ActivityManager activityManager = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
    	ConfigurationInfo configurationInfo = activityManager.getDeviceConfigurationInfo();
 
    	final boolean supportsEs2 =
        	configurationInfo.reqGlEsVersion >= 0x20000 || isProbablyEmulator();
 
	    if (supportsEs2) {
	        glSurfaceView = new GLSurfaceView(this);
	 
	        if (isProbablyEmulator()) {
	            // Avoids crashes on startup with some emulator images.
	            glSurfaceView.setEGLConfigChooser(8, 8, 8, 8, 16, 0);
	        }
	 
	        glSurfaceView.setEGLContextClientVersion(2);
	        glSurfaceView.setRenderer(new Renderer());
	        rendererSet = true;
	        setContentView(glSurfaceView);
	    } else {
	        // Should never be seen in production, since the manifest filters
	        // unsupported devices.
	        Toast.makeText(this, "This device does not support OpenGL ES 2.0.",
	                Toast.LENGTH_LONG).show();
	        return;
	    }
	}

	private boolean isProbablyEmulator() {
    	return Build.VERSION.SDK_INT >= Build.VERSION_CODES.ICE_CREAM_SANDWICH_MR1
            && (Build.FINGERPRINT.startsWith("generic")
                    || Build.FINGERPRINT.startsWith("unknown")
                    || Build.MODEL.contains("google_sdk")
                    || Build.MODEL.contains("Emulator")
                    || Build.MODEL.contains("Android SDK built for x86"));
	}

	@Override
	public void onResume() {
		super.onResume();
		if (rendererSet) {
        	glSurfaceView.onResume();
    	}
	}

	@Override
	public void onPause() {
		super.onPause();
		if (rendererSet) {
        	glSurfaceView.onPause();
    	}
	}

	@Override
	public void onDestroy() {
		super.onDestroy();
	}

	@Override
	public void onSaveInstanceState(Bundle outState) {
		super.onSaveInstanceState(outState);
	}

	@Override
	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);
	}

    static {
    	System.loadLibrary("gnustl_shared");
		System.loadLibrary("app");
    }

    public static native void onSurfaceCreated();
    public static native void onSurfaceChanged(int width, int height);
    public static native void onDrawFrame();
}
