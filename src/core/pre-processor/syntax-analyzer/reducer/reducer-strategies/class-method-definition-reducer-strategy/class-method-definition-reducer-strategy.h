//
// Created by Johny Georges on 2024-04-26.
//

#ifndef JETLANG_CLASS_METHOD_DEFINITION_REDUCER_STRATEGY_H
#define JETLANG_CLASS_METHOD_DEFINITION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-type-node.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-name-node.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-method-name-node.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-static-node.h"

class ClassMethodDefinitionReducerStrategy : public ReducerStrategy {
private:
    ASTClassMethodNameNode* getMethodName(std::vector<ASTNode*>* nodes);
    std::optional<ASTStaticNode*> getStatic(std::vector<ASTNode*>* nodes);
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_CLASS_METHOD_DEFINITION_REDUCER_STRATEGY_H
