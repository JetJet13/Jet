//
// Created by Johny Georges on 2024-04-13.
//

#include "ast-star-base-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ast-operator-nodes/ast-unary-operators/ast-unary-operator-node.h"
#include "../ast-operator-nodes/ast-binary-operators/ast-binary-arithmetic-operator-node.h"
#include "../ast-import-nodes/ast-import-list-items/ast-import-module-list-wildcard-item-node.h"
#include "../ast-import-nodes/ast-import-wildcard-node.h"

ASTStarBaseNode::ASTStarBaseNode(Lexeme* lexeme) {
    _lexeme = lexeme;
}

ASTNode * ASTStarBaseNode::transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode, SyntaxAnalyzerMode mode) {
    if (prevNode && prevNode.value()->is(AST_MODULE_ACCESS_NODE)) {
        return new ASTImportWildcardNode(_lexeme);
    }

    if (mode == SA_IMPORT_MODULE_LIST_MODE) {
        return new ASTImportModuleListWildcardItemNode(_lexeme);
    }

    return new ASTBinaryArithmeticOperatorNode(_lexeme);
}

ASTNodeType ASTStarBaseNode::getNodeType() {
    return AST_STAR_BASE_NODE;
}

std::string ASTStarBaseNode::toString() {
    return "STAR_BASE";
}
