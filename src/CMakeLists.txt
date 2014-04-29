
find_package(Qt5Core)

set(sources
    repo.cpp
    repostatus.cpp
    commit.cpp
    branch.cpp
    tag.cpp
    command.cpp
)

add_library(libgit SHARED ${sources})
qt5_use_modules(libgit Core)
