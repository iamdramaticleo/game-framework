project(graphics_index_buffer)

add_executable(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/build/${PROJECT_NAME}"
                                                 RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/build/${PROJECT_NAME}")

target_link_libraries(${PROJECT_NAME}   PRIVATE editor engine platform graphics)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_compile_options(${PROJECT_NAME}  PRIVATE /Wall)

target_sources(${PROJECT_NAME} PRIVATE main.cpp)