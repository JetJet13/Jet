//
// Created by Johny Georges on 2024-04-06.
//

#include "ast-function-lambda-type-parameter-list-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTFunctionLambdaTypeParameterListNode::ASTFunctionLambdaTypeParameterListNode(ASTFunctionNode* functionKeyword, ASTTypeParameterListNode* typeParameterList) {
    _functionKeyword = functionKeyword;
    _typeParameterList = typeParameterList;
    _children.push_back(_functionKeyword);
    _children.push_back(_typeParameterList);
}

ASTTypeParameterListNode* ASTFunctionLambdaTypeParameterListNode::getTypeParameterList() {
    return _typeParameterList;
}

std::vector<ASTTypeNode*> ASTFunctionLambdaTypeParameterListNode::getParameters() {
    return _typeParameterList->getParameters();
}

unsigned long ASTFunctionLambdaTypeParameterListNode::numParameters() {
    return _typeParameterList->getParameters().size();
}

ASTFunctionLambdaTypeParameterListNode* ASTFunctionLambdaTypeParameterListNode::addParameter(ASTTypeNode* parameter) {
    _typeParameterList->getParameters().push_back(parameter);
    return this;
}

Position* ASTFunctionLambdaTypeParameterListNode::getStartPosition() {
    return _functionKeyword->getStartPosition();
}

Position* ASTFunctionLambdaTypeParameterListNode::getEndPosition() {
    return _typeParameterList->getEndPosition();
}

ASTNodeType ASTFunctionLambdaTypeParameterListNode::getNodeType() {
    return AST_FUNCTION_LAMBDA_TYPE_PARAMETER_LIST_NODE;
}

std::string ASTFunctionLambdaTypeParameterListNode::toString() {
    return "FUNCTION_LAMBDA_TYPE_PARAMETER_LIST";
}

bool ASTFunctionLambdaTypeParameterListNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTFunctionLambdaTypeParameterListNode*)other;
    return this->getTypeParameterList()->isSameAs(otherNode->getTypeParameterList());
}

void ASTFunctionLambdaTypeParameterListNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _typeParameterList->print();
    Logger::log("----------");
}

std::string ASTFunctionLambdaTypeParameterListNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_functionKeyword)
    ->add(_typeParameterList);
    return sourceCodeBuilder.build();
}