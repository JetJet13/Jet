//
// Created by Johny Georges on 2024-04-13.
//

#include "ast-use-single-module-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTUseSingleModuleDeclarationNode::ASTUseSingleModuleDeclarationNode(std::shared_ptr<ASTUseNode> useKeyword, std::shared_ptr<ASTImportModuleNameNode> moduleName, std::shared_ptr<ASTFromNode> fromKeyword, std::shared_ptr<ASTImportPathNode> path) {
    _useKeyword = useKeyword;
    _moduleName = moduleName;
    _fromKeyword = fromKeyword;
    _path = path;
    _children.push_back(_moduleName);
    _children.push_back(_path);
}

std::shared_ptr<ASTImportModuleNameNode> ASTUseSingleModuleDeclarationNode::getModuleName() {
    return _moduleName;
}

std::shared_ptr<ASTImportPathNode> ASTUseSingleModuleDeclarationNode::getPath() {
    return _path;
}

Position* ASTUseSingleModuleDeclarationNode::getStartPosition() {
    return _useKeyword->getStartPosition();
}

Position* ASTUseSingleModuleDeclarationNode::getEndPosition() {
    return _path->getEndPosition();
}

ASTNodeType ASTUseSingleModuleDeclarationNode::getNodeType() {
    return AST_USE_SINGLE_MODULE_DECLARATION_NODE;
}

std::string ASTUseSingleModuleDeclarationNode::toString() {
    return "USE_SINGLE_MODULE_DECLARATION";
}

bool ASTUseSingleModuleDeclarationNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTUseSingleModuleDeclarationNode>(other);

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
    ->add(_moduleName)
    ->add(_fromKeyword)
    ->add(_path);
    return sourceCodeBuilder.build();
}