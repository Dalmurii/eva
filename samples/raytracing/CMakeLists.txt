cmake_minimum_required(VERSION 3.16)

project(raytracing)

add_executable(${PROJECT_NAME}
    # client code
    main.cpp
    test.cpp

    # general
    math_types.h
    input.h
    camera.h
)

add_definitions(
    -DPROJECT_CURRENT_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    eva
)
