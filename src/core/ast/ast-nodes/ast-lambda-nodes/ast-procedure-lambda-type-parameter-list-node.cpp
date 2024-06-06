//
// Created by Johny Georges on 2024-04-06.
//

#include "ast-procedure-lambda-type-parameter-list-node.h"
#include "../../types/source-code-builder/source-code-builder.h"
#include "../../../../shared/utils/logger/logger.h"

ASTProcedureLambdaTypeParameterListNode::ASTProcedureLambdaTypeParameterListNode(ASTProcedureNode* procedureKeyword, ASTTypeParameterListNode* typeParameterList) {
    _procedureKeyword = procedureKeyword;
    _typeParameterList = typeParameterList;
    _children.push_back(_procedureKeyword);
    _children.push_back(_typeParameterList);
}

ASTTypeParameterListNode* ASTProcedureLambdaTypeParameterListNode::getTypeParameterList() {
    return _typeParameterList;
}

std::vector<ASTTypeNode*> ASTProcedureLambdaTypeParameterListNode::getParameters() {
    return _typeParameterList->getParameters();
}

unsigned long ASTProcedureLambdaTypeParameterListNode::numParameters() {
    return _typeParameterList->getParameters().size();
}

ASTProcedureLambdaTypeParameterListNode* ASTProcedureLambdaTypeParameterListNode::addParameter(ASTTypeNode* parameter) {
    _typeParameterList->getParameters().push_back(parameter);
    return this;
}

Position* ASTProcedureLambdaTypeParameterListNode::getStartPosition() {
    return _procedureKeyword->getStartPosition();
}

Position* ASTProcedureLambdaTypeParameterListNode::getEndPosition() {
    return _typeParameterList->getEndPosition();
}

ASTNodeType ASTProcedureLambdaTypeParameterListNode::getNodeType() {
    return AST_PROCEDURE_LAMBDA_TYPE_PARAMETER_LIST_NODE;
}

std::string ASTProcedureLambdaTypeParameterListNode::toString() {
    return "PROCEDURE_LAMBDA_TYPE_PARAMETER_LIST";
}

bool ASTProcedureLambdaTypeParameterListNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTProcedureLambdaTypeParameterListNode*)other;
    return this->getTypeParameterList()->isSameAs(otherNode->getTypeParameterList());
}

void ASTProcedureLambdaTypeParameterListNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _typeParameterList->print();
    Logger::log("----------");
}

std::string ASTProcedureLambdaTypeParameterListNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_procedureKeyword)
    ->add(_typeParameterList);
    return sourceCodeBuilder.build();
}