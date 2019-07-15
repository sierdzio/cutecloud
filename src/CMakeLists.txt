set(cutecloud_SRCS root.h root.cpp cutecloud.h cutecloud.cpp
  utils/tags.h
  configs/cloudconfig.h configs/cloudconfig.cpp
)

add_subdirectory(milo/mconfig)
add_subdirectory(milo/mlog)

set(cutecloud_SRCS
  ${cutecloud_SRCS}
  ${TEMPLATES_SRC}
  ${OTHER_FILES}
)

# Create the application
add_library(cutecloud SHARED ${cutecloud_SRCS}
  $<TARGET_OBJECTS:mlog>
  $<TARGET_OBJECTS:mconfig>
)

target_include_directories(cutecloud PUBLIC
  $<TARGET_PROPERTY:mlog,INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:mconfig,INCLUDE_DIRECTORIES>
)

# Mark all warnings as errors
target_compile_options(cutecloud PRIVATE -Werror -fPIC)

# Defines
target_compile_definitions(cutecloud PRIVATE QT_USE_QSTRINGBUILDER)

# Enable LTCG (link time optimization)
option (ltcg "Enable LTCG (link time optimization)" ON)
if (ltcg)
  set_property(TARGET cutecloud PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
  message("Building with LTCG enabled")
endif (ltcg)

# Use C++ 14 standard
target_compile_features(cutecloud PRIVATE cxx_std_14)

# Link to Cutelyst
target_link_libraries(cutecloud
  Cutelyst::Core
  Qt5::Core
  Qt5::Network
)

