//
// Created by Johny Georges on 2024-04-13.
//

#include "ast-import-single-module-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTImportSingleModuleDeclarationNode::ASTImportSingleModuleDeclarationNode(std::shared_ptr<ASTImportNode> importKeyword, std::shared_ptr<ASTImportModuleNameNode> moduleName, std::shared_ptr<ASTFromNode> fromKeyword, std::shared_ptr<ASTImportPathNode> path) {
    _importKeyword = importKeyword;
    _moduleName = moduleName;
    _fromKeyword = fromKeyword;
    _path = path;
    _children.push_back(_importKeyword);
    _children.push_back(_moduleName);
    _children.push_back(_fromKeyword);
    _children.push_back(_path);
}

std::shared_ptr<ASTImportModuleNameNode> ASTImportSingleModuleDeclarationNode::getModuleName() {
    return _moduleName;
}

std::shared_ptr<ASTImportPathNode> ASTImportSingleModuleDeclarationNode::getPath() {
    return _path;
}

std::shared_ptr<Position> ASTImportSingleModuleDeclarationNode::getStartPosition() {
    return _importKeyword->getStartPosition();
}

std::shared_ptr<Position> ASTImportSingleModuleDeclarationNode::getEndPosition() {
    return _path->getEndPosition();
}

ASTNodeType ASTImportSingleModuleDeclarationNode::getNodeType() {
    return AST_IMPORT_SINGLE_MODULE_DECLARATION_NODE;
}

std::string ASTImportSingleModuleDeclarationNode::toString() {
    return "IMPORT_SINGLE_MODULE_DECLARATION";
}

bool ASTImportSingleModuleDeclarationNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTImportSingleModuleDeclarationNode>(other);
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
    ->add(_moduleName)
    ->add(_fromKeyword)
    ->add(_path);
    return sourceCodeBuilder.build();
}