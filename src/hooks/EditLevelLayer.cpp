#include "../GeodeInPauseMenu.hpp"
#include <Geode/modify/EditLevelLayer.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>

using namespace geode::prelude;

class $modify(GIPMEditLevelLayer, EditLevelLayer) {
    GIPM_MODIFY("level-edit-menu")

    bool init(GJGameLevel* level) {
        if (!EditLevelLayer::init(level)) return false;

        auto levelActionsMenu = getChildByID("level-actions-menu");
        if (!levelActionsMenu) return true;

        auto geodeButton = CCMenuItemSpriteExtra::create(CircleButtonSprite::createWithSpriteFrameName(
            "geode.loader/geode-logo-outline-gold.png",
            0.95f, CircleBaseColor::Green, CircleBaseSize::MediumAlt
        ), this, menu_selector(GeodeInPauseMenu::openGeodeMenu));
        geodeButton->setID("geode-button"_spr);
        levelActionsMenu->addChild(geodeButton);
        levelActionsMenu->updateLayout();

        return true;
    }
};
