//
// Created by Johny Georges on 2024-04-13.
//

#include "ast-import-module-name-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTImportModuleNameNode::ASTImportModuleNameNode(std::shared_ptr<ASTIdentifierNode> identifier) {
    _identifier = identifier;
    _children.push_back(_identifier);
}

std::shared_ptr<ASTIdentifierNode> ASTImportModuleNameNode::getIdentifier() {
    return _identifier;
}

std::shared_ptr<Position> ASTImportModuleNameNode::getStartPosition() {
    return _identifier->getStartPosition();
}

std::shared_ptr<Position> ASTImportModuleNameNode::getEndPosition() {
    return _identifier->getEndPosition();
}

ASTNodeType ASTImportModuleNameNode::getNodeType() {
    return AST_IMPORT_MODULE_NAME_NODE;
}

std::string ASTImportModuleNameNode::toString() {
    return "IMPORT_MODULE_NAME";
}

bool ASTImportModuleNameNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTImportModuleNameNode>(other);
    return this->getIdentifier()->isSameAs(otherNode->getIdentifier());
}

void ASTImportModuleNameNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _identifier->print();
    Logger::log("----------");
}

std::string ASTImportModuleNameNode::toSourceCode() {
    return _identifier->toSourceCode();
}