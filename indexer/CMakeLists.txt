include(version.cmake)

cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
if (POLICY CMP0043)
  cmake_policy(SET CMP0043 NEW)
endif()

project(indexertest
  VERSION ${INDEXER_VERSION}
  DESCRIPTION "Test indexer for Cutecloud"
  LANGUAGES CXX
)

if(WIN32)
  if(MSVC)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
  endif()
endif()

find_package(Qt5 COMPONENTS Core REQUIRED)

# Auto generate moc files
set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Create code for Qt Resource Files
set(CMAKE_AUTORCC ON)

set(OTHER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/README.md)

set(indexer_SRCS
  main.cpp
)

set(indexer_SRCS
  ${indexer_SRCS}
  ${OTHER_FILES}
)

# Create the application
add_executable(indexertest ${indexer_SRCS}
  $<TARGET_OBJECTS:mlog>
  $<TARGET_OBJECTS:mconfig>
  $<TARGET_OBJECTS:api>
)

target_include_directories(indexertest PUBLIC
  $<TARGET_PROPERTY:mlog,INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:mconfig,INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:api,INCLUDE_DIRECTORIES>
  src
)

# Mark all warnings as errors
if(WIN32)
  if(MSVC)
    #target_compile_options(indexertest PRIVATE -Werror -fPIC)
  endif()
else()
  target_compile_options(indexertest PRIVATE -Werror -fPIC)
endif()

# Defines
target_compile_definitions(indexertest PRIVATE QT_USE_QSTRINGBUILDER)

# Enable LTCG (link time optimization)
option (ltcg "Enable LTCG (link time optimization)" ON)
if (ltcg)
  set_property(TARGET indexertest PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
  message("Building with LTCG enabled")
endif (ltcg)

# Use C++ 14 standard
target_compile_features(indexertest PRIVATE cxx_std_14)

# Link to Cutelyst
target_link_libraries(indexertest
  Qt5::Core
)
