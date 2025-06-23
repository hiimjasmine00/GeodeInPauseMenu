#include "GeodeInPauseMenu.hpp"
#include "classes/ModsLayerWrapper.hpp"
#include <Geode/ui/GeodeUI.hpp>

using namespace geode::prelude;

void GeodeInPauseMenu::openGeodeMenu(CCObject*) {
    auto director = CCDirector::get();
    Ref runningScene = director->getRunningScene();
    auto dontCallWillSwitch = director->getDontCallWillSwitch();
    director->setDontCallWillSwitch(true);

    openModsList();
    Ref<CCLayer> modsLayer;
    if (auto transitionScene = typeinfo_cast<CCTransitionScene*>(director->m_pNextScene)) {
        if (transitionScene->m_pInScene) modsLayer = getChild<CCLayer>(transitionScene->m_pInScene, 0);
    }

    director->setDontCallWillSwitch(true);
    director->replaceScene(runningScene);
    director->setDontCallWillSwitch(dontCallWillSwitch);
    director->m_pNextScene = nullptr;

    if (!modsLayer) return;

    modsLayer->removeFromParentAndCleanup(false);
    queueInMainThread([modsLayer = std::move(modsLayer)] {
        ModsLayerWrapper::create(modsLayer)->show();
    });
}
