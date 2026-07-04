//
// Created by Johny Georges on 2024-04-25.
//

#ifndef JETLANG_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_NODE_H

#include <vector>
#include "../reducer-strategy.h"

class ClassPropertyAssignmentStatementReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_NODE_H
