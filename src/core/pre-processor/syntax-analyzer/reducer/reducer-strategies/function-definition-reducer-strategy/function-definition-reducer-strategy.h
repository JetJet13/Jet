//
// Created by Johny Georges on 2024-10-25.
//

#ifndef JETLANG_FUNCTION_DEFINITION_REDUCER_STRATEGY_H
#define JETLANG_FUNCTION_DEFINITION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class FunctionDefinitionReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_FUNCTION_DEFINITION_REDUCER_STRATEGY_H
