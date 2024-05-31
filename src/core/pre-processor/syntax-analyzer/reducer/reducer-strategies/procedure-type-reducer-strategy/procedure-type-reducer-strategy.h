//
// Created by Johny Georges on 2024-05-31.
//

#ifndef JETLANG_PROCEDURE_TYPE_REDUCER_STRATEGY_H
#define JETLANG_PROCEDURE_TYPE_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class ProcedureTypeReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_PROCEDURE_TYPE_REDUCER_STRATEGY_H
