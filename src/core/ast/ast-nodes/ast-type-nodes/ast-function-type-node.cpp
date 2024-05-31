//
// Created by Johny Georges on 2024-05-31.
//

#include "ast-function-type-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTFunctionTypeNode::ASTFunctionTypeNode(ASTFunctionLambdaTypeParameterListNode* parameterList, ASTLambdaTypeFatArrowNode* fatArrowNode, ASTTypeNode* returnType) {
    _parameterList = parameterList;
    _fatArrowNode = fatArrowNode;
    _returnType = returnType;
    _children.push_back(_parameterList);
    _children.push_back(_fatArrowNode);
    _children.push_back(_returnType);
}

ASTTypeParameterListNode* ASTFunctionTypeNode::getParameterList() {
    return _parameterList;
}

ASTTypeNode* ASTFunctionTypeNode::getReturnType() {
    return _returnType;
}

ASTNodeType ASTFunctionTypeNode::getNodeType() {
    return AST_FUNCTION_TYPE_NODE;
}

std::string ASTFunctionTypeNode::toString() {
    return "FUNCTION_TYPE";
}

bool ASTFunctionTypeNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTFunctionTypeNode*)other;

    return this->getParameterList()->isSameAs(otherNode->getParameterList()) &&
            this->getReturnType()->isSameAs(otherNode->getReturnType());
}

void ASTFunctionTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _parameterList->print();
    _returnType->print();
    Logger::log("----------");
}

std::string ASTFunctionTypeNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder
    .add(_parameterList)
    ->addWithWhitespace(_fatArrowNode)
    ->addWithWhitespace(_returnType);
    return sourceCodeBuilder.build();
}