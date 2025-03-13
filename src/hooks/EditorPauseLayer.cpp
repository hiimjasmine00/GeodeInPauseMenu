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

        auto mod = Mod::get();
        hook->setAutoEnable(mod->getSettingValue<bool>("editor-pause-menu"));

        listenForSettingChangesV3<bool>("editor-pause-menu", [hook](bool value) {
            (void)(value ? hook->enable().mapErr([value](const std::string& err) {
                return log::error("Failed to enable EditorPauseLayer::init hook: {}", err), err;
            }) : hook->disable().mapErr([value](const std::string& err) {
                return log::error("Failed to disable EditorPauseLayer::init hook: {}", err), err;
            }));
        }, mod);
    }

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
