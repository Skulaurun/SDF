/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#pragma once

namespace sdf {

    void initNetwork();

    /*
        Just a friendly helper
        for SDF Network abstraction
    */
    struct NetworkInitHelper {
        NetworkInitHelper() {
            initNetwork();
        }
    };

}

/*
    This should be part of the private interface,
    but this header seemed kind of empty...
*/
#define SDF_REQUIRE_NETWORK_INIT(variable) \
    static NetworkInitHelper variable = {};
