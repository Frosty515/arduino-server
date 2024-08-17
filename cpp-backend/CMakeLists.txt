# Copyright (©) 2024  Frosty515

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

set(cpp-backend_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CommandParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PinControl.cpp
)

add_executable(cpp-backend ${cpp-backend_sources})

target_include_directories(cpp-backend PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(cpp-backend PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libserialport/)

set_target_properties(cpp-backend PROPERTIES CXX_STANDARD 23)
set_target_properties(cpp-backend PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(cpp-backend PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(cpp-backend PROPERTIES C_STANDARD 23)
set_target_properties(cpp-backend PROPERTIES C_STANDARD_REQUIRED ON)
set_target_properties(cpp-backend PROPERTIES C_EXTENSIONS OFF)
    
if (("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang") OR ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU"))
    target_compile_options(cpp-backend
        PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:-m64>
        PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:-Wall>
        PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:-Wextra>
        PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:-O2>
        PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:-g>
        PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
    )
    target_link_libraries(cpp-backend cjson ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libserialport/.libs/libserialport.a)
elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
    target_compile_options(cpp-backend
        PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:/Wall>
        PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:/sdl>
        PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:/O2>
        PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:/Z7>
    )
    target_link_libraries(cpp-backend ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/cJSON/out/build/x64-Debug/cJSON.dll ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libserialport/.libs/libserialport.dll)
endif()

#add_dependencies(cpp-backend serial)

#add_subdirectory(dependencies/libserial)

install(TARGETS cpp-backend DESTINATION ${CMAKE_SOURCE_DIR}/bin)
