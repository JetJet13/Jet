//
// Created by Johny Georges on 2024-03-12.
//

#include "ast-array-access-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTArrayAccessNode::ASTArrayAccessNode(ASTLeftBracketNode* leftBracket, ASTExpressionNode* index, ASTRightBracketNode* rightBracket) {
    _leftBracket = leftBracket;
    _rightBracket = rightBracket;
    _index = index;
    _children.push_back(_leftBracket);
    _children.push_back(_rightBracket);
    _children.push_back(_index);
}

ASTExpressionNode* ASTArrayAccessNode::getIndex() {
    return _index;
}

ASTNodeType ASTArrayAccessNode::getNodeType() {
    return AST_ARRAY_ACCESS_NODE;
}

std::string ASTArrayAccessNode::toString() {
    return "ARRAY_ACCESS";
}

bool ASTArrayAccessNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTArrayAccessNode*)other;
    return _index->isSameAs(otherNode->getIndex());

}

void ASTArrayAccessNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _index->print();
    Logger::log("----------");
}

std::string ASTArrayAccessNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_leftBracket)
    ->add(_index)
    ->add(_rightBracket);
    return sourceCodeBuilder.build();
}