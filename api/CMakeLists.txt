include(version.cmake)

cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
if (POLICY CMP0043)
  cmake_policy(SET CMP0043 NEW)
endif()

if (POLICY CMP0079)
  cmake_policy(SET CMP0079 NEW)
endif()

project(api
  VERSION ${VERSION_API}
  DESCRIPTION "Cutecloud API"
  LANGUAGES CXX
)

find_package(Qt5 COMPONENTS REQUIRED Core)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)
# Create code for Qt Resource Files
set(CMAKE_AUTORCC ON)

set(SOURCES apicore.h apicore.cpp
    endpointdto.h endpointdto.cpp
    filelistdto.h filelistdto.cpp)

set(OTHER_FILES README.md)

add_library(api OBJECT ${SOURCES} ${OTHER_FILES})

target_include_directories(api
  PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

# Mark all warnings as errors
target_compile_options(api PRIVATE -Werror -fPIC)

# Enable LTCG (link time optimization)
option (ltcg "Enable LTCG (link time optimization)" ON)
if (ltcg)
  set_property(TARGET api PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif (ltcg)

# Use C++ 14 standard
target_compile_features(api PRIVATE cxx_std_14)

# Defines
target_compile_definitions(api PRIVATE QT_USE_QSTRINGBUILDER)

target_link_libraries(api
  Qt5::Core
)
