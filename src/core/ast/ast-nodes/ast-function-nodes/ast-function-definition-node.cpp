//
// Created by Johny Georges on 2024-10-25.
//

#include "ast-function-definition-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTFunctionDefinitionNode::ASTFunctionDefinitionNode(std::shared_ptr<ASTFunctionNode> functionKeyword, std::shared_ptr<ASTFunctionNameNode> name, std::shared_ptr<ASTFunctionParameterListNode> parameters, std::shared_ptr<ASTTypeColonNode> typeColon, std::shared_ptr<ASTTypeNode> returnType) {
    _functionKeyword = functionKeyword;
    _name = name;
    _typeColon = typeColon;
    _returnType = returnType;
    _parameters = parameters;
    _children.push_back(_functionKeyword);
    _children.push_back(_name);
    _children.push_back(_parameters);
    _children.push_back(typeColon);
    _children.push_back(_returnType);
}

std::shared_ptr<ASTFunctionParameterListNode> ASTFunctionDefinitionNode::getParameters() {
    return _parameters;
}

std::shared_ptr<ASTFunctionNameNode> ASTFunctionDefinitionNode::getName() {
    return _name;
}

std::shared_ptr<ASTTypeNode> ASTFunctionDefinitionNode::getReturnType() {
    return _returnType;
}

uint64_t ASTFunctionDefinitionNode::numParameters() {
    return _parameters->numParameters();
}

std::shared_ptr<Position> ASTFunctionDefinitionNode::getStartPosition() {
    return _functionKeyword->getStartPosition();
}

std::shared_ptr<Position> ASTFunctionDefinitionNode::getEndPosition() {
    return _returnType->getEndPosition();
}

ASTNodeType ASTFunctionDefinitionNode::getNodeType() {
    return AST_FUNCTION_DEFINITION_NODE;
}

std::string ASTFunctionDefinitionNode::toString() {
    return "FUNCTION_DEFINITION";
}

bool ASTFunctionDefinitionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTFunctionDefinitionNode>(other);

    return  this->getName()->isSameAs(otherNode->getName()) &&
            this->getParameters()->isSameAs(otherNode->getParameters()) &&
            this->getReturnType()->isSameAs(otherNode->getReturnType());
}

void ASTFunctionDefinitionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _name->print();
    _parameters->print();
    _typeColon->print();
    _returnType->print();
    Logger::log("----------");
}

std::string ASTFunctionDefinitionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_functionKeyword);
    sourceCodeBuilder.add(_name)
    ->add(_parameters)
    ->add(_typeColon)
    ->add(_returnType);
    return sourceCodeBuilder.build();
}