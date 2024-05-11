//
// Created by Johny Georges on 2024-03-22.
//

#include "ast-enum-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTEnumDeclarationNode::ASTEnumDeclarationNode(ASTEnumNameNode* name, ASTEnumKeyValueListNode* values) {
    _name = name;
    _values = values;
    _children.push_back(_name);
    _children.push_back(_values);
}

ASTEnumKeyValueListNode* ASTEnumDeclarationNode::getValues() {
    return _values;
}

ASTEnumNameNode* ASTEnumDeclarationNode::getName() {
    return _name;
}

ASTNodeType ASTEnumDeclarationNode::getNodeType() {
    return AST_ENUM_DECLARATION_NODE;
}

std::string ASTEnumDeclarationNode::toString() {
    return "ENUM_DECLARATION";
}

bool ASTEnumDeclarationNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTEnumDeclarationNode*)other;

    return  this->getName()->isSameAs(otherNode->getName()) &&
            this->getValues()->isSameAs(otherNode->getValues());
}

void ASTEnumDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _name->print();
    _values->print();
    Logger::log("----------");
}