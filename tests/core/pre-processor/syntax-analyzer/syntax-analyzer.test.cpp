//
// Created by Johny Georges on 2024-02-23.
//

#include <catch2/catch_all.hpp>
#include "../../../../src/core/token/token-table.h"
#include "../../../../src/core/reserved-keywords/reserved-keywords.h"
#include "../../../../src/core/pre-processor/lexical-analyzer/lexical-analyzer.h"
#include "../../../../src/core/pre-processor/syntax-analyzer/syntax-analyzer.h"
#include "../../../../src/core/ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-literal-expression-node.h"
#include "../../../../src/core/symbol/symbol-factory.h"
#include "../../../../src/core/ast/ast-nodes/ast-literal-nodes/ast-int-literal-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-literal-nodes/ast-float-literal-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-literal-nodes/ast-string-literal-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-literal-nodes/ast-char-literal-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-literal-nodes/ast-boolean-literal-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-binary-expression-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-arithmetic-operators/ast-plus-operator-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-unary-expression-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-arithmetic-operators/ast-star-operator-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-arithmetic-operators/ast-minus-operator-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-arithmetic-operators/ast-slash-operator-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-arithmetic-operators/ast-modulo-operator-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-operator-nodes/ast-unary-operators/ast-unary-plus-operator.h"
#include "../../../../src/core/ast/ast-nodes/ast-operator-nodes/ast-unary-operators/ast-unary-minus-operator.h"
#include "../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-operator-nodes/ast-unary-operators/ast-bang-operator-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-logical-expression-node.h"

Lexeme* createLexeme(Symbol* symbol) {
    return new Lexeme(new Token(symbol), 1, 0);
}

std::vector<ASTNode*> expectedNodes = {
        //        LET VARIABLE DECLARATION
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createVarSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol())                                )
                        ),
                new ASTLiteralExpressionNode(
                        new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                        )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createVarSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol())                                )
                ),
                new ASTLiteralExpressionNode(
                        new ASTFloatLiteralNode(createLexeme(SymbolFactory::createFloatSymbol()))
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createVarSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol())                                )
                ),
                new ASTLiteralExpressionNode(
                        new ASTStringLiteralNode(createLexeme(SymbolFactory::createStringSymbol()))
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createVarSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol())                                )
                ),
                new ASTLiteralExpressionNode(
                        new ASTCharLiteralNode(createLexeme(SymbolFactory::createCharSymbol()))
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createVarSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol())                                )
                ),
                new ASTLiteralExpressionNode(
                        new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createTrueSymbol()))
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createVarSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol())                                )
                ),
                new ASTLiteralExpressionNode(
                        new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createFalseSymbol()))
                )
        ),
//        CONST VARIABLE DECLARATION
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol())                                )
                ),
                new ASTLiteralExpressionNode(
                        new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol())                                )
                ),
                new ASTLiteralExpressionNode(
                        new ASTFloatLiteralNode(createLexeme(SymbolFactory::createFloatSymbol()))
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol())                                )
                ),
                new ASTLiteralExpressionNode(
                        new ASTStringLiteralNode(createLexeme(SymbolFactory::createStringSymbol()))
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol())                                )
                ),
                new ASTLiteralExpressionNode(
                        new ASTCharLiteralNode(createLexeme(SymbolFactory::createCharSymbol()))
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol())                                )
                ),
                new ASTLiteralExpressionNode(
                        new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createTrueSymbol()))
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol())                                )
                ),
                new ASTLiteralExpressionNode(
                        new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createFalseSymbol()))
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTBinaryExpressionNode(
                        new ASTLiteralExpressionNode(
                                new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                        ),
                        new ASTPlusOperatorNode(createLexeme(SymbolFactory::createPlusSymbol())),
                        new ASTLiteralExpressionNode(
                                new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTBinaryExpressionNode(
                        new ASTBinaryExpressionNode(
                                new ASTLiteralExpressionNode(
                                        new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                                ),
                                new ASTPlusOperatorNode(createLexeme(SymbolFactory::createPlusSymbol())),
                                new ASTLiteralExpressionNode(
                                        new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                                )
                        ),
                        new ASTPlusOperatorNode(createLexeme(SymbolFactory::createPlusSymbol())),
                        new ASTLiteralExpressionNode(
                                new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTBinaryExpressionNode(
                        new ASTLiteralExpressionNode(
                                new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                        ),
                        new ASTMinusOperatorNode(createLexeme(SymbolFactory::createMinusSymbol())),
                        new ASTLiteralExpressionNode(
                                new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTBinaryExpressionNode(
                        new ASTLiteralExpressionNode(
                                new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                        ),
                        new ASTStarOperatorNode(createLexeme(SymbolFactory::createStarSymbol())),
                        new ASTLiteralExpressionNode(
                                new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTBinaryExpressionNode(
                        new ASTLiteralExpressionNode(
                                new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                        ),
                        new ASTSlashOperatorNode(createLexeme(SymbolFactory::createSlashSymbol())),
                        new ASTLiteralExpressionNode(
                                new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTBinaryExpressionNode(
                        new ASTLiteralExpressionNode(
                                new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                        ),
                        new ASTModuloOperatorNode(createLexeme(SymbolFactory::createModuloSymbol())),
                        new ASTLiteralExpressionNode(
                                new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTBinaryExpressionNode(
                        new ASTLiteralExpressionNode(
                                new ASTStringLiteralNode(createLexeme(SymbolFactory::createStringSymbol()))
                        ),
                        new ASTPlusOperatorNode(createLexeme(SymbolFactory::createPlusSymbol())),
                        new ASTLiteralExpressionNode(
                                new ASTStringLiteralNode(createLexeme(SymbolFactory::createStringSymbol()))
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTUnaryExpressionNode(
                        new ASTUnaryMinusOperatorNode(createLexeme(SymbolFactory::createMinusSymbol())),
                        new ASTLiteralExpressionNode(
                                new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTBinaryExpressionNode(
                        new ASTUnaryExpressionNode(
                                new ASTUnaryMinusOperatorNode(createLexeme(SymbolFactory::createMinusSymbol())),
                                new ASTLiteralExpressionNode(
                                        new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                                )
                        ),
                        new ASTPlusOperatorNode(createLexeme(SymbolFactory::createPlusSymbol())),
                        new ASTLiteralExpressionNode(
                                new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTBinaryExpressionNode(
                        new ASTUnaryExpressionNode(
                                new ASTUnaryMinusOperatorNode(createLexeme(SymbolFactory::createMinusSymbol())),
                                new ASTLiteralExpressionNode(
                                        new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                                )
                        ),
                        new ASTMinusOperatorNode(createLexeme(SymbolFactory::createMinusSymbol())),
                        new ASTLiteralExpressionNode(
                                new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTBinaryExpressionNode(
                        new ASTUnaryExpressionNode(
                                new ASTUnaryMinusOperatorNode(createLexeme(SymbolFactory::createMinusSymbol())),
                                new ASTLiteralExpressionNode(
                                        new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                                )
                        ),
                        new ASTStarOperatorNode(createLexeme(SymbolFactory::createStarSymbol())),
                        new ASTLiteralExpressionNode(
                                new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTBinaryExpressionNode(
                        new ASTUnaryExpressionNode(
                                new ASTUnaryMinusOperatorNode(createLexeme(SymbolFactory::createMinusSymbol())),
                                new ASTLiteralExpressionNode(
                                        new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                                )
                        ),
                        new ASTSlashOperatorNode(createLexeme(SymbolFactory::createSlashSymbol())),
                        new ASTLiteralExpressionNode(
                                new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTBinaryExpressionNode(
                        new ASTUnaryExpressionNode(
                                new ASTUnaryMinusOperatorNode(createLexeme(SymbolFactory::createMinusSymbol())),
                                new ASTLiteralExpressionNode(
                                        new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                                )
                        ),
                        new ASTSlashOperatorNode(createLexeme(SymbolFactory::createSlashSymbol())),
                        new ASTUnaryExpressionNode(
                                new ASTUnaryPlusOperatorNode(createLexeme(SymbolFactory::createPlusSymbol())),
                                new ASTLiteralExpressionNode(
                                        new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                                )
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTUnaryExpressionNode(
                        new ASTUnaryPlusOperatorNode(createLexeme(SymbolFactory::createPlusSymbol())),
                        new ASTLiteralExpressionNode(
                                new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTBinaryExpressionNode(
                        new ASTUnaryExpressionNode(
                                new ASTUnaryPlusOperatorNode(createLexeme(SymbolFactory::createPlusSymbol())),
                                new ASTLiteralExpressionNode(
                                        new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                                )
                        ),
                        new ASTPlusOperatorNode(createLexeme(SymbolFactory::createPlusSymbol())),
                        new ASTLiteralExpressionNode(
                                new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTBinaryExpressionNode(
                        new ASTUnaryExpressionNode(
                                new ASTUnaryPlusOperatorNode(createLexeme(SymbolFactory::createPlusSymbol())),
                                new ASTLiteralExpressionNode(
                                        new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                                )
                        ),
                        new ASTMinusOperatorNode(createLexeme(SymbolFactory::createMinusSymbol())),
                        new ASTLiteralExpressionNode(
                                new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTBinaryExpressionNode(
                        new ASTUnaryExpressionNode(
                                new ASTUnaryPlusOperatorNode(createLexeme(SymbolFactory::createPlusSymbol())),
                                new ASTLiteralExpressionNode(
                                        new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                                )
                        ),
                        new ASTStarOperatorNode(createLexeme(SymbolFactory::createStarSymbol())),
                        new ASTLiteralExpressionNode(
                                new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTBinaryExpressionNode(
                        new ASTUnaryExpressionNode(
                                new ASTUnaryPlusOperatorNode(createLexeme(SymbolFactory::createPlusSymbol())),
                                new ASTLiteralExpressionNode(
                                        new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                                )
                        ),
                        new ASTSlashOperatorNode(createLexeme(SymbolFactory::createSlashSymbol())),
                        new ASTLiteralExpressionNode(
                                new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTBinaryExpressionNode(
                        new ASTUnaryExpressionNode(
                                new ASTUnaryPlusOperatorNode(createLexeme(SymbolFactory::createPlusSymbol())),
                                new ASTLiteralExpressionNode(
                                        new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                                )
                        ),
                        new ASTSlashOperatorNode(createLexeme(SymbolFactory::createSlashSymbol())),
                        new ASTUnaryExpressionNode(
                                new ASTUnaryMinusOperatorNode(createLexeme(SymbolFactory::createMinusSymbol())),
                                new ASTLiteralExpressionNode(
                                        new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                                )
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTUnaryExpressionNode(
                        new ASTUnaryMinusOperatorNode(createLexeme(SymbolFactory::createMinusSymbol())),
                        new ASTIdentifierExpressionNode(
                                new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTUnaryExpressionNode(
                        new ASTBangOperatorNode(createLexeme(SymbolFactory::createBangSymbol())),
                        new ASTLiteralExpressionNode(
                                new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createTrueSymbol()))
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTUnaryExpressionNode(
                        new ASTBangOperatorNode(createLexeme(SymbolFactory::createBangSymbol())),
                        new ASTLiteralExpressionNode(
                                new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createFalseSymbol()))
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTUnaryExpressionNode(
                        new ASTBangOperatorNode(createLexeme(SymbolFactory::createBangSymbol())),
                        new ASTIdentifierExpressionNode(
                                new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTLogicalExpressionNode(
                        new ASTLiteralExpressionNode(
                                new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createTrueSymbol()))
                        ),
                        new ASTLogicalOperatorNode(createLexeme(SymbolFactory::createAndSymbol())),
                        new ASTLiteralExpressionNode(
                                new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createFalseSymbol()))
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTLogicalExpressionNode(
                        new ASTLiteralExpressionNode(
                                new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createTrueSymbol()))
                        ),
                        new ASTLogicalOperatorNode(createLexeme(SymbolFactory::createOrSymbol())),
                        new ASTLiteralExpressionNode(
                                new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createFalseSymbol()))
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTLogicalExpressionNode(
                        new ASTUnaryExpressionNode(
                                new ASTBangOperatorNode(createLexeme(SymbolFactory::createBangSymbol())),
                                new ASTIdentifierExpressionNode(
                                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                                )
                        ),
                        new ASTLogicalOperatorNode(createLexeme(SymbolFactory::createAndSymbol())),
                        new ASTLiteralExpressionNode(
                                new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createTrueSymbol()))
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTLogicalExpressionNode(
                        new ASTUnaryExpressionNode(
                                new ASTBangOperatorNode(createLexeme(SymbolFactory::createBangSymbol())),
                                new ASTLiteralExpressionNode(
                                        new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createFalseSymbol()))
                                )
                        ),
                        new ASTLogicalOperatorNode(createLexeme(SymbolFactory::createAndSymbol())),
                        new ASTLiteralExpressionNode(
                                new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createTrueSymbol()))
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTLogicalExpressionNode(
                        new ASTUnaryExpressionNode(
                                new ASTBangOperatorNode(createLexeme(SymbolFactory::createBangSymbol())),
                                new ASTIdentifierExpressionNode(
                                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                                )
                        ),
                        new ASTLogicalOperatorNode(createLexeme(SymbolFactory::createOrSymbol())),
                        new ASTLiteralExpressionNode(
                                new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createTrueSymbol()))
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTLogicalExpressionNode(
                        new ASTUnaryExpressionNode(
                                new ASTBangOperatorNode(createLexeme(SymbolFactory::createBangSymbol())),
                                new ASTLiteralExpressionNode(
                                        new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createFalseSymbol()))
                                )
                        ),
                        new ASTLogicalOperatorNode(createLexeme(SymbolFactory::createOrSymbol())),
                        new ASTLiteralExpressionNode(
                                new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createTrueSymbol()))
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTLogicalExpressionNode(
                        new ASTLogicalExpressionNode(
                                new ASTLiteralExpressionNode(
                                        new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createTrueSymbol()))
                                ),
                                new ASTLogicalOperatorNode(createLexeme(SymbolFactory::createAndSymbol())),
                                new ASTLiteralExpressionNode(
                                        new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createFalseSymbol()))
                                )
                        ),
                        new ASTLogicalOperatorNode(createLexeme(SymbolFactory::createOrSymbol())),
                        new ASTLiteralExpressionNode(
                                new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createTrueSymbol()))
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTLogicalExpressionNode(
                        new ASTLogicalExpressionNode(
                                new ASTUnaryExpressionNode(
                                        new ASTBangOperatorNode(createLexeme(SymbolFactory::createBangSymbol())),
                                        new ASTLiteralExpressionNode(
                                                new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createTrueSymbol()))
                                        )
                                ),
                                new ASTLogicalOperatorNode(createLexeme(SymbolFactory::createAndSymbol())),
                                new ASTLiteralExpressionNode(
                                        new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createFalseSymbol()))
                                )
                        ),
                        new ASTLogicalOperatorNode(createLexeme(SymbolFactory::createOrSymbol())),
                        new ASTLiteralExpressionNode(
                                new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createTrueSymbol()))
                        )
                )
        ),
};

TEST_CASE( "should print the expected reduced nodes" ) {
std::string filePath = "./syntax-analyzer-test-file.jet";
auto tokenTable = new TokenTable();
auto reservedKeywords = new ReservedKeywords();
auto lexicalAnalyzer = new LexicalAnalyzer(tokenTable, reservedKeywords);
auto syntaxAnalyzer = SyntaxAnalyzer(tokenTable, lexicalAnalyzer);
auto fileNodeResult = syntaxAnalyzer.analyze(filePath);
Logger::log("===== TEST LOGS =====");
REQUIRE(fileNodeResult->getBody().size() == 43);
    for (int i = 0; i < 43; i++) {
        Logger::log("=====",fileNodeResult->getBody()[i]->toString(),"=====");
        REQUIRE(fileNodeResult->getBody()[i]->isEqual(expectedNodes[i]));
        Logger::log("====================================");
    }
}