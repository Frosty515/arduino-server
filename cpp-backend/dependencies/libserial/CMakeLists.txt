set(serial_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SerialPort.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SerialStream.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SerialStreamBuf.cpp
)

add_library(serial STATIC ${serial_sources})

target_include_directories(serial PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(serial PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(serial PROPERTIES CXX_STANDARD 20)
set_target_properties(serial PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(serial PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(serial PROPERTIES C_STANDARD 17)
set_target_properties(serial PROPERTIES C_STANDARD_REQUIRED ON)
set_target_properties(serial PROPERTIES C_EXTENSIONS OFF)

target_compile_options(serial
    PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:-m64>
    PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:-Wall>
    PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:-Wextra>
    PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:-O2>
    PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:-g>
)