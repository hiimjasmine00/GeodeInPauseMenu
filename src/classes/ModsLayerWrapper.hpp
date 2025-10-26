#include <Geode/binding/FLAlertLayer.hpp>

class ModsLayerWrapper : public FLAlertLayer {
protected:
    bool init(cocos2d::CCLayer*);
public:
    static ModsLayerWrapper* create(cocos2d::CCLayer*);

    void onClose(cocos2d::CCObject*);
    void keyBackClicked() override;
    void registerWithTouchDispatcher() override;
    void keyDown(cocos2d::enumKeyCodes) override;
};
