//
// Created by Johny Georges on 2025-07-09.
//

#include "ast-lambda-type-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTLambdaTypeNode::ASTLambdaTypeNode(ASTLambdaTypeParameterListNode* parameterList, ASTLambdaTypeFatArrowNode* fatArrowNode, ASTTypeNode* returnType) {
    _parameterList = parameterList;
    _fatArrowNode = fatArrowNode;
    _returnType = returnType;
    _children.push_back(_parameterList);
    _children.push_back(_fatArrowNode);
    _children.push_back(_returnType);
}

ASTLambdaTypeParameterListNode* ASTLambdaTypeNode::getParameterList() {
    return _parameterList;
}

ASTTypeNode* ASTLambdaTypeNode::getReturnType() {
    return _returnType;
}

ASTNodeType ASTLambdaTypeNode::getNodeType() {
    return AST_LAMBDA_TYPE_NODE;
}

std::string ASTLambdaTypeNode::toString() {
    return "LAMBDA_TYPE";
}

bool ASTLambdaTypeNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTLambdaTypeNode*)other;

    return this->getParameterList()->isSameAs(otherNode->getParameterList()) &&
           this->getReturnType()->isSameAs(otherNode->getReturnType());
}

void ASTLambdaTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _parameterList->print();
    _returnType->print();
    Logger::log("----------");
}

std::string ASTLambdaTypeNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder
            .add(_parameterList)
            ->addWithWhitespace(_fatArrowNode)
            ->addWithWhitespace(_returnType);
    return sourceCodeBuilder.build();
}