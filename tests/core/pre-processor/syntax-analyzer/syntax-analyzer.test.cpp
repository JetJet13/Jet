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
#include "../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-array-access-expression-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-struct-expression-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-object-access-expression-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-declaration-nodes/ast-function-declaration-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-statement-nodes/ast-variable-assignment-statement-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-declaration-nodes/ast-procedure-declaration-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-declaration-nodes/ast-enum-declaration-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-statement-nodes/ast-expression-statement-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-function-invocation-expression-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-tuple-expression-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-tuple-access-expression.h"
#include "../../../../src/core/ast/ast-nodes/ast-statement-nodes/ast-if-statement-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-statement-nodes/ast-while-statement-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-statement-nodes/ast-for-in-statement-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-statement-nodes/ast-try-statement-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-lambda-expression-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-lambda-nodes/ast-function-lambda-type-parameter-list-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-lambda-nodes/ast-procedure-lambda-type-parameter-list-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-curry-expression-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-declaration-nodes/ast-module-declaration-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-declaration-nodes/ast-use-single-module-declaration-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-declaration-nodes/ast-import-single-module-declaration-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-declaration-nodes/ast-use-many-module-declaration-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-declaration-nodes/ast-import-many-module-declaration-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-import-nodes/ast-import-list-items/ast-import-module-list-by-group-item-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-declaration-nodes/ast-class-declaration-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-new-class-instance-expression.h"
#include "../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-class-property-access-expression-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-statement-nodes/ast-class-property-assignment-statement-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-class-method-invocation-expression-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-declaration-nodes/ast-use-many-by-wildcard-module-declaration-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-declaration-nodes/ast-import-many-by-wildcard-module-declaration-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-lambda-with-fat-arrow-expression-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-module-access-expression-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-object-access-invocation-expression-node.h"

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
                    ASTNodeFactory::createArrayExpression(
                        {
                            ASTNodeFactory::intExpression,
                            ASTNodeFactory::intExpression,
                            ASTNodeFactory::intExpression
                    })
            )},
            {83, new ASTVariableDeclarationNode(
                    ASTNodeFactory::constInit,
                    new ASTArrayAccessExpressionNode(
                           ASTNodeFactory::idExpression,
                           ASTNodeFactory::createArrayAccess(ASTNodeFactory::intExpression)
                   )
            )},
            {84, new ASTVariableDeclarationNode(
                    ASTNodeFactory::constInit,
                    new ASTArrayAccessExpressionNode(
                            ASTNodeFactory::createArrayExpression({
                                ASTNodeFactory::intExpression,
                                ASTNodeFactory::intExpression
                            }),
                            ASTNodeFactory::createArrayAccess(
                                ASTNodeFactory::intExpression
                            )
                    )
            )},
            {85, new ASTVariableDeclarationNode(
                    ASTNodeFactory::constInit,
                    ASTNodeFactory::createArrayExpression({
                           ASTNodeFactory::createArrayExpression({ ASTNodeFactory::intExpression }),
                           ASTNodeFactory::createArrayExpression({ ASTNodeFactory::intExpression }),
                           ASTNodeFactory::createArrayExpression({ ASTNodeFactory::intExpression })
                    })
            )},
            {86, new ASTVariableDeclarationNode(
                    ASTNodeFactory::constInit,
                    ASTNodeFactory::createArrayExpression({
                           ASTNodeFactory::createArrayExpression({
                               new ASTBinaryExpressionNode(
                                       ASTNodeFactory::intExpression,
                                       ASTNodeFactory::plus,
                                       ASTNodeFactory::intExpression
                                       )
                           }),
                           ASTNodeFactory::createArrayExpression({
                                  new ASTBinaryExpressionNode(
                                          ASTNodeFactory::intExpression,
                                          ASTNodeFactory::plus,
                                          ASTNodeFactory::intExpression
                                  )
                          }),
                           ASTNodeFactory::createArrayExpression({
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
                    ASTNodeFactory::createArrayExpression({
                           ASTNodeFactory::idExpression,
                           ASTNodeFactory::idExpression,
                           ASTNodeFactory::idExpression
                    })
            )},
            {88, new ASTVariableDeclarationNode(
                    ASTNodeFactory::constInit,
                    new ASTArrayAccessExpressionNode(
                        new ASTArrayAccessExpressionNode(
                            ASTNodeFactory::createArrayExpression({
                               ASTNodeFactory::createArrayExpression({
                                      ASTNodeFactory::intExpression,
                                      ASTNodeFactory::intExpression,
                                      ASTNodeFactory::intExpression
                               }),
                               ASTNodeFactory::createArrayExpression({
                                      ASTNodeFactory::intExpression,
                                      ASTNodeFactory::intExpression,
                                      ASTNodeFactory::intExpression
                               }),
                            }),
                            ASTNodeFactory::createArrayAccess(
                                    ASTNodeFactory::intExpression
                            )
                        ),
                        ASTNodeFactory::createArrayAccess(
                                ASTNodeFactory::intExpression
                        )
                    )
            )},
            {89, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTArrayAccessExpressionNode(
                    new ASTArrayAccessExpressionNode(
                        new ASTArrayAccessExpressionNode(
                                ASTNodeFactory::createArrayExpression({
                                   ASTNodeFactory::createArrayExpression({
                                      ASTNodeFactory::createArrayExpression({ASTNodeFactory::intExpression}),
                                      ASTNodeFactory::createArrayExpression({ASTNodeFactory::intExpression}),
                                      ASTNodeFactory::createArrayExpression({ASTNodeFactory::intExpression})
                                  }),
                                  ASTNodeFactory::createArrayExpression({
                                      ASTNodeFactory::createArrayExpression({ASTNodeFactory::intExpression}),
                                      ASTNodeFactory::createArrayExpression({ASTNodeFactory::intExpression}),
                                      ASTNodeFactory::createArrayExpression({ASTNodeFactory::intExpression})
                                  }),
                            }),
                            ASTNodeFactory::createArrayAccess(
                                    ASTNodeFactory::intExpression
                            )
                        ),
                        ASTNodeFactory::createArrayAccess(
                                ASTNodeFactory::intExpression
                        )
                    ),
                    ASTNodeFactory::createArrayAccess(
                            ASTNodeFactory::intExpression
                    )
                )
            )},
        {90, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createStructExpression({
                    ASTNodeFactory::createStructKeyValue(ASTNodeFactory::intExpression),
                    ASTNodeFactory::createStructKeyValue(ASTNodeFactory::floatExpression),
                    ASTNodeFactory::createStructKeyValue(ASTNodeFactory::trueExpression),
                    ASTNodeFactory::createStructKeyValue(ASTNodeFactory::charExpression),
                    ASTNodeFactory::createStructKeyValue(ASTNodeFactory::stringExpression),
                    ASTNodeFactory::createStructKeyValue(ASTNodeFactory::idExpression),
                    ASTNodeFactory::createStructKeyValue(ASTNodeFactory::createArrayExpression({
                                                     ASTNodeFactory::intExpression,
                                                     ASTNodeFactory::intExpression,
                                                     ASTNodeFactory::intExpression
                                             })),
                    ASTNodeFactory::createStructKeyValue(new ASTArrayAccessExpressionNode(
                                                      ASTNodeFactory::idExpression,
                                                      ASTNodeFactory::arrayAccessInt
                                              )),
                    ASTNodeFactory::createStructKeyValue(ASTNodeFactory::createStructExpression({
                                                  ASTNodeFactory::createStructKeyValue(ASTNodeFactory::intExpression),
                                                  ASTNodeFactory::createStructKeyValue(
                                                          ASTNodeFactory::createStructExpression({
                                                              ASTNodeFactory::createStructKeyValue(
                                                                ASTNodeFactory::trueExpression
                                                              )
                                                          })
                                                  ),
                                              })
                    ),
                    ASTNodeFactory::createStructKeyValue(
                                              new ASTBinaryExpressionNode(
                                                      ASTNodeFactory::intExpression,
                                                      ASTNodeFactory::plus,
                                                      ASTNodeFactory::intExpression
                                              )),
                    ASTNodeFactory::createStructKeyValue(
                                              new ASTLogicalExpressionNode(
                                                      ASTNodeFactory::trueExpression,
                                                      ASTNodeFactory::andOperator,
                                                      ASTNodeFactory::falseExpression
                                              )),
                    ASTNodeFactory::createStructKeyValue(
                                              new ASTUnaryExpressionNode(
                                                      ASTNodeFactory::bang,
                                                      ASTNodeFactory::idExpression
                                              ))
            }))
         },
        {91, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createObjectAccessExpression(
                       ASTNodeFactory::objectAccessSourceId,
                       ASTNodeFactory::objectAccessTargetId
               )
        )},
        {92, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createObjectAccessExpression(
                    new ASTObjectAccessSourceNode(
                      ASTNodeFactory::createObjectAccessExpression(
                            ASTNodeFactory::objectAccessSourceId,
                            ASTNodeFactory::objectAccessTargetId
                      )),
                      ASTNodeFactory::objectAccessTargetId
                )
        )},
        {93, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createObjectAccessExpression(
                  new ASTObjectAccessSourceNode(
                      ASTNodeFactory::createObjectAccessExpression(
                          new ASTObjectAccessSourceNode(
                            ASTNodeFactory::createObjectAccessExpression(
                                  ASTNodeFactory::objectAccessSourceId,
                                  ASTNodeFactory::objectAccessTargetId
                            )),
                            ASTNodeFactory::objectAccessTargetId
                      )),
                      ASTNodeFactory::objectAccessTargetId
                )
        )},
        {94, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createArrayExpression({
                    ASTNodeFactory::createStructExpression({
                        ASTNodeFactory::createStructKeyValue(
                                ASTNodeFactory::stringExpression
                        ),
                        ASTNodeFactory::createStructKeyValue(
                                ASTNodeFactory::intExpression
                        ),
                    })
               })
        )},
        {95, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createObjectAccessExpression(
                        new ASTObjectAccessSourceNode(
                            new ASTArrayAccessExpressionNode({
                                   ASTNodeFactory::idExpression,
                                   ASTNodeFactory::arrayAccessInt
                            })),
                        ASTNodeFactory::objectAccessTargetId
                )
        )},
        {96, new ASTVariableDeclarationNode(
            ASTNodeFactory::constInit,
            ASTNodeFactory::createStructExpression({
                ASTNodeFactory::createStructKeyValue(
                    ASTNodeFactory::createArrayExpression({
                           ASTNodeFactory::createStructExpression({
                               ASTNodeFactory::createStructKeyValue(
                                       ASTNodeFactory::stringExpression
                               ),
                               ASTNodeFactory::createStructKeyValue(
                                       ASTNodeFactory::intExpression
                               ),
                           })
                   })
                ),
                ASTNodeFactory::createStructKeyValue(
                        ASTNodeFactory::createArrayExpression({
                           ASTNodeFactory::createArrayExpression({
                              ASTNodeFactory::createStructExpression({
                                  ASTNodeFactory::createStructKeyValue(
                                          ASTNodeFactory::stringExpression
                                  ),
                                  ASTNodeFactory::createStructKeyValue(
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
                 ASTNodeFactory::createObjectAccessExpression(
                         new ASTObjectAccessSourceNode(
                             new ASTArrayAccessExpressionNode(
                                ASTNodeFactory::createObjectAccessExpression(
                                    new ASTObjectAccessSourceNode(ASTNodeFactory::idExpression),
                                    ASTNodeFactory::objectAccessTargetId
                                ),
                                ASTNodeFactory::arrayAccessInt
                        )),
                        ASTNodeFactory::objectAccessTargetId
                )
            )
        },
        {98, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createObjectAccessExpression(
                    new ASTObjectAccessSourceNode(
                        new ASTArrayAccessExpressionNode(
                                    new ASTArrayAccessExpressionNode(
                                            ASTNodeFactory::createObjectAccessExpression(
                                                ASTNodeFactory::objectAccessSourceId,
                                                ASTNodeFactory::objectAccessTargetId
                                        ),
                                        ASTNodeFactory::arrayAccessInt
                            ),
                            ASTNodeFactory::arrayAccessInt
                    )),
                    ASTNodeFactory::objectAccessTargetId
                    )
        )},
        {99, new ASTFunctionDeclarationNode(
                ASTNodeFactory::createFunctionDefinition(
                ASTNodeFactory::functionName,
                ASTNodeFactory::createFunctionParameterList({
                     ASTNodeFactory::intFunctionParameter,
                     ASTNodeFactory::intFunctionParameter,
                 }),
                ASTNodeFactory::intType),
                ASTNodeFactory::createFunctionBlock({
                    new ASTVariableDeclarationNode(
                            ASTNodeFactory::constInit,
                            new ASTBinaryExpressionNode(
                                    ASTNodeFactory::idExpression,
                                    ASTNodeFactory::plus,
                                    ASTNodeFactory::idExpression
                                    )
                    ),
                    new ASTFunctionReturnExpressionNode(
                        ASTNodeFactory::functionReturn,
                        ASTNodeFactory::idExpression
                    )
                })
        )},
        {100, new ASTFunctionDeclarationNode(
                ASTNodeFactory::createFunctionDefinition(
                ASTNodeFactory::functionName,
                ASTNodeFactory::createFunctionParameterList(),
                ASTNodeFactory::intType),
                ASTNodeFactory::createFunctionBlock({
                     new ASTFunctionReturnExpressionNode(ASTNodeFactory::functionReturn, ASTNodeFactory::intExpression)
                 })
        )},
        {101, new ASTFunctionDeclarationNode(
                ASTNodeFactory::createFunctionDefinition(
                        ASTNodeFactory::functionName,
                        ASTNodeFactory::createFunctionParameterList({
                            ASTNodeFactory::intFunctionParameter,
                            ASTNodeFactory::intFunctionParameter,
                        }),
                        ASTNodeFactory::intType),
                ASTNodeFactory::createFunctionBlock({
                    new ASTFunctionReturnExpressionNode(
                        ASTNodeFactory::functionReturn,
                        new ASTBinaryExpressionNode(
                            ASTNodeFactory::intExpression,
                            ASTNodeFactory::plus,
                            new ASTBinaryExpressionNode(
                                ASTNodeFactory::idExpression,
                                ASTNodeFactory::plus,
                                ASTNodeFactory::idExpression
                            )
                        )
                    )
                })
        )},
        {102, new ASTProcedureDeclarationNode(
                ASTNodeFactory::createProcedureDefinition(
                ASTNodeFactory::functionName,
                ASTNodeFactory::createFunctionParameterList(

                    { ASTNodeFactory::intFunctionParameter }
                    
                )),
                ASTNodeFactory::createFunctionBlock({
                     new ASTVariableDeclarationNode(
                             ASTNodeFactory::letInit,
                             ASTNodeFactory::intExpression
                     ),
                     new ASTVariableAssignmentStatementNode(
                             ASTNodeFactory::varAssignment,
                             new ASTBinaryExpressionNode(
                                     ASTNodeFactory::idExpression,
                                     ASTNodeFactory::plus,
                                     ASTNodeFactory::intExpression
                             )
                     ),
                })
        )},
        {103, new ASTProcedureDeclarationNode(
                ASTNodeFactory::createProcedureDefinition(
                ASTNodeFactory::functionName,
                ASTNodeFactory::createFunctionParameterList()),
                ASTNodeFactory::createFunctionBlock({
                     new ASTVariableDeclarationNode(
                        ASTNodeFactory::letInit,
                        ASTNodeFactory::intExpression
                     ),
                })
        )},
        {104, new ASTProcedureDeclarationNode(
                ASTNodeFactory::createProcedureDefinition(
                ASTNodeFactory::functionName,
                ASTNodeFactory::createFunctionParameterList()),
                ASTNodeFactory::createFunctionBlock({})
        )},
        {105, new ASTEnumDeclarationNode(
                ASTNodeFactory::enumKeyword,
                ASTNodeFactory::enumName,
                ASTNodeFactory::createEnumKeyValueList({
                    new ASTEnumKeyValueNode(
                            ASTNodeFactory::enumKey,
                            ASTNodeFactory::assignment,
                            ASTNodeFactory::stringLiteral
                    ),
                    new ASTEnumKeyValueNode(
                            ASTNodeFactory::enumKey,
                            ASTNodeFactory::assignment,
                            ASTNodeFactory::stringLiteral
                    ),
                    new ASTEnumKeyValueNode(
                            ASTNodeFactory::enumKey,
                            ASTNodeFactory::assignment,
                            ASTNodeFactory::stringLiteral
                    )
                })
        )},
        {106, new ASTEnumDeclarationNode(
                ASTNodeFactory::enumKeyword,
                ASTNodeFactory::enumName,
                ASTNodeFactory::createEnumKeyValueList({
                        new ASTEnumKeyValueNode(
                                ASTNodeFactory::enumKey,
                                ASTNodeFactory::assignment,
                                ASTNodeFactory::charLiteral
                        ),
                        new ASTEnumKeyValueNode(
                                ASTNodeFactory::enumKey,
                                ASTNodeFactory::assignment,
                                ASTNodeFactory::charLiteral
                        ),
                        new ASTEnumKeyValueNode(
                                ASTNodeFactory::enumKey,
                                ASTNodeFactory::assignment,
                                ASTNodeFactory::charLiteral
                        )
                })
        )},
        {107, new ASTEnumDeclarationNode(
                ASTNodeFactory::enumKeyword,
                ASTNodeFactory::enumName,
                ASTNodeFactory::createEnumKeyValueList({
                        ASTNodeFactory::enumKeyOnly,
                        ASTNodeFactory::enumKeyOnly,
                        ASTNodeFactory::enumKeyOnly
                })
        )},
        {108, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::intExpression,
                        ASTNodeFactory::equality,
                        ASTNodeFactory::createObjectAccessExpression(
                                ASTNodeFactory::objectAccessSourceId,
                                ASTNodeFactory::objectAccessTargetId
                        )
                )
        )},
        {109, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLogicalExpressionNode(
                        ASTNodeFactory::createObjectAccessExpression(
                            new ASTObjectAccessSourceNode(
                                ASTNodeFactory::createObjectAccessExpression(
                                        ASTNodeFactory::objectAccessSourceId,
                                        ASTNodeFactory::objectAccessTargetId
                                )),
                                ASTNodeFactory::objectAccessTargetId
                        ),
                        ASTNodeFactory::andOperator,
                        ASTNodeFactory::createObjectAccessExpression(
                                ASTNodeFactory::objectAccessSourceId,
                                ASTNodeFactory::objectAccessTargetId
                        )
                )
        )},
        {110, new ASTExpressionStatementNode(
                new ASTFunctionInvocationExpressionNode(
                        ASTNodeFactory::callableIdExpression,
                        ASTNodeFactory::createFunctionArgumentList()
                )
        )},
        {111, new ASTExpressionStatementNode(
                new ASTLogicalExpressionNode(
                        new ASTFunctionInvocationExpressionNode(
                                ASTNodeFactory::callableIdExpression,
                                ASTNodeFactory::createFunctionArgumentList()
                        ),
                        ASTNodeFactory::andOperator,
                        new ASTFunctionInvocationExpressionNode(
                                ASTNodeFactory::callableIdExpression,
                                ASTNodeFactory::createFunctionArgumentList()
                        )
                )
        )},
        {112, new ASTExpressionStatementNode(
                ASTNodeFactory::createObjectAccessExpression(
                    new ASTObjectAccessSourceNode(
                        new ASTFunctionInvocationExpressionNode(
                                ASTNodeFactory::callableIdExpression,
                                ASTNodeFactory::createFunctionArgumentList()
                        )),
                        ASTNodeFactory::objectAccessTargetId
                )
        )},
        {113, new ASTExpressionStatementNode(
                new ASTUnaryExpressionNode(
                        ASTNodeFactory::bang,
                        new ASTFunctionInvocationExpressionNode(
                                ASTNodeFactory::callableIdExpression,
                                ASTNodeFactory::createFunctionArgumentList()
                        )
                )
        )},
        {114, new ASTExpressionStatementNode(
                new ASTArrayAccessExpressionNode(
                        new ASTFunctionInvocationExpressionNode(
                                ASTNodeFactory::callableIdExpression,
                                ASTNodeFactory::createFunctionArgumentList()
                        ),
                        ASTNodeFactory::arrayAccessInt
                )
        )},
        {115, new ASTExpressionStatementNode(
                new ASTFunctionInvocationExpressionNode(
                        ASTNodeFactory::callableIdExpression,
                        ASTNodeFactory::createFunctionArgumentList({
                            new ASTFunctionArgumentNode(
                                new ASTFunctionInvocationExpressionNode(
                                        ASTNodeFactory::callableIdExpression,
                                        ASTNodeFactory::createFunctionArgumentList()
                                )
                            )
                        })
                )
        )},
        {116, new ASTExpressionStatementNode(
                new ASTFunctionInvocationExpressionNode(
                        ASTNodeFactory::callableIdExpression,
                        ASTNodeFactory::createFunctionArgumentList({
                                new ASTFunctionArgumentNode(
                                        new ASTFunctionInvocationExpressionNode(
                                                ASTNodeFactory::callableIdExpression,
                                                ASTNodeFactory::createFunctionArgumentList({
                                                        new ASTFunctionArgumentNode(
                                                                new ASTFunctionInvocationExpressionNode(
                                                                        ASTNodeFactory::callableIdExpression,
                                                                        ASTNodeFactory::createFunctionArgumentList()
                                                                )
                                                        )
                                                })
                                        )
                                )
                        })
                )
        )},
        {117, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createTupleExpression({
                  ASTNodeFactory::stringExpression,
                  ASTNodeFactory::intExpression,
                  ASTNodeFactory::intExpression
                })
        )},
        {118, new ASTExpressionStatementNode(
                ASTNodeFactory::createTupleAccessExpression(
                        ASTNodeFactory::objectAccessSourceId,
                        ASTNodeFactory::tupleAccess
                )
        )},
        {119, new ASTExpressionStatementNode(
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::createTupleAccessExpression(
                                ASTNodeFactory::objectAccessSourceId,
                                ASTNodeFactory::tupleAccess
                        ),
                        ASTNodeFactory::plus,
                        ASTNodeFactory::createTupleAccessExpression(
                                ASTNodeFactory::objectAccessSourceId,
                                ASTNodeFactory::tupleAccess
                        )
                )
        )},
        {120, new ASTExpressionStatementNode(
                new ASTFunctionInvocationExpressionNode(
                        ASTNodeFactory::callableIdExpression,
                        ASTNodeFactory::createFunctionArgumentList({
                            new ASTFunctionArgumentNode(
                                ASTNodeFactory::createTupleAccessExpression(
                                    ASTNodeFactory::objectAccessSourceId,
                                    ASTNodeFactory::tupleAccess
                                )
                            )
                        })
                )
        )},
        {121, new ASTExpressionStatementNode(
                new ASTUnaryExpressionNode(
                    ASTNodeFactory::bang,
                    ASTNodeFactory::createTupleAccessExpression(
                            ASTNodeFactory::objectAccessSourceId,
                            ASTNodeFactory::tupleAccess
                    )
                )
        )},
        {122, new ASTExpressionStatementNode(
                new ASTUnaryExpressionNode(
                        ASTNodeFactory::bang,
                        ASTNodeFactory::createObjectAccessExpression(
                                new ASTObjectAccessSourceNode(
                                        ASTNodeFactory::createObjectAccessExpression(
                                                ASTNodeFactory::objectAccessSourceId,
                                                ASTNodeFactory::objectAccessTargetId
                                        )),
                                ASTNodeFactory::objectAccessTargetId
                        )
                )
        )},
        {123, new ASTExpressionStatementNode(
                    ASTNodeFactory::createTupleAccessExpression(
                            new ASTObjectAccessSourceNode(
                                ASTNodeFactory::createObjectAccessExpression(
                                        ASTNodeFactory::objectAccessSourceId,
                                        ASTNodeFactory::objectAccessTargetId
                                )),
                            ASTNodeFactory::tupleAccess
                    )
        )},
        {124, new ASTExpressionStatementNode(
                ASTNodeFactory::createObjectAccessExpression(
                        new ASTObjectAccessSourceNode(
                                ASTNodeFactory::createTupleAccessExpression(
                                        new ASTObjectAccessSourceNode(
                                                ASTNodeFactory::createObjectAccessExpression(
                                                        ASTNodeFactory::objectAccessSourceId,
                                                        ASTNodeFactory::objectAccessTargetId
                                                )),
                                        ASTNodeFactory::tupleAccess
                                )),
                        ASTNodeFactory::objectAccessTargetId
                )
        )},
        {125, new ASTExpressionStatementNode(
                ASTNodeFactory::createTupleAccessExpression(
                    new ASTObjectAccessSourceNode(
                        ASTNodeFactory::createObjectAccessExpression(
                            new ASTObjectAccessSourceNode(
                                ASTNodeFactory::createTupleAccessExpression(
                                        new ASTObjectAccessSourceNode(
                                                ASTNodeFactory::createObjectAccessExpression(
                                                        ASTNodeFactory::objectAccessSourceId,
                                                        ASTNodeFactory::objectAccessTargetId
                                                )),
                                        ASTNodeFactory::tupleAccess
                            )),
                            ASTNodeFactory::objectAccessTargetId
                )),
                ASTNodeFactory::tupleAccess
                )
        )},
        {126, new ASTExpressionStatementNode(
                ASTNodeFactory::createTupleAccessExpression(
                        new ASTObjectAccessSourceNode(
                                ASTNodeFactory::createTupleAccessExpression(
                                        new ASTObjectAccessSourceNode(
                                                ASTNodeFactory::createTupleAccessExpression(
                                                        ASTNodeFactory::objectAccessSourceId,
                                                        ASTNodeFactory::tupleAccess
                                        )),
                                        ASTNodeFactory::tupleAccess
                        )),
                        ASTNodeFactory::tupleAccess
                )
        )},
        {127, new ASTExpressionStatementNode(
                ASTNodeFactory::createTupleAccessExpression(
                    new ASTObjectAccessSourceNode(
                        new ASTArrayAccessExpressionNode(
                            ASTNodeFactory::createObjectAccessExpression(
                                new ASTObjectAccessSourceNode(
                                    ASTNodeFactory::createTupleAccessExpression(
                                        new ASTObjectAccessSourceNode(
                                            new ASTArrayAccessExpressionNode(
                                                ASTNodeFactory::createObjectAccessExpression(
                                                    ASTNodeFactory::objectAccessSourceId,
                                                    ASTNodeFactory::objectAccessTargetId
                                                ),
                                                ASTNodeFactory::arrayAccessInt
                                            )
                                        ),
                                        ASTNodeFactory::tupleAccess
                                    )
                                ),
                                ASTNodeFactory::objectAccessTargetId
                            ),
                            ASTNodeFactory::arrayAccessInt
                        )
                    ),
                    ASTNodeFactory::tupleAccess
                )
        )},
        {128, new ASTExpressionStatementNode(
                ASTNodeFactory::createTupleAccessExpression(
                    new ASTObjectAccessSourceNode(
                        ASTNodeFactory::createTupleAccessExpression(
                            new ASTObjectAccessSourceNode(
                                ASTNodeFactory::createObjectAccessExpression(
                                    new ASTObjectAccessSourceNode(
                                        ASTNodeFactory::createObjectAccessExpression(
                                            new ASTObjectAccessSourceNode(
                                                new ASTFunctionInvocationExpressionNode(
                                                    ASTNodeFactory::callableIdExpression,
                                                    ASTNodeFactory::createFunctionArgumentList()
                                                )
                                            ),
                                            ASTNodeFactory::objectAccessTargetId
                                        )
                                    ),
                                    ASTNodeFactory::objectAccessTargetId
                                )
                            ),
                            ASTNodeFactory::tupleAccess
                        )
                    ),
                    ASTNodeFactory::tupleAccess
                )
        )},
        {129, new ASTExpressionStatementNode(
                new ASTUnaryExpressionNode(
                    ASTNodeFactory::bang,
                    ASTNodeFactory::createTupleAccessExpression(
                        new ASTObjectAccessSourceNode(
                            ASTNodeFactory::createTupleAccessExpression(
                                new ASTObjectAccessSourceNode(
                                    ASTNodeFactory::createObjectAccessExpression(
                                        new ASTObjectAccessSourceNode(
                                            ASTNodeFactory::createObjectAccessExpression(
                                                new ASTObjectAccessSourceNode(
                                                    new ASTFunctionInvocationExpressionNode(
                                                        ASTNodeFactory::callableIdExpression,
                                                        ASTNodeFactory::createFunctionArgumentList()
                                                    )
                                                ),
                                                ASTNodeFactory::objectAccessTargetId
                                            )
                                        ),
                                        ASTNodeFactory::objectAccessTargetId
                                    )
                                ),
                                ASTNodeFactory::tupleAccess
                            )
                        ),
                        ASTNodeFactory::tupleAccess
                    )
                )
        )},
        {130, new ASTIfStatementNode(
                new ASTIfBlockNode(
                    ASTNodeFactory::ifKeyword,
                    new ASTControlFlowConditionNode(ASTNodeFactory::trueExpression),
                    ASTNodeFactory::createControlFlowBlock({
                        new ASTVariableDeclarationNode(
                            ASTNodeFactory::letInit,
                            ASTNodeFactory::intExpression
                        )
                    })
                ),
                {
                    new ASTElseIfBlockNode(
                            ASTNodeFactory::elseIfKeyword,
                            new ASTControlFlowConditionNode(
                                new ASTBinaryExpressionNode(
                                    ASTNodeFactory::intExpression,
                                    ASTNodeFactory::lessThan,
                                    ASTNodeFactory::intExpression
                                )
                            ),
                            ASTNodeFactory::createControlFlowBlock({
                                new ASTVariableDeclarationNode(
                                    ASTNodeFactory::letInit,
                                    ASTNodeFactory::intExpression
                                ),
                                new ASTVariableAssignmentStatementNode(
                                    ASTNodeFactory::varAssignment,
                                    ASTNodeFactory::intExpression
                                )
                            })
                    ),
                },
                new ASTElseBlockNode(
                    ASTNodeFactory::elseKeyword,
                    ASTNodeFactory::createControlFlowBlock({
                        new ASTVariableDeclarationNode(
                            ASTNodeFactory::letInit,
                            ASTNodeFactory::intExpression
                        ),
                        new ASTVariableAssignmentStatementNode(
                            ASTNodeFactory::varAssignment,
                            ASTNodeFactory::intExpression
                        ),
                        new ASTVariableAssignmentStatementNode(
                            ASTNodeFactory::varAssignment,
                            ASTNodeFactory::intExpression
                        )
                    })
                )
        )},
        {131, new ASTIfStatementNode(
                new ASTIfBlockNode(
                        ASTNodeFactory::ifKeyword,
                        new ASTControlFlowConditionNode(ASTNodeFactory::falseExpression),
                        ASTNodeFactory::createControlFlowBlock({
                            new ASTVariableDeclarationNode(
                                    ASTNodeFactory::letInit,
                                    ASTNodeFactory::intExpression
                            )
                        })
                ),
                {}
        )},
        {132, new ASTIfStatementNode(
                new ASTIfBlockNode(
                        ASTNodeFactory::ifKeyword,
                        new ASTControlFlowConditionNode(ASTNodeFactory::falseExpression),
                        ASTNodeFactory::createControlFlowBlock({
                            new ASTVariableDeclarationNode(
                                ASTNodeFactory::letInit,
                                ASTNodeFactory::intExpression
                            )
                        })
                ),
                {},
                new ASTElseBlockNode(
                    ASTNodeFactory::elseKeyword,
                    ASTNodeFactory::createControlFlowBlock({
                        new ASTVariableDeclarationNode(
                                ASTNodeFactory::letInit,
                                ASTNodeFactory::intExpression
                        ),
                        new ASTVariableAssignmentStatementNode(
                                ASTNodeFactory::varAssignment,
                                ASTNodeFactory::intExpression
                        )
                    })
                )
        )},
        {133, new ASTIfStatementNode(
                new ASTIfBlockNode(
                    ASTNodeFactory::ifKeyword,
                    new ASTControlFlowConditionNode(ASTNodeFactory::trueExpression),
                    ASTNodeFactory::createControlFlowBlock({
                        new ASTVariableDeclarationNode(
                            ASTNodeFactory::letInit,
                            ASTNodeFactory::intExpression
                        )
                    })
                ),
                {
                    new ASTElseIfBlockNode(
                        ASTNodeFactory::elseIfKeyword,
                        new ASTControlFlowConditionNode(
                            new ASTBinaryExpressionNode(
                                ASTNodeFactory::intExpression,
                                ASTNodeFactory::greaterThan,
                                ASTNodeFactory::intExpression
                            )
                        ),
                        ASTNodeFactory::createControlFlowBlock({
                            new ASTVariableDeclarationNode(
                                ASTNodeFactory::letInit,
                                ASTNodeFactory::intExpression
                            )
                        })
                    ),
                    new ASTElseIfBlockNode(
                            ASTNodeFactory::elseIfKeyword,
                            new ASTControlFlowConditionNode(
                                new ASTBinaryExpressionNode(
                                    ASTNodeFactory::intExpression,
                                    ASTNodeFactory::plus,
                                    ASTNodeFactory::intExpression
                                )
                            ),
                            ASTNodeFactory::createControlFlowBlock({
                                new ASTVariableDeclarationNode(
                                    ASTNodeFactory::letInit,
                                    ASTNodeFactory::intExpression
                                )
                            })
                    ),
                },
                new ASTElseBlockNode(
                    ASTNodeFactory::elseKeyword,
                    ASTNodeFactory::createControlFlowBlock({
                        new ASTVariableDeclarationNode(
                            ASTNodeFactory::letInit,
                            ASTNodeFactory::intExpression
                        ),
                    })
                )
        )},
        {134, new ASTIfStatementNode(
                new ASTIfBlockNode(
                        ASTNodeFactory::ifKeyword,
                        new ASTControlFlowConditionNode(
                            new ASTBinaryExpressionNode(
                                    new ASTBinaryExpressionNode(
                                        ASTNodeFactory::createObjectAccessExpression(
                                              new ASTObjectAccessSourceNode(
                                                      ASTNodeFactory::createObjectAccessExpression(
                                                            ASTNodeFactory::objectAccessSourceId,
                                                            ASTNodeFactory::objectAccessTargetId
                                              )),
                                              ASTNodeFactory::objectAccessTargetId
                                        ),
                                        ASTNodeFactory::plus,
                                        new ASTBinaryExpressionNode(
                                            ASTNodeFactory::createTupleAccessExpression(
                                                ASTNodeFactory::objectAccessSourceId,
                                                ASTNodeFactory::tupleAccess
                                            ),
                                            ASTNodeFactory::minus,
                                            new ASTFunctionInvocationExpressionNode(
                                                    ASTNodeFactory::callableIdExpression,
                                                    ASTNodeFactory::createFunctionArgumentList()
                                            )
                                        )),
                                    ASTNodeFactory::greaterThan,
                                    ASTNodeFactory::intExpression
                                    )
                        ),
                        ASTNodeFactory::createControlFlowBlock({
                                new ASTVariableDeclarationNode(
                                        ASTNodeFactory::letInit,
                                        ASTNodeFactory::intExpression
                                )
                        })
                ),
                {}
        )},
        {135, new ASTWhileStatementNode(
                ASTNodeFactory::whileKeyword,
                new ASTControlFlowConditionNode(
                        new ASTBinaryExpressionNode(
                                ASTNodeFactory::idExpression,
                                ASTNodeFactory::lessThan,
                                ASTNodeFactory::intExpression
                        )
                ),
                ASTNodeFactory::createControlFlowBlock({
                    new ASTVariableDeclarationNode(
                        ASTNodeFactory::letInit,
                        ASTNodeFactory::intExpression
                    )
                })
        )},
        {136, new ASTForInStatementNode(
                ASTNodeFactory::forKeyword,
                ASTNodeFactory::forVariable,
                ASTNodeFactory::forInKeyword,
                ASTNodeFactory::forSourceId,
                ASTNodeFactory::createControlFlowBlock({
                    new ASTVariableDeclarationNode(
                            ASTNodeFactory::letInit,
                            ASTNodeFactory::intExpression
                    )
                })
        )},
        {137, new ASTForInStatementNode(
                ASTNodeFactory::forKeyword,
                ASTNodeFactory::forVariable,
                ASTNodeFactory::forInKeyword,
                new ASTForInSourceNode(
                    new ASTFunctionInvocationExpressionNode(
                        ASTNodeFactory::callableIdExpression,
                        ASTNodeFactory::createFunctionArgumentList({
                            new ASTFunctionArgumentNode(ASTNodeFactory::intExpression),
                            new ASTFunctionArgumentNode(ASTNodeFactory::intExpression)
                        })
                    )
                ),
                ASTNodeFactory::createControlFlowBlock({
                    new ASTExpressionStatementNode(
                        new ASTFunctionInvocationExpressionNode(
                            ASTNodeFactory::callableIdExpression,
                            ASTNodeFactory::createFunctionArgumentList({
                                new ASTFunctionArgumentNode(ASTNodeFactory::idExpression),
                            })
                        )
                    ),
                    ASTNodeFactory::breakStatement,
                    ASTNodeFactory::skipStatement,
                })
        )},
        {138, new ASTIfStatementNode(
                new ASTIfBlockNode(
                    ASTNodeFactory::ifKeyword,
                    new ASTControlFlowConditionNode(ASTNodeFactory::idExpression),
                    ASTNodeFactory::createControlFlowBlock({
                        new ASTIfStatementNode(
                            new ASTIfBlockNode(
                                ASTNodeFactory::ifKeyword,
                                new ASTControlFlowConditionNode(ASTNodeFactory::idExpression),
                                ASTNodeFactory::createControlFlowBlock({
                                    ASTNodeFactory::breakStatement
                                })
                            )
                        ),
                        new ASTExpressionStatementNode(
                            new ASTFunctionInvocationExpressionNode(
                                ASTNodeFactory::callableIdExpression,
                                ASTNodeFactory::createFunctionArgumentList()
                            )
                        )
                    })
                ),
                {},
                new ASTElseBlockNode(
                    ASTNodeFactory::elseKeyword,
                    ASTNodeFactory::createControlFlowBlock({
                        new ASTExpressionStatementNode(
                            new ASTFunctionInvocationExpressionNode(
                                ASTNodeFactory::callableIdExpression,
                                ASTNodeFactory::createFunctionArgumentList()
                            )
                        )
                    })
                )
        )},
        {139, new ASTTryStatementNode(
                new ASTTryBlockNode(
                    ASTNodeFactory::tryKeyword,
                    ASTNodeFactory::createControlFlowBlock({
                        new ASTExpressionStatementNode(
                            new ASTFunctionInvocationExpressionNode(
                                ASTNodeFactory::callableIdExpression,
                                ASTNodeFactory::createFunctionArgumentList({
                                    new ASTFunctionArgumentNode(ASTNodeFactory::stringExpression)
                                })
                            )
                        )
                    })
                ),
                new ASTCatchBlockNode(
                    ASTNodeFactory::catchKeyword,
                    ASTNodeFactory::createControlFlowBlock({
                        new ASTExpressionStatementNode(
                            new ASTFunctionInvocationExpressionNode(
                                ASTNodeFactory::callableIdExpression,
                                ASTNodeFactory::createFunctionArgumentList({
                                    new ASTFunctionArgumentNode(ASTNodeFactory::idExpression)
                                })
                            )
                        )
                    }),
                    ASTNodeFactory::catchErrorVariable
                )
        )},
        {140, new ASTTryStatementNode(
                new ASTTryBlockNode(
                    ASTNodeFactory::tryKeyword,
                    ASTNodeFactory::createControlFlowBlock({
                        new ASTExpressionStatementNode(
                            new ASTFunctionInvocationExpressionNode(
                                ASTNodeFactory::callableIdExpression,
                                ASTNodeFactory::createFunctionArgumentList({
                                    new ASTFunctionArgumentNode(ASTNodeFactory::stringExpression)
                                })
                            )
                        )
                    })
                ),
                new ASTCatchBlockNode(
                    ASTNodeFactory::catchKeyword,
                    ASTNodeFactory::createControlFlowBlock({
                        new ASTExpressionStatementNode(
                            new ASTFunctionInvocationExpressionNode(
                                ASTNodeFactory::callableIdExpression,
                                ASTNodeFactory::createFunctionArgumentList({
                                    new ASTFunctionArgumentNode(ASTNodeFactory::stringExpression)
                                })
                            )
                        )
                    })
                )
        )},
        {141, new ASTTryStatementNode(
                new ASTTryBlockNode(
                    ASTNodeFactory::tryKeyword,
                    ASTNodeFactory::createControlFlowBlock({
                        new ASTExpressionStatementNode(
                            new ASTFunctionInvocationExpressionNode(
                                ASTNodeFactory::callableIdExpression,
                                ASTNodeFactory::createFunctionArgumentList({
                                    new ASTFunctionArgumentNode(ASTNodeFactory::stringExpression)
                                })
                            )
                        )
                    })
                ),
                new ASTCatchBlockNode(
                    ASTNodeFactory::catchKeyword,
                    ASTNodeFactory::createControlFlowBlock({
                        new ASTExpressionStatementNode(
                            new ASTFunctionInvocationExpressionNode(
                                ASTNodeFactory::callableIdExpression,
                                ASTNodeFactory::createFunctionArgumentList({
                                    new ASTFunctionArgumentNode(ASTNodeFactory::idExpression)
                                })
                            )
                        )
                    }),
                    ASTNodeFactory::catchErrorVariable
                ),
                new ASTFinallyBlockNode(
                    ASTNodeFactory::finallyKeyword,
                    ASTNodeFactory::createControlFlowBlock({
                        new ASTExpressionStatementNode(
                            new ASTFunctionInvocationExpressionNode(
                                ASTNodeFactory::callableIdExpression,
                                ASTNodeFactory::createFunctionArgumentList({
                                    new ASTFunctionArgumentNode(ASTNodeFactory::stringExpression)
                                })
                            )
                        )
                    })
                )
        )},
        {142, new ASTTryStatementNode(
                new ASTTryBlockNode(
                    ASTNodeFactory::tryKeyword,
                    ASTNodeFactory::createControlFlowBlock({
                        new ASTExpressionStatementNode(
                            new ASTFunctionInvocationExpressionNode(
                                ASTNodeFactory::callableIdExpression,
                                ASTNodeFactory::createFunctionArgumentList({
                                    new ASTFunctionArgumentNode(ASTNodeFactory::stringExpression)
                                })
                            )
                        )
                    })
                ),
                new ASTCatchBlockNode(
                    ASTNodeFactory::catchKeyword,
                    ASTNodeFactory::createControlFlowBlock({
                        new ASTExpressionStatementNode(
                            new ASTFunctionInvocationExpressionNode(
                                ASTNodeFactory::callableIdExpression,
                                ASTNodeFactory::createFunctionArgumentList({
                                    new ASTFunctionArgumentNode(ASTNodeFactory::stringExpression)
                                })
                            )
                        )
                    })
                ),
                new ASTFinallyBlockNode(
                    ASTNodeFactory::finallyKeyword,
                    ASTNodeFactory::createControlFlowBlock({
                        new ASTExpressionStatementNode(
                            new ASTFunctionInvocationExpressionNode(
                                ASTNodeFactory::callableIdExpression,
                                ASTNodeFactory::createFunctionArgumentList({
                                    new ASTFunctionArgumentNode(ASTNodeFactory::stringExpression)
                                })
                            )
                        )
                    })
                )
        )},
        {143, new ASTFunctionDeclarationNode(
                ASTNodeFactory::createFunctionDefinition(
                ASTNodeFactory::functionName,
                ASTNodeFactory::createFunctionParameterList(),
                ASTNodeFactory::idType),
                ASTNodeFactory::createFunctionBlock({
                    new ASTFunctionReturnExpressionNode(ASTNodeFactory::functionReturn, ASTNodeFactory::stringExpression)
                })
        )},
        {144, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLambdaWithFatArrowExpressionNode(
                        ASTNodeFactory::createFunctionParameterList(
                            {
                                ASTNodeFactory::createFunctionParameter(ASTNodeFactory::idExpression, ASTNodeFactory::idType),
                                ASTNodeFactory::createFunctionParameter(ASTNodeFactory::idExpression, ASTNodeFactory::idType)
                            }
                        ),
                        new ASTLambdaReturnExpressionNode(
                                ASTNodeFactory::lambdaFatArrow,
                                new ASTBinaryExpressionNode(
                                    ASTNodeFactory::idExpression,
                                    ASTNodeFactory::plus,
                                    ASTNodeFactory::idExpression
                                )
                        )

                )
        )},
        {145, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLambdaWithFatArrowExpressionNode(
                    ASTNodeFactory::createFunctionParameterList(
                        {
                         ASTNodeFactory::createFunctionParameter(ASTNodeFactory::idExpression, ASTNodeFactory::intType),
                         ASTNodeFactory::createFunctionParameter(ASTNodeFactory::idExpression, ASTNodeFactory::intType)
                        }
                    ),
                    new ASTLambdaReturnExpressionNode(
                            ASTNodeFactory::lambdaFatArrow,
                            new ASTBinaryExpressionNode(
                                    ASTNodeFactory::idExpression,
                                    ASTNodeFactory::greaterThan,
                                    ASTNodeFactory::idExpression
                            )
                    ),
                    ASTNodeFactory::booleanType
                )
        )},
        {146, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLambdaExpressionNode(
                    ASTNodeFactory::createFunctionParameterList(
                        {
                            ASTNodeFactory::createFunctionParameter(ASTNodeFactory::idExpression, ASTNodeFactory::intType),
                        }
                    ),
                    ASTNodeFactory::createFunctionBlock({
                            new ASTFunctionReturnExpressionNode(
                                    ASTNodeFactory::functionReturn,
                                    new ASTBinaryExpressionNode(
                                            ASTNodeFactory::idExpression,
                                            ASTNodeFactory::plus,
                                            ASTNodeFactory::intExpression
                                    )
                            )
                    }),
                    ASTNodeFactory::intType
                )
        )},
        {147, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLambdaExpressionNode(
                    ASTNodeFactory::createFunctionParameterList(
                        {
                            ASTNodeFactory::createFunctionParameter(ASTNodeFactory::idExpression, ASTNodeFactory::intType),
                        }
                    ),
                    ASTNodeFactory::createFunctionBlock({
                         new ASTFunctionReturnExpressionNode(
                             ASTNodeFactory::functionReturnFatArrow,
                             new ASTBinaryExpressionNode(
                                 ASTNodeFactory::idExpression,
                                 ASTNodeFactory::plus,
                                 ASTNodeFactory::intExpression
                             )
                         )
                    })
                )
        )},
        {148, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLambdaWithFatArrowExpressionNode(
                    ASTNodeFactory::createFunctionParameterList(
                        {
                            ASTNodeFactory::createFunctionParameter(ASTNodeFactory::idExpression, ASTNodeFactory::intType),
                        }
                    ),
                    new ASTLambdaReturnExpressionNode(
                        ASTNodeFactory::lambdaFatArrow,
                        new ASTLambdaWithFatArrowExpressionNode(
                            ASTNodeFactory::createFunctionParameterList(
                                {
                                    ASTNodeFactory::createFunctionParameter(ASTNodeFactory::idExpression, ASTNodeFactory::intType),
                                }
                            ),
                            new ASTLambdaReturnExpressionNode(
                                ASTNodeFactory::lambdaFatArrow,
                                new ASTLambdaWithFatArrowExpressionNode(
                                    ASTNodeFactory::createFunctionParameterList(
                                        {
                                            ASTNodeFactory::createFunctionParameter(ASTNodeFactory::idExpression, ASTNodeFactory::intType),
                                        }
                                    ),
                                    new ASTLambdaReturnExpressionNode(
                                        ASTNodeFactory::lambdaFatArrow,
                                        new ASTBinaryExpressionNode(
                                                ASTNodeFactory::idExpression,
                                                ASTNodeFactory::plus,
                                                new ASTBinaryExpressionNode(
                                                        ASTNodeFactory::idExpression,
                                                        ASTNodeFactory::plus,
                                                        ASTNodeFactory::idExpression
                                                )
                                        )
                                    )
                                )
                            )
                        )
                    )
                )
        )},
        {149, new ASTExpressionStatementNode(
                new ASTLambdaWithFatArrowExpressionNode(
                    ASTNodeFactory::createFunctionParameterList(
                        {
                            ASTNodeFactory::createFunctionParameter(ASTNodeFactory::idExpression, ASTNodeFactory::intType),
                        }
                    ),
                    new ASTLambdaReturnExpressionNode(
                            ASTNodeFactory::lambdaFatArrow,
                            new ASTBinaryExpressionNode(
                                    ASTNodeFactory::idExpression,
                                    ASTNodeFactory::plus,
                                    ASTNodeFactory::intExpression
                            )
                    )
                )
        )},
        {150, new ASTFunctionDeclarationNode(
                ASTNodeFactory::createFunctionDefinition(
                ASTNodeFactory::functionName,
                ASTNodeFactory::createFunctionParameterList(
                    {
                        ASTNodeFactory::createFunctionParameter(ASTNodeFactory::idExpression, ASTNodeFactory::intType),
                        ASTNodeFactory::createFunctionParameter(
                            ASTNodeFactory::idExpression,
                            ASTNodeFactory::createFunctionType({ ASTNodeFactory::intType }, ASTNodeFactory::booleanType))
                    }
                ),
                ASTNodeFactory::booleanType),
                ASTNodeFactory::createFunctionBlock({
                    new ASTFunctionReturnExpressionNode(
                        ASTNodeFactory::functionReturn,
                        new ASTFunctionInvocationExpressionNode(
                            ASTNodeFactory::callableIdExpression,
                            ASTNodeFactory::createFunctionArgumentList({
                                new ASTFunctionArgumentNode(ASTNodeFactory::idExpression)
                            })
                        )
                    )
                })
        )},
        {151, new ASTFunctionDeclarationNode(
                ASTNodeFactory::createFunctionDefinition(
                ASTNodeFactory::functionName,
                ASTNodeFactory::createFunctionParameterList(
                    {
                         ASTNodeFactory::createFunctionParameter(
                             ASTNodeFactory::idExpression,
                             ASTNodeFactory::createFunctionType(
                                 { ASTNodeFactory::intType, ASTNodeFactory::intType },
                                 ASTNodeFactory::createFunctionType(
                                         { ASTNodeFactory::intType },
                                         ASTNodeFactory::booleanType
                                 )
                             )
                         )
                    }
                ),
                ASTNodeFactory::booleanType),
                ASTNodeFactory::createFunctionBlock({
                     new ASTFunctionReturnExpressionNode(
                         ASTNodeFactory::functionReturn,
                         new ASTFunctionInvocationExpressionNode(
                             ASTNodeFactory::callableIdExpression,
                             ASTNodeFactory::createFunctionArgumentList({
                                 new ASTFunctionArgumentNode(ASTNodeFactory::idExpression)
                             })
                         )
                     )
                })
        )},
        {152, new ASTFunctionDeclarationNode(
                ASTNodeFactory::createFunctionDefinition(
                ASTNodeFactory::functionName,
                ASTNodeFactory::createFunctionParameterList(
                    {
                         ASTNodeFactory::createFunctionParameter(
                             ASTNodeFactory::idExpression,
                             ASTNodeFactory::createFunctionType(
                                 ASTNodeFactory::createFunctionType(
                                     {
                                        ASTNodeFactory::createFunctionType(
                                            { ASTNodeFactory::stringType },
                                            ASTNodeFactory::booleanType
                                        )
                                     },
                                     ASTNodeFactory::booleanType
                                 )
                             )
                         )
                    }
                ),
                ASTNodeFactory::booleanType),
                ASTNodeFactory::createFunctionBlock({
                     new ASTFunctionReturnExpressionNode(
                         ASTNodeFactory::functionReturn,
                         new ASTFunctionInvocationExpressionNode(
                             ASTNodeFactory::callableIdExpression,
                             ASTNodeFactory::createFunctionArgumentList({
                                     new ASTFunctionArgumentNode(ASTNodeFactory::idExpression)
                             })
                         )
                     )
                })
        )},
        {153, new ASTFunctionDeclarationNode(
                ASTNodeFactory::createFunctionDefinition(
                ASTNodeFactory::functionName,
                ASTNodeFactory::createFunctionParameterList(

                    {
                        ASTNodeFactory::createFunctionParameter(
                            ASTNodeFactory::idExpression,
                            ASTNodeFactory::intType
                        ),
                        ASTNodeFactory::createFunctionParameter(
                             ASTNodeFactory::idExpression,
                             ASTNodeFactory::createFunctionType(ASTNodeFactory::booleanType)
                        )
                    }
                    
                ),
                ASTNodeFactory::booleanType),
                ASTNodeFactory::createFunctionBlock({
                     new ASTFunctionReturnExpressionNode(
                         ASTNodeFactory::functionReturn,
                         new ASTFunctionInvocationExpressionNode(
                             ASTNodeFactory::callableIdExpression,
                             ASTNodeFactory::createFunctionArgumentList()
                         )
                     )
                })
        )},
        {154, new ASTFunctionDeclarationNode(
                ASTNodeFactory::createFunctionDefinition(
                ASTNodeFactory::functionName,
                ASTNodeFactory::createFunctionParameterList(),
                ASTNodeFactory::createFunctionType(ASTNodeFactory::intType)),
                ASTNodeFactory::createFunctionBlock({
                     new ASTFunctionReturnExpressionNode(
                         ASTNodeFactory::functionReturnFatArrow,
                         new ASTLambdaWithFatArrowExpressionNode(
                             ASTNodeFactory::createFunctionParameterList(),
                             new ASTLambdaReturnExpressionNode(
                                ASTNodeFactory::lambdaFatArrow,
                                ASTNodeFactory::intExpression
                             )
                         )
                     )
                })
        )},
        {155, new ASTFunctionDeclarationNode(
                ASTNodeFactory::createFunctionDefinition(
                ASTNodeFactory::functionName,
                ASTNodeFactory::createFunctionParameterList(),
                ASTNodeFactory::createFunctionType({ ASTNodeFactory::intType }, ASTNodeFactory::intType)),
                ASTNodeFactory::createFunctionBlock({
                     new ASTFunctionReturnExpressionNode(
                         ASTNodeFactory::functionReturn,
                         new ASTLambdaWithFatArrowExpressionNode(
                                 ASTNodeFactory::createFunctionParameterList(

                                     {
                                        ASTNodeFactory::createFunctionParameter(ASTNodeFactory::idExpression, ASTNodeFactory::intType)
                                     }

                                 ),
                                new ASTLambdaReturnExpressionNode(
                                        ASTNodeFactory::lambdaFatArrow,
                                        ASTNodeFactory::intExpression
                                )
                         )
                     )
                })
        )},
        {156, new ASTFunctionDeclarationNode(
                ASTNodeFactory::createFunctionDefinition(
                ASTNodeFactory::functionName,
                ASTNodeFactory::createFunctionParameterList(),
                ASTNodeFactory::booleanType),
                ASTNodeFactory::createFunctionBlock({
                     new ASTFunctionReturnExpressionNode(
                         ASTNodeFactory::functionReturn,
                         new ASTLogicalExpressionNode(
                                 ASTNodeFactory::trueExpression,
                                 ASTNodeFactory::andOperator,
                                 ASTNodeFactory::trueExpression
                         )
                     )
                })
        )},
        {157, new ASTFunctionDeclarationNode(
                ASTNodeFactory::createFunctionDefinition(
                ASTNodeFactory::functionName,
                ASTNodeFactory::createFunctionParameterList(

                    {
                        ASTNodeFactory::createFunctionParameter(
                            ASTNodeFactory::idExpression,
                            ASTNodeFactory::createFunctionType({ ASTNodeFactory::intType }, ASTNodeFactory::booleanType)
                        )
                    }
                    
                ),
                ASTNodeFactory::booleanType),
                ASTNodeFactory::createFunctionBlock({
                     new ASTFunctionReturnExpressionNode(
                         ASTNodeFactory::functionReturn,
                         new ASTLogicalExpressionNode(
                             ASTNodeFactory::trueExpression,
                             ASTNodeFactory::andOperator,
                             ASTNodeFactory::trueExpression
                         )
                     )
                })
        )},
        {158, new ASTFunctionDeclarationNode(
                ASTNodeFactory::createFunctionDefinition(
                ASTNodeFactory::functionName,
                ASTNodeFactory::createFunctionParameterList(

                    {
                         ASTNodeFactory::createFunctionParameter(
                             ASTNodeFactory::idExpression,
                             ASTNodeFactory::createProcedureType()
                         ),
                         ASTNodeFactory::createFunctionParameter(
                             ASTNodeFactory::idExpression,
                             ASTNodeFactory::createProcedureType({ ASTNodeFactory::idType })
                         )
                    }
                    
                ),
                ASTNodeFactory::booleanType),
                ASTNodeFactory::createFunctionBlock({
                    new ASTFunctionReturnExpressionNode(ASTNodeFactory::functionReturn,ASTNodeFactory::trueExpression)
                })
        )},
        {159, new ASTExpressionStatementNode(
                    new ASTLambdaExpressionNode(
                        ASTNodeFactory::createFunctionParameterList(),
                        ASTNodeFactory::createFunctionBlock({
                            new ASTFunctionReturnExpressionNode(
                                ASTNodeFactory::functionReturn,
                                new ASTLambdaWithFatArrowExpressionNode(
                                    ASTNodeFactory::createFunctionParameterList(),
                                    new ASTLambdaReturnExpressionNode(
                                        ASTNodeFactory::lambdaFatArrow,
                                        new ASTLambdaWithFatArrowExpressionNode(
                                                ASTNodeFactory::createFunctionParameterList(),
                                                new ASTLambdaReturnExpressionNode(
                                                    ASTNodeFactory::lambdaFatArrow,
                                                    ASTNodeFactory::intExpression
                                                )
                                        )
                                    )
                                )

                            )
                        }),
                        ASTNodeFactory::createFunctionType(
                            ASTNodeFactory::createFunctionType(ASTNodeFactory::intType)
                        )
                    )
        )},
        {160, new ASTExpressionStatementNode(
                new ASTLambdaWithFatArrowExpressionNode(
                        ASTNodeFactory::createFunctionParameterList(),
                        new ASTLambdaReturnExpressionNode(
                                ASTNodeFactory::lambdaFatArrow,
                                new ASTLambdaWithFatArrowExpressionNode(
                                        ASTNodeFactory::createFunctionParameterList(),
                                        new ASTLambdaReturnExpressionNode(
                                                ASTNodeFactory::lambdaFatArrow,
                                                new ASTLambdaWithFatArrowExpressionNode(
                                                        ASTNodeFactory::createFunctionParameterList(),
                                                        new ASTLambdaReturnExpressionNode(
                                                                ASTNodeFactory::lambdaFatArrow,
                                                                ASTNodeFactory::intExpression
                                                        )
                                                )
                                        )
                                )

                        ),
                        ASTNodeFactory::createFunctionType(
                            ASTNodeFactory::createFunctionType(ASTNodeFactory::intType)
                        )
                )
        )},
        {161, new ASTExpressionStatementNode(
                new ASTLambdaWithFatArrowExpressionNode(
                        ASTNodeFactory::createFunctionParameterList(),
                        new ASTLambdaReturnExpressionNode(
                            ASTNodeFactory::lambdaFatArrow,
                            new ASTLambdaWithFatArrowExpressionNode(
                                    ASTNodeFactory::createFunctionParameterList(),
                                    new ASTLambdaReturnExpressionNode(
                                            ASTNodeFactory::lambdaFatArrow,
                                            new ASTLambdaExpressionNode(
                                                ASTNodeFactory::createFunctionParameterList(),
                                                ASTNodeFactory::createFunctionBlock({
                                                    new ASTExpressionStatementNode(
                                                        new ASTBinaryExpressionNode(
                                                            ASTNodeFactory::intExpression,
                                                            ASTNodeFactory::plus,
                                                            ASTNodeFactory::intExpression
                                                        )
                                                    )
                                                })
                                            )
                                    )
                            )
                        ),
                     ASTNodeFactory::createFunctionType(
                        ASTNodeFactory::createProcedureType()
                     )
                )
        )},
        {162, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLambdaWithFatArrowExpressionNode(
                        ASTNodeFactory::createFunctionParameterList(),
                        new ASTLambdaReturnExpressionNode(
                            ASTNodeFactory::lambdaFatArrow,
                            ASTNodeFactory::intExpression
                        )
                )
        )},
        {163, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLambdaExpressionNode(
                    ASTNodeFactory::createFunctionParameterList(),
                    ASTNodeFactory::createFunctionBlock({
                         new ASTExpressionStatementNode(
                            new ASTBinaryExpressionNode(
                                ASTNodeFactory::idExpression,
                                ASTNodeFactory::plus,
                                ASTNodeFactory::intExpression
                            )
                         )
                    })
                )
        )},
        {164, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLambdaExpressionNode(
                    ASTNodeFactory::createFunctionParameterList(),
                    ASTNodeFactory::createFunctionBlock({})
                )
        )},
        {165, new ASTExpressionStatementNode(
                new ASTLambdaWithFatArrowExpressionNode(
                    ASTNodeFactory::createFunctionParameterList(),
                    new ASTLambdaReturnExpressionNode(
                            ASTNodeFactory::lambdaFatArrow,
                            ASTNodeFactory::intExpression
                    )
                )
        )},
        {166, new ASTExpressionStatementNode(
                new ASTCurryExpressionNode(
                    new ASTFunctionInvocationExpressionNode(
                            ASTNodeFactory::callableIdExpression,
                            ASTNodeFactory::createFunctionArgumentList({
                                new ASTFunctionArgumentNode(ASTNodeFactory::idExpression)
                            })
                    ),
                    ASTNodeFactory::createFunctionArgumentList({
                            new ASTFunctionArgumentNode(ASTNodeFactory::idExpression)
                    })
                )
        )},
        {167, new ASTExpressionStatementNode(
                new ASTCurryExpressionNode(
                    new ASTCurryExpressionNode(
                        new ASTFunctionInvocationExpressionNode(
                            ASTNodeFactory::callableIdExpression,
                            ASTNodeFactory::createFunctionArgumentList({
                                new ASTFunctionArgumentNode(ASTNodeFactory::idExpression)
                            })
                        ),
                        ASTNodeFactory::createFunctionArgumentList({
                            new ASTFunctionArgumentNode(ASTNodeFactory::idExpression)
                        })
                    ),
                    ASTNodeFactory::createFunctionArgumentList({
                        new ASTFunctionArgumentNode(ASTNodeFactory::idExpression)
                    })
                )
        )},
        {168, new ASTExpressionStatementNode(
                new ASTCurryExpressionNode(
                    new ASTCurryExpressionNode(
                        new ASTCurryExpressionNode(
                            new ASTFunctionInvocationExpressionNode(
                                ASTNodeFactory::callableIdExpression,
                                ASTNodeFactory::createFunctionArgumentList({
                                        new ASTFunctionArgumentNode(ASTNodeFactory::idExpression)
                                })
                            ),
                            ASTNodeFactory::createFunctionArgumentList({
                                    new ASTFunctionArgumentNode(ASTNodeFactory::idExpression)
                            })
                        ),
                        ASTNodeFactory::createFunctionArgumentList({
                            new ASTFunctionArgumentNode(ASTNodeFactory::idExpression)
                        })
                    ),
                    ASTNodeFactory::createFunctionArgumentList({
                        new ASTFunctionArgumentNode(ASTNodeFactory::idExpression)
                    })
                )
        )},
        {169, new ASTFunctionDeclarationNode(
                ASTNodeFactory::createFunctionDefinition(
                ASTNodeFactory::functionName,
                ASTNodeFactory::createFunctionParameterList(

                    {
                         ASTNodeFactory::createFunctionParameter(
                             ASTNodeFactory::idExpression,
                             ASTNodeFactory::createTupleType({
                                 ASTNodeFactory::intType,
                                 ASTNodeFactory::stringType,
                                 ASTNodeFactory::booleanType,
                                 ASTNodeFactory::idType
                             })
                         ),
                    }
                    
                ),
                ASTNodeFactory::booleanType),
                ASTNodeFactory::createFunctionBlock({
                    new ASTFunctionReturnExpressionNode(ASTNodeFactory::functionReturn,ASTNodeFactory::trueExpression)
                })
        )},
        {170, new ASTFunctionDeclarationNode(
                ASTNodeFactory::createFunctionDefinition(
                ASTNodeFactory::functionName,
                ASTNodeFactory::createFunctionParameterList(
                    {
                         ASTNodeFactory::createFunctionParameter(
                             ASTNodeFactory::idExpression,
                             ASTNodeFactory::createArrayType(ASTNodeFactory::intType)
                         ),
                         ASTNodeFactory::createFunctionParameter(
                             ASTNodeFactory::idExpression,
                             ASTNodeFactory::createArrayType(ASTNodeFactory::idType)
                         ),
                         ASTNodeFactory::createFunctionParameter(
                             ASTNodeFactory::idExpression,
                             ASTNodeFactory::createArrayType(
                                 ASTNodeFactory::createArrayType(ASTNodeFactory::intType)
                             )
                         ),
                         ASTNodeFactory::createFunctionParameter(
                                 ASTNodeFactory::idExpression,
                                 ASTNodeFactory::createArrayType(
                                    ASTNodeFactory::createArrayType(
                                        ASTNodeFactory::createArrayType(ASTNodeFactory::intType)
                                    )
                                 )
                         ),
                    }
                    
                ),
                ASTNodeFactory::booleanType),
                ASTNodeFactory::createFunctionBlock({
                    new ASTFunctionReturnExpressionNode(ASTNodeFactory::functionReturn,ASTNodeFactory::trueExpression)
                })
        )},
        {171, new ASTFunctionDeclarationNode(
                ASTNodeFactory::createFunctionDefinition(
                ASTNodeFactory::functionName,
                ASTNodeFactory::createFunctionParameterList(

                    {
                         ASTNodeFactory::createFunctionParameter(
                             ASTNodeFactory::idExpression,
                             ASTNodeFactory::createArrayType(
                                ASTNodeFactory::createFunctionType(
                                    { ASTNodeFactory::intType },
                                    ASTNodeFactory::booleanType
                                )
                             )
                         ),
                    }
                    
                ),
                ASTNodeFactory::booleanType),
                ASTNodeFactory::createFunctionBlock({
                    new ASTFunctionReturnExpressionNode(ASTNodeFactory::functionReturn,ASTNodeFactory::trueExpression)
                })
        )},
        {172, new ASTVariableDeclarationNode(
                ASTNodeFactory::createConstInitWithType(ASTNodeFactory::intType),
                ASTNodeFactory::intExpression
        )},
        {173, new ASTVariableDeclarationNode(
                ASTNodeFactory::createConstInitWithType(ASTNodeFactory::floatType),
                ASTNodeFactory::floatExpression
        )},
        {174, new ASTVariableDeclarationNode(
                ASTNodeFactory::createConstInitWithType(ASTNodeFactory::charType),
                ASTNodeFactory::charExpression
        )},
        {175, new ASTVariableDeclarationNode(
                ASTNodeFactory::createConstInitWithType(ASTNodeFactory::stringType),
                ASTNodeFactory::stringExpression
        )},
        {176, new ASTVariableDeclarationNode(
                ASTNodeFactory::createConstInitWithType(ASTNodeFactory::booleanType),
                ASTNodeFactory::trueExpression
        )},
        {177, new ASTVariableDeclarationNode(
                ASTNodeFactory::createConstInitWithType(
                    ASTNodeFactory::createArrayType(ASTNodeFactory::intType)
                ),
                ASTNodeFactory::createArrayExpression({
                    ASTNodeFactory::intExpression,
                    ASTNodeFactory::intExpression,
                    ASTNodeFactory::intExpression
                })
        )},
        {178, new ASTVariableDeclarationNode(
                ASTNodeFactory::createConstInitWithType(
                    ASTNodeFactory::createFunctionType({ ASTNodeFactory::intType }, ASTNodeFactory::booleanType)
                ),
                new ASTLambdaWithFatArrowExpressionNode(
                        ASTNodeFactory::createFunctionParameterList(
                            {
                                ASTNodeFactory::createFunctionParameter(ASTNodeFactory::idExpression, ASTNodeFactory::intType)
                            }
                        ),
                        new ASTLambdaReturnExpressionNode(
                                ASTNodeFactory::lambdaFatArrow,
                                ASTNodeFactory::trueExpression
                        )
                )
        )},
        {179, new ASTVariableDeclarationNode(
                ASTNodeFactory::createConstInitWithType(
                    ASTNodeFactory::createProcedureType({ ASTNodeFactory::intType })
                ),
                new ASTLambdaExpressionNode(
                        ASTNodeFactory::createFunctionParameterList(

                            {
                                ASTNodeFactory::createFunctionParameter(ASTNodeFactory::idExpression, ASTNodeFactory::intType)
                            }
                            
                        ),
                        ASTNodeFactory::createFunctionBlock({
                             new ASTExpressionStatementNode(
                                 new ASTBinaryExpressionNode(
                                     ASTNodeFactory::idExpression,
                                     ASTNodeFactory::plus,
                                     ASTNodeFactory::intExpression
                                 )
                             )
                        })
                )
        )},
        {180, new ASTVariableDeclarationNode(
                ASTNodeFactory::createConstInitWithType(
                    ASTNodeFactory::createTupleType({
                        ASTNodeFactory::intType,
                        ASTNodeFactory::intType
                    })
                ),
                ASTNodeFactory::createTupleExpression({
                    ASTNodeFactory::intExpression,
                    ASTNodeFactory::intExpression
                })
        )},
        {181, new ASTVariableDeclarationNode(
                ASTNodeFactory::createConstInitWithType(ASTNodeFactory::idType),
                ASTNodeFactory::stringExpression
        )},
        {182, new ASTUseSingleModuleDeclarationNode(
                ASTNodeFactory::useKeyword,
                ASTNodeFactory::importModuleName,
                ASTNodeFactory::fromKeyword,
                ASTNodeFactory::importPath
        )},
        {183, new ASTUseManyByWildcardModuleDeclarationNode(
                ASTNodeFactory::useKeyword,
                ASTNodeFactory::createImportModuleByWildcard(),
                ASTNodeFactory::fromKeyword,
                ASTNodeFactory::importPath
        )},
        {184, new ASTImportManyByWildcardModuleDeclarationNode(
                ASTNodeFactory::importKeyword,
                ASTNodeFactory::createImportModuleByWildcard(),
                ASTNodeFactory::fromKeyword,
                ASTNodeFactory::importPath
        )},
        {185, new ASTUseManyModuleDeclarationNode(
                ASTNodeFactory::useKeyword,
                ASTNodeFactory::createImportModuleByGroupItem({
                      new ASTImportModuleListItemNode(
                          ASTNodeFactory::createImportModuleByGroupItem({
                            ASTNodeFactory::importModuleNormalItem,
                            ASTNodeFactory::importModuleSpreadItem
                      })),
                      ASTNodeFactory::importModuleAliasItem,
                      ASTNodeFactory::importModuleNormalItem,
                      ASTNodeFactory::importModuleByWildcardItem,
                      ASTNodeFactory::importModuleSpreadItem,
                      ASTNodeFactory::importModuleWildcardItem
                }),
                ASTNodeFactory::fromKeyword,
                ASTNodeFactory::importPath
        )},
        {186, new ASTImportManyModuleDeclarationNode(
                ASTNodeFactory::importKeyword,
                ASTNodeFactory::createImportModuleByGroupItem({
                      new ASTImportModuleListItemNode(
                              ASTNodeFactory::createImportModuleByGroupItem({
                                    ASTNodeFactory::importModuleNormalItem,
                                    ASTNodeFactory::importModuleSpreadItem
                      })),
                      ASTNodeFactory::importModuleAliasItem,
                      ASTNodeFactory::importModuleNormalItem,
                      ASTNodeFactory::importModuleByWildcardItem,
                      ASTNodeFactory::importModuleSpreadItem,
                      ASTNodeFactory::importModuleWildcardItem
                }),
                ASTNodeFactory::fromKeyword,
                ASTNodeFactory::importPath
        )},
        {187, new ASTClassDeclarationNode(
                ASTNodeFactory::classKeyword,
                ASTNodeFactory::className,
                ASTNodeFactory::createClassBlock(
                    {
                        new ASTClassPropertyDeclarationNode(
                            new ASTClassPropertyInitNode(
                                ASTNodeFactory::publicModifier,
                                ASTNodeFactory::classPropertyName,
                                {},
                                {},
                                {},
                                ASTNodeFactory::typeColon,
                                ASTNodeFactory::intType
                            )
                        ),
                        new ASTClassPropertyDeclarationNode(
                                new ASTClassPropertyInitNode(
                                        ASTNodeFactory::publicModifier,
                                        ASTNodeFactory::classPropertyName,
                                        {},
                                        {},
                                        {},
                                        ASTNodeFactory::typeColon,
                                        ASTNodeFactory::intType
                                ),
                                ASTNodeFactory::intExpression
                        ),
                        new ASTClassPropertyDeclarationNode(
                                new ASTClassPropertyInitNode(
                                        ASTNodeFactory::publicModifier,
                                        ASTNodeFactory::classPropertyName,
                                        {},
                                        {},
                                        ASTNodeFactory::assignment
                                ),
                                ASTNodeFactory::intExpression
                        ),
                        new ASTClassPropertyDeclarationNode(
                                new ASTClassPropertyInitNode(
                                        ASTNodeFactory::publicModifier,
                                        ASTNodeFactory::classPropertyName,
                                        {},
                                        ASTNodeFactory::constKeyword,
                                        {},
                                        ASTNodeFactory::typeColon,
                                        ASTNodeFactory::intType
                                )
                        ),
                        new ASTClassPropertyDeclarationNode(
                                new ASTClassPropertyInitNode(
                                        ASTNodeFactory::publicModifier,
                                        ASTNodeFactory::classPropertyName,
                                        {},
                                        ASTNodeFactory::constKeyword,
                                        ASTNodeFactory::assignment,
                                        ASTNodeFactory::typeColon,
                                        ASTNodeFactory::intType
                                ),
                                ASTNodeFactory::intExpression
                        ),
                        new ASTClassPropertyDeclarationNode(
                                new ASTClassPropertyInitNode(
                                        ASTNodeFactory::publicModifier,
                                        ASTNodeFactory::classPropertyName,
                                        {},
                                        ASTNodeFactory::constKeyword,
                                        ASTNodeFactory::assignment
                                ),
                                ASTNodeFactory::intExpression
                        ),
                        new ASTClassPropertyDeclarationNode(
                                new ASTClassPropertyInitNode(
                                        ASTNodeFactory::protectedModifier,
                                        ASTNodeFactory::classPropertyName,
                                        ASTNodeFactory::staticKeyword,
                                        {},
                                        {},
                                        ASTNodeFactory::typeColon,
                                        ASTNodeFactory::intType
                                )
                        ),
                        new ASTClassPropertyDeclarationNode(
                                new ASTClassPropertyInitNode(
                                        ASTNodeFactory::protectedModifier,
                                        ASTNodeFactory::classPropertyName,
                                        ASTNodeFactory::staticKeyword,
                                        {},
                                        ASTNodeFactory::assignment,
                                        ASTNodeFactory::typeColon,
                                        ASTNodeFactory::intType
                                ),
                                ASTNodeFactory::intExpression
                        ),
                        new ASTClassPropertyDeclarationNode(
                                new ASTClassPropertyInitNode(
                                        ASTNodeFactory::protectedModifier,
                                        ASTNodeFactory::classPropertyName,
                                        ASTNodeFactory::staticKeyword,
                                        {},
                                        ASTNodeFactory::assignment
                                ),
                                ASTNodeFactory::intExpression
                        ),
                        new ASTClassPropertyDeclarationNode(
                            new ASTClassPropertyInitNode(
                                ASTNodeFactory::privateModifier,
                                ASTNodeFactory::classPropertyName,
                                ASTNodeFactory::staticKeyword,
                                ASTNodeFactory::constKeyword,
                                {},
                                ASTNodeFactory::typeColon,
                                ASTNodeFactory::booleanType
                            )
                        ),
                        new ASTClassPropertyDeclarationNode(
                                new ASTClassPropertyInitNode(
                                        ASTNodeFactory::privateModifier,
                                        ASTNodeFactory::classPropertyName,
                                        ASTNodeFactory::staticKeyword,
                                        ASTNodeFactory::constKeyword,
                                        ASTNodeFactory::assignment,
                                        ASTNodeFactory::typeColon,
                                        ASTNodeFactory::booleanType
                                ),
                                ASTNodeFactory::trueExpression
                        ),
                        new ASTClassPropertyDeclarationNode(
                                new ASTClassPropertyInitNode(
                                        ASTNodeFactory::privateModifier,
                                        ASTNodeFactory::classPropertyName,
                                        ASTNodeFactory::staticKeyword,
                                        ASTNodeFactory::constKeyword,
                                        ASTNodeFactory::assignment
                                ),
                                ASTNodeFactory::trueExpression
                        )
                    },
                    {
                        new ASTClassMethodDeclarationNode(
                            new ASTClassMethodDefinitionNode(
                                ASTNodeFactory::publicModifier,
                                ASTNodeFactory::classMethodName,
                                ASTNodeFactory::staticKeyword
                            ),
                            ASTNodeFactory::createFunctionParameterList(

                                {
                                    ASTNodeFactory::createFunctionParameter(ASTNodeFactory::idExpression, ASTNodeFactory::intType)
                                }
                                
                            ),
                            ASTNodeFactory::createFunctionBlock({
                                new ASTFunctionReturnExpressionNode(
                                    ASTNodeFactory::functionReturn,
                                    new ASTNewClassInstanceExpressionNode(
                                        ASTNodeFactory::newKeyword,
                                        ASTNodeFactory::className,
                                        ASTNodeFactory::createFunctionArgumentList({
                                            new ASTFunctionArgumentNode(ASTNodeFactory::idExpression)
                                        })
                                  )
                                )
                            }),
                            ASTNodeFactory::idType
                        ),
                        new ASTClassMethodDeclarationNode(
                                new ASTClassMethodDefinitionNode(
                                        ASTNodeFactory::protectedModifier,
                                        ASTNodeFactory::classMethodName,
                                        ASTNodeFactory::staticKeyword
                                ),
                                ASTNodeFactory::createFunctionParameterList(),
                                ASTNodeFactory::createFunctionBlock({
                                     new ASTFunctionReturnExpressionNode(
                                         ASTNodeFactory::functionReturn,
                                         new ASTNewClassInstanceExpressionNode(
                                             ASTNodeFactory::newKeyword,
                                             ASTNodeFactory::className,
                                             ASTNodeFactory::createFunctionArgumentList()
                                         )
                                     )
                                }),
                                ASTNodeFactory::idType
                        ),
                        new ASTClassMethodDeclarationNode(
                                new ASTClassMethodDefinitionNode(
                                        ASTNodeFactory::privateModifier,
                                        ASTNodeFactory::classMethodName,
                                        ASTNodeFactory::staticKeyword
                                ),
                                ASTNodeFactory::createFunctionParameterList(),
                                ASTNodeFactory::createFunctionBlock({
                                    new ASTFunctionReturnExpressionNode(
                                        ASTNodeFactory::functionReturn,
                                        new ASTNewClassInstanceExpressionNode(
                                            ASTNodeFactory::newKeyword,
                                            ASTNodeFactory::className,
                                            ASTNodeFactory::createFunctionArgumentList({
                                                new ASTFunctionArgumentNode(ASTNodeFactory::intExpression)
                                            })
                                        )
                                    )
                                }),
                                ASTNodeFactory::idType
                        ),
                        new ASTClassMethodDeclarationNode(
                            new ASTClassMethodDefinitionNode(
                                    ASTNodeFactory::publicModifier,
                                    ASTNodeFactory::classMethodName
                            ),
                                ASTNodeFactory::createFunctionParameterList(),
                                ASTNodeFactory::createFunctionBlock({
                                    new ASTFunctionReturnExpressionNode(
                                        ASTNodeFactory::functionReturn,
                                        ASTNodeFactory::classPropertyAccessExpression
                                    )
                                }),
                                ASTNodeFactory::booleanType
                        ),
                        new ASTClassMethodDeclarationNode(
                            new ASTClassMethodDefinitionNode(
                                    ASTNodeFactory::protectedModifier,
                                    ASTNodeFactory::classMethodName
                            ),
                            ASTNodeFactory::createFunctionParameterList(

                                {
                                    ASTNodeFactory::createFunctionParameter(
                                        ASTNodeFactory::idExpression,
                                        ASTNodeFactory::booleanType
                                    )
                                }
                                
                            ),
                            ASTNodeFactory::createFunctionBlock({
                                new ASTClassPropertyAssignmentStatementNode(
                                    ASTNodeFactory::classPropertyAssignment,
                                    ASTNodeFactory::idExpression
                                ),
                                new ASTFunctionReturnExpressionNode(
                                    ASTNodeFactory::functionReturn,
                                    ASTNodeFactory::thisExpression
                                )
                            }),
                            ASTNodeFactory::thisType
                        ),
                        new ASTClassMethodDeclarationNode(
                            new ASTClassMethodDefinitionNode(
                                    ASTNodeFactory::privateModifier,
                                    ASTNodeFactory::classMethodName
                            ),
                            ASTNodeFactory::createFunctionParameterList(),
                            ASTNodeFactory::createFunctionBlock({
                                new ASTFunctionReturnExpressionNode(
                                    ASTNodeFactory::functionReturn,
                                    ASTNodeFactory::stringExpression
                                )
                            }),
                            ASTNodeFactory::stringType
                        ),
                        new ASTClassMethodDeclarationNode(
                                new ASTClassMethodDefinitionNode(
                                        ASTNodeFactory::privateModifier,
                                        ASTNodeFactory::classMethodName
                                ),
                                ASTNodeFactory::createFunctionParameterList(),
                                ASTNodeFactory::createFunctionBlock({
                                     new ASTClassPropertyAssignmentStatementNode(
                                         ASTNodeFactory::classPropertyAssignment,
                                         ASTNodeFactory::trueExpression
                                     )
                                })
                        )
                    },
                    {
                        new ASTClassConstructorDeclarationNode(
                                ASTNodeFactory::classConstructor,
                                ASTNodeFactory::createFunctionParameterList(),
                                ASTNodeFactory::createFunctionBlock({
                                    new ASTExpressionStatementNode(
                                        new ASTClassMethodInvocationExpressionNode(
                                            ASTNodeFactory::classAccess,
                                            ASTNodeFactory::classMethodCall,
                                            ASTNodeFactory::createFunctionArgumentList({
                                                new ASTFunctionArgumentNode(ASTNodeFactory::intExpression)
                                            })
                                        )
                                    ),
                                    new ASTClassPropertyAssignmentStatementNode(
                                         ASTNodeFactory::classPropertyAssignment,
                                         ASTNodeFactory::intExpression
                                    ),
                                    new ASTClassPropertyAssignmentStatementNode(
                                         ASTNodeFactory::classPropertyAssignment,
                                         ASTNodeFactory::trueExpression
                                    ),
                                })
                        ),
                        new ASTClassConstructorDeclarationNode(
                            ASTNodeFactory::classConstructor,
                            ASTNodeFactory::createFunctionParameterList(

                                {
                                    ASTNodeFactory::createFunctionParameter(
                                        ASTNodeFactory::idExpression,
                                        ASTNodeFactory::intType
                                    )
                                }
                                
                            ),
                            ASTNodeFactory::createFunctionBlock({
                                     new ASTClassPropertyAssignmentStatementNode(
                                         ASTNodeFactory::classPropertyAssignment,
                                         ASTNodeFactory::idExpression
                                     ),
                                     new ASTClassPropertyAssignmentStatementNode(
                                         ASTNodeFactory::classPropertyAssignment,
                                         ASTNodeFactory::trueExpression
                                     ),
                                     new ASTExpressionStatementNode(
                                         new ASTClassMethodInvocationExpressionNode(
                                             ASTNodeFactory::classAccess,
                                             ASTNodeFactory::classMethodCall,
                                             ASTNodeFactory::createFunctionArgumentList({
                                                new ASTFunctionArgumentNode(ASTNodeFactory::classPropertyAccessExpression)
                                             })
                                         )
                                     )
                             })
                        )
                    }
                )
        )},
        {188, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::intExpression,
                ASTNodeFactory::exportKeyword
        )},
        {189, new ASTFunctionDeclarationNode(
                ASTNodeFactory::createFunctionDefinition(
                    ASTNodeFactory::functionName,
                    ASTNodeFactory::createFunctionParameterList({
                            ASTNodeFactory::intFunctionParameter,
                    }),
                    ASTNodeFactory::intType),
                ASTNodeFactory::createFunctionBlock({
                    new ASTFunctionReturnExpressionNode(
                        ASTNodeFactory::functionReturn,
                        new ASTBinaryExpressionNode(
                            ASTNodeFactory::idExpression,
                            ASTNodeFactory::plus,
                            ASTNodeFactory::intExpression
                        )
                    )
                }),
                ASTNodeFactory::exportKeyword
        )},
        {190, new ASTProcedureDeclarationNode(
                ASTNodeFactory::createProcedureDefinition(
                    ASTNodeFactory::functionName,
                    ASTNodeFactory::createFunctionParameterList({
                        ASTNodeFactory::intFunctionParameter,
                })),
                ASTNodeFactory::createFunctionBlock({
                    new ASTVariableDeclarationNode(
                            ASTNodeFactory::constInit,
                            ASTNodeFactory::intExpression
                    )
                }),
                ASTNodeFactory::exportKeyword
        )},
        {191, new ASTExpressionStatementNode(
                new ASTFunctionInvocationExpressionNode(
                        ASTNodeFactory::callableModuleAccessExpression,
                        ASTNodeFactory::createFunctionArgumentList({
                            new ASTFunctionArgumentNode(ASTNodeFactory::stringExpression)
                        })
                )
        )},
        {192, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLogicalExpressionNode(
                    ASTNodeFactory::bangId,
                    ASTNodeFactory::andOperator,
                    ASTNodeFactory::trueExpression
                )
        )},
        {193, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createRefExpression(ASTNodeFactory::intExpression)
        )},
        {194, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createRefExpression(ASTNodeFactory::floatExpression)
        )},
        {195, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createRefExpression(ASTNodeFactory::stringExpression)
        )},
        {196, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createRefExpression(ASTNodeFactory::trueExpression)
        )},
        {197, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createRefExpression(ASTNodeFactory::charExpression)
        )},
        {198, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createRefExpression(ASTNodeFactory::createArrayExpression({
                  ASTNodeFactory::intExpression,
                  ASTNodeFactory::intExpression,
                  ASTNodeFactory::intExpression
                }))
        )},
        {199, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createRefExpression(ASTNodeFactory::createStructExpression({
                    ASTNodeFactory::createStructKeyValue(ASTNodeFactory::intExpression),
                    ASTNodeFactory::createStructKeyValue(ASTNodeFactory::trueExpression)
                }))
        )},
        {200, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createRefExpression(ASTNodeFactory::createTupleExpression({
                    ASTNodeFactory::stringExpression,
                    ASTNodeFactory::trueExpression,
                    ASTNodeFactory::intExpression
                }))
        )},
        {201, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createRefExpression(ASTNodeFactory::idExpression)
        )},
        {202, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createRefExpression(
                    ASTNodeFactory::createObjectAccessExpression(
                        ASTNodeFactory::objectAccessSourceId,
                        ASTNodeFactory::objectAccessTargetId
                    )
                )
        )},
        {203, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createRefExpression(
                    new ASTArrayAccessExpressionNode(
                        ASTNodeFactory::idExpression,
                        ASTNodeFactory::arrayAccessInt
                    )
                )
        )},
        {204, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createRefExpression(
                    ASTNodeFactory::createTupleAccessExpression(
                        ASTNodeFactory::objectAccessSourceId,
                        ASTNodeFactory::tupleAccess
                    )
                )
        )},
        {205, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createArrayExpression({
                  ASTNodeFactory::refIntExpression,
                  ASTNodeFactory::refIntExpression,
                  ASTNodeFactory::refIntExpression
               })
        )},
        {206, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createStructExpression({
                   ASTNodeFactory::createStructKeyValue(ASTNodeFactory::refIntExpression),
                   ASTNodeFactory::createStructKeyValue(ASTNodeFactory::refCharExpression)
               })
        )},
        {207, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createTupleExpression({
                    ASTNodeFactory::refStringExpression,
                    ASTNodeFactory::refTrueExpression,
                    ASTNodeFactory::refIntExpression
                })
        )},
        {208, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createDrefExpression(ASTNodeFactory::idExpression)
        )},
        {209, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createDrefExpression(
                    ASTNodeFactory::createObjectAccessExpression(
                        ASTNodeFactory::objectAccessSourceId,
                        ASTNodeFactory::objectAccessTargetId
                    )
                )
        )},
        {210, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createDrefExpression(
                    new ASTArrayAccessExpressionNode(
                        ASTNodeFactory::idExpression,
                        ASTNodeFactory::arrayAccessInt
                    )
                )
        )},
        {211, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createDrefExpression(
                    ASTNodeFactory::createTupleAccessExpression(
                        ASTNodeFactory::objectAccessSourceId,
                        ASTNodeFactory::tupleAccess
                    )
                )
        )},
        {212, new ASTFunctionDeclarationNode(
                ASTNodeFactory::createFunctionDefinition(
                    ASTNodeFactory::functionName,
                    ASTNodeFactory::createFunctionParameterList({
                            ASTNodeFactory::createFunctionParameter(ASTNodeFactory::createRefType(ASTNodeFactory::intType)),
                            ASTNodeFactory::createFunctionParameter(ASTNodeFactory::createRefType(ASTNodeFactory::booleanType)),
                            ASTNodeFactory::createFunctionParameter(ASTNodeFactory::createRefType(ASTNodeFactory::createArrayType(ASTNodeFactory::intType))),
                    }),
                    ASTNodeFactory::createRefType(ASTNodeFactory::intType)
                ),
                ASTNodeFactory::createFunctionBlock({
                    new ASTFunctionReturnExpressionNode(
                        ASTNodeFactory::functionReturn,
                        ASTNodeFactory::createRefExpression(ASTNodeFactory::intExpression)
                    )
                })
        )},
        {213, new ASTVariableDeclarationNode(
                ASTNodeFactory::createConstInitWithType(ASTNodeFactory::createRefType(ASTNodeFactory::intType)),
                ASTNodeFactory::idExpression
        )},
        {214, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLambdaWithFatArrowExpressionNode(
                        ASTNodeFactory::createFunctionParameterList({
                            ASTNodeFactory::createFunctionParameter(ASTNodeFactory::idExpression, ASTNodeFactory::createRefType(ASTNodeFactory::intType))
                        }),
                        new ASTLambdaReturnExpressionNode(
                            ASTNodeFactory::lambdaFatArrow,
                            new ASTBinaryExpressionNode(
                                ASTNodeFactory::idExpression,
                                ASTNodeFactory::plus,
                                ASTNodeFactory::intExpression
                            )
                        )
                )
        )},
        {215, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLambdaExpressionNode(
                    ASTNodeFactory::createFunctionParameterList({
                        ASTNodeFactory::createFunctionParameter(ASTNodeFactory::idExpression, ASTNodeFactory::createRefType(ASTNodeFactory::intType)),
                    }),
                    ASTNodeFactory::createFunctionBlock({
                        new ASTFunctionReturnExpressionNode(
                            ASTNodeFactory::functionReturn,
                            ASTNodeFactory::createRefExpression(
                                new ASTBinaryExpressionNode(
                                    ASTNodeFactory::idExpression,
                                    ASTNodeFactory::plus,
                                    ASTNodeFactory::intExpression
                            ))
                        )
                    }),
                    ASTNodeFactory::createRefType(ASTNodeFactory::intType)
                )
        )},
        {216, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createRefExpression(
                    ASTNodeFactory::createArrayExpression({
                        ASTNodeFactory::intExpression,
                        ASTNodeFactory::intExpression,
                        ASTNodeFactory::intExpression
                    })
                )
        )},
        {217, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createSrefExpression(ASTNodeFactory::idExpression)
        )},
        {218, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createSrefExpression(
                        ASTNodeFactory::createObjectAccessExpression(
                                ASTNodeFactory::objectAccessSourceId,
                                ASTNodeFactory::objectAccessTargetId
                        )
                )
        )},
        {219, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createSrefExpression(
                        new ASTArrayAccessExpressionNode(
                                ASTNodeFactory::idExpression,
                                ASTNodeFactory::arrayAccessInt
                        )
                )
        )},
        {220, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createSrefExpression(
                        ASTNodeFactory::createTupleAccessExpression(
                                ASTNodeFactory::objectAccessSourceId,
                                ASTNodeFactory::tupleAccess
                        )
                )
        )},
        {221, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createConcatExpression(
                        ASTNodeFactory::stringExpression,
                        ASTNodeFactory::stringExpression
                )
        )},
        {222, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createConcatExpression(
                    ASTNodeFactory::stringExpression,
                    ASTNodeFactory::createConcatExpression(
                        ASTNodeFactory::stringExpression,
                        ASTNodeFactory::stringExpression
                    )
                )
        )},
        {223, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createConcatExpression(
                        ASTNodeFactory::idExpression,
                        ASTNodeFactory::idExpression
                )
        )},
        {224, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createConcatExpression(
                    ASTNodeFactory::createArrayExpression(
                        {
                            ASTNodeFactory::intExpression,
                            ASTNodeFactory::intExpression,
                        }),
                    ASTNodeFactory::createArrayExpression(
                        {
                            ASTNodeFactory::intExpression,
                            ASTNodeFactory::intExpression,
                        })
                )
        )},
        {225, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTObjectAccessInvocationExpressionNode(
                    ASTNodeFactory::createObjectAccessExpression(
                        ASTNodeFactory::objectAccessSourceId,
                        ASTNodeFactory::objectAccessTargetCallableId
                     ),
                    ASTNodeFactory::createFunctionArgumentList({
                       new ASTFunctionArgumentNode(ASTNodeFactory::intExpression)
                    })
                )
        )},
        {226, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createStructExpression({
                   ASTNodeFactory::createStructKeyValue(
                           new ASTLambdaWithFatArrowExpressionNode(
                                   ASTNodeFactory::createFunctionParameterList(
                                           {
                                               ASTNodeFactory::createFunctionParameter(
                                                   ASTNodeFactory::idExpression,
                                                   ASTNodeFactory::intType
                                               )
                                           }
                                   ),
                                   new ASTLambdaReturnExpressionNode(
                                           ASTNodeFactory::lambdaFatArrow,
                                           new ASTBinaryExpressionNode(
                                                   ASTNodeFactory::idExpression,
                                                   ASTNodeFactory::plus,
                                                   ASTNodeFactory::intExpression
                                           )
                                   )
                           )
                   ),
                   ASTNodeFactory::createStructKeyValue(
                           new ASTLambdaWithFatArrowExpressionNode(
                                   ASTNodeFactory::createFunctionParameterList(),
                                   new ASTLambdaReturnExpressionNode(
                                           ASTNodeFactory::lambdaFatArrow,
                                           ASTNodeFactory::intExpression
                                   )
                           )
                   ),
                   ASTNodeFactory::createStructKeyValue(
                           new ASTLambdaExpressionNode(
                                   ASTNodeFactory::createFunctionParameterList({
                                       ASTNodeFactory::createFunctionParameter(
                                               ASTNodeFactory::idExpression,
                                               ASTNodeFactory::intType
                                       )
                                   }),
                                   ASTNodeFactory::createFunctionBlock({
                                       new ASTFunctionReturnExpressionNode(
                                           ASTNodeFactory::functionReturn,
                                           new ASTBinaryExpressionNode(
                                               ASTNodeFactory::idExpression,
                                               ASTNodeFactory::plus,
                                               ASTNodeFactory::intExpression
                                           )
                                       )
                                   }),
                                   ASTNodeFactory::intType
                           )
                   )
               })
        )},
        {227, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::createTupleExpression({
                   new ASTLambdaWithFatArrowExpressionNode(
                       ASTNodeFactory::createFunctionParameterList(
                               {
                                       ASTNodeFactory::createFunctionParameter(
                                               ASTNodeFactory::idExpression,
                                               ASTNodeFactory::intType
                                       )
                               }
                       ),
                       new ASTLambdaReturnExpressionNode(
                               ASTNodeFactory::lambdaFatArrow,
                               new ASTBinaryExpressionNode(
                                       ASTNodeFactory::idExpression,
                                       ASTNodeFactory::plus,
                                       ASTNodeFactory::intExpression
                               )
                       )
                   ),
                   new ASTLambdaWithFatArrowExpressionNode(
                       ASTNodeFactory::createFunctionParameterList(),
                       new ASTLambdaReturnExpressionNode(
                           ASTNodeFactory::lambdaFatArrow,
                           ASTNodeFactory::intExpression
                       )
                   ),
                   new ASTLambdaExpressionNode(
                       ASTNodeFactory::createFunctionParameterList({
                           ASTNodeFactory::createFunctionParameter(
                               ASTNodeFactory::idExpression,
                               ASTNodeFactory::intType
                           )
                       }),
                       ASTNodeFactory::createFunctionBlock({
                           new ASTFunctionReturnExpressionNode(
                               ASTNodeFactory::functionReturn,
                               new ASTBinaryExpressionNode(
                                   ASTNodeFactory::idExpression,
                                   ASTNodeFactory::plus,
                                   ASTNodeFactory::intExpression
                               )
                           )
                       }),
                       ASTNodeFactory::intType
                   )
           })
        )},

};

TEST_CASE( "should print the expected reduced nodes" ) {
std::string filePath = "./syntax-analyzer-test-file.jet";
auto tokenTable = new TokenTable();
auto reservedKeywords = new ReservedKeywords();
auto lexicalAnalyzer = new LexicalAnalyzer(tokenTable, reservedKeywords);
auto syntaxAnalyzer = SyntaxAnalyzer(tokenTable, lexicalAnalyzer);
auto fileScope = syntaxAnalyzer.analyze(filePath);
auto expectedModuleDeclaration = new ASTModuleDeclarationNode(ASTNodeFactory::moduleKeyword, ASTNodeFactory::moduleName);
auto expectedImportDeclarations = std::vector {
        new ASTImportSingleModuleDeclarationNode(
                ASTNodeFactory::importKeyword,
                ASTNodeFactory::importModuleName,
                ASTNodeFactory::fromKeyword,
                ASTNodeFactory::importPath
        )
};
Logger::log("===== TEST LOGS =====");
REQUIRE(fileScope->getModule().value()->isSameAs(expectedModuleDeclaration) == true);
REQUIRE(fileScope->getImports().size() == 1);
for (int i = 0; i < 1; i++) {
    auto importDeclaration = fileScope->getImports()[i];
    importDeclaration->print();
    auto result = importDeclaration->isSameAs(expectedImportDeclarations[i]);
    Logger::log("RESULT =", result);
    if (!result) {
        expectedImportDeclarations[i]->print();
    }
    REQUIRE(result == true);
}
REQUIRE(fileScope->getScope().size() == 227);
    for (int i = 0; i < 227; i++) {
        auto declaration = fileScope->getScope()[i];
        Logger::log("=====", i + 1, declaration->toString(), "=====");
        declaration->print();
        auto result = declaration->isSameAs(expectedNodes[i + 1]);
        Logger::log("RESULT =", result);
        if (!result) {
            expectedNodes[i + 1]->print();
        }
        REQUIRE(result == true);
        Logger::log("====================================");
    }
}
