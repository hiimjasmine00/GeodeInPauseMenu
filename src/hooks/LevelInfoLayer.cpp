#include "../GeodeInPauseMenu.hpp"
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>

using namespace geode::prelude;

class $modify(GIPMLevelInfoLayer, LevelInfoLayer) {
    static void onModify(ModifyBase<ModifyDerive<GIPMLevelInfoLayer, LevelInfoLayer>>& self) {
        (void)self.getHook("LevelInfoLayer::init").map([](Hook* hook) {
            auto mod = Mod::get();
            hook->setAutoEnable(mod->getSettingValue<bool>("level-info-menu"));

            listenForSettingChangesV3<bool>("level-info-menu", [hook](bool value) {
                (void)(value ? hook->enable().mapErr([value](const std::string& err) {
                    return log::error("Failed to enable LevelInfoLayer::init hook: {}", err), err;
                }) : hook->disable().mapErr([value](const std::string& err) {
                    return log::error("Failed to disable LevelInfoLayer::init hook: {}", err), err;
                }));
            }, mod);

            return hook;
        }).mapErr([](const std::string& err) {
            return log::error("Failed to get LevelInfoLayer::init hook: {}", err), err;
        });
    }

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
