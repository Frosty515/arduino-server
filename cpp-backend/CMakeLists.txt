cmake_minimum_required(VERSION 3.20)

project(cpp-backend CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(cpp-backend_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CommandParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PinControl.cpp
)

add_executable(cpp-backend ${cpp-backend_sources})

target_include_directories(cpp-backend PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(cpp-backend PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libserial/include)

set_target_properties(cpp-backend PROPERTIES CXX_STANDARD 20)
set_target_properties(cpp-backend PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(cpp-backend PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(cpp-backend PROPERTIES C_STANDARD 17)
set_target_properties(cpp-backend PROPERTIES C_STANDARD_REQUIRED ON)
set_target_properties(cpp-backend PROPERTIES C_EXTENSIONS OFF)

target_link_libraries(cpp-backend serial cjson)

target_compile_options(cpp-backend
    PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:-m64>
    PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:-Wall>
    PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:-Wextra>
    PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:-O2>
    PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:-g>
    PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
)

add_dependencies(cpp-backend serial)

add_subdirectory(dependencies/libserial)

install(TARGETS cpp-backend DESTINATION ${CMAKE_SOURCE_DIR}/bin)
