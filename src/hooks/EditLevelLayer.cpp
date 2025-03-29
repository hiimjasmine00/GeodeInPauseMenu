#include "../GeodeInPauseMenu.hpp"
#include <Geode/modify/EditLevelLayer.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>

using namespace geode::prelude;

class $modify(GIPMEditLevelLayer, EditLevelLayer) {
    static void onModify(ModifyBase<ModifyDerive<GIPMEditLevelLayer, EditLevelLayer>>& self) {
        (void)self.getHook("EditLevelLayer::init").map([](Hook* hook) {
            auto mod = Mod::get();
            hook->setAutoEnable(mod->getSettingValue<bool>("level-edit-menu"));

            listenForSettingChangesV3<bool>("level-edit-menu", [hook](bool value) {
                (void)(value ? hook->enable().mapErr([value](const std::string& err) {
                    return log::error("Failed to enable EditLevelLayer::init hook: {}", err), err;
                }) : hook->disable().mapErr([value](const std::string& err) {
                    return log::error("Failed to disable EditLevelLayer::init hook: {}", err), err;
                }));
            }, mod);

            return hook;
        }).mapErr([](const std::string& err) {
            return log::error("Failed to get EditLevelLayer::init hook: {}", err), err;
        });
    }

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
