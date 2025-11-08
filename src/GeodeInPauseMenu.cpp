#include "GeodeInPauseMenu.hpp"
#include "classes/ModsLayerWrapper.hpp"
#include <Geode/ui/GeodeUI.hpp>

using namespace geode::prelude;

void GeodeInPauseMenu::openGeodeMenu(CCObject* sender) {
    auto director = CCDirector::get();
    Ref runningScene = director->getRunningScene();
    auto dontCallWillSwitch = director->getDontCallWillSwitch();
    director->setDontCallWillSwitch(true);

    openModsList();
    Ref<CCLayer> modsLayer;
    if (auto transitionScene = typeinfo_cast<CCTransitionScene*>(director->m_pNextScene)) {
        if (auto inScene = transitionScene->m_pInScene) {
            modsLayer = inScene->getChildByIndex<CCLayer>(0);
        }
    }

    director->setDontCallWillSwitch(true);
    director->replaceScene(runningScene);
    director->setDontCallWillSwitch(dontCallWillSwitch);
    director->m_pNextScene = nullptr;

    if (!modsLayer) return;

    modsLayer->removeFromParentAndCleanup(false);
    queueInMainThread([modsLayer = std::move(modsLayer)] {
        ModsLayerWrapper::create(modsLayer)->show();
    });
}

void GeodeInPauseMenu::addGeodeButton(CCNode* parent, std::string_view id, float scale, float sprScale, CircleBaseSize size) {
    auto menu = parent->getChildByID(id);
    if (!menu) return;

    auto geodeButtonSprite = CircleButtonSprite::createWithSpriteFrameName(
        "geode.loader/geode-logo-outline-gold.png", sprScale, CircleBaseColor::Green, size
    );
    geodeButtonSprite->setScale(scale);
    auto geodeButton = CCMenuItemSpriteExtra::create(geodeButtonSprite, parent, menu_selector(GeodeInPauseMenu::openGeodeMenu));
    geodeButton->setID("geode-button"_spr);
    menu->addChild(geodeButton);
    menu->updateLayout();
}
