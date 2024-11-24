#include "ModsLayerWrapper.hpp"

using namespace geode::prelude;

uintptr_t geodeButtonAddress;

void openGeodeMenu(CCObject* target, CCObject* sender) {
    auto director = CCDirector::get();
    auto runningScene = CCScene::get();
    runningScene->retain();
    auto dontCallWillSwitch = director->getDontCallWillSwitch();
    director->setDontCallWillSwitch(true);
    reinterpret_cast<void(*)(CCObject*, CCObject*)>(geodeButtonAddress)(target, sender);
    CCLayer* modsLayer = nullptr;
    if (auto transitionScene = typeinfo_cast<CCTransitionScene*>(director->m_pNextScene)) {
        if (auto inScene = *reinterpret_cast<CCScene**>(reinterpret_cast<uintptr_t>(transitionScene) + sizeof(CCScene))) {
            if (inScene->getChildrenCount() > 0)
                modsLayer = static_cast<CCLayer*>(inScene->getChildren()->objectAtIndex(0));
        }
    }

    director->setDontCallWillSwitch(true);
    director->replaceScene(runningScene);
    director->setDontCallWillSwitch(dontCallWillSwitch);
    runningScene->release();
    director->m_pNextScene = nullptr;

    if (!modsLayer) return;

    modsLayer->retain();
    modsLayer->removeFromParentAndCleanup(false);
    queueInMainThread([modsLayer] {
        auto modsLayerWrapper = ModsLayerWrapper::create(modsLayer);
        modsLayer->release();
        modsLayerWrapper->show();
    });
}

#include <Geode/modify/MenuLayer.hpp>
class $modify(GIPMMenuLayer, MenuLayer) {
    bool init() override {
        if (!MenuLayer::init()) return false;

        if (auto bottomMenu = getChildByID("bottom-menu")) {
            if (auto geodeButton = static_cast<CCMenuItemSpriteExtra*>(bottomMenu->getChildByID("geode.loader/geode-button")))
                geodeButtonAddress = addresser::getNonVirtual(geodeButton->m_pfnSelector);
        }

        return true;
    }
};

#include <Geode/modify/PauseLayer.hpp>
class $modify(GIPMPauseLayer, PauseLayer) {
    void customSetup() override {
        PauseLayer::customSetup();

        if (geodeButtonAddress == 0) return;

        if (auto rightButtonMenu = getChildByID("right-button-menu")) {
            auto geodeButtonSprite = CircleButtonSprite::createWithSpriteFrameName("geode.loader/geode-logo-outline-gold.png",
                1.0f, CircleBaseColor::Green, CircleBaseSize::MediumAlt);
            geodeButtonSprite->setScale(0.6f);
            auto geodeButton = CCMenuItemSpriteExtra::create(geodeButtonSprite, this, menu_selector(GIPMPauseLayer::onGeode));
            geodeButton->setID("geode-button"_spr);
            rightButtonMenu->addChild(geodeButton);
            rightButtonMenu->updateLayout();
        }
    }

    void onGeode(CCObject* sender) {
        openGeodeMenu(this, sender);
    }
};

#include <Geode/modify/EditorPauseLayer.hpp>
class $modify(GIPMEditorPauseLayer, EditorPauseLayer) {
    bool init(LevelEditorLayer* lel) {
        if (!EditorPauseLayer::init(lel)) return false;

        if (geodeButtonAddress == 0) return true;

        if (auto guidelinesMenu = getChildByID("guidelines-menu")) {
            auto geodeButton = CCMenuItemSpriteExtra::create(CircleButtonSprite::createWithSpriteFrameName("geode.loader/geode-logo-outline-gold.png",
                1.0f, CircleBaseColor::Green, CircleBaseSize::Small), this, menu_selector(GIPMEditorPauseLayer::onGeode));
            geodeButton->setID("geode-button"_spr);
            guidelinesMenu->addChild(geodeButton);
            guidelinesMenu->updateLayout();
        }

        return true;
    }

    void onGeode(CCObject* sender) {
        openGeodeMenu(this, sender);
    }
};
