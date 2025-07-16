//
// Created by Johny Georges on 2024-03-26.
//

#include "ast-tuple-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTTupleExpressionNode::ASTTupleExpressionNode(ASTTupleListStartNode* tupleListStart, ASTTupleListEndNode* tupleListEnd) {
    _tupleListStart = tupleListStart;
    _tupleListEnd = tupleListEnd;
    _commas = std::vector<ASTCommaNode*>();
    _items = std::vector<ASTTupleItemNode*>();
}

ASTTupleExpressionNode::ASTTupleExpressionNode(ASTTupleListStartNode* tupleListStart, std::vector<ASTTupleItemNode*> items, std::vector<ASTCommaNode*> commas, ASTTupleListEndNode* tupleListEnd) {
    _tupleListStart = tupleListStart;
    _tupleListEnd = tupleListEnd;
    _commas = commas;
    _items = std::vector<ASTTupleItemNode*>();
    for (auto item: items) {
        this->addItem(item);
    }
}

std::vector<ASTTupleItemNode*> ASTTupleExpressionNode::getItems() {
    return _items;
}

unsigned long ASTTupleExpressionNode::numItems() {
    return _items.size();
}

ASTTupleExpressionNode* ASTTupleExpressionNode::addItem(ASTTupleItemNode* item) {
    _items.push_back(item);
    _children.push_back(item);
    return this;
}

ASTTupleExpressionNode* ASTTupleExpressionNode::addComma(ASTCommaNode* comma) {
    _commas.push_back(comma);
    return this;
}

void ASTTupleExpressionNode::markAsReferenced() {
    _isReferenced = true;
}

TupleTypeSignature* ASTTupleExpressionNode::getTypeSignature() {
    return _typeSignature;
}

void ASTTupleExpressionNode::setTypeSignature(TupleTypeSignature* tupleTypeSignature) {
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

bool ASTTupleExpressionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTTupleExpressionNode*)other;
    if (this->numItems() != otherNode->numItems()) {
        return false;
    }
    for (int i = 0; i < this->numItems(); i++) {
        if (!_items[i]->isSameAs(otherNode->getItems()[i])) {
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
    for (int i = 0; i < _items.size(); ++i) {
        sourceCodeBuilder.add(_items.at(i));
        if (i < _commas.size() ) {
            sourceCodeBuilder.add(_commas.at(i));
        }
    }
    sourceCodeBuilder.add(_tupleListEnd);
    return sourceCodeBuilder.build();
}