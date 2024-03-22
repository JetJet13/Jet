//
// Created by Johny Georges on 2024-02-23.
//

#include <catch2/catch_all.hpp>
#include "./resources/ast-node-factory.h"
#include "../../../../src/core/reserved-keywords/reserved-keywords.h"
#include "../../../../src/core/pre-processor/lexical-analyzer/lexical-analyzer.h"
#include "../../../../src/core/pre-processor/syntax-analyzer/syntax-analyzer.h"
#include "../../../../src/core/ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-binary-expression-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-logical-expression-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-array-expression-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-array-access-expression.h"
#include "../../../../src/core/ast/ast-nodes/ast-array-nodes/ast-array-access-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-struct-expression-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-struct-access-expression-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-declaration-nodes/ast-function-declaration-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-function-nodes/ast-function-block-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-statement-nodes/ast-variable-assignment-statement-node.h"


std::unordered_map<int, ASTNode*> expectedNodes = {
        {1, new ASTVariableDeclarationNode(
                ASTNodeFactory::letInit,
                ASTNodeFactory::intExpression
        )},
        {2, new ASTVariableDeclarationNode(
                ASTNodeFactory::letInit,
                ASTNodeFactory::floatExpression
        )},
        {3, new ASTVariableDeclarationNode(
                ASTNodeFactory::letInit,
                ASTNodeFactory::stringExpression
        )},
        {4, new ASTVariableDeclarationNode(
                ASTNodeFactory::letInit,
                ASTNodeFactory::charExpression
        )},
        {5, new ASTVariableDeclarationNode(
                ASTNodeFactory::letInit,
                ASTNodeFactory::trueExpression
        )},
        {6, new ASTVariableDeclarationNode(
                ASTNodeFactory::letInit,
                ASTNodeFactory::falseExpression
        )},
        {7, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::intExpression
        )},
        {8, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::floatExpression
        )},
        {9, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::stringExpression
        )},
        {10, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::charExpression
        )},
        {11, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::trueExpression
        )},
        {12, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::falseExpression
        )},
        {13, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::intExpression,
                        ASTNodeFactory::plus,
                        ASTNodeFactory::intExpression
                )
        )},
        {14, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                    ASTNodeFactory::intExpression,
                    ASTNodeFactory::plus,
                new ASTBinaryExpressionNode(
                    ASTNodeFactory::intExpression,
                    ASTNodeFactory::plus,
                    ASTNodeFactory::intExpression
                )
                )
        )},
        {15, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::intExpression,
                        ASTNodeFactory::minus,
                        ASTNodeFactory::intExpression
                )
        )},
        {16, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::intExpression,
                        ASTNodeFactory::star,
                        ASTNodeFactory::intExpression
                )
        )},
        {17, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::intExpression,
                        ASTNodeFactory::slash,
                        ASTNodeFactory::intExpression
                )
        )},
        {18, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::intExpression,
                        ASTNodeFactory::modulo,
                        ASTNodeFactory::intExpression
                )
        )},
        {19, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::stringExpression,
                        ASTNodeFactory::plus,
                        ASTNodeFactory::stringExpression
                )
        )},
        {20, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::negativeInt
        )},
        {21, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::negativeInt,
                        ASTNodeFactory::plus,
                        ASTNodeFactory::intExpression
                )
        )},
        {22, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::negativeInt,
                        ASTNodeFactory::minus,
                        ASTNodeFactory::intExpression
                )
        )},
        {23, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::negativeInt,
                        ASTNodeFactory::star,
                        ASTNodeFactory::intExpression
                )
        )},
        {24, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::negativeInt,
                        ASTNodeFactory::slash,
                        ASTNodeFactory::intExpression
                )
        )},
        {25, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::negativeInt,
                        ASTNodeFactory::slash,
                        ASTNodeFactory::positiveInt
                )
        )},
        {26, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::positiveInt
        )},
        {27, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::positiveInt,
                        ASTNodeFactory::plus,
                        ASTNodeFactory::intExpression
                )
        )},
        {28, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::positiveInt,
                        ASTNodeFactory::minus,
                        ASTNodeFactory::intExpression
                )
        )},
        {29, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::positiveInt,
                        ASTNodeFactory::star,
                        ASTNodeFactory::intExpression
                )
        )},
        {30, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::positiveInt,
                        ASTNodeFactory::slash,
                        ASTNodeFactory::intExpression
                )
        )},
        {31, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::positiveInt,
                        ASTNodeFactory::slash,
                        ASTNodeFactory::negativeInt
                )
        )},
        {32, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTUnaryExpressionNode(
                        ASTNodeFactory::unaryMinus,
                        ASTNodeFactory::idExpression
                )
        )},
        {33, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::bangTrue
        )},
        {34, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::bangFalse
        )},
        {35, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::bangId
        )},
        {36, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLogicalExpressionNode(
                        ASTNodeFactory::trueExpression,
                        ASTNodeFactory::andOperator,
                        ASTNodeFactory::falseExpression
                )
        )},
        {37, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLogicalExpressionNode(
                        ASTNodeFactory::trueExpression,
                        ASTNodeFactory::orOperator,
                        ASTNodeFactory::falseExpression
                )
        )},
        {38, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLogicalExpressionNode(
                        ASTNodeFactory::bangId,
                        ASTNodeFactory::andOperator,
                        ASTNodeFactory::trueExpression
                )
        )},
        {39, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLogicalExpressionNode(
                        ASTNodeFactory::bangFalse,
                        ASTNodeFactory::andOperator,
                        ASTNodeFactory::trueExpression
                )
        )},
        {40, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLogicalExpressionNode(
                        ASTNodeFactory::bangId,
                        ASTNodeFactory::orOperator,
                        ASTNodeFactory::trueExpression
                )
        )},
        {41, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLogicalExpressionNode(
                        ASTNodeFactory::bangFalse,
                        ASTNodeFactory::orOperator,
                        ASTNodeFactory::trueExpression
                )
        )},
        {42, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLogicalExpressionNode(
                        ASTNodeFactory::trueExpression,
                        ASTNodeFactory::andOperator,
                new ASTLogicalExpressionNode(
                        ASTNodeFactory::falseExpression,
                        ASTNodeFactory::orOperator,
                        ASTNodeFactory::trueExpression
                )
                )
        )},
        {43, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLogicalExpressionNode(
                        ASTNodeFactory::bangTrue,
                        ASTNodeFactory::andOperator,
                        new ASTLogicalExpressionNode(
                                ASTNodeFactory::falseExpression,
                                ASTNodeFactory::orOperator,
                                ASTNodeFactory::trueExpression
                        )
                )
        )},
        {44, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLogicalExpressionNode(
                        ASTNodeFactory::intExpression,
                        ASTNodeFactory::andOperator,
                        ASTNodeFactory::intExpression
                )
        )},
        {45, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLogicalExpressionNode(
                        ASTNodeFactory::intExpression,
                        ASTNodeFactory::orOperator,
                        ASTNodeFactory::intExpression
                )
        )},
        {46, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLogicalExpressionNode(
                        ASTNodeFactory::bangInt,
                        ASTNodeFactory::andOperator,
                        ASTNodeFactory::intExpression
                )
        )},
        {47, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLogicalExpressionNode(
                        ASTNodeFactory::intExpression,
                        ASTNodeFactory::orOperator,
                        ASTNodeFactory::bangInt
                )
        )},
        {48, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLogicalExpressionNode(
                        new ASTUnaryExpressionNode(
                                ASTNodeFactory::bang,
                                ASTNodeFactory::intExpression
                        ),
                        ASTNodeFactory::andOperator,
                        new ASTUnaryExpressionNode(
                                ASTNodeFactory::bang,
                                ASTNodeFactory::intExpression
                        )
                )
        )},
        {49, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLogicalExpressionNode(
                        new ASTUnaryExpressionNode(
                                ASTNodeFactory::bang,
                                ASTNodeFactory::charExpression
                        ),
                        ASTNodeFactory::andOperator,
                        new ASTLogicalExpressionNode(
                                new ASTUnaryExpressionNode(
                                        ASTNodeFactory::bang,
                                        ASTNodeFactory::charExpression
                                ),
                                ASTNodeFactory::orOperator,
                                new ASTUnaryExpressionNode(
                                        ASTNodeFactory::bang,
                                        ASTNodeFactory::charExpression
                                )
                        )
                )
        )},
        {50, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::intExpression,
                        ASTNodeFactory::greaterThan,
                        ASTNodeFactory::intExpression
                )
        )},
        {51, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::intExpression,
                        ASTNodeFactory::greaterThanOrEqual,
                        ASTNodeFactory::intExpression
                )
        )},
        {52, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::intExpression,
                        ASTNodeFactory::lessThan,
                        ASTNodeFactory::intExpression
                )
        )},
        {53, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::intExpression,
                        ASTNodeFactory::lessThanOrEqual,
                        ASTNodeFactory::intExpression
                )
        )},
        {54, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::intExpression,
                        ASTNodeFactory::plus,
                        ASTNodeFactory::intExpression
                )
        )},
        {55, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::intExpression,
                        ASTNodeFactory::plus,
                        ASTNodeFactory::intExpression
                )
        )},
        {56, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::intExpression,
                        ASTNodeFactory::plus,
                        ASTNodeFactory::intExpression
                )
        )},
        {57, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        new ASTBinaryExpressionNode(
                                ASTNodeFactory::intExpression,
                                ASTNodeFactory::plus,
                                ASTNodeFactory::intExpression
                        ),
                        ASTNodeFactory::plus,
                        new ASTBinaryExpressionNode(
                                ASTNodeFactory::intExpression,
                                ASTNodeFactory::plus,
                                ASTNodeFactory::intExpression
                        )
                )
        )},
        {58, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        new ASTBinaryExpressionNode(
                                ASTNodeFactory::intExpression,
                                ASTNodeFactory::plus,
                                ASTNodeFactory::intExpression
                        ),
                        ASTNodeFactory::plus,
                        new ASTBinaryExpressionNode(
                                ASTNodeFactory::intExpression,
                                ASTNodeFactory::plus,
                                ASTNodeFactory::intExpression
                        )
                )
        )},
        {59, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLogicalExpressionNode(
                        new ASTBinaryExpressionNode(
                                ASTNodeFactory::intExpression,
                                ASTNodeFactory::plus,
                                ASTNodeFactory::intExpression
                        ),
                        ASTNodeFactory::orOperator,
                        new ASTBinaryExpressionNode(
                                ASTNodeFactory::intExpression,
                                ASTNodeFactory::plus,
                                ASTNodeFactory::intExpression
                        )
                )
        )},
        {60, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTUnaryExpressionNode(
                        ASTNodeFactory::bang,
                        ASTNodeFactory::trueExpression
                )
        )},
        {61, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTUnaryExpressionNode(
                        ASTNodeFactory::bang,
                        new ASTUnaryExpressionNode(
                            ASTNodeFactory::bang,
                            ASTNodeFactory::trueExpression
                        )
                )
        )},
        {62, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLogicalExpressionNode(
                        new ASTUnaryExpressionNode(
                                ASTNodeFactory::bang,
                                new ASTUnaryExpressionNode(
                                        ASTNodeFactory::bang,
                                        ASTNodeFactory::trueExpression
                                )
                        ),
                        ASTNodeFactory::andOperator,
                        new ASTUnaryExpressionNode(
                                ASTNodeFactory::bang,
                                new ASTUnaryExpressionNode(
                                        ASTNodeFactory::bang,
                                        ASTNodeFactory::falseExpression
                                )
                        )
                        )
        )},
        {63, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::intExpression,
                        ASTNodeFactory::plus,
                        new ASTBinaryExpressionNode(
                                new ASTBinaryExpressionNode(
                                        ASTNodeFactory::intExpression,
                                        ASTNodeFactory::plus,
                                        ASTNodeFactory::intExpression
                                        ),
                                        ASTNodeFactory::plus,
                                        ASTNodeFactory::intExpression
                                )
                )
        )},
        {64, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLogicalExpressionNode(
                        ASTNodeFactory::trueExpression,
                        ASTNodeFactory::andOperator,
                        new ASTLogicalExpressionNode(
                                new ASTLogicalExpressionNode(
                                        ASTNodeFactory::trueExpression,
                                        ASTNodeFactory::orOperator,
                                        ASTNodeFactory::trueExpression
                                ),
                                ASTNodeFactory::andOperator,
                                ASTNodeFactory::trueExpression
                        )
                )
        )},
        {65, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTUnaryExpressionNode(
                        ASTNodeFactory::bang,
                        new ASTLogicalExpressionNode(
                                ASTNodeFactory::trueExpression,
                                ASTNodeFactory::andOperator,
                            new ASTUnaryExpressionNode(
                                        ASTNodeFactory::bang,
                                new ASTLogicalExpressionNode(
                                        new ASTUnaryExpressionNode(
                                            ASTNodeFactory::bang,
                                            new ASTLogicalExpressionNode(
                                                    ASTNodeFactory::trueExpression,
                                                    ASTNodeFactory::orOperator,
                                                    ASTNodeFactory::trueExpression
                                            )
                                        ),
                                        ASTNodeFactory::andOperator,
                                        ASTNodeFactory::trueExpression
                                )
                            )
                        )
                )
        )},
        {66, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::intExpression,
                        ASTNodeFactory::plus,
                        new ASTBinaryExpressionNode(
                                ASTNodeFactory::intExpression,
                                ASTNodeFactory::star,
                                ASTNodeFactory::intExpression
                        )
                )
        )},
        {67, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        new ASTBinaryExpressionNode(
                        ASTNodeFactory::intExpression,
                        ASTNodeFactory::star,
                        ASTNodeFactory::intExpression
                        ),
                        ASTNodeFactory::plus,
                        ASTNodeFactory::intExpression
                )
        )},
        {68, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::intExpression,
                        ASTNodeFactory::star,
                        new ASTBinaryExpressionNode(
                            ASTNodeFactory::intExpression,
                            ASTNodeFactory::plus,
                            ASTNodeFactory::intExpression
                        )
                )
        )},
        {69, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::intExpression,
                        ASTNodeFactory::star,
                        new ASTBinaryExpressionNode(
                                ASTNodeFactory::intExpression,
                                ASTNodeFactory::slash,
                                ASTNodeFactory::intExpression
                        )
                )
        )},
        {70, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        new ASTBinaryExpressionNode(
                            new ASTBinaryExpressionNode(
                                ASTNodeFactory::intExpression,
                                ASTNodeFactory::star,
                                ASTNodeFactory::intExpression
                            ),
                            ASTNodeFactory::minus,
                            ASTNodeFactory::intExpression
                        ),
                        ASTNodeFactory::plus,
                        ASTNodeFactory::intExpression
                )
        )},
        {71, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        new ASTBinaryExpressionNode(
                                new ASTBinaryExpressionNode(
                                        ASTNodeFactory::intExpression,
                                        ASTNodeFactory::star,
                                        ASTNodeFactory::intExpression
                                ),
                                ASTNodeFactory::minus,
                                ASTNodeFactory::intExpression
                        ),
                        ASTNodeFactory::plus,
                        new ASTBinaryExpressionNode(
                                ASTNodeFactory::intExpression,
                                ASTNodeFactory::slash,
                                ASTNodeFactory::intExpression
                        )
                )
        )},
        {72, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        new ASTBinaryExpressionNode(
                                ASTNodeFactory::intExpression,
                                ASTNodeFactory::star,
                                ASTNodeFactory::intExpression
                        ),
                        ASTNodeFactory::minus,
                        new ASTBinaryExpressionNode(
                                new ASTBinaryExpressionNode(
                                    ASTNodeFactory::intExpression,
                                    ASTNodeFactory::plus,
                                    ASTNodeFactory::intExpression
                                ),
                                ASTNodeFactory::slash,
                                ASTNodeFactory::intExpression
                        )
                )
        )},
        {73, new ASTVariableDeclarationNode(
                    ASTNodeFactory::constInit,
                    new ASTBinaryExpressionNode(
                            ASTNodeFactory::idExpression,
                            ASTNodeFactory::plus,
                            new ASTBinaryExpressionNode(
                                    ASTNodeFactory::idExpression,
                                    ASTNodeFactory::star,
                                    ASTNodeFactory::idExpression
                            )
                    )
            )},
        {74, new ASTVariableDeclarationNode(
                    ASTNodeFactory::constInit,
                    new ASTBinaryExpressionNode(
                            new ASTBinaryExpressionNode(
                                    ASTNodeFactory::idExpression,
                                    ASTNodeFactory::star,
                                    ASTNodeFactory::idExpression
                            ),
                            ASTNodeFactory::plus,
                            ASTNodeFactory::idExpression
                    )
            )},
        {75, new ASTVariableDeclarationNode(
                    ASTNodeFactory::constInit,
                    new ASTBinaryExpressionNode(
                            ASTNodeFactory::idExpression,
                            ASTNodeFactory::star,
                            new ASTBinaryExpressionNode(
                                    ASTNodeFactory::idExpression,
                                    ASTNodeFactory::plus,
                                    ASTNodeFactory::idExpression
                            )
                    )
            )},
        {76, new ASTVariableDeclarationNode(
                    ASTNodeFactory::constInit,
                    new ASTBinaryExpressionNode(
                            ASTNodeFactory::idExpression,
                            ASTNodeFactory::star,
                            new ASTBinaryExpressionNode(
                                    ASTNodeFactory::idExpression,
                                    ASTNodeFactory::slash,
                                    ASTNodeFactory::idExpression
                            )
                    )
        )},
        {77, new ASTVariableDeclarationNode(
                    ASTNodeFactory::constInit,
                    new ASTBinaryExpressionNode(
                            new ASTBinaryExpressionNode(
                                    new ASTBinaryExpressionNode(
                                            ASTNodeFactory::idExpression,
                                            ASTNodeFactory::star,
                                            ASTNodeFactory::idExpression
                                    ),
                                    ASTNodeFactory::minus,
                                    ASTNodeFactory::idExpression
                            ),
                            ASTNodeFactory::plus,
                            ASTNodeFactory::idExpression
                    )
            )},
        {78, new ASTVariableDeclarationNode(
                    ASTNodeFactory::constInit,
                    new ASTBinaryExpressionNode(
                            new ASTBinaryExpressionNode(
                                    new ASTBinaryExpressionNode(
                                            ASTNodeFactory::idExpression,
                                            ASTNodeFactory::star,
                                            ASTNodeFactory::idExpression
                                    ),
                                    ASTNodeFactory::minus,
                                    ASTNodeFactory::idExpression
                            ),
                            ASTNodeFactory::plus,
                            new ASTBinaryExpressionNode(
                                    ASTNodeFactory::idExpression,
                                    ASTNodeFactory::slash,
                                    ASTNodeFactory::idExpression
                            )
                    )
            )},
        {79, new ASTVariableDeclarationNode(
                    ASTNodeFactory::constInit,
                    new ASTBinaryExpressionNode(
                            new ASTBinaryExpressionNode(
                                    ASTNodeFactory::idExpression,
                                    ASTNodeFactory::star,
                                    ASTNodeFactory::idExpression
                            ),
                            ASTNodeFactory::minus,
                            new ASTBinaryExpressionNode(
                                    new ASTBinaryExpressionNode(
                                            ASTNodeFactory::idExpression,
                                            ASTNodeFactory::plus,
                                            ASTNodeFactory::idExpression
                                    ),
                                    ASTNodeFactory::slash,
                                    ASTNodeFactory::idExpression
                            )
                    )
            )},
            {80, new ASTVariableDeclarationNode(
                    ASTNodeFactory::constInit,
                    new ASTBinaryExpressionNode(
                            new ASTUnaryExpressionNode(
                                ASTNodeFactory::unaryPlus,
                                ASTNodeFactory::intExpression
                            ),
                            ASTNodeFactory::star,
                            new ASTBinaryExpressionNode(
                                    ASTNodeFactory::intExpression,
                                    ASTNodeFactory::slash,
                                    new ASTUnaryExpressionNode(
                                            ASTNodeFactory::unaryMinus,
                                            ASTNodeFactory::intExpression
                                    )
                            )
                    )
            )},
            {81, new ASTVariableDeclarationNode(
                    ASTNodeFactory::constInit,
                    new ASTBinaryExpressionNode(
                            new ASTBinaryExpressionNode(
                                    new ASTBinaryExpressionNode(
                                            new ASTUnaryExpressionNode(
                                                    ASTNodeFactory::unaryPlus,
                                                    ASTNodeFactory::intExpression
                                            ),
                                            ASTNodeFactory::star,
                                            ASTNodeFactory::intExpression
                                    ),
                                    ASTNodeFactory::minus,
                                    new ASTUnaryExpressionNode(
                                            ASTNodeFactory::unaryMinus,
                                            ASTNodeFactory::intExpression
                                    )
                            ),
                            ASTNodeFactory::plus,
                            ASTNodeFactory::intExpression
                    )
            )},
            {82, new ASTVariableDeclarationNode(
                    ASTNodeFactory::constInit,
                    new ASTArrayExpressionNode({
                       ASTNodeFactory::intExpression,
                       ASTNodeFactory::intExpression,
                       ASTNodeFactory::intExpression
                    })
            )},
            {83, new ASTVariableDeclarationNode(
                    ASTNodeFactory::constInit,
                    new ASTArrayAccessExpressionNode(
                           ASTNodeFactory::idExpression,
                           new ASTArrayAccessNode(
                                ASTNodeFactory::intExpression
                           )
                   )
            )},
            {84, new ASTVariableDeclarationNode(
                    ASTNodeFactory::constInit,
                    new ASTArrayAccessExpressionNode(
                            new ASTArrayExpressionNode({
                                ASTNodeFactory::intExpression,
                                ASTNodeFactory::intExpression
                            }),
                            new ASTArrayAccessNode(
                                ASTNodeFactory::intExpression
                            )
                    )
            )},
            {85, new ASTVariableDeclarationNode(
                    ASTNodeFactory::constInit,
                    new ASTArrayExpressionNode({
                           new ASTArrayExpressionNode({ ASTNodeFactory::intExpression }),
                           new ASTArrayExpressionNode({ ASTNodeFactory::intExpression }),
                           new ASTArrayExpressionNode({ ASTNodeFactory::intExpression })
                    })
            )},
            {86, new ASTVariableDeclarationNode(
                    ASTNodeFactory::constInit,
                    new ASTArrayExpressionNode({
                           new ASTArrayExpressionNode({
                               new ASTBinaryExpressionNode(
                                       ASTNodeFactory::intExpression,
                                       ASTNodeFactory::plus,
                                       ASTNodeFactory::intExpression
                                       )
                           }),
                           new ASTArrayExpressionNode({
                                  new ASTBinaryExpressionNode(
                                          ASTNodeFactory::intExpression,
                                          ASTNodeFactory::plus,
                                          ASTNodeFactory::intExpression
                                  )
                          }),
                           new ASTArrayExpressionNode({
                                  new ASTBinaryExpressionNode(
                                          ASTNodeFactory::intExpression,
                                          ASTNodeFactory::plus,
                                          ASTNodeFactory::intExpression
                                  )
                          }),
                   })
            )},
            {87, new ASTVariableDeclarationNode(
                    ASTNodeFactory::constInit,
                    new ASTArrayExpressionNode({
                           ASTNodeFactory::idExpression,
                           ASTNodeFactory::idExpression,
                           ASTNodeFactory::idExpression
                    })
            )},
            {88, new ASTVariableDeclarationNode(
                    ASTNodeFactory::constInit,
                    new ASTArrayAccessExpressionNode(
                        new ASTArrayAccessExpressionNode(
                            new ASTArrayExpressionNode({
                               new ASTArrayExpressionNode({
                                      ASTNodeFactory::intExpression,
                                      ASTNodeFactory::intExpression,
                                      ASTNodeFactory::intExpression
                               }),
                               new ASTArrayExpressionNode({
                                      ASTNodeFactory::intExpression,
                                      ASTNodeFactory::intExpression,
                                      ASTNodeFactory::intExpression
                               }),
                            }),
                            new ASTArrayAccessNode(
                                    ASTNodeFactory::intExpression
                            )
                        ),
                        new ASTArrayAccessNode(
                                ASTNodeFactory::intExpression
                        )
                    )
            )},
            {89, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTArrayAccessExpressionNode(
                    new ASTArrayAccessExpressionNode(
                        new ASTArrayAccessExpressionNode(
                                new ASTArrayExpressionNode({
                                   new ASTArrayExpressionNode({
                                      new ASTArrayExpressionNode({ASTNodeFactory::intExpression}),
                                      new ASTArrayExpressionNode({ASTNodeFactory::intExpression}),
                                      new ASTArrayExpressionNode({ASTNodeFactory::intExpression})
                                  }),
                                  new ASTArrayExpressionNode({
                                      new ASTArrayExpressionNode({ASTNodeFactory::intExpression}),
                                      new ASTArrayExpressionNode({ASTNodeFactory::intExpression}),
                                      new ASTArrayExpressionNode({ASTNodeFactory::intExpression})
                                  }),
                            }),
                            new ASTArrayAccessNode(
                                    ASTNodeFactory::intExpression
                            )
                        ),
                        new ASTArrayAccessNode(
                                ASTNodeFactory::intExpression
                        )
                    ),
                    new ASTArrayAccessNode(
                            ASTNodeFactory::intExpression
                    )
                )
            )},
        {90, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTStructExpressionNode({
                    new ASTStructKeyValueNode(ASTNodeFactory::idExpression,
                                              ASTNodeFactory::intExpression),
                    new ASTStructKeyValueNode(ASTNodeFactory::idExpression,
                                              ASTNodeFactory::floatExpression),
                    new ASTStructKeyValueNode(ASTNodeFactory::idExpression,
                                              ASTNodeFactory::trueExpression),
                    new ASTStructKeyValueNode(ASTNodeFactory::idExpression,
                                              ASTNodeFactory::charExpression),
                    new ASTStructKeyValueNode(ASTNodeFactory::idExpression,
                                              ASTNodeFactory::stringExpression),
                    new ASTStructKeyValueNode(ASTNodeFactory::idExpression,
                                              ASTNodeFactory::idExpression),
                    new ASTStructKeyValueNode(ASTNodeFactory::idExpression,
                                              new ASTArrayExpressionNode({
                                                     ASTNodeFactory::intExpression,
                                                     ASTNodeFactory::intExpression,
                                                     ASTNodeFactory::intExpression
                                             })),
                    new ASTStructKeyValueNode(ASTNodeFactory::idExpression,
                                              new ASTArrayAccessExpressionNode(
                                                      ASTNodeFactory::idExpression,
                                                      ASTNodeFactory::arrayAccessInt
                                              )),
                    new ASTStructKeyValueNode(ASTNodeFactory::idExpression,
                                              new ASTStructExpressionNode({
                                                  new ASTStructKeyValueNode(
                                                      ASTNodeFactory::idExpression,
                                                      ASTNodeFactory::intExpression
                                                  ),
                                                  new ASTStructKeyValueNode(
                                                          ASTNodeFactory::idExpression,
                                                          new ASTStructExpressionNode({
                                                              new ASTStructKeyValueNode(
                                                                      ASTNodeFactory::idExpression,
                                                                      ASTNodeFactory::trueExpression
                                                              )
                                                          })
                                                  ),
                                              })
                    ),
                    new ASTStructKeyValueNode(ASTNodeFactory::idExpression,
                                              new ASTBinaryExpressionNode(
                                                      ASTNodeFactory::intExpression,
                                                      ASTNodeFactory::plus,
                                                      ASTNodeFactory::intExpression
                                              )),
                    new ASTStructKeyValueNode(ASTNodeFactory::idExpression,
                                              new ASTLogicalExpressionNode(
                                                      ASTNodeFactory::trueExpression,
                                                      ASTNodeFactory::andOperator,
                                                      ASTNodeFactory::falseExpression
                                              )),
                    new ASTStructKeyValueNode(ASTNodeFactory::idExpression,
                                              new ASTUnaryExpressionNode(
                                                      ASTNodeFactory::bang,
                                                      ASTNodeFactory::idExpression
                                              ))
            }))
         },
        {91, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTStructAccessExpressionNode({
                       ASTNodeFactory::idExpression,
                       ASTNodeFactory::idExpression,
               })
        )},
        {92, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTStructAccessExpressionNode({
                      new ASTStructAccessExpressionNode({
                            ASTNodeFactory::idExpression,
                            ASTNodeFactory::idExpression,
                      }),
                      ASTNodeFactory::idExpression,
                })
        )},
        {93, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTStructAccessExpressionNode({
                      new ASTStructAccessExpressionNode({
                            new ASTStructAccessExpressionNode({
                                  ASTNodeFactory::idExpression,
                                  ASTNodeFactory::idExpression,
                            }),
                            ASTNodeFactory::idExpression,
                      }),
                      ASTNodeFactory::idExpression
                })
        )},
        {94, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTArrayExpressionNode({
                    new ASTStructExpressionNode({
                        new ASTStructKeyValueNode(
                                ASTNodeFactory::idExpression,
                                ASTNodeFactory::stringExpression
                        ),
                        new ASTStructKeyValueNode(
                                ASTNodeFactory::idExpression,
                                ASTNodeFactory::intExpression
                        ),
                    })
               })
        )},
        {95, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTStructAccessExpressionNode({
                  new ASTArrayAccessExpressionNode({
                      ASTNodeFactory::idExpression,
                      ASTNodeFactory::arrayAccessInt
                  }),
                  ASTNodeFactory::idExpression
                })
        )},
        {96, new ASTVariableDeclarationNode(
            ASTNodeFactory::constInit,
            new ASTStructExpressionNode({
                new ASTStructKeyValueNode(
                    ASTNodeFactory::idExpression,
                    new ASTArrayExpressionNode({
                           new ASTStructExpressionNode({
                               new ASTStructKeyValueNode(
                                       ASTNodeFactory::idExpression,
                                       ASTNodeFactory::stringExpression
                               ),
                               new ASTStructKeyValueNode(
                                       ASTNodeFactory::idExpression,
                                       ASTNodeFactory::intExpression
                               ),
                           })
                   })
                ),
                new ASTStructKeyValueNode(
                        ASTNodeFactory::idExpression,
                        new ASTArrayExpressionNode({
                           new ASTArrayExpressionNode({
                              new ASTStructExpressionNode({
                                  new ASTStructKeyValueNode(
                                          ASTNodeFactory::idExpression,
                                          ASTNodeFactory::stringExpression
                                  ),
                                  new ASTStructKeyValueNode(
                                          ASTNodeFactory::idExpression,
                                          ASTNodeFactory::intExpression
                                  ),
                              })
                           })
                       })
                )
            })
        )},
        {97, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                 new ASTStructAccessExpressionNode(
                        new ASTArrayAccessExpressionNode(
                                new ASTStructAccessExpressionNode(
                                    ASTNodeFactory::idExpression,
                                    ASTNodeFactory::idExpression
                                ),
                                ASTNodeFactory::arrayAccessInt
                        ),
                        ASTNodeFactory::idExpression
                )
            )
        },
        {98, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTStructAccessExpressionNode(
                    new ASTArrayAccessExpressionNode(
                                new ASTArrayAccessExpressionNode(
                                        new ASTStructAccessExpressionNode(
                                            ASTNodeFactory::idExpression,
                                            ASTNodeFactory::idExpression
                                    ),
                                    ASTNodeFactory::arrayAccessInt
                        ),
                        ASTNodeFactory::arrayAccessInt
                    ),
                    ASTNodeFactory::idExpression
                    )
        )},
        {99, new ASTFunctionDeclarationNode(
                ASTNodeFactory::functionName,
                new ASTFunctionParameterListNode({
                     ASTNodeFactory::intFunctionParameter,
                     ASTNodeFactory::intFunctionParameter,
                }),
                ASTNodeFactory::intType,
                new ASTFunctionBlockNode({
                    new ASTVariableDeclarationNode(
                            ASTNodeFactory::constInit,
                            new ASTBinaryExpressionNode(
                                    ASTNodeFactory::idExpression,
                                    ASTNodeFactory::plus,
                                    ASTNodeFactory::idExpression
                                    )
                    ),
                    new ASTFunctionReturnExpressionNode(ASTNodeFactory::idExpression)
                })
        )},
        {100, new ASTFunctionDeclarationNode(
                ASTNodeFactory::functionName,
                new ASTFunctionParameterListNode(),
                ASTNodeFactory::intType,
                new ASTFunctionBlockNode({
                     new ASTFunctionReturnExpressionNode(ASTNodeFactory::intExpression)
                 })
        )},
        {101, new ASTBlockNode({
                   new ASTVariableDeclarationNode(
                           ASTNodeFactory::letInit,
                           ASTNodeFactory::stringExpression
                   ),
                   new ASTVariableAssignmentStatementNode(
                           ASTNodeFactory::varAssignment,
                           ASTNodeFactory::stringExpression
                   ),
                   new ASTBlockNode({
                        new ASTVariableDeclarationNode(
                                ASTNodeFactory::constInit,
                                ASTNodeFactory::stringExpression
                        ),
                        new ASTVariableAssignmentStatementNode(
                                ASTNodeFactory::varAssignment,
                                ASTNodeFactory::stringExpression
                        ),
                   })
        })}
};

TEST_CASE( "should print the expected reduced nodes" ) {
std::string filePath = "./syntax-analyzer-test-file.jet";
auto tokenTable = new TokenTable();
auto reservedKeywords = new ReservedKeywords();
auto lexicalAnalyzer = new LexicalAnalyzer(tokenTable, reservedKeywords);
auto syntaxAnalyzer = SyntaxAnalyzer(tokenTable, lexicalAnalyzer);
auto fileNodeResult = syntaxAnalyzer.analyze(filePath);
Logger::log("===== TEST LOGS =====");
REQUIRE(fileNodeResult->getBody()->size() == 101);
    for (int i = 0; i < 101; i++) {
        auto declaration = fileNodeResult->getBody()->getContents()[i];
        Logger::log("=====", i + 1, declaration->toString(), "=====");
        declaration->print();
        Logger::log("RESULT =", declaration->isSameAs(expectedNodes[i + 1]));
        REQUIRE(declaration->isSameAs(expectedNodes[i + 1]));
        Logger::log("====================================");
    }
}
