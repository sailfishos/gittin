
find_package(Qt5Core)

set(sources
    repo.cpp
    repostatus.cpp
    commit.cpp
    branch.cpp
    tag.cpp
    command.cpp
)

add_library(gittin SHARED ${sources})
qt5_use_modules(gittin Core)

install(TARGETS gittin LIBRARY DESTINATION ${DST_LIB})
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
install(FILES ${headers} DESTINATION include/gittin)
