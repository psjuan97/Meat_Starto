# this one is important
SET(CMAKE_SYSTEM_NAME ps3-Psl1ght)
#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
SET(CMAKE_C_COMPILER   /usr/local/ps3dev/ppu/bin/ppu-gcc)
SET(CMAKE_CXX_COMPILER /usr/local/ps3dev/ppu/bin/ppu-g++)

# where is the target environment
SET(CMAKE_FIND_ROOT_PATH  /usr/local/ps3dev/ppu/bin /usr/local/ps3dev/portlibs/ppu/)

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

