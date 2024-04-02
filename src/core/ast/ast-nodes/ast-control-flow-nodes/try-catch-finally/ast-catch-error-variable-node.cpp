//
// Created by Johny Georges on 2024-04-01.
//

#include "ast-catch-error-variable-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTCatchErrorVariableNode::ASTCatchErrorVariableNode(ASTIdentifierNode* identifier) {
    _identifier = identifier;
}

ASTIdentifierNode* ASTCatchErrorVariableNode::getIdentifier() {
    return _identifier;
}

ASTNodeType ASTCatchErrorVariableNode::getNodeType() {
    return AST_CATCH_ERROR_VARIABLE_NODE;
}

std::string ASTCatchErrorVariableNode::toString() {
    return "CATCH_ERROR_VARIABLE";
}

bool ASTCatchErrorVariableNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTCatchErrorVariableNode*)other;
    return this->getIdentifier()->isSameAs(otherNode->getIdentifier());
}

void ASTCatchErrorVariableNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _identifier->print();
    Logger::log("----------");
}