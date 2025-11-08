#include "../GeodeInPauseMenu.hpp"
#include <Geode/modify/LevelInfoLayer.hpp>
#include <jasmine/hook.hpp>

using namespace geode::prelude;

class $modify(GIPMLevelInfoLayer, LevelInfoLayer) {
    static void onModify(ModifyBase<ModifyDerive<GIPMLevelInfoLayer, LevelInfoLayer>>& self) {
        jasmine::hook::modify(self.m_hooks, "LevelInfoLayer::init", "level-info-menu");
    }

    bool init(GJGameLevel* level, bool challenge) {
        if (!LevelInfoLayer::init(level, challenge)) return false;

        GeodeInPauseMenu::addGeodeButton(this, "left-side-menu", 1.0f, 1.0f, CircleBaseSize::Medium);

        return true;
    }
};
