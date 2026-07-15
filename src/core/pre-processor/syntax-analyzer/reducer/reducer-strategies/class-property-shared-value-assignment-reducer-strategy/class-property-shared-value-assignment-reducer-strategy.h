//
// Created by Johny Georges on 2026-02-18.
//

#ifndef JETLANG_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_REDUCER_STRATEGY_H
#define JETLANG_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-type-node.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-name-node.h"

class ClassPropertySharedValueAssignmentReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_REDUCER_STRATEGY_H
