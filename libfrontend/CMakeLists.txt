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

set(frontend_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PinControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Server.cpp
)

add_library(frontend STATIC ${frontend_sources})

target_include_directories(frontend PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(frontend PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

set_target_properties(frontend PROPERTIES CXX_STANDARD 23)
set_target_properties(frontend PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(frontend PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(frontend PROPERTIES C_STANDARD 23)
set_target_properties(frontend PROPERTIES C_STANDARD_REQUIRED ON)
set_target_properties(frontend PROPERTIES C_EXTENSIONS OFF)

if (("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang") OR ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU"))
    target_compile_options(frontend
        PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:-m64>
        PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:-Wall>
        PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:-Wextra>
        PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:-O2>
        PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:-g>
    )
    target_link_libraries(frontend cjson)
elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
    target_compile_options(frontend
        PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:/Wall>
        PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:/sdl>
        PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:/O2>
        PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:/Z7>
    )
    target_link_libraries(frontend ${CMAKE_CURRENT_SOURCE_DIR}/../cpp-backend/dependencies/cJSON/out/build/x64-Debug/cJSON.dll)
endif()

install(TARGETS frontend DESTINATION ${CMAKE_SOURCE_DIR}/bin)
