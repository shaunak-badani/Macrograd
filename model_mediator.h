#ifndef MODEL_MEDIATOR_H
#define MODEL_MEDIATOR_H
#include <nlohmann/json.hpp>
#include "Model.h"
#include "DataSetReader.h"

class ModelMediator
{
    public:
        int num_epochs;
        std::shared_ptr<Model> model;
        std::shared_ptr<DataSetReader> dataset_reader;

        void run();
};


void from_json(const nlohmann::json& j, ModelMediator& p);

#endif