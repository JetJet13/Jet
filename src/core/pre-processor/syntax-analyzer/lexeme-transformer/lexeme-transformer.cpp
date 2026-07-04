//
// Created by Johny Georges on 2024-02-17.
//

#include "lexeme-transformer.h"
#include "../../../ast/ast-nodes/ast-variable-nodes/ast-variable-type-node.h"
#include "../../../ast/ast-nodes/ast-operator-nodes/ast-assignment-operator-node.h"
#include "../../../ast/ast-nodes/ast-literal-nodes/ast-int-literal-node.h"
#include "../../../ast/ast-nodes/ast-literal-nodes/ast-float-literal-node.h"
#include "../../../ast/ast-nodes/ast-literal-nodes/ast-char-literal-node.h"
#include "../../../ast/ast-nodes/ast-literal-nodes/ast-string-literal-node.h"
#include "../../../ast/ast-nodes/ast-literal-nodes/ast-boolean-literal-node.h"
#include "../../../ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-binary-arithmetic-operator-node.h"
#include "../../../ast/ast-nodes/ast-operator-nodes/ast-logical-operators/ast-logical-operator-node.h"
#include "../../../ast/ast-nodes/ast-terminator-node.h"
#include "../../../ast/ast-nodes/ast-base-nodes/ast-plus-base-node.h"
#include "../../../ast/ast-nodes/ast-base-nodes/ast-minus-base-node.h"
#include "../../../ast/ast-nodes/ast-operator-nodes/ast-unary-operators/ast-unary-operator-node.h"
#include "../../../ast/ast-nodes/ast-group-nodes/ast-group-start-node.h"
#include "../../../ast/ast-nodes/ast-group-nodes/ast-group-end-node.h"
#include "../../../ast/ast-nodes/ast-array-nodes/ast-left-bracket-node.h"
#include "../../../ast/ast-nodes/ast-array-nodes/ast-right-bracket-node.h"
#include "../../../ast/ast-nodes/ast-comma-node.h"
#include "../../../ast/ast-nodes/ast-base-nodes/ast-colon-base-node.h"
#include "../../../ast/ast-nodes/ast-block-nodes/ast-block-end-node.h"
#include "../../../ast/ast-nodes/ast-block-nodes/ast-block-start-node.h"
#include "../../../ast/ast-nodes/ast-period-node.h"
#include "../../../ast/ast-nodes/ast-function-nodes/ast-function-return-node.h"
#include "../../../ast/ast-nodes/ast-function-nodes/ast-function-node.h"
#include "../../../ast/ast-nodes/ast-procedure-nodes/ast-procedure-node.h"
#include "../../../ast/ast-nodes/ast-enum-nodes/ast-enum-node.h"
#include "../../../ast/ast-nodes/ast-tuple-nodes/ast-tuple-node.h"
#include "../../../ast/ast-nodes/ast-control-flow-nodes/ast-if-node.h"
#include "../../../ast/ast-nodes/ast-control-flow-nodes/ast-else-node.h"
#include "../../../ast/ast-nodes/ast-control-flow-nodes/ast-while-node.h"
#include "../../../ast/ast-nodes/ast-control-flow-nodes/ast-for-in-node.h"
#include "../../../ast/ast-nodes/ast-control-flow-nodes/ast-for-node.h"
#include "../../../ast/ast-nodes/ast-control-flow-nodes/ast-break-node.h"
#include "../../../ast/ast-nodes/ast-control-flow-nodes/ast-skip-node.h"
#include "../../../ast/ast-nodes/ast-control-flow-nodes/try-catch-finally/ast-catch-node.h"
#include "../../../ast/ast-nodes/ast-control-flow-nodes/try-catch-finally/ast-try-node.h"
#include "../../../ast/ast-nodes/ast-control-flow-nodes/try-catch-finally/ast-finally-node.h"
#include "../../../ast/ast-nodes/ast-base-nodes/ast-fat-arrow-base-node.h"
#include "../../../ast/ast-nodes/ast-type-nodes/ast-type-node-factory.h"
#include "../../../ast/ast-nodes/ast-base-nodes/ast-less-than-base-node.h"
#include "../../../ast/ast-nodes/ast-base-nodes/ast-greater-than-base-node.h"
#include "../../../ast/ast-nodes/ast-base-nodes/ast-star-base-node.h"
#include "../../../ast/ast-nodes/ast-module-nodes/ast-module-node.h"
#include "../../../ast/ast-nodes/ast-module-nodes/ast-as-node.h"
#include "../../../ast/ast-nodes/ast-base-nodes/ast-dot-dot-dot-base-node.h"
#include "../../../ast/ast-nodes/ast-import-nodes/ast-import-node.h"
#include "../../../ast/ast-nodes/ast-import-nodes/ast-package-node/ast-use-node.h"
#include "../../../ast/ast-nodes/ast-import-nodes/ast-from-node.h"
#include "../../../ast/ast-nodes/ast-module-nodes/ast-module-access-node.h"
#include "../../../ast/ast-nodes/ast-class-nodes/ast-class-node.h"
#include "../../../ast/ast-nodes/ast-access-modifier-nodes/ast-public-node.h"
#include "../../../ast/ast-nodes/ast-access-modifier-nodes/ast-protected-node.h"
#include "../../../ast/ast-nodes/ast-access-modifier-nodes/ast-private-node.h"
#include "../../../ast/ast-nodes/ast-class-nodes/ast-static-node.h"
#include "../../../ast/ast-nodes/ast-class-nodes/ast-constructor-node.h"
#include "../../../ast/ast-nodes/ast-const-node.h"
#include "../../../ast/ast-nodes/ast-class-nodes/ast-new-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../../ast/ast-nodes/ast-export-node.h"
#include "../../../ast/ast-nodes/ast-base-nodes/ast-ref-base-node.h"
#include "../../../ast/ast-nodes/ast-dref-node.h"
#include "../../../ast/ast-nodes/ast-concat-node.h"
#include "../../../ast/ast-nodes/ast-interface-nodes/ast-interface-node.h"
#include "../../../ast/ast-nodes/ast-interface-nodes/ast-implements-node.h"
#include "../../../ast/ast-nodes/ast-type-nodes/ast-type-keyword-node.h"
#include "../../../ast/ast-nodes/ast-operator-nodes/ast-ref-value-assignment-operator-node.h"
#include "../../../ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-binary-comparator-operator-node.h"
#include "../../../ast/ast-nodes/ast-base-nodes/ast-colon-colon-base-node.h"

std::optional<std::shared_ptr<ASTNode>> LexemeTransformer::transform(std::optional<Lexeme*> lexeme) {
    if (lexeme) {
        return LexemeTransformer::transform(lexeme.value());
    }
    return {};
}

std::shared_ptr<ASTNode> LexemeTransformer::transform(Lexeme* lexeme) {
    auto symbol = lexeme->getToken()->getSymbol();
    if (symbol->isIdentifier()) {
        return std::make_shared<ASTIdentifierNode>(lexeme);
    } else if (symbol->isLet()) {
        return std::make_shared<ASTVariableTypeNode>(lexeme);
    } else if (symbol->isConst()) {
        return std::make_shared<ASTConstNode>(lexeme);
    } else if (symbol->isEqual()) {
        return std::make_shared<ASTAssignmentOperatorNode>(lexeme);
    } else if (symbol->isColonEqual()) {
        return std::make_shared<ASTRefValueAssignmentOperatorNode>(lexeme);
    } else if (symbol->isInt()) {
        return std::make_shared<ASTIntLiteralNode>(lexeme);
    } else if (symbol->isFloat()) {
        return std::make_shared<ASTFloatLiteralNode>(lexeme);
    } else if (symbol->isChar()) {
        return std::make_shared<ASTCharLiteralNode>(lexeme);
    } else if (symbol->isString()) {
        return std::make_shared<ASTStringLiteralNode>(lexeme);
    } else if (symbol->isBoolean()) {
        return std::make_shared<ASTBooleanLiteralNode>(lexeme);
    } else if (symbol->isPlus()) {
        return std::make_shared<ASTPlusBaseNode>(lexeme);
    } else if (symbol->isMinus()) {
        return std::make_shared<ASTMinusBaseNode>(lexeme);
    } else if (symbol->isStar()) {
        return std::make_shared<ASTStarBaseNode>(lexeme);
    } else if (symbol->isSlash() || symbol->isModulo()) {
        return std::make_shared<ASTBinaryArithmeticOperatorNode>(lexeme);
    } else if (symbol->isEqualityOperator() ||
               symbol->isInequalityOperator() ||
               symbol->isGreaterThanOrEqual() ||
               symbol->isLessThanOrEqual()) {
        return std::make_shared<ASTBinaryComparatorOperatorNode>(lexeme);
    } else if (symbol->isLogicalOperator()) {
        return std::make_shared<ASTLogicalOperatorNode>(lexeme);
    } else if (symbol->isUnaryOperator()) {
        return std::make_shared<ASTUnaryOperatorNode>(lexeme);
    } else if (symbol->isLeftParentheses()) {
        return std::make_shared<ASTGroupStartNode>(lexeme);
    } else if (symbol->isRightParentheses()) {
        return std::make_shared<ASTGroupEndNode>(lexeme);
    } else if (symbol->isSemicolon()) {
        return std::make_shared<ASTTerminatorNode>(lexeme);
    } else if (symbol->isLeftBracket()) {
        return std::make_shared<ASTLeftBracketNode>(lexeme);
    } else if (symbol->isRightBracket()) {
        return std::make_shared<ASTRightBracketNode>(lexeme);
    } else if (symbol->isLeftBrace()) {
        return std::make_shared<ASTBlockStartNode>(lexeme);
    } else if (symbol->isRightBrace()) {
        return std::make_shared<ASTBlockEndNode>(lexeme);
    } else if (symbol->isComma()) {
        return std::make_shared<ASTCommaNode>(lexeme);
    } else if (symbol->isColon()) {
        return std::make_shared<ASTColonBaseNode>(lexeme);
    } else if (symbol->isPeriod()) {
        return std::make_shared<ASTPeriodNode>(lexeme);
    }  else if (symbol->isFunction()) {
        return std::make_shared<ASTFunctionNode>(lexeme);
    }  else if (symbol->isReturn()) {
        return std::make_shared<ASTFunctionReturnNode>(lexeme);
    } else if (symbol->isProcedure()) {
        return std::make_shared<ASTProcedureNode>(lexeme);
    } else if (symbol->isEnum()) {
        return std::make_shared<ASTEnumNode>(lexeme);
    } else if (symbol->isTuple()) {
        return std::make_shared<ASTTupleNode>(lexeme);
    } else if (symbol->isIf()) {
        return std::make_shared<ASTIfNode>(lexeme);
    } else if (symbol->isElse()) {
        return std::make_shared<ASTElseNode>(lexeme);
    } else if (symbol->isFor()) {
        return std::make_shared<ASTForNode>(lexeme);
    } else if (symbol->isIn()) {
        return std::make_shared<ASTForInNode>(lexeme);
    } else if (symbol->isWhile()) {
        return std::make_shared<ASTWhileNode>(lexeme);
    } else if (symbol->isBreak()) {
        return std::make_shared<ASTBreakNode>(lexeme);
    } else if (symbol->isSkip()) {
        return std::make_shared<ASTSkipNode>(lexeme);
    } else if (symbol->isType()) {
        return ASTTypeNodeFactory::createPrimitiveTypeNode(lexeme);
    } else if (symbol->isTry()) {
        return std::make_shared<ASTTryNode>(lexeme);
    } else if (symbol->isCatch()) {
        return std::make_shared<ASTCatchNode>(lexeme);
    } else if (symbol->isFinally()) {
        return std::make_shared<ASTFinallyNode>(lexeme);
    } else if (symbol->isFatArrow()) {
        return std::make_shared<ASTFatArrowBaseNode>(lexeme);
    } else if (symbol->isLessThan()) {
        return std::make_shared<ASTLessThanBaseNode>(lexeme);
    } else if (symbol->isGreaterThan()) {
        return std::make_shared<ASTGreaterThanBaseNode>(lexeme);
    } else if (symbol->isModule()) {
        return std::make_shared<ASTModuleNode>(lexeme);
    } else if (symbol->isAsKeyword()) {
        return std::make_shared<ASTAsNode>(lexeme);
    } else if (symbol->isDotDotDot()) {
        return std::make_shared<ASTDotDotDotBaseNode>(lexeme);
    } else if (symbol->isImport()) {
        return std::make_shared<ASTImportNode>(lexeme);
    } else if (symbol->isUseKeyword()) {
        return std::make_shared<ASTUseNode>(lexeme);
    } else if (symbol->isFromKeyword()) {
        return std::make_shared<ASTFromNode>(lexeme);
    } else if (symbol->isColonColon()) {
        return std::make_shared<ASTColonColonBaseNode>(lexeme);
    } else if (symbol->isClass()) {
        return std::make_shared<ASTClassNode>(lexeme);
    } else if (symbol->isPublic()) {
        return std::make_shared<ASTPublicNode>(lexeme);
    } else if (symbol->isProtected()) {
        return std::make_shared<ASTProtectedNode>(lexeme);
    } else if (symbol->isPrivate()) {
        return std::make_shared<ASTPrivateNode>(lexeme);
    } else if (symbol->isStatic()) {
        return std::make_shared<ASTStaticNode>(lexeme);
    } else if (symbol->isConstructor()) {
        return std::make_shared<ASTConstructorNode>(lexeme);
    } else if (symbol->isNew()) {
        return std::make_shared<ASTNewNode>(lexeme);
    } else if (symbol->isExport()) {
        return std::make_shared<ASTExportNode>(lexeme);
    } else if (symbol->isRef()) {
        return std::make_shared<ASTRefBaseNode>(lexeme);
    } else if (symbol->isDref()) {
        return std::make_shared<ASTDrefNode>(lexeme);
    } else if (symbol->isConcat()) {
        return std::make_shared<ASTConcatNode>(lexeme);
    } else if (symbol->isInterface()) {
        return std::make_shared<ASTInterfaceNode>(lexeme);
    } else if (symbol->isImplements()) {
        return std::make_shared<ASTImplementsNode>(lexeme);
    } else if (symbol->isTypeKeyword()) {
        return std::make_shared<ASTTypeKeywordNode>(lexeme);
    } else if (symbol->isVoid()) {
        return ASTTypeNodeFactory::createVoidTypeNode(std::make_shared<ASTVoidNode>(lexeme));
    } else if (symbol->isThis()) {
        return std::make_shared<ASTThisNode>(lexeme);
    } else {
        Logger::log(lexeme->toString());
        throw std::invalid_argument("failed to transform lexeme...unknown symbol");
    }
}