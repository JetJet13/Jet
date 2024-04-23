//
// Created by Johny Georges on 2024-04-20.
//

#include "ast-class-constructor-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTClassConstructorNode::ASTClassConstructorNode(ASTFunctionParameterListNode* parameters, ASTFunctionBlockNode* content) {
    _content = content;
    _parameters = parameters;
}

ASTFunctionParameterListNode* ASTClassConstructorNode::getParameters() {
    return _parameters;
}

ASTFunctionBlockNode* ASTClassConstructorNode::getContent() {
    return _content;
}

unsigned long ASTClassConstructorNode::numParameters() {
    return _parameters->numParameters();
}

ASTNodeType ASTClassConstructorNode::getNodeType() {
    return AST_CLASS_CONSTRUCTOR_NODE;
}

std::string ASTClassConstructorNode::toString() {
    return "CLASS_CONSTRUCTOR";
}

bool ASTClassConstructorNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTClassConstructorNode*)other;

    return this->getParameters()->isSameAs(otherNode->getParameters()) &&
           this->getContent()->isSameAs(otherNode->getContent());
}

void ASTClassConstructorNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _parameters->print();
    _content->print();
    Logger::log("----------");
}