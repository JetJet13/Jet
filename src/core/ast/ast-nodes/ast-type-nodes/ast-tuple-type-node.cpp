//
// Created by Johny Georges on 2024-04-09.
//

#include "ast-tuple-type-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTTupleTypeNodeDep::ASTTupleTypeNodeDep(ASTTupleNode* tupleNode, ASTTypeParameterListNode* typeParameterList) {
    _tupleNode = tupleNode;
    _typeParameterList = typeParameterList;
    _children.push_back(_typeParameterList);
}

ASTTypeParameterListNode* ASTTupleTypeNodeDep::getParameterList() {
    return _typeParameterList;
}

Position* ASTTupleTypeNodeDep::getStartPosition() {
    return _tupleNode->getStartPosition();
}

Position* ASTTupleTypeNodeDep::getEndPosition() {
    return _typeParameterList->getEndPosition();
}

ASTNodeType ASTTupleTypeNodeDep::getNodeType() {
    return AST_TUPLE_TYPE_NODE;
}

std::string ASTTupleTypeNodeDep::toString() {
    return "TUPLE_TYPE";
}

bool ASTTupleTypeNodeDep::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTTupleTypeNodeDep*)other;
    return this->getParameterList()->isSameAs(otherNode->getParameterList());
}

void ASTTupleTypeNodeDep::print() {
    Logger::log("----------", this->toString(), "----------");
    _typeParameterList->print();
    Logger::log("----------");
}

std::string ASTTupleTypeNodeDep::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_tupleNode)->add(_typeParameterList);
    return sourceCodeBuilder.build();
}