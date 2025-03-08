#include "GeodeInPauseMenu.hpp"
#include "classes/ModsLayerWrapper.hpp"
#include <Geode/ui/GeodeUI.hpp>

using namespace geode::prelude;

void GeodeInPauseMenu::openGeodeMenu() {
    auto director = CCDirector::sharedDirector();
    auto runningScene = director->getRunningScene();
    runningScene->retain();
    auto dontCallWillSwitch = director->getDontCallWillSwitch();
    director->setDontCallWillSwitch(true);
    openModsList();
    CCLayer* modsLayer = nullptr;
    if (auto transitionScene = typeinfo_cast<CCTransitionScene*>(director->m_pNextScene); transitionScene && transitionScene->m_pInScene) {
        if (auto children = transitionScene->m_pInScene->getChildren()) modsLayer = static_cast<CCLayer*>(children->objectAtIndex(0));
    }

    director->setDontCallWillSwitch(true);
    director->replaceScene(runningScene);
    director->setDontCallWillSwitch(dontCallWillSwitch);
    runningScene->release();
    director->m_pNextScene = nullptr;

    if (!modsLayer) return;

    modsLayer->retain();
    modsLayer->removeFromParentAndCleanup(false);
    queueInMainThread([modsLayer] {
        auto modsLayerWrapper = ModsLayerWrapper::create(modsLayer);
        modsLayer->release();
        modsLayerWrapper->show();
    });
}
