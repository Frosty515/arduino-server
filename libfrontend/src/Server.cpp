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

#include <Server.hpp>

#include <string_view>

#include "ServerInternal.hpp"
#include "HTTPRequest.hpp"

namespace Server {

    std::string_view g_url = "";

    http::Response SendPOSTRequest(const std::string& url, const std::string_view& body) {
        http::Request request{url};
        return request.send("POST", body, {
            {"Content-Type", "application/json"}
        });
    }

    void SetURL(const std::string_view& url) {
        g_url = url;
    }

    std::string_view& GetURL() {
        return g_url;
    }

    std::string SendHTTPPostRequest(const std::string_view& subURL, const std::string_view& body) {
        const http::Response response = SendPOSTRequest(std::string(g_url) + std::string(subURL), body);
        return {response.body.begin(), response.body.end()};
    }
}