//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-import-module-alias-name-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTImportModuleAliasNameNode::ASTImportModuleAliasNameNode(std::shared_ptr<ASTIdentifierNode> identifier) {
    _identifier = identifier;
    _children.push_back(_identifier);
}

std::shared_ptr<ASTIdentifierNode> ASTImportModuleAliasNameNode::getIdentifier() {
    return _identifier;
}

std::shared_ptr<Position> ASTImportModuleAliasNameNode::getStartPosition() {
    return _identifier->getStartPosition();
}

std::shared_ptr<Position> ASTImportModuleAliasNameNode::getEndPosition() {
    return _identifier->getEndPosition();
}

ASTNodeType ASTImportModuleAliasNameNode::getNodeType() {
    return AST_IMPORT_MODULE_ALIAS_NAME_NODE;
}

std::string ASTImportModuleAliasNameNode::toString() {
    return "IMPORT_MODULE_ALIAS_NAME";
}

bool ASTImportModuleAliasNameNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTImportModuleAliasNameNode>(other);
    return this->getIdentifier()->isSameAs(otherNode->getIdentifier());
}

void ASTImportModuleAliasNameNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _identifier->print();
    Logger::log("----------");
}

std::string ASTImportModuleAliasNameNode::toSourceCode() {
    return _identifier->toSourceCode();
}