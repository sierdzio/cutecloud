file(GLOB_RECURSE cutecloud_SRCS *.cpp *.h)

set(cutecloud_SRCS
    ${cutecloud_SRCS}
    ${TEMPLATES_SRC}
)

# Create the application
add_library(cutecloud SHARED ${cutecloud_SRCS})

# Link to Cutelyst
target_link_libraries(cutecloud
    Cutelyst::Core
    Qt5::Core
    Qt5::Network
)

