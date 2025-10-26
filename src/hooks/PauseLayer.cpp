#include "../GeodeInPauseMenu.hpp"
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class $modify(GIPMPauseLayer, PauseLayer) {
    static void onModify(ModifyBase<ModifyDerive<GIPMPauseLayer, PauseLayer>>& self) {
        GeodeInPauseMenu::modify(self.m_hooks, "PauseLayer::customSetup", "game-pause-menu");
    }

    void customSetup() override {
        PauseLayer::customSetup();

        GeodeInPauseMenu::addGeodeButton(this, "right-button-menu", 0.6f, 0.95f, CircleBaseSize::MediumAlt);
    }
};
