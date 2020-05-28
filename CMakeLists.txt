cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{DOLCESDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{DOLCESDK}/share/dolce.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define DOLCESDK to point to your SDK path!")
  endif()
endif()

project(Helloworld LANGUAGES C)
include("${DOLCESDK}/share/dolce.cmake" REQUIRED)

set(VITA_APP_NAME "Hello world !")
set(VITA_TITLEID  "HELLOWORL")
set(VITA_VERSION  "01.00")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11 -Wall -O3 -Wno-unknown-pragmas -fno-lto")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions")
set(DOLCE_MKSFOEX_FLAGS "${DOLCE_MKSFOEX_FLAGS} -d PARENTAL_LEVEL=1")

include_directories()

add_definitions(-DDEBUG)

link_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(${PROJECT_NAME}
    REALmain.c
    debugScreenFont.c
)

target_link_libraries(${PROJECT_NAME}
	SceCtrl_stub
	SceTouch_stub
	SceLibKernel_stub
  SceDisplay_stub

	taihen_stub

	SceAppMgr_stub
)

dolce_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})
dolce_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
)