cmake_minimum_required(VERSION 3.10)

project(blast)

set(LLVM_DIR "/media/jack/32A07C604A5709A8/Jack/Programs/llvm13")

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/raylib)

file(GLOB BLAST_SRC
     "src/**/*.h"
     "src/**/*.cpp"
     "src/*.h"
     "src/*.cpp"
)
include_directories("src")

add_executable(blast ${BLAST_SRC})
llvm_map_components_to_libnames(LLVM_LIBS core support x86asmparser x86codegen)
target_link_libraries(blast PRIVATE spdlog::spdlog raylib ${LLVM_LIBS})