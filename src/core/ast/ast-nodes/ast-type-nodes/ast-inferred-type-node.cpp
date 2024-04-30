//
// Created by Johny Georges on 2024-04-29.
//

#include "ast-inferred-type-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTInferredTypeNode::ASTInferredTypeNode(BaseType* inferredType) {
    _inferredType = inferredType;
}


ASTNodeType ASTInferredTypeNode::getNodeType() {
    return AST_INFERRED_TYPE_NODE;
}

std::string ASTInferredTypeNode::toString() {
    return "INFERRED_TYPE";
}

bool ASTInferredTypeNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTInferredTypeNode*)other;
    return this->getType() == otherNode->getType();
}

void ASTInferredTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    Logger::log("TYPE: ", _inferredType);
    Logger::log("----------");
}

BaseType* ASTInferredTypeNode::getType() {
    return _inferredType;
}