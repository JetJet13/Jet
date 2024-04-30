//
// Created by Johny Georges on 2024-04-09.
//

#include "ast-tuple-type-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "types/tuple-type.h"

ASTTupleTypeNode::ASTTupleTypeNode(ASTTypeParameterListNode* typeParameterList) {
    _typeParameterList = typeParameterList;
}

ASTTypeParameterListNode* ASTTupleTypeNode::getParameterList() {
    return _typeParameterList;
}

ASTNodeType ASTTupleTypeNode::getNodeType() {
    return AST_TUPLE_TYPE_NODE;
}

std::string ASTTupleTypeNode::toString() {
    return "TUPLE_TYPE";
}

bool ASTTupleTypeNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTTupleTypeNode*)other;
    return this->getParameterList()->isSameAs(otherNode->getParameterList());
}

void ASTTupleTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _typeParameterList->print();
    Logger::log("----------");
}

BaseType* ASTTupleTypeNode::getType() {
    auto tupleTypeParameterList = new std::vector<BaseType*>();
    for (auto parameter : _typeParameterList->getParameters()) {
        tupleTypeParameterList->push_back(parameter->getType());
    }

    return new TupleType(tupleTypeParameterList);
}