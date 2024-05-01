//
// Created by Johny Georges on 2024-03-26.
//

#include "ast-tuple-access-expression.h"
#include "../../../../shared/utils/logger/logger.h"
#include "ast-tuple-expression-node.h"

ASTTupleAccessExpressionNode::ASTTupleAccessExpressionNode(ASTObjectAccessSourceNode* source, ASTTupleAccessNode* index) {
    _source = source;
    _index = index;
}

ASTObjectAccessSourceNode* ASTTupleAccessExpressionNode::getSource() {
    return _source;
}

ASTTupleAccessNode* ASTTupleAccessExpressionNode::getIndex() {
    return _index;
}

ASTNodeType ASTTupleAccessExpressionNode::getNodeType() {
    return AST_TUPLE_ACCESS_EXPRESSION_NODE;
}

std::string ASTTupleAccessExpressionNode::toString() {
    return "TUPLE_ACCESS_EXPRESSION";
}

bool ASTTupleAccessExpressionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTTupleAccessExpressionNode*)other;
    return this->getSource()->isSameAs(otherNode->getSource()) &&
           this->getIndex()->isSameAs(otherNode->getIndex());
}

void ASTTupleAccessExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _source->print();
    _index->print();
    Logger::log("----------");
}

TypeSignature* ASTTupleAccessExpressionNode::getType() {
    auto tuple = (ASTTupleExpressionNode*)_source->getSource();
    return tuple
            ->getTupleList()
            ->getItems()[_index->getLexeme()->getToken()->getValueId().value()]
            ->getItem()
            ->getType();
}