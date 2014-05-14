
set(example1_sources example1.cpp)
add_executable(example1 ${example1_sources})
qt5_use_modules(example1 Core)
target_link_libraries(example1 gittin)
