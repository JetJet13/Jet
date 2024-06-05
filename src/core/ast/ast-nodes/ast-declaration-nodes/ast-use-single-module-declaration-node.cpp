//
// Created by Johny Georges on 2024-04-13.
//

#include "ast-use-single-module-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTUseSingleModuleDeclarationNode::ASTUseSingleModuleDeclarationNode(ASTUseNode* useKeyword, ASTImportModuleNameNode* moduleName, ASTFromNode* fromKeyword, ASTImportPathNode* path) {
    _useKeyword = useKeyword;
    _moduleName = moduleName;
    _fromKeyword = fromKeyword;
    _path = path;
    _children.push_back(_moduleName);
    _children.push_back(_path);
}

ASTImportModuleNameNode* ASTUseSingleModuleDeclarationNode::getModuleName() {
    return _moduleName;
}

ASTImportPathNode* ASTUseSingleModuleDeclarationNode::getPath() {
    return _path;
}

ASTNodeType ASTUseSingleModuleDeclarationNode::getNodeType() {
    return AST_USE_SINGLE_MODULE_DECLARATION_NODE;
}

std::string ASTUseSingleModuleDeclarationNode::toString() {
    return "USE_SINGLE_MODULE_DECLARATION";
}

bool ASTUseSingleModuleDeclarationNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTUseSingleModuleDeclarationNode*)other;

    return  this->getModuleName()->isSameAs(otherNode->getModuleName()) &&
            this->getPath()->isSameAs(otherNode->getPath());
}

void ASTUseSingleModuleDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleName->print();
    _path->print();
    Logger::log("----------");
}

std::string ASTUseSingleModuleDeclarationNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_useKeyword)
    ->addWithWhitespace(_moduleName)
    ->addWithWhitespace(_fromKeyword)
    ->addWithWhitespace(_path);
    return sourceCodeBuilder.build();
}