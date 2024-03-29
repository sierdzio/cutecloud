
project(mconfig
  VERSION 0.0.1
  DESCRIPTION "Milo Config"
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

set(SOURCES mbaseconfig.h mbaseconfig.cpp mconfig.h mconfig.cpp
  mmetaconfig.h mmetaconfig.cpp
)

option (mconfig-editors "Build GUI (QtWidgets) config editors" OFF)

if(mconfig-editors)
  find_package(Qt5 COMPONENTS REQUIRED Widgets)
  list(APPEND SOURCES editors/mmetaconfigeditor.h editors/mmetaconfigeditor.cpp
    editors/propertyeditor.h editors/propertyeditor.cpp
    editors/stringeditor.h editors/stringeditor.cpp)
endif(mconfig-editors)

set(OTHER_FILES README.md AUTHORS.md mconfig.doxyfile)

add_library(mconfig OBJECT ${SOURCES} ${OTHER_FILES})

target_include_directories(mconfig
  PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

# Mark all warnings as errors
if(WIN32)
  if(MSVC)
    #target_compile_options(mconfig PRIVATE -Werror -fPIC)
  endif()
else()
  target_compile_options(mconfig PRIVATE -Werror -fPIC)
endif()

# Enable LTCG (link time optimization)
option (ltcg "Enable LTCG (link time optimization)" ON)
if (ltcg)
  set_property(TARGET mconfig PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif (ltcg)

# Use C++ 14 standard
target_compile_features(mconfig PRIVATE cxx_std_14)

# Defines
target_compile_definitions(mconfig PRIVATE QT_USE_QSTRINGBUILDER PUBLIC
  MCONFIG_LIB)

if(mconfig-editors)
  target_link_libraries(mconfig
    Qt5::Core
    Qt5::Widgets
  )
else(mconfig-editors)
  target_link_libraries(mconfig
    Qt5::Core
  )
endif(mconfig-editors)
