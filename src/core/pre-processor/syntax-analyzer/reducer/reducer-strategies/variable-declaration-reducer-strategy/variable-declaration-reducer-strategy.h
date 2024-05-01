//
// Created by Johny Georges on 2024-02-17.
//

#ifndef JETLANG_VARIABLE_DECLARATION_REDUCER_STRATEGY_H
#define JETLANG_VARIABLE_DECLARATION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../type-signature-generator/types/type-signature.h"
#include "../../../../../ast/ast-nodes/ast-variable-nodes/ast-variable-init-node.h"

class VariableDeclarationReducerStrategy : public ReducerStrategy {
private:
    TypeSignature* determineTypeSignature(ASTVariableInitNode* varInit, ASTExpressionNode* expression);
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_VARIABLE_DECLARATION_REDUCER_STRATEGY_H
