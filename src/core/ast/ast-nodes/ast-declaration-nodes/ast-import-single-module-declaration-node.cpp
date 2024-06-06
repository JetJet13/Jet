//
// Created by Johny Georges on 2024-04-13.
//

#include "ast-import-single-module-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTImportSingleModuleDeclarationNode::ASTImportSingleModuleDeclarationNode(ASTImportNode* importKeyword, ASTImportModuleNameNode* moduleName, ASTFromNode* fromKeyword, ASTImportPathNode* path) {
    _importKeyword = importKeyword;
    _moduleName = moduleName;
    _fromKeyword = fromKeyword;
    _path = path;
    _children.push_back(_importKeyword);
    _children.push_back(_moduleName);
    _children.push_back(_fromKeyword);
    _children.push_back(_path);
}

ASTImportModuleNameNode* ASTImportSingleModuleDeclarationNode::getModuleName() {
    return _moduleName;
}

ASTImportPathNode* ASTImportSingleModuleDeclarationNode::getPath() {
    return _path;
}

Position* ASTImportSingleModuleDeclarationNode::getStartPosition() {
    return _importKeyword->getStartPosition();
}

Position* ASTImportSingleModuleDeclarationNode::getEndPosition() {
    return _path->getEndPosition();
}

ASTNodeType ASTImportSingleModuleDeclarationNode::getNodeType() {
    return AST_IMPORT_SINGLE_MODULE_DECLARATION_NODE;
}

std::string ASTImportSingleModuleDeclarationNode::toString() {
    return "IMPORT_SINGLE_MODULE_DECLARATION";
}

bool ASTImportSingleModuleDeclarationNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTImportSingleModuleDeclarationNode*)other;
    return  this->getModuleName()->isSameAs(otherNode->getModuleName()) &&
            this->getPath()->isSameAs(otherNode->getPath());
}

void ASTImportSingleModuleDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleName->print();
    _path->print();
    Logger::log("----------");
}

std::string ASTImportSingleModuleDeclarationNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_importKeyword)
    ->addWithWhitespace(_moduleName)
    ->addWithWhitespace(_fromKeyword)
    ->addWithWhitespace(_path);
    return sourceCodeBuilder.build();
}