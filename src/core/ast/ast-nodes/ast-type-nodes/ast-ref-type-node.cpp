//
// Created by Johny Georges on 2025-02-07.
//

#include "ast-ref-type-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTRefTypeNode::ASTRefTypeNode(ASTRefTypeKeywordNode* refNode, ASTTypeParameterListNode* typeParameterList) {
    _ref = refNode;
    _typeParameterList = typeParameterList;
    _children.push_back(_ref);
    _children.push_back(_typeParameterList);
}

ASTTypeNode* ASTRefTypeNode::getRefType() {
    return _typeParameterList->getParameters()[0];
}

Position* ASTRefTypeNode::getStartPosition() {
    return _ref->getStartPosition();
}

Position* ASTRefTypeNode::getEndPosition() {
    return _typeParameterList->getEndPosition();
}

ASTNodeType ASTRefTypeNode::getNodeType() {
    return AST_REF_TYPE_NODE;
}

std::string ASTRefTypeNode::toString() {
    return "REF_TYPE";
}

bool ASTRefTypeNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }

    auto otherNode = (ASTRefTypeNode*)other;
    return this->getRefType()->isSameAs(otherNode->getRefType());
}

void ASTRefTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _typeParameterList->print();
    Logger::log("----------");
}

std::string ASTRefTypeNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_ref)->add(_typeParameterList);
    return sourceCodeBuilder.build();
}