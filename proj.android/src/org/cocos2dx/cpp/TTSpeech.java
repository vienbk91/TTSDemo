package org.cocos2dx.cpp;

import java.util.Locale;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.speech.tts.TextToSpeech;
import android.speech.tts.TextToSpeech.OnInitListener;
import android.util.Log;

public class TTSpeech extends Activity implements OnInitListener {
	
	private TextToSpeech texttospeech = null;
	public int _languageIndex;
	
	public TTSpeech(Context context){
		super();
		if(texttospeech == null){
			texttospeech = new TextToSpeech(context, this);
		}
	}
	
	

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
	}

	@Override
	public void onInit(int status) {
		// TODO Auto-generated method stub
		
	}
	
	public static native int getLanguageIndex();
	
	public void SpeekString(String string){
		//_languageIndex = getLanguageIndex();
		Log.d("==========LanguageIndex=============" , _languageIndex + "");
		if(!texttospeech.isSpeaking()){
			
			switch(2) // _languageIndex
			{
			case 1:
				texttospeech.setLanguage(Locale.US);
				break;
			case 2: 
				texttospeech.setLanguage(Locale.JAPANESE);
				break;
			default :
				texttospeech.setLanguage(Locale.US);
				break;
			}
			
			texttospeech.setPitch((float)1.2);
			texttospeech.setSpeechRate(1);
			texttospeech.speak(string, TextToSpeech.QUEUE_FLUSH, null);
		}
	}
}
