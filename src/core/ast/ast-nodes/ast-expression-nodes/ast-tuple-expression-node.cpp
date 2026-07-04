//
// Created by Johny Georges on 2024-03-26.
//

#include "ast-tuple-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTTupleExpressionNode::ASTTupleExpressionNode(std::shared_ptr<ASTTupleListStartNode> tupleListStart, std::shared_ptr<ASTTupleListEndNode> tupleListEnd) {
    _tupleListStart = tupleListStart;
    _tupleListEnd = tupleListEnd;
    _commas = std::vector<std::shared_ptr<ASTCommaNode>>();
    _items = std::vector<std::shared_ptr<ASTTupleItemNode>>();
}

ASTTupleExpressionNode::ASTTupleExpressionNode(std::shared_ptr<ASTTupleListStartNode> tupleListStart, std::vector<std::shared_ptr<ASTTupleItemNode>> items, std::vector<std::shared_ptr<ASTCommaNode>> commas, std::shared_ptr<ASTTupleListEndNode> tupleListEnd) {
    _tupleListStart = tupleListStart;
    _tupleListEnd = tupleListEnd;
    _commas = commas;
    _items = std::vector<std::shared_ptr<ASTTupleItemNode>>();
    for (auto item: items) {
        this->addItem(item);
    }
}

std::vector<std::shared_ptr<ASTTupleItemNode>>* ASTTupleExpressionNode::getItems() {
    return &_items;
}

unsigned long ASTTupleExpressionNode::numItems() {
    return _items.size();
}

std::shared_ptr<ASTTupleExpressionNode> ASTTupleExpressionNode::addItem(std::shared_ptr<ASTTupleItemNode> item) {
    _items.push_back(item);
    _children.push_back(item);
    return std::dynamic_pointer_cast<ASTTupleExpressionNode>(shared_from_this());
}

std::shared_ptr<ASTTupleExpressionNode> ASTTupleExpressionNode::addComma(std::shared_ptr<ASTCommaNode> comma) {
    _commas.push_back(comma);
    return std::dynamic_pointer_cast<ASTTupleExpressionNode>(shared_from_this());
}

std::shared_ptr<TypeSignature> ASTTupleExpressionNode::getTypeSignature() {
    return _typeSignature;
}

std::shared_ptr<TupleTypeSignature> ASTTupleExpressionNode::getTupleTypeSignature() {
    return std::dynamic_pointer_cast<TupleTypeSignature>(_typeSignature);
}

void ASTTupleExpressionNode::setTypeSignature(std::shared_ptr<TupleTypeSignature> tupleTypeSignature) {
    _typeSignature = tupleTypeSignature;
}

Position* ASTTupleExpressionNode::getStartPosition() {
    return _tupleListStart->getStartPosition();
}

Position* ASTTupleExpressionNode::getEndPosition() {
    return _tupleListEnd->getEndPosition();
}

ASTNodeType ASTTupleExpressionNode::getNodeType() {
    return AST_TUPLE_EXPRESSION_NODE;
}

std::string ASTTupleExpressionNode::toString() {
    return "TUPLE_EXPRESSION";
}

bool ASTTupleExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTTupleExpressionNode>(other);
    if (this->numItems() != otherNode->numItems()) {
        return false;
    }
    for (unsigned long i = 0; i < this->numItems(); i++) {
        if (!_items[i]->isSameAs(otherNode->getItems()->at(i))) {
            return false;
        }
    }
    return true;
}

void ASTTupleExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto item : _items) {
        item->print();
    }
    Logger::log("----------");
}

std::string ASTTupleExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_tupleListStart);
    for (unsigned long i = 0; i < _items.size(); ++i) {
        sourceCodeBuilder.add(_items.at(i));
        if (i < _commas.size() ) {
            sourceCodeBuilder.add(_commas.at(i));
        }
    }
    sourceCodeBuilder.add(_tupleListEnd);
    return sourceCodeBuilder.build();
}