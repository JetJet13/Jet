//
// Created by Johny Georges on 2024-03-26.
//

#include "ast-tuple-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"


ASTTupleExpressionNode::ASTTupleExpressionNode(ASTTupleNode* tupleKeyword, ASTTupleListNode* tupleList) {
    _tupleKeyword = tupleKeyword;
    _tupleList = tupleList;
    _children.push_back(_tupleList);
}

ASTTupleListNode* ASTTupleExpressionNode::getTupleList() {
    return _tupleList;
}

Position* ASTTupleExpressionNode::getStartPosition() {
    return _tupleList->getStartPosition();
}

Position* ASTTupleExpressionNode::getEndPosition() {
    return _tupleList->getEndPosition();
}

ASTNodeType ASTTupleExpressionNode::getNodeType() {
    return AST_TUPLE_EXPRESSION_NODE;
}

std::string ASTTupleExpressionNode::toString() {
    return "TUPLE_EXPRESSION";
}

bool ASTTupleExpressionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTTupleExpressionNode*)other;

    return _tupleList->isSameAs(otherNode->getTupleList());
}

void ASTTupleExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _tupleList->print();
    Logger::log("----------");
}

std::string ASTTupleExpressionNode::toSourceCode() {
    return _tupleList->toSourceCode();
}