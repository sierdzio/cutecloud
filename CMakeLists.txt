cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
if (POLICY CMP0043)
  cmake_policy(SET CMP0043 NEW)
endif()

project(cutecloud_root
  DESCRIPTION "Cutelyst-based cloud solution - root directory"
  LANGUAGES CXX
)

# Support libraries and projects:
add_subdirectory(milo/mconfig)
add_subdirectory(milo/mlog)
add_subdirectory(api)

# Main apps and libs:
add_subdirectory(indexer)
add_subdirectory(cloud)
add_subdirectory(client)
