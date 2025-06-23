#include <cocos2d.h>

#define GIPM_MODIFY(settingName) \
    static void onModify(auto& self) { \
        auto mod = Mod::get(); \
        auto enabled = mod->getSettingValue<bool>(settingName); \
        auto& hooks = self.m_hooks; \
        for (auto& [name, hook] : hooks) { \
            hook->setAutoEnable(enabled); \
        } \
        if (!hooks.empty()) listenForSettingChangesV3<bool>(settingName, [hooks](bool value) { \
            for (auto& [name, hook] : hooks) { \
                (void)(value ? hook->enable().inspectErr([&name](const std::string& err) { \
                    log::error("Failed to enable {} hook: {}", name, err); \
                }) : hook->disable().inspectErr([&name](const std::string& err) { \
                    log::error("Failed to disable {} hook: {}", name, err); \
                })); \
            } \
        }, mod); \
    } \

class GeodeInPauseMenu : public cocos2d::CCObject {
public:
    void openGeodeMenu(CCObject*);
};
