cmake_minimum_required(VERSION 3.1)

set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)


project(LibSWOSEdt CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)


set(CC_SRC ${PROJECT_SOURCE_DIR}/src)
set(CC_SWOSLIB ${PROJECT_SOURCE_DIR}/src/SwosEdt)

set(CC_INCLUDE ${PROJECT_SOURCE_DIR}/include)
set(CC_SWOSLIB_INC ${CC_INCLUDE}/SwosEdt)

#set(CC_DEPS ${PROJECT_SOURCE_DIR}/deps)
#set(CC_SPDLOG_INC ${CC_DEPS}/spdlog/include)

set(CC_TEST ${PROJECT_SOURCE_DIR}/test)

set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Os -s -DNDEBUG")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-O3 -Os -s -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG")

include_directories(${CC_INCLUDE})
include_directories(${CC_SWOSLIB_INC})
include_directories(${CC_SRC})
include_directories(${CC_SWOSLIB})
#include_directories(${CC_SPDLOG_INC})

include_directories(${CC_TEST})

set(CC_SWOSLIBFILES 
  ${CC_SWOSLIB}/swosdb.cc  
)

set(CC_DUPL 
  ${CC_TEST}/main.cc  
)

set(CC_SWSDB 
  ${CC_TEST}/swsdata.cc  
)
add_library(SwosEdt SHARED ${CC_SWOSLIBFILES})
target_link_options(SwosEdt PRIVATE -static)

add_executable(finddupl ${CC_DUPL})
target_link_libraries(finddupl SwosEdt)

add_executable(swsduplfinder ${CC_SWSDB})
target_link_libraries(swsduplfinder SwosEdt)