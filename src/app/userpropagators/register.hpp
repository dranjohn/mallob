#pragma once

#include <fstream>

#include "app/app_registry.hpp"
#include "data/job_description.hpp"
#include "interface/api/api_connector.hpp"
#include "util/logger.hpp"

struct ClientSideSatProgram : public app_registry::ClientSideProgram {
    ClientSideSatProgram(const Parameters& params, APIConnector& api, JobDescription& desc) :
        app_registry::ClientSideProgram()
    {
        LOG(V4_VVER, "Creating client side job\n");
        this->function = [&desc]() {
            JobResult res;
            res.id = desc.getId();
            res.revision = 0;
            res.result = 0;
            return res;
        };
    }
    virtual ~ClientSideSatProgram() {}
};

void register_mallob_app_userpropagators() {
    app_registry::AppEntry entry;
    entry.key = "USERPROPAGATORS";
    entry.type = app_registry::AppEntry::CLIENT_SIDE;

    entry.reader = [](const Parameters& params, const std::vector<std::string>& files, JobDescription& desc) {
        for (const std::string& file : files) {
            LOG(V4_VVER, "Reading input file %s\n", file.c_str());
        }
        LOG(V4_VVER, "Creating job with user propagator id %d\n", params.userPropagatorId());
        desc.beginInitialization(0);
        desc.endInitialization();
        return true;
    };

    entry.clientSideProgramCreator = [](const Parameters& params, APIConnector& api, JobDescription& desc) {
        return new ClientSideSatProgram(params, api, desc);
    };

    entry.solutionFormatter = [](const Parameters& params, const JobResult& result, const JobProcessingStatistics& stat) {
        auto json = nlohmann::json::array();
        auto model = result.copySolution();
        json = std::move(model);
        return json;
    };

    app_registry::registerApplication(entry);
}
