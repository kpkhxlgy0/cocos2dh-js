package org.cocos2dxh.lib;

import java.util.UUID;

import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Vibrator;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

public class Cocos2dxhHelper {
    public static String generateUuid() {
        UUID uuid = UUID.randomUUID();
        String uniqueId = uuid.toString();
        return uniqueId;
    }
    public static String getOpenUDID() {
        return OpenUDID_manager.getOpenUDID();
    }
    public static void vibrate() {
        /* 
         * 想设置震动大小可以通过改变pattern来设定，如果开启时间太短，震动效果可能感觉不到 
         * */  
    	Vibrator vibrator = (Vibrator)Cocos2dxActivity.getContext().getSystemService(Context.VIBRATOR_SERVICE);  
        long [] pattern = {100,400,100,400};   // 停止 开启 停止 开启   
        vibrator.vibrate(pattern,2);           //重复两次上面的pattern 如果只想震动一次，index设为-1
    }
    public static void loadURL(String INurl) {
    	final String url = INurl;
    	Cocos2dxGLSurfaceView.getInstance().queueEvent(new Runnable() {
			@Override
			public void run() {
				Intent intent = new Intent(Intent.ACTION_VIEW, Uri.parse(url));
		    	Cocos2dxActivity.getContext().startActivity(intent);
			}
		});
    }
}
