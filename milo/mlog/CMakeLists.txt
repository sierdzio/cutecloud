
project(mlog
  VERSION 0.0.1
  DESCRIPTION "Milo Log"
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

set(SOURCES mlog.h mlog.cpp)

set(OTHER_FILES README.md AUTHORS.md mlog.doxyfile)

add_library(mlog OBJECT ${SOURCES} ${OTHER_FILES})

target_include_directories(mlog
  PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

# Mark all warnings as errors
if(WIN32)
  if(MSVC)
    #target_compile_options(indexertest PRIVATE -Werror -fPIC)
  endif()
else()
  target_compile_options(indexertest PRIVATE -Werror -fPIC)
endif()

# Enable LTCG (link time optimization)
option (ltcg "Enable LTCG (link time optimization)" ON)
if (ltcg)
  set_property(TARGET mlog PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif (ltcg)

# Use C++ 14 standard
target_compile_features(mlog PRIVATE cxx_std_14)

# Defines
target_compile_definitions(mlog PRIVATE QT_USE_QSTRINGBUILDER)

target_link_libraries(mlog
  Qt5::Core
)
