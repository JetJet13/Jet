//
// Created by Johny Georges on 2024-03-26.
//

#include "ast-tuple-access-expression.h"
#include "../../../../shared/utils/logger/logger.h"
#include "ast-tuple-expression-node.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTTupleAccessExpressionNode::ASTTupleAccessExpressionNode(std::shared_ptr<ASTObjectAccessSourceNode> source, std::shared_ptr<ASTPeriodNode> period, std::shared_ptr<ASTTupleAccessNode> index) {
    _source = source;
    _period = period;
    _index = index;
    _children.push_back(_source);
    _children.push_back(_period);
    _children.push_back(_index);
}

std::shared_ptr<ASTObjectAccessSourceNode> ASTTupleAccessExpressionNode::getSource() {
    return _source;
}

std::shared_ptr<ASTTupleAccessNode> ASTTupleAccessExpressionNode::getIndex() {
    return _index;
}

Position* ASTTupleAccessExpressionNode::getStartPosition() {
    return _source->getStartPosition();
}

Position* ASTTupleAccessExpressionNode::getEndPosition() {
    return _index->getEndPosition();
}

ASTNodeType ASTTupleAccessExpressionNode::getNodeType() {
    return AST_TUPLE_ACCESS_EXPRESSION_NODE;
}

std::string ASTTupleAccessExpressionNode::toString() {
    return "TUPLE_ACCESS_EXPRESSION";
}

bool ASTTupleAccessExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTTupleAccessExpressionNode>(other);
    return this->getSource()->isSameAs(otherNode->getSource()) &&
           this->getIndex()->isSameAs(otherNode->getIndex());
}

void ASTTupleAccessExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _source->print();
    _index->print();
    Logger::log("----------");
}


std::string ASTTupleAccessExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_source)
    ->add(_period)
    ->add(_index);
    return sourceCodeBuilder.build();
}
