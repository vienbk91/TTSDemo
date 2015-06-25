#include "HelloWorldScene.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "jni.h"
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>

#endif


USING_NS_CC;
using namespace std;
using namespace ui;

static HelloWorld* _helloWorld = nullptr;

HelloWorld* HelloWorld::getInstance(){
	if(!_helloWorld){
		_helloWorld = new (std::nothrow) HelloWorld();
		_helloWorld->init();
	}

	return _helloWorld;
}

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}


bool HelloWorld::init()
{

    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	////////////////////////////////////////////////////////////////
	// CREATE COMBOBOX
	// Combobox khong duoc cocos2dx suport nen se phai tu xay dung
	////////////////////////////////////////////////////////////////

	auto englishItem = MenuItemImage::create("selectLang1.png", "selectLang1.png", CC_CALLBACK_1(HelloWorld::selectLanguage, this , 1));
	englishItem->setScale(2.0);
	englishItem->setPosition(Vec2(origin.x + englishItem->getContentSize().width / 2 + 140, origin.y + visibleSize.height/2  + englishItem->getContentSize().height / 2 + 50));

	auto japaneseItem = MenuItemImage::create("selectLang2.png", "selectLang2.png", CC_CALLBACK_1(HelloWorld::selectLanguage, this , 2));
	japaneseItem->setScale(2.0);
	japaneseItem->setPosition(Vec2(origin.x + japaneseItem->getContentSize().width / 2 + 140, origin.y + visibleSize.height / 2 - japaneseItem->getContentSize().height / 2 - 50));

	auto menuLanguage = Menu::create(englishItem , japaneseItem , NULL);
	menuLanguage->setPosition(Vec2::ZERO);
	this->addChild(menuLanguage , 1);
	


    ////////////////////////////////////////////////////////////////
    // CREATE BUTTON
    ////////////////////////////////////////////////////////////////
    auto speakItem = MenuItemImage::create( "speak.png", "speak.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	speakItem->setScale(2.0);
	speakItem->setPosition(Vec2(origin.x + visibleSize.width - speakItem->getContentSize().width/2 - 100, origin.y + speakItem->getContentSize().height/2 + 50));
	
	auto menu = Menu::create(speakItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	////////////////////////////////////////////////////////////////
	// CREATE INPUT EDITBOX
	////////////////////////////////////////////////////////////////

	Size editBoxSize = Size(visibleSize.width * 2/3  , visibleSize.height * 2/3 - 100 );
	inputBox = EditBox::create(editBoxSize, Scale9Sprite::create("input.png"));
	inputBox->setPosition(Vec2(origin.x + visibleSize.width / 2 + 200, speakItem->getPositionY() + inputBox->getContentSize().height / 2 + 100));
	inputBox->setFontName("Arial");
	inputBox->setFontSize(50);
	inputBox->setFontColor(Color3B::RED);
	inputBox->setPlaceHolder("Input Form");
	inputBox->setPlaceholderFontColor(Color3B::WHITE);
	inputBox->setMaxLength(100);
	inputBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	this->addChild(inputBox);

	
	////////////////////////////////////////////////////////////////
	// CREATE LANGUAGE LABEL
	////////////////////////////////////////////////////////////////

	LabelTTF* languageTitle = LabelTTF::create("Language : ", "fonts/arial.ttf", 50, Size::ZERO, TextHAlignment::CENTER);
	languageTitle->setPosition(Vec2(visibleSize.width/2 - languageTitle->getContentSize().width/2 - 100 , inputBox->getPositionY() + inputBox->getContentSize().height/2 + 50));
	addChild(languageTitle);


	languageSelected = LabelTTF::create("", "fonts/arial.ttf", 50, Size::ZERO, TextHAlignment::CENTER);
	languageSelected->setPosition(Vec2(languageTitle->getPositionX() + languageTitle->getContentSize().width / 2 + languageSelected->getContentSize().width / 2 + 150, languageTitle->getPositionY()));
	addChild(languageSelected);

    
    return true;
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void HelloWorld::jni_callVoidSpeechString(const char* speechString){
	cocos2d::JniMethodInfo methodInfo;
	if(!JniHelper::getStaticMethodInfo(methodInfo ,
			"org/cocos2dx/cpp/AppActivity" ,
			"SpeakString" ,
			"(Ljava/lang/String;)V")){
		log("Call Java Function From C++");
		return;
	}

	jstring stringJava = methodInfo.env->NewStringUTF(speechString);

	methodInfo.env->CallVoidMethod(methodInfo.classID , methodInfo.methodID , stringJava);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);
	methodInfo.env->DeleteLocalRef(stringJava);
}
#endif

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	inputText = inputBox->getText();
	log("%s", inputText);

	jni_callVoidSpeechString(inputText);
}

void HelloWorld::selectLanguage(Ref* pSender, int languageIndex)
{
	switch (languageIndex)
	{
	case 1:
		languageSelected->setString("English");
		_languageIndex = 1;
		break;
	case 2:
		languageSelected->setString("Japanese");
		_languageIndex = 2;
		break;
	default:
		break;
	}
}




int HelloWorld::getLanguageIndexC()
{
	return _languageIndex;
}

//////////////////////////////////////////////////////////////////////////////
// Xay dung ham tra ve gia tri LanguageIndex tu C++
//////////////////////////////////////////////////////////////////////////////

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

extern "C"
{
	JNIEXPORT jint JNICALL Java_org_cocos2dx_cpp_TTSpeech_getLanguageIndex(JNIEnv* env, jobject thiz)
	{
		int result = 2;
		log("==========%d========" , result);
		return result;
	}
}
#endif




#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C"
{
 JNIEXPORT jint JNICALL Java_org_cocos2dx_cpp_AppActivity_testJavaCallCPlusPlus(JNIEnv* env , jobject thiz , jstring stringParamJava)
 {
	 const char* str = env->GetStringUTFChars(stringParamJava , nullptr);
	 env->ReleaseStringUTFChars(stringParamJava , str);

	 log("======== %s =========" , str);
 }
}

#endif
