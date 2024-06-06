//
// Created by Johny Georges on 2024-04-09.
//

#include "ast-array-type-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTArrayTypeNode::ASTArrayTypeNode(ASTArrayTypeKeywordNode* arrayKeywordNode, ASTTypeParameterListNode* typeParameterList) {
    _arrayKeyword = arrayKeywordNode;
    _typeParameterList = typeParameterList;
    _children.push_back(_arrayKeyword);
    _children.push_back(_typeParameterList);
}

ASTTypeNode* ASTArrayTypeNode::getElementType() {
    return _typeParameterList->getParameters()[0];
}

Position* ASTArrayTypeNode::getStartPosition() {
    return _arrayKeyword->getStartPosition();
}

Position* ASTArrayTypeNode::getEndPosition() {
    return _typeParameterList->getEndPosition();
}

ASTNodeType ASTArrayTypeNode::getNodeType() {
    return AST_ARRAY_TYPE_NODE;
}

std::string ASTArrayTypeNode::toString() {
    return "ARRAY_TYPE";
}

bool ASTArrayTypeNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }

    auto otherNode = (ASTArrayTypeNode*)other;
    return this->getElementType()->isSameAs(otherNode->getElementType());
}

void ASTArrayTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _typeParameterList->print();
    Logger::log("----------");
}

std::string ASTArrayTypeNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_arrayKeyword)->add(_typeParameterList);
    return sourceCodeBuilder.build();
}