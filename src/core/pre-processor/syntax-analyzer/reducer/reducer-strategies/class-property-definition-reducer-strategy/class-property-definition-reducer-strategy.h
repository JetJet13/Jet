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
    std::shared_ptr<ASTClassPropertyNameNode> getPropertyName(std::vector<std::shared_ptr<ASTNode>>* nodes);
    std::optional<std::shared_ptr<ASTStaticNode>> getStatic(std::vector<std::shared_ptr<ASTNode>>* nodes);
    std::optional<std::shared_ptr<ASTConstNode>> getConstant(std::vector<std::shared_ptr<ASTNode>>* nodes);
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_CLASS_PROPERTY_DEFINITION_REDUCER_STRATEGY_H
