#pragma once

#include "algorithm"
#include "queue"
#include "raylib.h"
#include "spdlog/spdlog.h"
#include "string"
#include "vector"

#define WIDTH 640
#define HEIGHT 480

#define DEBUG(...) spdlog::debug(__VA_ARGS__);
#define INFO(...) spdlog::info(__VA_ARGS__);
#define WARN(...) spdlog::warn(__VA_ARGS__);
#define ERROR(...) spdlog::error(__VA_ARGS__);
#define CRITICAL(...)                                                          \
  spdlog::critical(__VA_ARGS__);                                               \
  exit(-1);

#define DARK100                                                                \
  { 50, 50, 50, 255 }
#define DARK200                                                                \
  { 40, 40, 40, 255 }
#define DARK300                                                                \
  { 30, 30, 30, 255 }

#define RED300                                                                 \
  CLITERAL(Color){ 252, 165, 165, 255 }
#define ORANGE300                                                              \
  CLITERAL(Color){ 253, 186, 116, 255 }
#define AMBER300                                                               \
  CLITERAL(Color){ 252, 211, 77, 255 }
#define YELLOW300                                                              \
  CLITERAL(Color){ 253, 224, 71, 255 }
#define LIME300                                                                \
  CLITERAL(Color){ 190, 242, 100, 255 }
#define GREEN300                                                               \
  CLITERAL(Color){ 134, 239, 172, 255 }
#define EMERALD300                                                             \
  CLITERAL(Color){ 110, 231, 183, 255 }
#define TEAL300                                                                \
  CLITERAL(Color){ 94, 234, 212, 255 }
#define CYAN300                                                                \
  CLITERAL(Color){ 103, 232, 249, 255 }
#define SKY300                                                                 \
  CLITERAL(Color){ 125, 211, 252, 255 }
#define BLUE300                                                                \
  CLITERAL(Color){ 147, 197, 253, 255 }
#define INDIGO300                                                              \
  CLITERAL(Color){ 165, 180, 252, 255 }
#define VIOLET300                                                              \
  CLITERAL(Color){ 196, 181, 253, 255 }
#define PURPLE300                                                              \
  CLITERAL(Color){ 216, 180, 254, 255 }
#define FUCHSIA300                                                             \
  CLITERAL(Color){ 240, 171, 252, 255 }
#define PINK300                                                                \
  CLITERAL(Color){ 249, 168, 212, 255 }
#define ROSE300                                                                \
  CLITERAL(Color){ 253, 164, 175, 255 }
#define GENCOLOUR(col) "/" _stringify_colour(col)
#define _stringify_colour(r, g, b, a) #r #g #b #a

#define NEWLINE "\n"