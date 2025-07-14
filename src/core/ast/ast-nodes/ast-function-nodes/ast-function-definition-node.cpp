//
// Created by Johny Georges on 2024-10-25.
//

#include "ast-function-definition-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTFunctionDefinitionNode::ASTFunctionDefinitionNode(ASTFunctionNode* functionKeyword, ASTFunctionNameNode* name, ASTFunctionParameterListNode* parameters, ASTTypeNode* returnType) {
    _functionKeyword = functionKeyword;
    _name = name;
    _returnType = returnType;
    _parameters = parameters;
    _children.push_back(_functionKeyword);
    _children.push_back(_name);
    _children.push_back(_returnType);
    _children.push_back(_parameters);
}

ASTFunctionParameterListNode* ASTFunctionDefinitionNode::getParameters() {
    return _parameters;
}

ASTFunctionNameNode* ASTFunctionDefinitionNode::getName() {
    return _name;
}

ASTTypeNode* ASTFunctionDefinitionNode::getReturnType() {
    return _returnType;
}

unsigned long ASTFunctionDefinitionNode::numParameters() {
    return _parameters->numParameters();
}

Position* ASTFunctionDefinitionNode::getStartPosition() {
    return _functionKeyword->getStartPosition();
}

Position* ASTFunctionDefinitionNode::getEndPosition() {
    return _returnType->getEndPosition();
}

ASTNodeType ASTFunctionDefinitionNode::getNodeType() {
    return AST_FUNCTION_DEFINITION_NODE;
}

std::string ASTFunctionDefinitionNode::toString() {
    return "FUNCTION_DEFINITION";
}

bool ASTFunctionDefinitionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTFunctionDefinitionNode*)other;

    return  this->getName()->isSameAs(otherNode->getName()) &&
            this->getParameters()->isSameAs(otherNode->getParameters()) &&
            this->getReturnType()->isSameAs(otherNode->getReturnType());
}

void ASTFunctionDefinitionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _name->print();
    _parameters->print();
    _returnType->print();
    Logger::log("----------");
}

std::string ASTFunctionDefinitionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_functionKeyword);
    sourceCodeBuilder.add(_name)
    ->add(_parameters);
    return sourceCodeBuilder.build();
}