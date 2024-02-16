//
// Created by Johny Georges on 2024-02-09.
//

#include "ast-terminator-node.h"

ASTTerminatorNode::ASTTerminatorNode(Lexeme *lexeme) {
    _terminator = lexeme;
}

std::optional<ReduceNode*> accept(Recognizer* recognizer) {
    return recognizer->recognizeTerminatorNode()
}

ASTNodeType ASTTerminatorNode::getNodeType() {
    return AST_TERMINATOR_NODE;
}