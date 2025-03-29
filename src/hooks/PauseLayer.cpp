#include "../GeodeInPauseMenu.hpp"
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>

using namespace geode::prelude;

class $modify(GIPMPauseLayer, PauseLayer) {
    static void onModify(ModifyBase<ModifyDerive<GIPMPauseLayer, PauseLayer>>& self) {
        (void)self.getHook("PauseLayer::customSetup").map([](Hook* hook) {
            auto mod = Mod::get();
            hook->setAutoEnable(Mod::get()->getSettingValue<bool>("game-pause-menu"));

            listenForSettingChangesV3<bool>("game-pause-menu", [hook](bool value) {
                (void)(value ? hook->enable().mapErr([value](const std::string& err) {
                    return log::error("Failed to enable PauseLayer::customSetup hook: {}", err), err;
                }) : hook->disable().mapErr([value](const std::string& err) {
                    return log::error("Failed to disable PauseLayer::customSetup hook: {}", err), err;
                }));
            }, mod);

            return hook;
        }).mapErr([](const std::string& err) {
            return log::error("Failed to get PauseLayer::customSetup hook: {}", err), err;
        });
    }

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
