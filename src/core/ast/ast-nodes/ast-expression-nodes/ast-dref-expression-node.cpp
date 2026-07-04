//
// Created by Johny Georges on 2025-01-15.
//

#include "ast-dref-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"


ASTDrefExpressionNode::ASTDrefExpressionNode(std::shared_ptr<ASTDrefNode> drefNode, std::shared_ptr<ASTExpressionNode> astExpressionNode) {
    _drefNode = drefNode;
    _expression = astExpressionNode;
    _children.push_back(_drefNode);
    _children.push_back(_expression);
}

std::shared_ptr<ASTExpressionNode> ASTDrefExpressionNode::getExpressionNode() {
    return _expression;
}

std::shared_ptr<ASTDrefNode> ASTDrefExpressionNode::getDrefNode() {
    return _drefNode;
}

Position* ASTDrefExpressionNode::getStartPosition() {
    return _drefNode->getStartPosition();
}

Position* ASTDrefExpressionNode::getEndPosition() {
    return _expression->getEndPosition();
}

ASTNodeType ASTDrefExpressionNode::getNodeType() {
    return AST_DREF_EXPRESSION_NODE;
}

std::string ASTDrefExpressionNode::toString() {
    return "DREF_EXPRESSION";
}

bool ASTDrefExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTDrefExpressionNode>(other);
    return this->getExpressionNode()->isSameAs(otherNode->getExpressionNode());
}

void ASTDrefExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _drefNode->print();
    _expression->print();
    Logger::log("----------");
}

std::string ASTDrefExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_drefNode)
    ->add(_expression);
    return sourceCodeBuilder.build();
}