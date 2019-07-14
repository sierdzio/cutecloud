include(version.cmake)

cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
if (POLICY CMP0043)
  cmake_policy(SET CMP0043 NEW)
endif()

project(cutecloud
  VERSION ${VERSION}
  DESCRIPTION "Cutelyst-based cloud solution"
  LANGUAGES CXX
)

if(WIN32)
  if(MSVC)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
  endif()
endif()

find_package(Qt5 COMPONENTS Core Network REQUIRED)
find_package(Cutelyst2Qt5 REQUIRED)

# Auto generate moc files
set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB_RECURSE TEMPLATES_SRC root/*)

set(OTHER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/README.md)

add_subdirectory(src)
