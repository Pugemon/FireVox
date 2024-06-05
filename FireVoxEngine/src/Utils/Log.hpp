//
// Created by Pugemon on 21.05.2024.
//

#ifndef LOG_HPP
#define LOG_HPP

#include "spdlog/spdlog.h"

namespace FireVoxEngine::Logging {

#ifdef NDEBUG

#define LOG_INFO(...) ((void) 0)
#define LOG_WARN(...) ((void) 0)
#define LOG_ERROR(...) ((void) 0)
#define LOG_CRITICAL(...) ((void) 0)
#define LOG_DEBUG(...) ((void) 0)
#define LOG_TRACE(...) ((void) 0)

#else

#define LOG_INFO(...) spdlog::info(__VA_ARGS__)
#define LOG_WARN(...) spdlog::warn(__VA_ARGS__)
#define LOG_ERROR(...) spdlog::error(__VA_ARGS__)
#define LOG_CRITICAL(...) spdlog::critical(__VA_ARGS__)
#define LOG_DEBUG(...) spdlog::debug(__VA_ARGS__)
#define LOG_TRACE(...) SPDLOG_TRACE(__VA_ARGS__)

#endif

}  // namespace FireVoxEngine::Logging

#endif  // LOG_HPP
