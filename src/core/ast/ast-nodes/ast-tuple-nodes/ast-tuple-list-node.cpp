//
// Created by Johny Georges on 2024-03-26.
//

#include "ast-tuple-list-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTTupleListNode::ASTTupleListNode(ASTTupleListStartNode* tupleListStart, ASTTupleListEndNode* tupleListEnd) {
    _tupleListStart = tupleListStart;
    _tupleListEnd = tupleListEnd;
    _items = std::vector<ASTTupleItemNode*>();
}

ASTTupleListNode::ASTTupleListNode(ASTTupleListStartNode* tupleListStart, std::vector<ASTTupleItemNode*> items, ASTTupleListEndNode* tupleListEnd) {
    _tupleListStart = tupleListStart;
    _tupleListEnd = tupleListEnd;
    _items = std::vector<ASTTupleItemNode*>();
    for (auto item: items) {
        this->addItem(item);
    }
}

std::vector<ASTTupleItemNode*> ASTTupleListNode::getItems() {
    return _items;
}

void ASTTupleListNode::markAsReferenced() {
    for (auto item : _items) {
        item->getItem()->markAsReferenced();
    }
}

unsigned long ASTTupleListNode::numItems() {
    return _items.size();
}

ASTTupleListNode* ASTTupleListNode::addItem(ASTTupleItemNode* item) {
    _items.push_back(item);
    _children.push_back(item);
    return this;
}

Position* ASTTupleListNode::getStartPosition() {
    return _tupleListStart->getStartPosition();
}

Position* ASTTupleListNode::getEndPosition() {
    return _tupleListEnd->getEndPosition();
}

ASTNodeType ASTTupleListNode::getNodeType() {
    return AST_TUPLE_LIST_NODE;
}

std::string ASTTupleListNode::toString() {
    return "TUPLE_LIST";
}

bool ASTTupleListNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTTupleListNode*)other;
    auto otherNodeElements = otherNode->getItems();
    if (this->numItems() != otherNode->numItems()) {
        return false;
    }
    for (int i = 0; i < this->numItems(); i++) {
        if (!_items[i]->isSameAs(otherNodeElements[i])) {
            return false;
        }
    }

    return true;
}

void ASTTupleListNode::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto item : _items) {
        item->print();
    }
    Logger::log("----------");
}

std::string ASTTupleListNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_tupleListStart);
    for (auto item : _items) {
        sourceCodeBuilder.addWithWhitespace(item);
    }
    sourceCodeBuilder.add(_tupleListEnd);
    return sourceCodeBuilder.build();
}