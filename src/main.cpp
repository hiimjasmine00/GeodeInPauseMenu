#include "ModsLayerWrapper.hpp"
#include <Geode/ui/GeodeUI.hpp>

using namespace geode::prelude;

void openGeodeMenu() {
    auto director = CCDirector::get();
    auto runningScene = CCScene::get();
    runningScene->retain();
    auto dontCallWillSwitch = director->getDontCallWillSwitch();
    director->setDontCallWillSwitch(true);
    openModsList();
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

#include <Geode/modify/PauseLayer.hpp>
class $modify(GIPMPauseLayer, PauseLayer) {
    void customSetup() override {
        PauseLayer::customSetup();

        if (!Mod::get()->getSettingValue<bool>("game-pause-menu")) return;

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

    void onGeode(CCObject*) {
        openGeodeMenu();
    }
};

#include <Geode/modify/EditorPauseLayer.hpp>
class $modify(GIPMEditorPauseLayer, EditorPauseLayer) {
    bool init(LevelEditorLayer* lel) {
        if (!EditorPauseLayer::init(lel)) return false;

        if (!Mod::get()->getSettingValue<bool>("editor-pause-menu")) return true;

        if (auto guidelinesMenu = getChildByID("guidelines-menu")) {
            auto geodeButton = CCMenuItemSpriteExtra::create(CircleButtonSprite::createWithSpriteFrameName("geode.loader/geode-logo-outline-gold.png",
                1.0f, CircleBaseColor::Green, CircleBaseSize::Small), this, menu_selector(GIPMEditorPauseLayer::onGeode));
            geodeButton->setID("geode-button"_spr);
            guidelinesMenu->addChild(geodeButton);
            guidelinesMenu->updateLayout();
        }

        return true;
    }

    void onGeode(CCObject*) {
        openGeodeMenu();
    }
};
