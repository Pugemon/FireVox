//
// Created by Pugemon on 05.06.2024.
//

#include "Utils/Log.hpp"

int main() {
#ifdef DEBUG
    spdlog::set_level(spdlog::level::debug);
#endif
    LOG_INFO("Starting...");

    LOG_INFO("Exit");
    return 0;
}
