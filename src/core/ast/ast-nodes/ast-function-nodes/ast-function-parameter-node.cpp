//
// Created by Johny Georges on 2024-03-20.
//

#include "ast-function-parameter-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTFunctionParameterNode::ASTFunctionParameterNode(ASTIdentifierExpressionNode* identifier, ASTTypeColonNode* colon, ASTTypeNode* type) {
    _identifier = identifier;
    _colon = colon;
    _type = type;
    _children.push_back(_identifier);
    _children.push_back(_colon);
    _children.push_back(_type);
}

ASTIdentifierExpressionNode* ASTFunctionParameterNode::getIdentifier() {
    return _identifier;
}

ASTTypeNode* ASTFunctionParameterNode::getType() {
    return _type;
}

void ASTFunctionParameterNode::setTypeSignature(ParameterListItemTypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

ParameterListItemTypeSignature* ASTFunctionParameterNode::getTypeSignature() {
    return _typeSignature;
}

Position* ASTFunctionParameterNode::getStartPosition() {
    return _identifier->getStartPosition();
}

Position* ASTFunctionParameterNode::getEndPosition() {
    return _type->getEndPosition();
}

ASTNodeType ASTFunctionParameterNode::getNodeType() {
    return AST_FUNCTION_PARAMETER_NODE;
}

std::string ASTFunctionParameterNode::toString() {
    return "FUNCTION_PARAMETER";
}

bool ASTFunctionParameterNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTFunctionParameterNode*)other;
    return this->getIdentifier()->isSameAs(otherNode->getIdentifier()) &&
           this->getType()->isSameAs(otherNode->getType());
}

void ASTFunctionParameterNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _identifier->print();
    _type->print();
    Logger::log("----------");
}

std::string ASTFunctionParameterNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_identifier)
    ->add(_colon)
    ->add(_type);
    return sourceCodeBuilder.build();
}