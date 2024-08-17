/*
Copyright (©) 2024  Frosty515

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef _SERVER_INTERNAL_HPP
#define _SERVER_INTERNAL_HPP

#include <string_view>

namespace Server {
    std::string_view& GetURL();

    std::string SendHTTPPostRequest(const std::string_view& subURL, const std::string_view& body);
}

#endif /* _SERVER_INTERNAL_HPP */