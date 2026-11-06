#pragma once

#include <vector>
#include "cadical/src/cadical.hpp"
#include "util/logger.hpp"

class TestPropagator : public CaDiCaL::ExternalPropagator {
public:
    TestPropagator() {
        LOG(V2_INFO, "Starting test propagator\n");
    }

    void notify_assignment(const std::vector<int>& lits) override {
        for (int lit : lits) {
            //
        }
    }

    void notify_new_decision_level() override {
        //
    }

    void notify_backtrack(size_t new_level) override {
        //
    }


    bool cb_check_found_model(const std::vector<int>& model) override { return true; }
    bool cb_has_external_clause(bool& is_forgettable) override { return false; }
    int cb_add_external_clause_lit() override { return 0; }
};
