#include "Broadcast.h"


std::shared_ptr<Node> Broadcast::Add::calculate(std::shared_ptr<Node> operandA, std::shared_ptr<Node> operandB)
{
    // Broadcast will only work if matrices are of type:
    // (m, n) and (1, n)

    std::pair<int, int> aShape = operandA->data->getShape();
    std::pair<int, int> bShape = operandB->data->getShape();

    if(aShape.second != bShape.second)
        throw std::runtime_error("Matrices of shape (" 
                + std::to_string(aShape.first) + "," + std::to_string(aShape.second) + ") and ("
                + std::to_string(bShape.first) + "," + std::to_string(bShape.second) + ") cannot be broadcasted.");
            
    if(aShape.first == 1)
        return calculate(operandB, operandA);

    svf bMatrix = operandB->data->getPiece();
        
    std::shared_ptr<Mat> outMatrix = operandA->data->mapFunction([=](int i, int j, float value) {
        return value + bMatrix[0][j];
    });

    std::shared_ptr<Node> out = std::make_shared<Node>(outMatrix,
        std::unordered_set<std::shared_ptr<Node>>({operandA, operandB}));
    
    out->backward = getBackward(operandA, operandB, out);
    return out;
}

std::function<void(void)> Broadcast::Add::getBackward(std::shared_ptr<Node> operandA, std::shared_ptr<Node> operandB, std::shared_ptr<Node> out)
{
    std::weak_ptr<Node> weakA(operandA);
    std::weak_ptr<Node> weakB(operandB);
    std::weak_ptr<Node> weakOut(out);

    return [weakA, weakB, weakOut]() {
        std::shared_ptr<Node> operandAPtr = weakA.lock();
        if(!operandAPtr)
            throw std::runtime_error("Can't access operand A lock");

        std::shared_ptr<Node> operandBPtr = weakB.lock();
        if(!operandBPtr)
            throw std::runtime_error("Can't access operand B lock");

        std::shared_ptr<Node> outPtr = weakOut.lock();
        if(!outPtr)
            throw std::runtime_error("Can't access out lock");
        
        *(operandAPtr->grad.get()) += *outPtr->grad.get();

        svf& bGrad = operandBPtr->grad->getPiece();

        outPtr->grad->forEach([&bGrad](int i, int j, float value){
            bGrad[0][j] += value;
        });
    };
}