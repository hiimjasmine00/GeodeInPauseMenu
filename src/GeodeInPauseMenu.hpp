#include <Geode/loader/Types.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>

class GeodeInPauseMenu : public cocos2d::CCObject {
public:
    void openGeodeMenu(cocos2d::CCObject* sender);
    static void modify(std::map<std::string, std::shared_ptr<geode::Hook>>& hooks, const std::string& name, std::string_view setting);
    static void addGeodeButton(cocos2d::CCNode* parent, std::string_view id, float scale, float sprScale, geode::CircleBaseSize size);
};
