//
// Created by Johny Georges on 2024-04-26.
//

#include "class-method-definition-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-identifier-node.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-method-definition-node.h"

ASTNode* ClassMethodDefinitionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() < 2 || nodes.size() > 3) {
        throw std::invalid_argument("unable to reduce to class method definition since nodes list size is < 2 or > 3");
    }

    return new ASTClassMethodDefinitionNode(
            (ASTAccessModifierNode*)nodes[0],
            this->getMethodName(&nodes),
            this->getIsStatic(&nodes)
    );
}

ASTClassMethodNameNode* ClassMethodDefinitionReducerStrategy::getMethodName(std::vector<ASTNode*>* nodes) {
    if (nodes->size() == 3 && nodes->at(2)->is(AST_IDENTIFIER_NODE)) {
        return new ASTClassMethodNameNode(((ASTIdentifierNode*)nodes->at(2))->getIdentifier());
    } else {
        return new ASTClassMethodNameNode(((ASTIdentifierNode*)nodes->at(1))->getIdentifier());
    }
}

bool ClassMethodDefinitionReducerStrategy::getIsStatic(std::vector<ASTNode*>* nodes) {
    return nodes->at(1)->is(AST_STATIC_NODE);
}
