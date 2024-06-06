//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-import-module-list-spread-item-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTImportModuleListSpreadItemNode::ASTImportModuleListSpreadItemNode(ASTImportSpreadNode* spread, ASTImportModuleNameNode* moduleName) {
    _spread = spread;
    _moduleName = moduleName;
    _children.push_back(_spread);
    _children.push_back(_moduleName);
}

ASTImportModuleNameNode* ASTImportModuleListSpreadItemNode::getModuleName() {
    return _moduleName;
}

Position* ASTImportModuleListSpreadItemNode::getStartPosition() {
    return _spread->getStartPosition();
}

Position* ASTImportModuleListSpreadItemNode::getEndPosition() {
    return _moduleName->getEndPosition();
}

ASTNodeType ASTImportModuleListSpreadItemNode::getNodeType() {
    return AST_IMPORT_MODULE_LIST_SPREAD_ITEM_NODE;
}

std::string ASTImportModuleListSpreadItemNode::toString() {
    return "IMPORT_MODULE_LIST_SPREAD_ITEM";
}

bool ASTImportModuleListSpreadItemNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTImportModuleListSpreadItemNode*)other;
    return this->getModuleName()->isSameAs(otherNode->getModuleName());
}

void ASTImportModuleListSpreadItemNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleName->print();
    Logger::log("----------");
}

std::string ASTImportModuleListSpreadItemNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_spread)
    ->add(_moduleName);
    return sourceCodeBuilder.build();
}