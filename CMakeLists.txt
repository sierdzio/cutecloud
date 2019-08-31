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
option (build-indexer "Build indexer project (just for testing the file indexer)" OFF)
if (build-indexer)
    add_subdirectory(indexer)
endif (build-indexer)

option (build-cloud "Build cloud project (server-side)" ON)
if (build-cloud)
    add_subdirectory(cloud)
endif (build-cloud)

option (build-client "Build client project (desktop / mobile / WebAssembly)" ON)
if (build-client)
    add_subdirectory(client)
endif (build-client)
