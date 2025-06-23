#include "../GeodeInPauseMenu.hpp"
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>

using namespace geode::prelude;

class $modify(GIPMPauseLayer, PauseLayer) {
    GIPM_MODIFY("game-pause-menu")

    void customSetup() override {
        PauseLayer::customSetup();

        auto rightButtonMenu = getChildByID("right-button-menu");
        if (!rightButtonMenu) return;

        auto geodeButtonSprite = CircleButtonSprite::createWithSpriteFrameName("geode.loader/geode-logo-outline-gold.png",
            0.95f, CircleBaseColor::Green, CircleBaseSize::MediumAlt);
        geodeButtonSprite->setScale(0.6f);
        auto geodeButton = CCMenuItemSpriteExtra::create(geodeButtonSprite, this, menu_selector(GeodeInPauseMenu::openGeodeMenu));
        geodeButton->setID("geode-button"_spr);
        rightButtonMenu->addChild(geodeButton);
        rightButtonMenu->updateLayout();
    }
};
