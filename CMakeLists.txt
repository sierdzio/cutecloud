cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
if (POLICY CMP0043)
  cmake_policy(SET CMP0043 NEW)
endif()

project(cutecloud_root
  DESCRIPTION "Cutelyst-based cloud solution - root directory"
  LANGUAGES CXX
)

#add_subdirectory(api)
add_subdirectory(cloud)
