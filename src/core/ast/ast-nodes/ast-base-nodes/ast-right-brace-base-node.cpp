//
// Created by Johny Georges on 2026-06-06.
//

#include "ast-right-brace-base-node.h"
#include "../ast-struct-nodes/ast-struct-end-node.h"
#include "../ast-enum-nodes/ast-enum-key-value-list-end-node.h"
#include "../ast-tuple-nodes/ast-tuple-list-end-node.h"
#include "../ast-module-nodes/ast-module-list-end-node.h"
#include "../ast-import-nodes/ast-import-module-list-end-node.h"
#include "../ast-interface-nodes/ast-interface-end-node.h"
#include "../ast-type-nodes/ast-struct-type-nodes/ast-struct-type-end-node.h"
#include "../ast-type-nodes/ast-tuple-type-nodes/ast-tuple-type-end-node.h"
#include "../ast-block-nodes/ast-block-end-node.h"

ASTNode* ASTRightBraceBaseNode::transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode, SyntaxAnalyzerMode mode) {
    if (mode == SA_STRUCT_MODE) {
        return new ASTStructEndNode(_lexeme);
    }

    if (mode == SA_ENUM_KEY_VALUE_LIST_MODE) {
        return new ASTEnumKeyValueListEndNode(_lexeme);
    }

    if (mode == SA_STRUCT_TYPE_MODE) {
        return new ASTStructTypeEndNode(_lexeme);
    }

    if (mode == SA_TUPLE_TYPE_MODE) {
        return new ASTTupleTypeEndNode(_lexeme);
    }

    if (mode == SA_TUPLE_LIST_MODE) {
        return new ASTTupleListEndNode(_lexeme);
    }

    if (mode == SA_INTERFACE_MODE) {
        return new ASTInterfaceEndNode(_lexeme);
    }

    if (mode == SA_MODULE_LIST_MODE) {
        return new ASTModuleListEndNode(_lexeme);
    }

    if (mode == SA_IMPORT_MODULE_LIST_MODE) {
        return new ASTImportModuleListEndNode(_lexeme);
    }

    if (mode != SA_INTERMEDIATE_MODE) {
        return new ASTBlockEndNode(_lexeme);
    }

    if (nextNode && nextNode.value()->is(AST_LEFT_BRACE_BASE_NODE)) {
        return new ASTTupleTypeEndNode(_lexeme);
    }

    return this;
}

ASTNodeType ASTRightBraceBaseNode::getNodeType() {
    return AST_RIGHT_BRACE_BASE_NODE;
}

std::string ASTRightBraceBaseNode::toString() {
    return "RIGHT_BRACE_BASE";
}