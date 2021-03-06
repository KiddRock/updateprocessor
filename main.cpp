#include <iostream>
#include <fstream>

#include "play_manager.h"
#include "discord_state.h"
#include "telegram_state.h"


int main() {
    std::cout << "Starting up!" << std::endl;

    PlayManager playManager;
    ApkManager apkManager (playManager);

    //playManager.getDeviceARM().downloadApk("com.mojang.minecraftpe", 871021311, "priv/test.apk");
    static DiscordState* discordState = new DiscordState(playManager, apkManager);
    TelegramState telegramState(apkManager);

    apkManager.startChecking();

    signal(SIGINT, [](int signo) { discordState->storeSessionInfo(); exit(0); });
    signal(SIGTERM, [](int signo) { discordState->storeSessionInfo(); exit(0); });
    discordState->loop();

    delete discordState;
    return 0;
}