#pragma once

#include "spdlog/spdlog.h"

#include "memory"
#include "vector"
#include "string"
#include "queue"

const int WIDTH = 640;
const int HEIGHT = 480;

#define DEBUG(...) spdlog::debug(__VA_ARGS__);
#define INFO(...) spdlog::info(__VA_ARGS__);
#define WARN(...) spdlog::warn(__VA_ARGS__);
#define ERROR(...) spdlog::error(__VA_ARGS__);
#define CRITICAL(...) spdlog::critical(__VA_ARGS__); exit(0);