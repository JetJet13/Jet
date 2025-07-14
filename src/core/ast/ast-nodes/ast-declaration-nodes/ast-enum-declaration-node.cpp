//
// Created by Johny Georges on 2024-03-22.
//

#include "ast-enum-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTEnumDeclarationNode::ASTEnumDeclarationNode(ASTEnumNode* enumKeyword, ASTEnumNameNode* name, ASTEnumKeyValueListNode* values) {
    _enumKeyword = enumKeyword;
    _name = name;
    _values = values;
    _children.push_back(_enumKeyword);
    _children.push_back(_name);
    _children.push_back(_values);
}

ASTEnumKeyValueListNode* ASTEnumDeclarationNode::getValues() {
    return _values;
}

ASTEnumNameNode* ASTEnumDeclarationNode::getName() {
    return _name;
}

void ASTEnumDeclarationNode::setTypeSignature(EnumTypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

EnumTypeSignature* ASTEnumDeclarationNode::getTypeSignature() {
    return _typeSignature;
}

Position* ASTEnumDeclarationNode::getStartPosition() {
    return _enumKeyword->getStartPosition();
}

Position* ASTEnumDeclarationNode::getEndPosition() {
    return _values->getEndPosition();
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

std::string ASTEnumDeclarationNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_enumKeyword)
    ->add(_name)
    ->add(_values);
    return sourceCodeBuilder.build();
}