#include "../GeodeInPauseMenu.hpp"
#include <Geode/modify/EditLevelLayer.hpp>

using namespace geode::prelude;

class $modify(GIPMEditLevelLayer, EditLevelLayer) {
    static void onModify(ModifyBase<ModifyDerive<GIPMEditLevelLayer, EditLevelLayer>>& self) {
        GeodeInPauseMenu::modify(self.m_hooks, "EditLevelLayer::init", "level-edit-menu");
    }

    bool init(GJGameLevel* level) {
        if (!EditLevelLayer::init(level)) return false;

        GeodeInPauseMenu::addGeodeButton(this, "level-actions-menu", 1.0f, 0.95f, CircleBaseSize::MediumAlt);

        return true;
    }
};
