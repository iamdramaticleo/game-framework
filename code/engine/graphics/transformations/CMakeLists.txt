#=======================================================================================================================
project(transformations)
#=======================================================================================================================
add_executable(${PROJECT_NAME})
#=======================================================================================================================
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/build/engine/graphics/${PROJECT_NAME}"
                                                 RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/build/engine/graphics/${PROJECT_NAME}")
#=======================================================================================================================
target_link_libraries(${PROJECT_NAME}    PRIVATE tools)
#=======================================================================================================================
target_link_libraries(${PROJECT_NAME}    PRIVATE platform graphics resources core)
target_compile_features(${PROJECT_NAME}  PRIVATE cxx_std_23)
target_sources(${PROJECT_NAME}           PRIVATE main.cpp)
#=======================================================================================================================