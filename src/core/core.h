#pragma once

#include "vector"
#include "string"
#include "algorithm"
#include "queue"
#include "spdlog/spdlog.h"

#define WIDTH 640
#define HEIGHT 480

#define DEBUG(...) spdlog::debug(__VA_ARGS__);
#define INFO(...) spdlog::info(__VA_ARGS__);
#define WARN(...) spdlog::warn(__VA_ARGS__);
#define ERROR(...) spdlog::error(__VA_ARGS__);
#define CRITICAL(...) spdlog::critical(__VA_ARGS__); exit(-1);

#define DARK100 {50, 50, 50, 255}
#define DARK200 {40, 40, 40, 255}
#define DARK300 {30, 30, 30, 255}

#define NEWLINE "\n"