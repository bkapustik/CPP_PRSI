cmake_minimum_required(VERSION 3.5)
project(HelloWorld)

# Find SFML shared libraries
add_subdirectory(SFML-2.5.1)

file(GLOB SOURCES *.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-window sfml-graphics)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_BINARY_DIR}/SFML-2.5.1/lib"
         $<TARGET_FILE_DIR:${PROJECT_NAME}>
)