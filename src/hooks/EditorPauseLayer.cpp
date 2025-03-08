#include "../GeodeInPauseMenu.hpp"
#include <Geode/modify/EditorPauseLayer.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>

using namespace geode::prelude;

class $modify(GIPMEditorPauseLayer, EditorPauseLayer) {
    static void onModify(ModifyBase<ModifyDerive<GIPMEditorPauseLayer, EditorPauseLayer>>& self) {
        auto hook = self.getHook("EditorPauseLayer::init").mapErr([](const std::string& err) {
            return log::error("Failed to get EditorPauseLayer::init hook: {}", err), err;
        }).unwrapOr(nullptr);
        if (!hook) return;
        hook->setAutoEnable(Mod::get()->getSettingValue<bool>("editor-pause-menu"));

        listenForSettingChanges<bool>("editor-pause-menu", [hook](bool value) {
            (void)(value ? hook->enable() : hook->disable()).mapErr([value](const std::string& err) {
                return log::error("Failed to {} EditorPauseLayer::init hook: {}", value ? "enable" : "disable", err), err;
            });
        });
    }

    bool init(LevelEditorLayer* lel) {
        if (!EditorPauseLayer::init(lel)) return false;

        if (auto guidelinesMenu = getChildByID("guidelines-menu")) {
            auto geodeButton = CCMenuItemSpriteExtra::create(CircleButtonSprite::createWithSpriteFrameName("geode.loader/geode-logo-outline-gold.png",
                1.0f, CircleBaseColor::Green, CircleBaseSize::MediumAlt), this, menu_selector(GIPMEditorPauseLayer::onGeode));
            geodeButton->setID("geode-button"_spr);
            guidelinesMenu->addChild(geodeButton);
            guidelinesMenu->updateLayout();
        }

        return true;
    }

    void onGeode(CCObject*) {
        GeodeInPauseMenu::openGeodeMenu();
    }
};
