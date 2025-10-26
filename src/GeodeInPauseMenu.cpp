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

void GeodeInPauseMenu::modify(std::map<std::string, std::shared_ptr<geode::Hook>>& hooks, const std::string& name, std::string_view setting) {
    auto it = hooks.find(name);
    if (it == hooks.end()) return;

    auto mod = Mod::get();
    auto enabled = mod->getSettingValue<bool>(setting);

    auto hook = it->second.get();
    hook->setAutoEnable(enabled);

    listenForSettingChangesV3<bool>(setting, [hook, name](bool value) {
        if (auto err = hook->toggle(value).err()) {
            log::error("Failed to toggle {} hook: {}", name, *err);
        }
    }, mod);
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
