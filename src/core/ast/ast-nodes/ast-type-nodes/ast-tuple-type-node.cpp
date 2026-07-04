//
// Created by Johny Georges on 2024-04-09.
//

#include "ast-tuple-type-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTTupleTypeNode::ASTTupleTypeNode(std::shared_ptr<ASTTupleNode> tupleNode, std::shared_ptr<ASTTypeParameterListNode> typeParameterList) {
    _tupleNode = tupleNode;
    _typeParameterList = typeParameterList;
    _children.push_back(_typeParameterList);
}

std::shared_ptr<ASTTypeParameterListNode> ASTTupleTypeNode::getParameterList() {
    return _typeParameterList;
}

Position* ASTTupleTypeNode::getStartPosition() {
    return _tupleNode->getStartPosition();
}

Position* ASTTupleTypeNode::getEndPosition() {
    return _typeParameterList->getEndPosition();
}

ASTNodeType ASTTupleTypeNode::getNodeType() {
    return AST_TUPLE_TYPE_NODE;
}

std::string ASTTupleTypeNode::toString() {
    return "TUPLE_TYPE";
}

bool ASTTupleTypeNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTTupleTypeNode>(other);
    return this->getParameterList()->isSameAs(otherNode->getParameterList());
}

void ASTTupleTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _typeParameterList->print();
    Logger::log("----------");
}

std::string ASTTupleTypeNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_tupleNode)->add(_typeParameterList);
    return sourceCodeBuilder.build();
}