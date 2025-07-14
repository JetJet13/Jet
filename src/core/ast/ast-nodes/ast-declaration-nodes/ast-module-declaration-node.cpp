//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-module-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTModuleDeclarationNode::ASTModuleDeclarationNode(ASTModuleNode* moduleKeyword, ASTModuleNameNode* name) {
    _moduleKeyword = moduleKeyword;
    _name = name;
    _children.push_back(_name);
}


ASTModuleNameNode* ASTModuleDeclarationNode::getName() {
    return _name;
}

std::vector<ASTNode*>* ASTModuleDeclarationNode::getExports() {
    return &_exportedDeclarations;
}

void ASTModuleDeclarationNode::addExportedDeclaration(ASTNode* declarationNode) {
    _exportedDeclarations.push_back(declarationNode);
}

void ASTModuleDeclarationNode::setTypeSignature(ModuleTypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

ModuleTypeSignature* ASTModuleDeclarationNode::getTypeSignature() {
    return _typeSignature;
}

Position* ASTModuleDeclarationNode::getStartPosition() {
    return _moduleKeyword->getStartPosition();
}

Position* ASTModuleDeclarationNode::getEndPosition() {
    return _moduleKeyword->getEndPosition();
}

ASTNodeType ASTModuleDeclarationNode::getNodeType() {
    return AST_MODULE_DECLARATION_NODE;
}

std::string ASTModuleDeclarationNode::toString() {
    return "MODULE_DECLARATION";
}

bool ASTModuleDeclarationNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTModuleDeclarationNode*)other;

    return  this->getName()->isSameAs(otherNode->getName());
}

void ASTModuleDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _name->print();
    Logger::log("----------");
}

std::string ASTModuleDeclarationNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_moduleKeyword)
    ->add(_name);
    return sourceCodeBuilder.build();
}