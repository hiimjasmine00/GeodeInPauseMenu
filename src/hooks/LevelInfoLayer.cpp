#include "../GeodeInPauseMenu.hpp"
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>

using namespace geode::prelude;

class $modify(GIPMLevelInfoLayer, LevelInfoLayer) {
    GIPM_MODIFY("level-info-menu")

    bool init(GJGameLevel* level, bool challenge) {
        if (!LevelInfoLayer::init(level, challenge)) return false;

        auto leftSideMenu = getChildByID("left-side-menu");
        if (!leftSideMenu) return true;

        auto geodeButton = CCMenuItemSpriteExtra::create(CircleButtonSprite::createWithSpriteFrameName(
            "geode.loader/geode-logo-outline-gold.png",
            1.0f, CircleBaseColor::Green, CircleBaseSize::Medium
        ), this, menu_selector(GeodeInPauseMenu::openGeodeMenu));
        geodeButton->setID("geode-button"_spr);
        leftSideMenu->addChild(geodeButton);
        leftSideMenu->updateLayout();

        return true;
    }
};
