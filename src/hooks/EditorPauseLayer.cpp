#include "../GeodeInPauseMenu.hpp"
#include <Geode/modify/EditorPauseLayer.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>

using namespace geode::prelude;

class $modify(GIPMEditorPauseLayer, EditorPauseLayer) {
    GIPM_MODIFY("editor-pause-menu")

    bool init(LevelEditorLayer* lel) {
        if (!EditorPauseLayer::init(lel)) return false;

        auto guidelinesMenu = getChildByID("guidelines-menu");
        if (!guidelinesMenu) return true;

        auto geodeButton = CCMenuItemSpriteExtra::create(CircleButtonSprite::createWithSpriteFrameName(
            "geode.loader/geode-logo-outline-gold.png",
            1.0f, CircleBaseColor::Green, CircleBaseSize::Small
        ), this, menu_selector(GeodeInPauseMenu::openGeodeMenu));
        geodeButton->setID("geode-button"_spr);
        guidelinesMenu->addChild(geodeButton);
        guidelinesMenu->updateLayout();

        return true;
    }
};
