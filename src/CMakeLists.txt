
find_package(Qt5Core)

set(sources
    repo.cpp
    repostatus.cpp
)

add_library(libgit SHARED ${sources})
qt5_use_modules(libgit Core)
