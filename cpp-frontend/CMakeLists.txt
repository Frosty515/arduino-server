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

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk4)

set(cpp-frontend_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

add_executable(cpp-frontend ${cpp-frontend_sources})

target_include_directories(cpp-frontend PRIVATE ${CMAKE_SOURCE_DIR}/libfrontend/include)
target_include_directories(cpp-frontend PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(cpp-frontend PRIVATE ${GTK_INCLUDE_DIRS})

set_target_properties(cpp-frontend PROPERTIES CXX_STANDARD 23)
set_target_properties(cpp-frontend PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(cpp-frontend PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(cpp-frontend PROPERTIES C_STANDARD 23)
set_target_properties(cpp-frontend PROPERTIES C_STANDARD_REQUIRED ON)
set_target_properties(cpp-frontend PROPERTIES C_EXTENSIONS OFF)

if (("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang") OR ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU"))
    target_compile_options(cpp-frontend
        PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:-m64>
        PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:-Wall>
        PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:-Wextra>
        PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:-O2>
        PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:-g>
    )
    target_link_libraries(cpp-frontend frontend ${GTK_LIBRARIES})
elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
    target_compile_options(cpp-frontend
        PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:/Wall>
        PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:/sdl>
        PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:/O2>
        PRIVATE $<$<COMPILE_LANGUAGE:CXX,C>:/Z7>
    )
    target_link_libraries(cpp-frontend frontend)
endif()

install(TARGETS cpp-frontend DESTINATION ${CMAKE_SOURCE_DIR}/bin)
