//
// Created by Johny Georges on 2024-03-22.
//

#ifndef JETLANG_PROCEDURE_DECLARATION_REDUCER_STRATEGY_H
#define JETLANG_PROCEDURE_DECLARATION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class ProcedureDeclarationReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_PROCEDURE_DECLARATION_REDUCER_STRATEGY_H
