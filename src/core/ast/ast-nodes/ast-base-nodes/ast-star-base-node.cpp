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

std::shared_ptr<ASTNode> ASTStarBaseNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    if (prevNode && prevNode.value()->is(AST_MODULE_ACCESS_NODE)) {
        return std::make_shared<ASTImportWildcardNode>(_lexeme);
    }

    if (mode == SA_IMPORT_MODULE_LIST_MODE) {
        return std::make_shared<ASTImportModuleListWildcardItemNode>(_lexeme);
    }

    return std::make_shared<ASTBinaryArithmeticOperatorNode>(_lexeme);
}

ASTNodeType ASTStarBaseNode::getNodeType() {
    return AST_STAR_BASE_NODE;
}

std::string ASTStarBaseNode::toString() {
    return "STAR_BASE";
}
