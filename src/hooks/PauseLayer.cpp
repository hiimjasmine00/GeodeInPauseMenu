#include "../GeodeInPauseMenu.hpp"
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>

using namespace geode::prelude;

class $modify(GIPMPauseLayer, PauseLayer) {
    static void onModify(ModifyBase<ModifyDerive<GIPMPauseLayer, PauseLayer>>& self) {
        auto hook = self.getHook("PauseLayer::customSetup").mapErr([](const std::string& err) {
            return log::error("Failed to get PauseLayer::customSetup hook: {}", err), err;
        }).unwrapOr(nullptr);
        if (!hook) return;
        hook->setAutoEnable(Mod::get()->getSettingValue<bool>("game-pause-menu"));

        listenForSettingChanges<bool>("game-pause-menu", [hook](bool value) {
            (void)(value ? hook->enable() : hook->disable()).mapErr([value](const std::string& err) {
                return log::error("Failed to {} PauseLayer::customSetup hook: {}", value ? "enable" : "disable", err), err;
            });
        });
    }

    void customSetup() override {
        PauseLayer::customSetup();

        if (auto rightButtonMenu = getChildByID("right-button-menu")) {
            auto geodeButtonSprite = CircleButtonSprite::createWithSpriteFrameName("geode.loader/geode-logo-outline-gold.png",
                1.0f, CircleBaseColor::Green, CircleBaseSize::MediumAlt);
            geodeButtonSprite->setScale(0.6f);
            geodeButtonSprite->getTopNode()->setScale(1.0f);
            auto geodeButton = CCMenuItemSpriteExtra::create(geodeButtonSprite, this, menu_selector(GIPMPauseLayer::onGeode));
            geodeButton->setID("geode-button"_spr);
            rightButtonMenu->addChild(geodeButton);
            rightButtonMenu->updateLayout();
        }
    }

    void onGeode(CCObject*) {
        GeodeInPauseMenu::openGeodeMenu();
    }
};
