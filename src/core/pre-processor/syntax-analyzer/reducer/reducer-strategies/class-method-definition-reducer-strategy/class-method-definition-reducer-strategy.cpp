//
// Created by Johny Georges on 2024-04-26.
//

#include "class-method-definition-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-identifier-node.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-method-definition-node.h"

std::shared_ptr<ASTNode> ClassMethodDefinitionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() < 2 || nodes.size() > 3) {
        throw std::invalid_argument("unable to reduce to class method definition since nodes list size is < 2 or > 3");
    }

    return std::make_shared<ASTClassMethodDefinitionNode>(
            std::dynamic_pointer_cast<ASTAccessModifierNode>(nodes[0]),
            this->getMethodName(&nodes),
            this->getStatic(&nodes)
    );
}

std::shared_ptr<ASTClassMethodNameNode> ClassMethodDefinitionReducerStrategy::getMethodName(std::vector<std::shared_ptr<ASTNode>>* nodes) {
    if (nodes->size() == 3) {
        return std::dynamic_pointer_cast<ASTClassMethodNameNode>(nodes->at(2));
    } else {
        return std::dynamic_pointer_cast<ASTClassMethodNameNode>(nodes->at(1));
    }
}

std::optional<std::shared_ptr<ASTStaticNode>> ClassMethodDefinitionReducerStrategy::getStatic(std::vector<std::shared_ptr<ASTNode>>* nodes) {
    if (nodes->at(1)->is(AST_STATIC_NODE)) {
        return std::dynamic_pointer_cast<ASTStaticNode>(nodes->at(1));
    }
    return {};
}
