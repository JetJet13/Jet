//
// Created by Johny Georges on 2025-07-09.
//

#include "ast-void-type-node.h"

#include "../../../../shared/utils/logger/logger.h"

ASTVoidTypeNode::ASTVoidTypeNode(std::shared_ptr<ASTVoidNode> voidNode) {
    _void = voidNode;
    _children.push_back(_void);
}

std::shared_ptr<Position> ASTVoidTypeNode::getStartPosition() {
    return _void->getStartPosition();
}

std::shared_ptr<Position> ASTVoidTypeNode::getEndPosition() {
    return _void->getEndPosition();
}

ASTNodeType ASTVoidTypeNode::getNodeType() {
    return AST_VOID_TYPE_NODE;
}

std::string ASTVoidTypeNode::toString() {
    return "VOID_TYPE";
}

bool ASTVoidTypeNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    return true;
}

void ASTVoidTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _void->print();
    Logger::log("----------");
}

std::string ASTVoidTypeNode::toSourceCode() {
    return _void->toSourceCode();
}