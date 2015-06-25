//////////////////////////////////////////////////////////////////////
// TTS = Text To Speech
//////////////////////////////////////////////////////////////////////

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/UIEditBox/UIEditBox.h"

USING_NS_CC;
using namespace ui;

class HelloWorld : public cocos2d::Layer
{
public:
	static HelloWorld* getInstance();
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(HelloWorld);
    
	void menuCloseCallback(cocos2d::Ref* pSender);
	void selectLanguage(Ref* pSender, int languageIndex);
    void jni_callVoidSpeechString(const char* speechString);


    int getLanguageIndexC();


    ui::EditBox* inputBox;
    const char* inputText;

    int _languageIndex = 1;

private:
	LabelTTF* languageSelected;
};

#endif // __HELLOWORLD_SCENE_H__
