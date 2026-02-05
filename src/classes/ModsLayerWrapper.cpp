#include "ModsLayerWrapper.hpp"
#include <Geode/utils/cocos.hpp>

using namespace geode::prelude;

ModsLayerWrapper* ModsLayerWrapper::create(CCLayer* modsLayer) {
    auto ret = new ModsLayerWrapper();
    if (ret->init(modsLayer)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool ModsLayerWrapper::init(CCLayer* modsLayer) {
    if (!FLAlertLayer::init(150)) return false;

    setID("ModsLayerWrapper");

    m_noElasticity = true;

    if (m_mainLayer) m_mainLayer->removeFromParent();

    m_mainLayer = modsLayer;
    addChild(modsLayer);

    modsLayer->removeChildByID("SwelvyBG");
    modsLayer->removeChildByID("bg");
    modsLayer->removeChildByID("side-art-top-left");
    modsLayer->removeChildByID("side-art-top-right");
    modsLayer->removeChildByID("side-art-bottom-left");
    modsLayer->removeChildByID("side-art-bottom-right");
    static_cast<CCMenuItem*>(modsLayer->getChildByID("back-menu")->getChildByID("back-button"))->setTarget(
        this, menu_selector(ModsLayerWrapper::onClose));

    setKeyboardEnabled(true);
    handleTouchPriority(this, true);

    return true;
}

void ModsLayerWrapper::onClose(CCObject*) {
    setKeypadEnabled(false);
    setKeyboardEnabled(false);
    setTouchEnabled(false);
    removeFromParent();
}

void ModsLayerWrapper::keyBackClicked() {
    onClose(nullptr);
}

void ModsLayerWrapper::registerWithTouchDispatcher() {
    CCTouchDispatcher::get()->addTargetedDelegate(this, -500, true);
}

void ModsLayerWrapper::keyDown(enumKeyCodes key, double timestamp) {
    m_mainLayer->keyDown(key, timestamp);
}
