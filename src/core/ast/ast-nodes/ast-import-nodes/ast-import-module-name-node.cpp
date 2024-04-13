//
// Created by Johny Georges on 2024-04-13.
//

#include "ast-import-module-name-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTImportModuleNameNode::ASTImportModuleNameNode(ASTIdentifierNode* identifier) {
    _identifier = identifier;
}

ASTIdentifierNode* ASTImportModuleNameNode::getIdentifier() {
    return _identifier;
}

ASTNodeType ASTImportModuleNameNode::getNodeType() {
    return AST_IMPORT_MODULE_NAME_NODE;
}

std::string ASTImportModuleNameNode::toString() {
    return "IMPORT_MODULE_NAME";
}

bool ASTImportModuleNameNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTImportModuleNameNode*)other;
    return this->getIdentifier()->isSameAs(otherNode->getIdentifier());
}

void ASTImportModuleNameNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _identifier->print();
    Logger::log("----------");
}