include(version.cmake)

cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
if (POLICY CMP0043)
  cmake_policy(SET CMP0043 NEW)
endif()

project(clienttest
  VERSION ${CLIENT_VERSION}
  DESCRIPTION "Test client for Cutecloud"
  LANGUAGES CXX
)

if(WIN32)
  if(MSVC)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
  endif()
endif()

find_package(Qt5 COMPONENTS Core Gui Network Widgets REQUIRED)

# Auto generate moc files
set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(OTHER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/README.md)

set(client_SRCS
  main.cpp
)

set(client_SRCS
  ${client_SRCS}
  ${OTHER_FILES}
)

# Create the application
add_executable(clienttest ${client_SRCS}
  $<TARGET_OBJECTS:mlog>
  $<TARGET_OBJECTS:mconfig>
  $<TARGET_OBJECTS:api>
)

target_include_directories(clienttest PUBLIC
  $<TARGET_PROPERTY:mlog,INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:mconfig,INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:api,INCLUDE_DIRECTORIES>
)

# Mark all warnings as errors
target_compile_options(clienttest PRIVATE -Werror -fPIC)

# Defines
target_compile_definitions(clienttest PRIVATE QT_USE_QSTRINGBUILDER)

# Enable LTCG (link time optimization)
option (ltcg "Enable LTCG (link time optimization)" ON)
if (ltcg)
  set_property(TARGET clienttest PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
  message("Building with LTCG enabled")
endif (ltcg)

# Use C++ 14 standard
target_compile_features(clienttest PRIVATE cxx_std_14)

# Link to Cutelyst
target_link_libraries(clienttest
  Qt5::Core
  Qt5::Gui
  Qt5::Network
  Qt5::Widgets
)
# Cutelyst::StaticSimple
