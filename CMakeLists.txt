cmake_minimum_required(VERSION 3.13)
project(mn)

set(CMAKE_CXX_STANDARD 17)

add_executable(mn "Zajecia 2/main.cpp" "utils/Vector.h" "utils/Matrix.h")

include_directories(/usr/local/include)
include_directories(./utils)

target_link_libraries(mn
        m
        /usr/local/lib/libgslcblas.a
        /usr/local/lib/libgsl.a
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)