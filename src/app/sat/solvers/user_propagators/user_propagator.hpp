#pragma once

#include "cadical/src/cadical.hpp"
#include "util/logger.hpp"

// Include list of propagators so only this file needs to be included to get them all
#include "test_propagator.hpp"

void warnUnneededInfo(const std::string& upInfoPath) {
    if (upInfoPath == "") return;
    LOG(V1_WARN, "User propagator was provided info file \"%s\", but none is needed\n", upInfoPath.c_str());
}

CaDiCaL::ExternalPropagator* convertIdToUserPropagator(int id, const std::string& upInfoPath) {
    switch (id) {
        case 1:
            warnUnneededInfo(upInfoPath);
            return new TestPropagator();
        
        default:
            LOG(V0_CRIT, "Unknown user propagator id %d\n", id);
            break;
    }
    return nullptr;
}
