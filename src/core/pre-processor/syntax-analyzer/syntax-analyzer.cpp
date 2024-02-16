//
// Created by Johny Georges on 2024-01-10.
//

#include "syntax-analyzer.h"
#include "../../ast/ast-nodes/ast-symbol-node.h"
#include "../../ast/ast-nodes/ast-identifier-node.h"
#include "../../ast/ast-nodes/ast-literal-nodes/ast-int-literal-node.h"
#include "../../ast/ast-nodes/ast-literal-nodes/ast-float-literal-node.h"
#include "../../ast/ast-nodes/ast-literal-nodes/ast-char-literal-node.h"
#include "../../ast/ast-nodes/ast-literal-nodes/ast-string-literal-node.h"
#include "../../ast/ast-nodes/ast-literal-nodes/ast-boolean-literal-node.h"
#include "../../ast/ast-nodes/ast-operator-nodes/ast-binary-operator-node.h"
#include "../../ast/ast-nodes/ast-operator-nodes/ast-logical-operator-node.h"
#include "../../ast/ast-nodes/ast-declaration-nodes/ast-variable-type-node.h"
#include "../../ast/ast-nodes/ast-operator-nodes/ast-assignment-operator-node.h"
#include "../../ast/ast-nodes/ast-terminator-node.h"

SyntaxAnalyzer::SyntaxAnalyzer(TokenTable *tokenTable, LexicalAnalyzer* lexicalAnalyzer) {
    _tokenTable = tokenTable;
    _reducer = Reducer();
    _handle = Handle();
    _stack = std::stack<ASTNode*>();
    _syntaxDfa = new SyntaxDfa();
    _lexicalAnalyzer = lexicalAnalyzer;
}

void SyntaxAnalyzer::analyze() {
    while (true) {
        auto reduceNode = this->recognizeHandle();
        if (reduceNode) {
            this->reduceHandle(reduceNode.value());
        } else {
            this->shift();
        }

        if (!_lexicalAnalyzer->hasMore()) {
            _handle.isEmpty() ? this->accept() : this->error();
            break;
        }
    }
}

std::optional<ReduceNode*> SyntaxAnalyzer::recognizeHandle() {
    if (_handle.isEmpty()) {
        return {};
    }
    if (_handle.size() == 1 && _handle.isNodeTypeAt(0, AST_TERMINATOR_NODE)) {
        if (_stack.empty()) {
            _handle.clear();
            return {};
        } else if (_stack.size() == 1) {
            _handle.push(_stack.top());
            auto reduceNode = new ReduceNode(1);
            _stack.pop();
            return reduceNode;
        } else {
            while (!_stack.empty()) {
                _handle.push(_stack.top());
                _stack.pop();
            }
            return _syntaxDfa->recognize(_handle);
        }
    }
    return _syntaxDfa->recognize(_handle);
}

ASTNode* SyntaxAnalyzer::convertLexemeToAstNode(Lexeme lexeme) {
    auto symbol = lexeme.getToken()->getSymbol();
    if (symbol->isVarTypeQualifier()) {
        return new ASTVariableTypeNode(&lexeme);
    } else if (symbol->isIdentifier()) {
        return new ASTIdentifierNode(&lexeme);
    } else if (symbol->isEqual()) {
        return new ASTAssignmentOperatorNode(&lexeme);
    } else if (symbol->isInt()) {
        return new ASTIntLiteralNode(&lexeme);
    } else if (symbol->isFloat()) {
        return new ASTFloatLiteralNode(&lexeme);
    } else if (symbol->isChar()) {
        return new ASTCharLiteralNode(&lexeme);
    } else if (symbol->isString()) {
        return new ASTStringLiteralNode(&lexeme);
    } else if (symbol->isBoolean()) {
        return new ASTBooleanLiteralNode(&lexeme);
    } else if (symbol->isArithmeticOperator() || symbol->isEqualityOperator()) {
        return new ASTBinaryOperatorNode(&lexeme);
    } else if (symbol->isLogicalOperator()) {
        return new ASTLogicalOperatorNode(&lexeme);
    } else if (symbol->isSemicolon()) {
        return new ASTTerminatorNode(&lexeme);
    } else {
        return new ASTSymbolNode(symbol);
    }
}

void SyntaxAnalyzer::shift() {
    auto nextLexeme = _lexicalAnalyzer->next();
    if (nextLexeme) {
        _handle.push(this->convertLexemeToAstNode(nextLexeme.value()));
    }
}

void SyntaxAnalyzer::reduceHandle(ReduceNode* reduceNode) {
    _stack.push(_reducer.reduce(_handle, reduceNode));
    _handle.removeFirstNodes(reduceNode->getNumReducedNodes());
}

void SyntaxAnalyzer::accept() {

}

void SyntaxAnalyzer::error() {

}
