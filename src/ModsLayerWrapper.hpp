class ModsLayerWrapper : public FLAlertLayer {
protected:
    bool init(CCLayer*);
public:
    static ModsLayerWrapper* create(CCLayer*);

    void onClose(CCObject*);
    void keyBackClicked() override {
        onClose(nullptr);
    }
    void registerWithTouchDispatcher() override {
        cocos2d::CCTouchDispatcher::get()->addTargetedDelegate(this, -500, true);
    }
    void keyDown(cocos2d::enumKeyCodes key) override {
        m_mainLayer->keyDown(key);
    }
};
