//
// Created by Johny Georges on 2024-04-20.
//

#include "ast-class-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTClassDeclarationNode::ASTClassDeclarationNode(ASTClassNode* classKeyword, ASTClassNameNode* name, ASTClassBlockNode* block, std::optional<ASTImplementsInterfaceListNode*> implementsInterfaceList) {
    _classKeyword = classKeyword;
    _name = name;
    _block = block;
    _implementsInterfaceList = implementsInterfaceList;
    _children.push_back(_classKeyword);
    _children.push_back(_name);
    if (_implementsInterfaceList) {
        _children.push_back(_implementsInterfaceList.value());
    }
    _children.push_back(_block);
}

ASTClassBlockNode* ASTClassDeclarationNode::getBlock() {
    return _block;
}

ASTClassNameNode* ASTClassDeclarationNode::getName() {
    return _name;
}

void ASTClassDeclarationNode::setTypeSignature(ClassTypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

std::optional<ASTImplementsInterfaceListNode*>* ASTClassDeclarationNode::getImplementsInterfaceList() {
    return &_implementsInterfaceList;
}

ClassTypeSignature* ASTClassDeclarationNode::getTypeSignature() {
    return _typeSignature;
}

Position* ASTClassDeclarationNode::getStartPosition() {
    return _classKeyword->getStartPosition();
}

Position* ASTClassDeclarationNode::getEndPosition() {
    return _block->getEndPosition();
}

ASTNodeType ASTClassDeclarationNode::getNodeType() {
    return AST_CLASS_DECLARATION_NODE;
}

std::string ASTClassDeclarationNode::toString() {
    return "CLASS_DECLARATION";
}

bool ASTClassDeclarationNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTClassDeclarationNode*)other;

    if (!_implementsInterfaceList.has_value() && otherNode->getImplementsInterfaceList()->has_value() ||
        _implementsInterfaceList.has_value() && !otherNode->getImplementsInterfaceList()->has_value()) {
        return false;
    }

    if (_implementsInterfaceList.has_value() && otherNode->getImplementsInterfaceList()->has_value() &&
        !_implementsInterfaceList.value()->isSameAs(otherNode->getImplementsInterfaceList()->value())) {
        return false;
    }

    return this->getName()->isSameAs(otherNode->getName()) &&
           this->getBlock()->isSameAs(otherNode->getBlock());
}

void ASTClassDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _name->print();
    if (_implementsInterfaceList) {
        _implementsInterfaceList.value()->print();
    }
    _block->print();
    Logger::log("----------");
}

std::string ASTClassDeclarationNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_classKeyword)
    ->addWithWhitespace(_name);
    if (_implementsInterfaceList) {
        sourceCodeBuilder.addWithWhitespace(_implementsInterfaceList.value());
    }
    sourceCodeBuilder.addWithWhitespace(_block);
    return sourceCodeBuilder.build();
}