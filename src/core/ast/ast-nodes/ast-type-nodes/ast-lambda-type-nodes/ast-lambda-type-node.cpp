//
// Created by Johny Georges on 2025-07-09.
//

#include "ast-lambda-type-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTLambdaTypeNode::ASTLambdaTypeNode(std::shared_ptr<ASTLambdaTypeParameterListNode> parameterList, std::shared_ptr<ASTLambdaArrowNode> arrowNode, std::shared_ptr<ASTTypeNode> returnType) {
    _parameterList = parameterList;
    _arrowNode = arrowNode;
    _returnType = returnType;
    _children.push_back(_parameterList);
    _children.push_back(_arrowNode);
    _children.push_back(_returnType);
}

std::shared_ptr<ASTLambdaTypeParameterListNode> ASTLambdaTypeNode::getParameterList() {
    return _parameterList;
}

std::shared_ptr<ASTTypeNode> ASTLambdaTypeNode::getReturnType() {
    return _returnType;
}

std::shared_ptr<Position> ASTLambdaTypeNode::getStartPosition() {
    return _parameterList->getStartPosition();
}

std::shared_ptr<Position> ASTLambdaTypeNode::getEndPosition() {
    return _returnType->getEndPosition();
}

ASTNodeType ASTLambdaTypeNode::getNodeType() {
    return AST_LAMBDA_TYPE_NODE;
}

std::string ASTLambdaTypeNode::toString() {
    return "LAMBDA_TYPE";
}

bool ASTLambdaTypeNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTLambdaTypeNode>(other);

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
            ->add(_arrowNode)
            ->add(_returnType);
    return sourceCodeBuilder.build();
}