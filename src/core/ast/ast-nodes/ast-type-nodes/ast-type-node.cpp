//
// Created by Johny Georges on 2024-03-19.
//

#include "ast-type-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTTypeNode::ASTTypeNode(std::shared_ptr<ASTTypeBaseNode> type) {
    _type = type;
    _children.push_back(_type);
}

std::shared_ptr<ASTTypeBaseNode> ASTTypeNode::getType() {
    return _type;
}

void ASTTypeNode::setTypeSignature(std::shared_ptr<TypeSignature> typeSignature) {
    _type->setTypeSignature(typeSignature);
}

std::shared_ptr<TypeSignature> ASTTypeNode::getTypeSignature() {
    return _type->getTypeSignature();
}

Position* ASTTypeNode::getStartPosition() {
    return _type->getStartPosition();
}

Position* ASTTypeNode::getEndPosition() {
    return _type->getEndPosition();
}

ASTNodeType ASTTypeNode::getNodeType() {
    return AST_TYPE_NODE;
}

std::string ASTTypeNode::toString() {
    return "TYPE";
}

bool ASTTypeNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTTypeNode>(other);
    return _type->isSameAs(otherNode->getType());
}

void ASTTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _type->print();
    Logger::log("----------");
}

std::string ASTTypeNode::toSourceCode() {
    return _type->toSourceCode();
}