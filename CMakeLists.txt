cmake_minimum_required(VERSION 3.26)
project(jetlang)
set(LT_LLVM_INSTALL_DIR, "/usr/local/opt/llvm")
set(LT_LLVM_INCLUDE_DIR "${LT_LLVM_INSTALL_DIR}/include")
find_package(LLVM CONFIG)
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
add_definitions(${LLVM_DEFINITIONS})
include_directories(src)
set(CMAKE_EXE_LINKER_FLAGS "-lc++")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
add_executable(jetlang src/main.cpp src/main.h
        src/shared/types/exit-status.enum.h
        src/shared/utils/logger/logger.cpp
        src/shared/utils/logger/logger.h
)
target_link_libraries(jetlang LLVMSupport)