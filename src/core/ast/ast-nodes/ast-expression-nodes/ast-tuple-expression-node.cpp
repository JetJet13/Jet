//
// Created by Johny Georges on 2024-03-26.
//

#include "ast-tuple-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ast-type-nodes/types/tuple-type.h"

ASTTupleExpressionNode::ASTTupleExpressionNode(ASTTupleListNode* tupleList) {
    _tupleList = tupleList;
}

ASTTupleListNode* ASTTupleExpressionNode::getTupleList() {
    return _tupleList;
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

BaseType* ASTTupleExpressionNode::getType() {
    auto tupleTypeParameterList = new std::vector<BaseType*>();
    for (auto tupleItem : _tupleList->getItems()) {
        tupleTypeParameterList->push_back(tupleItem->getItem()->getType());
    }
    return new TupleType(tupleTypeParameterList);
}