//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-module-list-spread-item-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTModuleListSpreadItemNode::ASTModuleListSpreadItemNode(ASTModuleNameNode* moduleName, ASTModuleSpreadNode* spread) {
    _moduleName = moduleName;
    _spread = spread;
    _children.push_back(_moduleName);
    _children.push_back(_spread);
}

ASTModuleNameNode* ASTModuleListSpreadItemNode::getModuleName() {
    return _moduleName;
}

Position* ASTModuleListSpreadItemNode::getStartPosition() {
    return _spread->getStartPosition();
}

Position* ASTModuleListSpreadItemNode::getEndPosition() {
    return _moduleName->getEndPosition();
}

ASTNodeType ASTModuleListSpreadItemNode::getNodeType() {
    return AST_MODULE_LIST_SPREAD_ITEM_NODE;
}

std::string ASTModuleListSpreadItemNode::toString() {
    return "MODULE_LIST_SPREAD_ITEM";
}

bool ASTModuleListSpreadItemNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTModuleListSpreadItemNode*)other;
    return this->getModuleName()->isSameAs(otherNode->getModuleName());
}

void ASTModuleListSpreadItemNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleName->print();
    Logger::log("----------");
}

std::string ASTModuleListSpreadItemNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_moduleName)
    ->add(_spread);
    return sourceCodeBuilder.build();
}