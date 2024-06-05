//
// Created by Johny Georges on 2024-04-22.
//

#ifndef JETLANG_CLASS_PROPERTY_DEFINITION_REDUCER_STRATEGY_H
#define JETLANG_CLASS_PROPERTY_DEFINITION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-type-node.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-name-node.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-static-node.h"
#include "../../../../../ast/ast-nodes/ast-const-node.h"

class ClassPropertyDefinitionReducerStrategy : public ReducerStrategy {
private:
    ASTClassPropertyNameNode* getPropertyName(std::vector<ASTNode*>* nodes);
    std::optional<ASTStaticNode*> getStatic(std::vector<ASTNode*>* nodes);
    std::optional<ASTConstNode*> getConstant(std::vector<ASTNode*>* nodes);
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_CLASS_PROPERTY_DEFINITION_REDUCER_STRATEGY_H
