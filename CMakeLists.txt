cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()


## Set our project name
project(Meat_Starto_Mod)

include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME "Meat Starto")
set(VITA_TITLEID  "VSDK00006")
set(VITA_VERSION  "01.00")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_EXE_LINKER_FLAGS "-Wl,-q")


include_directories("src" "src/Mapa" "src/physicsEngine", "src/renderEngine" )

include_directories("lib/")
include_directories("lib/tinyxml2")


## Use all the *.cpp files we found under this folder for the project
FILE(GLOB_RECURSE SRCS "src/*.cpp" "src/Mapa/*.cpp"  "src/physicsEngine/*.cpp" "src/renderEngine/*.cpp" , "lib/tinyxml2/*.cpp")

## Define the executable
add_executable(${PROJECT_NAME} ${SRCS})


target_link_libraries(${PROJECT_NAME}
  SDL2
  SDL2_image
  SDL2_ttf
  png
  jpeg
  freetype
  z
  SceDisplay_stub
  SceCtrl_stub
  SceAudio_stub
  SceGxm_stub
  SceCommonDialog_stub
  SceTouch_stub
  SceHid_stub
  SceMotion_stub
  Box2D

)


## Create Vita files
vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})
# The FILE directive lets you add additional files to the VPK, the syntax is
# FILE src_path dst_path_in_vpk. In this case, we add the LiveArea paths.
vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  FILE sce_sys/icon0.png sce_sys/icon0.png
  FILE sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
  FILE sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
  FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
)

