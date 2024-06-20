#ifndef MODEL_MEDIATOR_H
#define MODEL_MEDIATOR_H
#include <nlohmann/json.hpp>
#include "Model.h"
#include "DataSetReader.h"
#include "output_handler.h"

class ModelMediator
{
    public:
        int num_epochs;
        std::shared_ptr<Model> model;
        std::shared_ptr<DataSetReader> dataset_reader;
        std::shared_ptr<OutputHandler> output_handler;

        void run();
};


void from_json(const nlohmann::json& j, ModelMediator& p);

#endif