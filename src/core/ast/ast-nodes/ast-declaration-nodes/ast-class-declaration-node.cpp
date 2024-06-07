//
// Created by Johny Georges on 2024-04-20.
//

#include "ast-class-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTClassDeclarationNode::ASTClassDeclarationNode(ASTClassNode* classKeyword, ASTClassNameNode* name, ASTClassBlockNode* block) {
    _classKeyword = classKeyword;
    _name = name;
    _block = block;
    _children.push_back(_classKeyword);
    _children.push_back(_name);
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

    return this->getName()->isSameAs(otherNode->getName()) &&
           this->getBlock()->isSameAs(otherNode->getBlock());
}

void ASTClassDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _name->print();
    _block->print();
    Logger::log("----------");
}

std::string ASTClassDeclarationNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_classKeyword)
    ->addWithWhitespace(_name)
    ->addWithWhitespace(_block);
    return sourceCodeBuilder.build();
}