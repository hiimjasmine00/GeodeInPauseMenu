#include "../GeodeInPauseMenu.hpp"
#include <Geode/modify/EditorPauseLayer.hpp>

using namespace geode::prelude;

class $modify(GIPMEditorPauseLayer, EditorPauseLayer) {
    static void onModify(ModifyBase<ModifyDerive<GIPMEditorPauseLayer, EditorPauseLayer>>& self) {
        GeodeInPauseMenu::modify(self.m_hooks, "EditorPauseLayer::init", "editor-pause-menu");
    }

    bool init(LevelEditorLayer* lel) {
        if (!EditorPauseLayer::init(lel)) return false;

        GeodeInPauseMenu::addGeodeButton(this, "guidelines-menu", 1.0f, 1.0f, CircleBaseSize::Small);

        return true;
    }
};
