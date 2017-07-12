package org.linux.jniexample.utils;


import android.util.Log;

public class NativeUtil {
    static {
        System.loadLibrary("native_util");
    }
    public static int add(int x,int y){
        return nativeAdd(x,y);
    }

    public static native int nativeAdd(int x,int y);
}
