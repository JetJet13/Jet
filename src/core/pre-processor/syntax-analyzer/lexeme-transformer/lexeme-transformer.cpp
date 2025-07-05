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
#include "../../../ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-binary-operator-node.h"
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
#include "../../../ast/ast-nodes/ast-array-nodes/ast-array-type-keyword-node.h"
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
#include "../../../ast/ast-nodes/ast-sref-node.h"
#include "../../../ast/ast-nodes/ast-concat-node.h"
#include "../../../ast/ast-nodes/ast-interface-nodes/ast-interface-node.h"
#include "../../../ast/ast-nodes/ast-interface-nodes/ast-implements-node.h"

std::optional<ASTNode*> LexemeTransformer::transform(std::optional<Lexeme*> lexeme) {
    if (lexeme) {
        return LexemeTransformer::transform(lexeme.value());
    }
    return {};
}

ASTNode* LexemeTransformer::transform(Lexeme* lexeme) {
    auto symbol = lexeme->getToken()->getSymbol();
    if (symbol->isIdentifier()) {
        return new ASTIdentifierNode(lexeme);
    } else if (symbol->isLet()) {
        return new ASTVariableTypeNode(lexeme);
    } else if (symbol->isConst()) {
        return new ASTConstNode(lexeme);
    } else if (symbol->isEqual()) {
        return new ASTAssignmentOperatorNode(lexeme);
    } else if (symbol->isInt()) {
        return new ASTIntLiteralNode(lexeme);
    } else if (symbol->isFloat()) {
        return new ASTFloatLiteralNode(lexeme);
    } else if (symbol->isChar()) {
        return new ASTCharLiteralNode(lexeme);
    } else if (symbol->isString()) {
        return new ASTStringLiteralNode(lexeme);
    } else if (symbol->isBoolean()) {
        return new ASTBooleanLiteralNode(lexeme);
    } else if (symbol->isPlus()) {
        return new ASTPlusBaseNode(lexeme);
    } else if (symbol->isMinus()) {
        return new ASTMinusBaseNode(lexeme);
    } else if (symbol->isStar()) {
        return new ASTStarBaseNode(lexeme);
    } else if (symbol->isEqualityOperator() ||
               symbol->isInequalityOperator() ||
               symbol->isGreaterThanOrEqual() ||
               symbol->isLessThanOrEqual() ||
               symbol->isSlash() ||
               symbol->isModulo()) {
        return new ASTBinaryOperatorNode(lexeme);
    } else if (symbol->isLogicalOperator()) {
        return new ASTLogicalOperatorNode(lexeme);
    } else if (symbol->isUnaryOperator()) {
        return new ASTUnaryOperatorNode(lexeme);
    } else if (symbol->isLeftParentheses()) {
        return new ASTGroupStartNode(lexeme);
    } else if (symbol->isRightParentheses()) {
        return new ASTGroupEndNode(lexeme);
    } else if (symbol->isSemicolon()) {
        return new ASTTerminatorNode(lexeme);
    } else if (symbol->isLeftBracket()) {
        return new ASTLeftBracketNode(lexeme);
    } else if (symbol->isRightBracket()) {
        return new ASTRightBracketNode(lexeme);
    } else if (symbol->isLeftBrace()) {
        return new ASTBlockStartNode(lexeme);
    } else if (symbol->isRightBrace()) {
        return new ASTBlockEndNode(lexeme);
    } else if (symbol->isComma()) {
        return new ASTCommaNode(lexeme);
    } else if (symbol->isColon()) {
        return new ASTColonBaseNode(lexeme);
    } else if (symbol->isPeriod()) {
        return new ASTPeriodNode(lexeme);
    }  else if (symbol->isFunction()) {
        return new ASTFunctionNode(lexeme);
    }  else if (symbol->isReturn()) {
        return new ASTFunctionReturnNode(lexeme);
    } else if (symbol->isProcedure()) {
        return new ASTProcedureNode(lexeme);
    } else if (symbol->isEnum()) {
        return new ASTEnumNode(lexeme);
    } else if (symbol->isTuple()) {
        return new ASTTupleNode(lexeme);
    } else if (symbol->isIf()) {
        return new ASTIfNode(lexeme);
    } else if (symbol->isElse()) {
        return new ASTElseNode(lexeme);
    } else if (symbol->isFor()) {
        return new ASTForNode(lexeme);
    } else if (symbol->isIn()) {
        return new ASTForInNode(lexeme);
    } else if (symbol->isWhile()) {
        return new ASTWhileNode(lexeme);
    } else if (symbol->isBreak()) {
        return new ASTBreakNode(lexeme);
    } else if (symbol->isSkip()) {
        return new ASTSkipNode(lexeme);
    } else if (symbol->isType()) {
        return ASTTypeNodeFactory::createPrimitiveTypeNode(lexeme);
    } else if (symbol->isTry()) {
        return new ASTTryNode(lexeme);
    } else if (symbol->isCatch()) {
        return new ASTCatchNode(lexeme);
    } else if (symbol->isFinally()) {
        return new ASTFinallyNode(lexeme);
    } else if (symbol->isFatArrow()) {
        return new ASTFatArrowBaseNode(lexeme);
    } else if (symbol->isLessThan()) {
        return new ASTLessThanBaseNode(lexeme);
    } else if (symbol->isGreaterThan()) {
        return new ASTGreaterThanBaseNode(lexeme);
    } else if (symbol->isArrayTypeKeyword()) {
        return new ASTArrayTypeKeywordNode(lexeme);
    } else if (symbol->isModule()) {
        return new ASTModuleNode(lexeme);
    } else if (symbol->isAsKeyword()) {
        return new ASTAsNode(lexeme);
    } else if (symbol->isDotDotDot()) {
        return new ASTDotDotDotBaseNode(lexeme);
    } else if (symbol->isImport()) {
        return new ASTImportNode(lexeme);
    } else if (symbol->isUseKeyword()) {
        return new ASTUseNode(lexeme);
    } else if (symbol->isFromKeyword()) {
        return new ASTFromNode(lexeme);
    } else if (symbol->isColonColon()) {
        return new ASTModuleAccessNode(lexeme);
    } else if (symbol->isClass()) {
        return new ASTClassNode(lexeme);
    } else if (symbol->isPublic()) {
        return new ASTPublicNode(lexeme);
    } else if (symbol->isProtected()) {
        return new ASTProtectedNode(lexeme);
    } else if (symbol->isPrivate()) {
        return new ASTPrivateNode(lexeme);
    } else if (symbol->isStatic()) {
        return new ASTStaticNode(lexeme);
    } else if (symbol->isConstructor()) {
        return new ASTConstructorNode(lexeme);
    } else if (symbol->isNew()) {
        return new ASTNewNode(lexeme);
    } else if (symbol->isExport()) {
        return new ASTExportNode(lexeme);
    } else if (symbol->isRef()) {
        return new ASTRefBaseNode(lexeme);
    } else if (symbol->isDref()) {
        return new ASTDrefNode(lexeme);
    } else if (symbol->isSref()) {
        return new ASTSrefNode(lexeme);
    } else if (symbol->isConcat()) {
        return new ASTConcatNode(lexeme);
    } else if (symbol->isInterface()) {
        return new ASTInterfaceNode(lexeme);
    } else if (symbol->isImplements()) {
        return new ASTImplementsNode(lexeme);
    } else if (symbol->isThis()) {
        return new ASTThisNode(lexeme);
    } else {
        Logger::log(lexeme->toString());
        throw std::invalid_argument("failed to transform lexeme...unknown symbol");
    }
}