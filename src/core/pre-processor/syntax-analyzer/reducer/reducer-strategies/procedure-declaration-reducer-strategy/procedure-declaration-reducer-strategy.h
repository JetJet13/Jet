//
// Created by Johny Georges on 2024-03-22.
//

#ifndef JETLANG_PROCEDURE_DECLARATION_REDUCER_STRATEGY_H
#define JETLANG_PROCEDURE_DECLARATION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class ProcedureDeclarationReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_PROCEDURE_DECLARATION_REDUCER_STRATEGY_H
