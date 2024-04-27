//
// Created by Johny Georges on 2024-03-13.
//

#include "ast-block-end-node.h"
#include "../ast-struct-nodes/ast-struct-end-node.h"
#include "../ast-enum-nodes/ast-enum-key-value-list-end-node.h"
#include "../ast-tuple-nodes/ast-tuple-list-end-node.h"
#include "../ast-module-nodes/ast-module-list-end-node.h"
#include "../ast-import-nodes/ast-import-module-list-end-node.h"

ASTBlockEndNode::ASTBlockEndNode(Lexeme* lexeme) {
    _lexeme = lexeme;
}

ASTNode * ASTBlockEndNode::transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode,
                                                SyntaxAnalyzerMode mode) {
    if (mode == SA_STRUCT_MODE) {
        return new ASTStructEndNode(_lexeme);
    }

    if (mode == SA_ENUM_KEY_VALUE_LIST_MODE) {
        return new ASTEnumKeyValueListEndNode(_lexeme);
    }

    if (mode == SA_TUPLE_LIST_MODE) {
        return new ASTTupleListEndNode(_lexeme);
    }

    if (mode == SA_MODULE_LIST_MODE) {
        return new ASTModuleListEndNode(_lexeme);
    }

    if (mode == SA_IMPORT_MODULE_LIST_MODE) {
        return new ASTImportModuleListEndNode(_lexeme);
    }
    
    return this;
}

ASTNodeType ASTBlockEndNode::getNodeType() {
    return AST_BLOCK_END_NODE;
}

std::string ASTBlockEndNode::toString() {
    return "BLOCK_END";
}