#Required lines
cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{DOLCESDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{DOLCESDK}/share/dolce.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define DOLCESDK to point to your SDK path!")
  endif()
endif()


project(Helloworld LANGUAGES C) #This is the name of your project. Note that "LANGUAGES C" is optional
include("${DOLCESDK}/share/dolce.cmake" REQUIRED) #Including the SDK's .cmake script is required

set(VITA_APP_NAME "Hello world !") #Name displayed on the Home Screen
set(VITA_TITLEID  "HELLOWORL") #Title ID : 9 characters, capital letters or digits only
set(VITA_VERSION  "01.00") #Version of the app

#Settings for the compilers, this will output an optimized C binary while displaying all warnings
#(-Wno-unknown-pragmas is for the "#pragma region" used in Visual Studio Code)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11 -Wall -O3 -Wno-unknown-pragmas -fno-lto")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions")
#Settings for the param.sfo flags. This sets parental level to the minimum level.
set(DOLCE_MKSFOEX_FLAGS "${DOLCE_MKSFOEX_FLAGS} -d PARENTAL_LEVEL=1")

#If you have any headers you use, make sure to put the directory here.
#Note that the PSP2, VitaSDK/DolceSDK and taiHEN headers are already included by default.
include_directories()

#This is equivalent to placing "#define DEBUG" somewhere in your code.
#Useful for testing purposes.
add_definitions(-DDEBUG)

link_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)

#All the .c files used by the project.
add_executable(${PROJECT_NAME}
    main.c
    debugScreenFont.c
)

#Libraries the project will be linked against. VitaSDK docs can help you find most of them.
target_link_libraries(${PROJECT_NAME}
	SceCtrl_stub
	SceTouch_stub
	SceLibKernel_stub
  	SceDisplay_stub
	SceAppMgr_stub
	taihen_stub
)

#Creates a signed elf (EBOOT.BIN)
dolce_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})
#Packages the EBOOT.BIN into a vpk for installation.
dolce_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
)
