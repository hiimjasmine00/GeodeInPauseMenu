#include <Geode/loader/Types.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>

class GeodeInPauseMenu : public cocos2d::CCObject {
public:
    void openGeodeMenu(cocos2d::CCObject* sender);
    static void addGeodeButton(cocos2d::CCNode* parent, std::string_view id, float scale, float sprScale, geode::CircleBaseSize size);
};
