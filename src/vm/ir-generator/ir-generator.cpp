//
// Created by Johny Georges on 2024-06-11.
//

#include "ir-generator.h"
#include "../../core/ast/ast-nodes/ast-node-utils/ast-node-utils.h"
#include "../../core/ast/ast-nodes/ast-statement-nodes/ast-while-statement-node.h"
#include "ir-strategies/literal-ir-strategies/int-literal-ir-strategy/int-literal-ir-strategy.h"
#include "ir-strategies/literal-ir-strategies/float-literal-ir-strategy/float-literal-ir-strategy.h"
#include "ir-strategies/literal-ir-strategies/char-literal-ir-strategy/char-literal-ir-strategy.h"
#include "ir-strategies/literal-ir-strategies/string-literal-ir-strategy/string-literal-ir-strategy.h"
#include "ir-strategies/literal-ir-strategies/bool-literal-ir-strategy/bool-literal-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/literal-expression-ir-strategy/literal-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/binary-expression-ir-strategy/binary-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/concat-expression-ir-strategy/concat-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/logical-expression-ir-strategy/logical-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/array-expression-ir-strategy/array-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/array-access-expression-ir-strategy/array-access-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/array-access-invocation-expression-ir-strategy/array-access-invocation-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/struct-expression-ir-strategy/struct-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/unary-expression-ir-strategy/unary-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/tuple-expression-ir-strategy/tuple-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/identifier-expression-ir-strategy/identifier-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/object-access-expression-ir-strategy/object-access-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/object-access-invocation-expression-ir-strategy/object-access-invocation-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/tuple-access-expression-ir-strategy/tuple-access-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/tuple-access-invocation-expression-ir-strategy/tuple-access-invocation-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/function-invocation-expression-ir-strategy/function-invocation-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/lambda-expression-ir-strategy/lambda-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/class-property-access-expression-ir-strategy/class-property-access-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/class-method-invocation-expression-ir-strategy/class-method-invocation-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/new-class-instance-expression-ir-strategy/new-class-instance-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/ref-expression-ir-strategy/ref-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/dref-expression-ir-strategy/dref-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/sref-expression-ir-strategy/sref-expression-ir-strategy.h"
#include "ir-strategies/expression-statement-ir-strategy/expression-statement-ir-strategy.h"
#include "ir-strategies/print-statement-ir-strategy/print-statement-ir-strategy.h"
#include "ir-strategies/class-property-assignment-statement-ir-strategy/class-property-assignment-statement-ir-strategy.h"
#include "ir-strategies/class-property-ref-value-assignment-statement-ir-strategy/class-property-ref-value-assignment-statement-ir-strategy.h"
#include "ir-strategies/ref-value-assignment-statement-ir-strategy/ref-value-assignment-statement-ir-strategy.h"
#include "ir-strategies/variable-assignment-statement-ir-strategy/variable-assignment-statement-ir-strategy.h"
#include "ir-strategies/array-access-assignment-statement-ir-strategy/array-access-assignment-statement-ir-strategy.h"
#include "ir-strategies/object-access-assignment-statement-ir-strategy/object-access-assignment-statement-ir-strategy.h"
#include "ir-strategies/tuple-access-assignment-statement-ir-strategy/tuple-access-assignment-statement-ir-strategy.h"
#include "ir-strategies/if-statement-ir-strategy/if-statement-ir-strategy.h"
#include "ir-strategies/while-statement-ir-strategy/while-statement-ir-strategy.h"
#include "ir-strategies/for-in-statement-ir-strategy/for-in-statement-ir-strategy.h"
#include "ir-strategies/variable-declaration-ir-strategy/variable-declaration-ir-strategy.h"
#include "ir-strategies/function-declaration-ir-strategy/function-declaration-ir-strategy.h"
#include "ir-strategies/function-parameter-list-ir-strategy/function-parameter-list-ir-strategy.h"
#include "ir-strategies/function-return-expression-ir-strategy/function-return-expression-ir-strategy.h"
#include "ir-strategies/procedure-declaration-ir-strategy/procedure-declaration-ir-strategy.h"
#include "ir-strategies/enum-declaration-ir-strategy/enum-declaration-ir-strategy.h"
#include "ir-strategies/interface-type-declaration-ir-strategy/interface-type-declaration-ir-strategy.h"
#include "ir-strategies/custom-type-declaration-ir-strategy/custom-type-declaration-ir-strategy.h"
#include "ir-strategies/module-declaration-ir-strategy/module-declaration-ir-strategy.h"
#include "ir-strategies/import-single-module-declaration-ir-strategy/import-single-module-declaration-ir-strategy.h"
#include "ir-strategies/class-declaration-ir-strategy/class-declaration-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/array-type-signature-ir-strategy/array-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/literal-type-signature-ir-strategy/literal-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/class-type-signature-ir-strategy/class-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/enum-type-signature-ir-strategy/enum-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/interface-type-signature-ir-strategy/interface-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/invocable-type-signature-ir-strategies/function-type-signature-ir-strategy/function-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/invocable-type-signature-ir-strategies/lambda-type-signature-ir-strategy/lambda-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/invocable-type-signature-ir-strategies/procedure-type-signature-ir-strategy/procedure-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/parameter-list-type-signature-ir-strategy/parameter-list-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/parameter-list-type-signature-ir-strategy/parameter-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/struct-type-signature-ir-strategy/struct-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/tuple-type-signature-ir-strategy/tuple-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/enum-access-type-signature-ir-strategy/enum-access-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/module-type-signature-ir-strategy/module-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/pointer-type-signature-ir-strategy/pointer-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/ref-type-signature-ir-strategy/ref-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/function-invocation-type-signature-ir-strategy/function-invocation-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/class-method-type-signature-ir-strategy/class-method-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/class-property-type-signature-ir-strategy/class-property-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/new-class-instance-type-signature-ir-strategy/new-class-instance-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/class-instance-type-signature-ir-strategy/class-instance-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/lambda-scope-type-signature-ir-strategy/lambda-scope-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/void-type-signature-ir-strategy/void-type-signature-ir-strategy.h"
#include "ir-util-functions/array-access-ir-function/array-access-ir-function.h"
#include "ir-util-functions/copy-string-ir-function/copy-string-ir-function.h"
#include "ir-util-functions/print-ir-function/print-ir-function.h"
#include "ir-internal-modules/ir-util-internal-module/ir-util-internal-module.h"
#include "../../shared/utils/logger/logger.h"
#include "ir-util-functions/malloc-ir-function/malloc-ir-function.h"
#include "ir-util-functions/malloc-free-ir-function/malloc-free-ir-function.h"
#include "ir-util-functions/malloc-size-ir-function/malloc-size-ir-function.h"
#include "ir-util-functions/copy-array-ir-function/copy-array-ir-function.h"
#include "ir-util-functions/memcpy-ir-function/memcpy-ir-function.h"
#include "ir-util-functions/copy-struct-ir-function/copy-struct-ir-function.h"
#include "ir-util-functions/copy-value-ir-function/copy-value-ir-function.h"
#include "ir-util-functions/copy-pointer-ir-function/copy-pointer-ir-function.h"
#include "ir-util-functions/free-value-ir-function/free-value-ir-function.h"
#include "ir-util-functions/free-array-ir-function/free-array-ir-function.h"
#include "ir-util-functions/free-pointer-ir-function/free-pointer-ir-function.h"
#include "ir-util-functions/free-struct-ir-function/free-struct-ir-function.h"
#include "ir-util-functions/free-string-ir-function/free-string-ir-function.h"
#include "ir-util-functions/copy-ref-ir-function/copy-ref-ir-function.h"
#include "ir-util-functions/free-ref-ir-function/free-ref-ir-function.h"
#include "ir-util-functions/setup-sref-ir-function/setup-sref-ir-function.h"
#include "ir-util-functions/setup-ref-ir-function/setup-ref-ir-function.h"
#include "ir-util-functions/range-ir-function/range-ir-function.h"
#include "ir-util-functions/array-concat-ir-function/array-concat-ir-function.h"
#include "ir-util-functions/array-head-ir-function/array-head-ir-function.h"
#include "ir-util-functions/array-last-ir-function/array-last-ir-function.h"
#include "ir-util-functions/array-drop-ir-function/array-drop-ir-function.h"
#include "ir-util-functions/array-drop-last-ir-function/array-drop-last-ir-function.h"
#include "ir-util-functions/array-tail-ir-function/array-tail-ir-function.h"
#include "ir-util-functions/array-append-ir-function/array-append-ir-function.h"
#include "ir-util-functions/array-prepend-ir-function/array-prepend-ir-function.h"
#include "ir-util-functions/array-take-ir-function/array-take-ir-function.h"
#include "ir-util-functions/array-take-last-ir-function/array-take-last-ir-function.h"
#include "ir-prototypes/ir-array-prototype-map.h"
#include "ir-util-functions/array-size-ir-function/array-size-ir-function.h"
#include "ir-util-functions/array-empty-ir-function/array-empty-ir-function.h"
#include "ir-util-functions/equal-value-ir-function/equal-value-ir-function.h"
#include "ir-util-functions/equal-ref-ir-function/equal-ref-ir-function.h"
#include "ir-util-functions/equal-struct-ir-function/equal-struct-ir-function.h"
#include "ir-util-functions/equal-array-ir-function/equal-array-ir-function.h"
#include "ir-util-functions/equal-string-ir-function/equal-string-ir-function.h"
#include "ir-prototypes/ir-ref-prototype-map.h"
#include "ir-util-functions/ref-of-ir-function/ref-of-ir-function.h"
#include "ir-util-functions/sref-with-ir-function/sref-with-ir-function.h"
#include "ir-util-functions/same-ref-as-ir-function/same-ref-as-ir-function.h"
#include "ir-util-functions/free-captured-variable-ir-function/free-captured-variable-ir-function.h"
#include "ir-util-functions/increment-ref-count-ir-function/increment-ref-count-ir-function.h"
#include "ir-util-functions/copy-lambda-ir-function/copy-lambda-ir-function.h"
#include "ir-util-functions/free-lambda-ir-function/free-lambda-ir-function.h"
#include "ir-util-functions/get-ref-count-ir-function/get-ref-count-ir-function.h"
#include "ir-util-functions/setup-ref-for-struct-ir-function/setup-ref-for-struct-ir-function.h"
#include "ir-util-functions/copy-struct-ref-ir-function/copy-struct-ref-ir-function.h"
#include "ir-util-functions/free-struct-ref-ir-function/free-struct-ref-ir-function.h"
#include "ir-util-functions/equal-struct-ref-ir-function/equal-struct-ref-ir-function.h"
#include "ir-util-functions/increment-lambda-ref-count-ir-function/increment-lambda-ref-count-ir-function.h"
#include "ir-util-functions/free-invocable-ir-function/free-invocable-ir-function.h"
#include "ir-util-functions/string-concat-ir-function/string-concat-ir-function.h"
#include "ir-internal-modules/ir-debug-internal-module/ir-debug-internal-module.h"
#include "ir-internal-modules/ir-core-internal-module/ir-core-internal-module.h"
#include "ir-util-functions/equal-lambda-ir-function/equal-lambda-ir-function.h"
#include "ir-util-functions/increment-ref-count-if-necessary-ir-function/increment-ref-count-if-necessary-ir-function.h"
#include "ir-util-functions/set-ref-value-ir-function/set-ref-value-ir-function.h"
#include "ir-util-functions/free-ref-value-ir-function/free-ref-value-ir-function.h"


// The IRGenerator will be responsible for programmatically generating
// vm code.
// we need to figure out how to generate vm code for an ASTNode and its
// type signature.
IRGenerator::IRGenerator(IRInjector* irInjector) {
    _context = std::make_unique<llvm::LLVMContext>();
    _irStrategyMap = IRStrategyMap();
    _irInjector = irInjector;
    _arrayPointerType = llvm::StructType::create(*_context, {
            this->generateIntType(),
            this->generateIntType(),
            this->generatePointerType()
    }, "ArrayPointer");
    _structRefType = llvm::StructType::create(*_context, {
            this->generatePointerType(),
            this->generatePointerType(),
    }, "StructRef");
    _typeValueType = llvm::StructType::create(*_context, {
            this->generateIntType(),
            this->generateIntType(),
            this->generateIntType(),
            this->generatePointerType(),
            this->generatePointerType(),
            this->generatePointerType(),
    }, "TypeValueType");
    _refType = llvm::StructType::create(*_context, {
            this->generatePointerType(),
            this->generatePointerType()
    }, "Ref");
    _invocableType = llvm::StructType::create(*_context, {
            this->generatePointerType(),
            this->generatePointerType(),
            this->generatePointerType(),
            this->generatePointerType()
    }, "Invocable");
    _genericClassInstanceIRType = new IRClassInstanceType(
        new IRClassType(
            "generic_class",
            this->generateIRStructType()
        ),
        this->generateIRStructRefType()
    );
}

IRNode* IRGenerator::generateFor(ASTNode* node, IRLookupTable* scope, IRContext* irContext) {
    if (ASTNodeUtils::isTypeDeclarationNode(node)) {
        return this->generateFor((ASTTypeDeclarationNode*)node, scope, irContext);
    } else if (ASTNodeUtils::isDeclarationNode(node)) {
        return this->generateFor((ASTDeclarationNode*)node, scope, irContext);
    } else if (ASTNodeUtils::isStatementNode(node)) {
        return this->generateFor((ASTStatementNode*)node, scope, irContext);
    }
    throw std::logic_error("unable to generate llvm value for node " + node->toString());
}

IRStatementNode* IRGenerator::generateFor(ASTStatementNode* node, IRLookupTable* scope, IRContext* irContext) {
    if (node->is(AST_FUNCTION_RETURN_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getFunctionReturnExpressionIRStrategy()->generate((ASTFunctionReturnExpressionNode*)node,  this, scope, irContext);
    } else if (node->is(AST_EXPRESSION_STATEMENT_NODE)) {
        return this->_irStrategyMap.getExpressionStatementIRStrategy()->generate((ASTExpressionStatementNode*)node,  this, scope, irContext);
    } else if (node->is(AST_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_NODE)) {
        return this->_irStrategyMap.getClassPropertyAssignmentStatementIRStrategy()->generate((ASTClassPropertyAssignmentStatementNode*)node,  this, scope, irContext);
    } else if (node->is(AST_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_STATEMENT_NODE)) {
        return this->_irStrategyMap.getClassPropertyRefValueAssignmentStatementIRStrategy()->generate((ASTClassPropertyRefValueAssignmentStatementNode*)node,  this, scope, irContext);
    } else if (node->is(AST_REF_VALUE_ASSIGNMENT_STATEMENT_NODE)) {
        return this->_irStrategyMap.getRefValueAssignmentStatementIRStrategy()->generate((ASTRefValueAssignmentStatementNode*)node,  this, scope, irContext);
    } else if (node->is(AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE)) {
        return this->_irStrategyMap.getVariableAssignmentStatementIRStrategy()->generate((ASTVariableAssignmentStatementNode*)node,  this, scope, irContext);
    } else if (node->is(AST_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_NODE)) {
        return this->_irStrategyMap.getArrayAccessAssignmentStatementIRStrategy()->generate((ASTArrayAccessAssignmentStatementNode*)node,  this, scope, irContext);
    } else if (node->is(AST_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_NODE)) {
        return this->_irStrategyMap.getObjectAccessAssignmentStatementIRStrategy()->generate((ASTObjectAccessAssignmentStatementNode*)node,  this, scope, irContext);
    } else if (node->is(AST_TUPLE_ACCESS_ASSIGNMENT_STATEMENT_NODE)) {
        return this->_irStrategyMap.getTupleAccessAssignmentStatementIRStrategy()->generate((ASTTupleAccessAssignmentStatementNode*)node,  this, scope, irContext);
    } else if (node->is(AST_IF_STATEMENT_NODE)) {
        return this->_irStrategyMap.getIfStatementIRStrategy()->generate((ASTIfStatementNode*)node,  this, scope, irContext);
    } else if (node->is(AST_WHILE_STATEMENT_NODE)) {
        return this->_irStrategyMap.getWhileStatementIRStrategy()->generate((ASTWhileStatementNode*)node,  this, scope, irContext);
    } else if (node->is(AST_FOR_IN_STATEMENT_NODE)) {
        return this->_irStrategyMap.getForInStatementIRStrategy()->generate((ASTForInStatementNode*)node,  this, scope, irContext);
    } else if (node->is(AST_PRINT_STATEMENT_NODE)) {
        return this->_irStrategyMap.getPrintStatementIRStrategy()->generate((ASTPrintStatementNode*)node,  this, scope, irContext);
    }
    throw std::logic_error("unable to generate llvm value for statement " + node->toString());
}

IRDeclarationNode* IRGenerator::generateFor(ASTDeclarationNode* node, IRLookupTable* scope, IRContext* irContext) {
    if (node->is(AST_VARIABLE_DECLARATION_NODE)) {
        return this->_irStrategyMap.getVariableDeclarationIRStrategy()->generate((ASTVariableDeclarationNode*)node,  this, scope, irContext);
    } else if (node->is(AST_FUNCTION_DECLARATION_NODE)) {
        return this->_irStrategyMap.getFunctionDeclarationIRStrategy()->generate((ASTFunctionDeclarationNode*)node,  this, scope, irContext);
    } else if (node->is(AST_PROCEDURE_DECLARATION_NODE)) {
        return this->_irStrategyMap.getProcedureDeclarationIRStrategy()->generate((ASTProcedureDeclarationNode*)node,  this, scope, irContext);
    } else if (node->is(AST_ENUM_DECLARATION_NODE)) {
        return this->_irStrategyMap.getEnumDeclarationIRStrategy()->generate((ASTEnumDeclarationNode*)node,  this, scope, irContext);
    } else if (node->is(AST_MODULE_DECLARATION_NODE)) {
        return this->_irStrategyMap.getModuleDeclarationIRStrategy()->generate((ASTModuleDeclarationNode*)node,  this, scope, irContext);
    } else if (node->is(AST_IMPORT_SINGLE_MODULE_DECLARATION_NODE)) {
        return this->_irStrategyMap.getImportSingleModuleDeclarationIRStrategy()->generate((ASTImportSingleModuleDeclarationNode*)node,  this, scope, irContext);
    } else if (node->is(AST_CLASS_DECLARATION_NODE)) {
        return this->_irStrategyMap.getClassDeclarationIRStrategy()->generate((ASTClassDeclarationNode*)node,  this, scope, irContext);
    }
    throw std::logic_error("unable to generate llvm value for declaration " + node->toString());
}

IRTypeDeclarationNode* IRGenerator::generateFor(ASTTypeDeclarationNode* node, IRLookupTable* scope, IRContext* irContext) {
    if (node->is(AST_INTERFACE_TYPE_DECLARATION_NODE)) {
        return this->_irStrategyMap.getInterfaceTypeDeclarationIRStrategy()->generate((ASTInterfaceTypeDeclarationNode*)node,  this, scope, irContext);
    } else if (node->is(AST_CUSTOM_TYPE_DECLARATION_NODE)) {
        return this->_irStrategyMap.getCustomTypeDeclarationIRStrategy()->generate((ASTCustomTypeDeclarationNode*)node,  this, scope, irContext);
    }
    throw std::logic_error("unable to generate llvm value for type declaration " + node->toString());
}

IRFunctionParameterListNode* IRGenerator::generateFor(ASTFunctionParameterListNode* node, IRLookupTable* scope, IRContext* irContext, llvm::Function* irFunction) {
    return this->_irStrategyMap.getFunctionParameterListIRStrategy()->generate(node,  this, scope, irContext, irFunction);
}

IRExpressionNode* IRGenerator::generateFor(ASTExpressionNode* node, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    if (node->is(AST_LITERAL_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getLiteralExpressionIRStrategy()->generate((ASTLiteralExpressionNode*)node,  this, scope, irContext, irOperation);
    } else if (node->is(AST_BINARY_ARITHMETIC_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getBinaryExpressionIRStrategy()->generate((ASTBinaryArithmeticExpressionNode*)node, this, scope, irContext, irOperation);
    } else if (node->is(AST_BINARY_COMPARATOR_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getBinaryExpressionIRStrategy()->generate((ASTBinaryComparatorExpressionNode*)node, this, scope, irContext, irOperation);
    } else if (node->is(AST_CONCAT_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getConcatExpressionIRStrategy()->generate((ASTConcatExpressionNode*)node,  this, scope, irContext, irOperation);
    } else if (node->is(AST_LOGICAL_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getLogicalExpressionIRStrategy()->generate((ASTLogicalExpressionNode*)node,  this, scope, irContext, irOperation);
    } else if (node->is(AST_ARRAY_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getArrayExpressionIRStrategy()->generate((ASTArrayExpressionNode*)node,  this, scope, irContext, irOperation);
    } else if (node->is(AST_ARRAY_ACCESS_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getArrayAccessExpressionIRStrategy()->generate((ASTArrayAccessExpressionNode*)node,  this, scope, irContext, irOperation);
    } else if (node->is(AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getArrayAccessInvocationExpressionIRStrategy()->generate((ASTArrayAccessInvocationExpressionNode*)node,  this, scope, irContext, irOperation);
    } else if (node->is(AST_STRUCT_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getStructExpressionIRStrategy()->generate((ASTStructExpressionNode*)node,  this, scope, irContext, irOperation);
    } else if (node->is(AST_UNARY_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getUnaryExpressionIRStrategy()->generate((ASTUnaryExpressionNode*)node,  this, scope, irContext, irOperation);
    } else if (node->is(AST_TUPLE_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getTupleExpressionIRStrategy()->generate((ASTTupleExpressionNode*) node,  this, scope, irContext, irOperation);
    } else if (node->is(AST_IDENTIFIER_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getIdentifierExpressionIRStrategy()->generate((ASTIdentifierExpressionNode*)node,  this, scope, irContext, irOperation);
    } else if (node->is(AST_OBJECT_ACCESS_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getObjectAccessExpressionIRStrategy()->generate((ASTObjectAccessExpressionNode*)node,  this, scope, irContext, irOperation);
    } else if (node->is(AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getObjectAccessInvocationExpressionIRStrategy()->generate((ASTObjectAccessInvocationExpressionNode*)node, this, scope, irContext, irOperation);
    } else if (node->is(AST_TUPLE_ACCESS_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getTupleAccessExpressionIRStrategy()->generate((ASTTupleAccessExpressionNode*)node,  this, scope, irContext, irOperation);
    } else if (node->is(AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getTupleAccessInvocationExpressionIRStrategy()->generate((ASTTupleAccessInvocationExpressionNode*)node,  this, scope, irContext, irOperation);
    } else if (node->is(AST_FUNCTION_INVOCATION_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getFunctionInvocationExpressionIRStrategy()->generate((ASTFunctionInvocationExpressionNode*)node,  this, scope, irContext, irOperation);
    } else if (node->is(AST_LAMBDA_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getLambdaExpressionIRStrategy()->generate((ASTLambdaExpressionNode*)node,  this, scope, irContext);
    } else if (node->is(AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getLambdaExpressionIRStrategy()->generate((ASTLambdaWithFatArrowExpressionNode*)node,  this, scope, irContext);
    } else if (node->is(AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getClassPropertyAccessExpressionIRStrategy()->generate((ASTClassPropertyAccessExpressionNode*)node,  this, scope, irContext, irOperation);
    } else if (node->is(AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getClassMethodInvocationExpressionIRStrategy()->generate((ASTClassMethodInvocationExpressionNode*)node,  this, scope, irContext, irOperation);
    } else if (node->is(AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getNewClassInstanceExpressionIRStrategy()->generate((ASTNewClassInstanceExpressionNode*)node,  this, scope, irContext, irOperation);
    } else if (node->is(AST_REF_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getRefExpressionIRStrategy()->generate((ASTRefExpressionNode*)node,  this, scope, irContext, irOperation);
    } else if (node->is(AST_DREF_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getDrefExpressionIRStrategy()->generate((ASTDrefExpressionNode*)node,  this, scope, irContext, irOperation);
    } else if (node->is(AST_SREF_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getSrefExpressionIRStrategy()->generate((ASTSrefExpressionNode*)node,  this, scope, irContext, irOperation);
    }
    throw std::logic_error("unable to generate llvm value for expression " + node->toString());
}

IRFunctionArgumentNode* IRGenerator::generateFor(ASTFunctionArgumentNode* node, unsigned long index, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation, InvocableTypeSignature* invocableTypeSignature) {
    auto irExpression = this->generateFor(node->getArgument(), scope, irContext, irOperation);
    auto operation = invocableTypeSignature->isArgumentVarArg(index)
                     || invocableTypeSignature->getParameterTypes()->at(index)->isGeneric()
                     || invocableTypeSignature->isPrototype()
                    ? new IROperation(IR_OPERAND_POINTER_OP)
                    : new IROperation(IR_FUNCTION_ARGUMENT_OP);
    return new IRFunctionArgumentNode(irExpression, operation);
}

IRLiteralNode* IRGenerator::generateFor(ASTLiteralNode* node, IRLookupTable* scope, IRContext* irContext) {
    switch (node->getNodeType()) {
        case AST_INT_LITERAL_NODE:
            return _irStrategyMap.getIntLiteralIRStrategy()->generate((ASTIntLiteralNode*) node, irContext);
        case AST_FLOAT_LITERAL_NODE:
            return _irStrategyMap.getFloatLiteralIRStrategy()->generate((ASTFloatLiteralNode*) node, this, irContext);
        case AST_CHAR_LITERAL_NODE:
            return _irStrategyMap.getCharLiteralIRStrategy()->generate((ASTCharLiteralNode*) node, this, irContext);
        case AST_STRING_LITERAL_NODE:
            return _irStrategyMap.getStringLiteralIRStrategy()->generate((ASTStringLiteralNode*) node, this, irContext);
        case AST_BOOLEAN_LITERAL_NODE:
            return _irStrategyMap.getBoolLiteralIRStrategy()->generate((ASTBooleanLiteralNode*) node, irContext);
        default:
            throw std::logic_error("unknown literal node");
    }
}

void IRGenerator::generateInitialTypeFor(ASTNode* node, IRLookupTable* scope, IRContext* irContext) {
    if (node->is(AST_CLASS_DECLARATION_NODE)) {
        this->generateInitialTypeFor(node->getTypeSignature(), scope, irContext);
    }
}

void IRGenerator::generatePostInitialTypeFor(ASTNode* node, IRLookupTable* scope, IRContext* irContext) {
    if (node->is(AST_CLASS_DECLARATION_NODE)) {
        auto irClassType = this->generatePostInitialTypeFor(node->getTypeSignature(), scope, irContext);
    }
}

IRClassInstanceType* IRGenerator::getGenericClassInstanceIRType() {
    return _genericClassInstanceIRType;
}

IRType* IRGenerator::generateInitialTypeFor(TypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext) {
    switch (typeSignature->getTypeSource()) {
        case CLASS_TYPE_SOURCE:
            return this->_irStrategyMap.getClassTypeSignatureIRStrategy()->generateInitial((ClassTypeSignature*)typeSignature, this, scope, irContext);
        default:
            return this->generateTypeFor(typeSignature, scope, irContext);
    }
}

IRType* IRGenerator::generatePostInitialTypeFor(TypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext) {
    switch (typeSignature->getTypeSource()) {
        case CLASS_TYPE_SOURCE:
            return this->_irStrategyMap.getClassTypeSignatureIRStrategy()->generatePostInitial((ClassTypeSignature*)typeSignature, this, scope, irContext);
        default:
            return this->generateTypeFor(typeSignature, scope, irContext);
    }
}

IRType* IRGenerator::generateTypeFor(llvm::Constant* constant) {
    return new IRType(constant->getType());
}

IRType* IRGenerator::generateTypeFor(TypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext) {
    auto existingIRType = scope->findType(typeSignature->getId());
    if (existingIRType) {
        return existingIRType.value();
    }
    switch (typeSignature->getTypeSource()) {
        case VOID_TYPE_SOURCE:
            return _irStrategyMap.getVoidTypeSignatureIRStrategy()->generate(this);
        case ARRAY_TYPE_SOURCE:
            return _irStrategyMap.getArrayTypeSignatureIRStrategy()->generate((ArrayTypeSignature*) typeSignature,
                                                                              this, scope, irContext);
        case CLASS_TYPE_SOURCE:
            return _irStrategyMap.getClassTypeSignatureIRStrategy()->generate((ClassTypeSignature*) typeSignature,
                                                                              this, scope, irContext);
        case ENUM_TYPE_SOURCE:
            return _irStrategyMap.getEnumTypeSignatureIRStrategy()->generate((EnumTypeSignature*) typeSignature, this, scope, irContext);
        case ENUM_ACCESS_TYPE_SOURCE:
            return _irStrategyMap.getEnumAccessTypeSignatureIRStrategy()->generate(
                    (EnumAccessTypeSignature*) typeSignature, this, scope, irContext);
        case FUNCTION_TYPE_SOURCE:
            return _irStrategyMap.getFunctionTypeSignatureIRStrategy()->generate(
                    (FunctionTypeSignature*) typeSignature, this, scope, irContext);
        case PROCEDURE_TYPE_SOURCE:
            return _irStrategyMap.getProcedureTypeSignatureIRStrategy()->generate(
                    (ProcedureTypeSignature*) typeSignature, this, scope, irContext);
        case LAMBDA_EXPRESSION_TYPE_SOURCE:
            return _irStrategyMap.getLambdaTypeSignatureIRStrategy()->generate(
                    (LambdaExpressionTypeSignature*) typeSignature, this, scope, irContext);
        case LAMBDA_TYPE_SOURCE:
            return _irStrategyMap.getLambdaTypeSignatureIRStrategy()->generate(
                    (LambdaTypeSignature*) typeSignature, this, scope, irContext);
        case INTERFACE_TYPE_SOURCE:
            return _irStrategyMap.getInterfaceTypeSignatureIRStrategy()->generate(
                    (InterfaceTypeSignature*)typeSignature, this, scope, irContext);
        case STRUCT_TYPE_SOURCE:
            return _irStrategyMap.getStructTypeSignatureIRStrategy()->generate((StructTypeSignature*) typeSignature,
                                                                               this, scope, irContext);
        case TUPLE_TYPE_SOURCE:
            return _irStrategyMap.getTupleTypeSignatureIRStrategy()->generate((TupleTypeSignature*) typeSignature,
                                                                              this, scope, irContext);
        case MODULE_TYPE_SOURCE:
            return _irStrategyMap.getModuleTypeSignatureIRStrategy()->generate((ModuleTypeSignature*) typeSignature,
                                                                               this, scope, irContext);
        case POINTER_TYPE_SOURCE:
            return _irStrategyMap.getPointerTypeSignatureIRStrategy()->generate((PointerTypeSignature*) typeSignature,
                                                                                this, scope, irContext);
        case REF_TYPE_SOURCE:
            return _irStrategyMap.getRefTypeSignatureIRStrategy()->generate((RefTypeSignature*)typeSignature,
                                                                                this, scope, irContext);
        case FUNCTION_INVOCATION_TYPE_SOURCE:
            return _irStrategyMap.getFunctionInvocationTypeSignatureIRStrategy()->generate(
                    (FunctionInvocationTypeSignature*) typeSignature, this, scope, irContext);
        case CLASS_METHOD_TYPE_SOURCE:
            return _irStrategyMap.getClassMethodTypeSignatureIRStrategy()->generate(
                    (ClassMethodTypeSignature*) typeSignature, this, scope, irContext);
        case CLASS_PROPERTY_TYPE_SOURCE:
            return _irStrategyMap.getClassPropertyTypeSignatureIRStrategy()->generate(
                    (ClassPropertyTypeSignature*) typeSignature, this, scope, irContext);
        case NEW_CLASS_INSTANCE_TYPE_SOURCE:
            return _irStrategyMap.getNewClassInstanceTypeSignatureIRStrategy()->generate(
                    (NewClassInstanceTypeSignature*) typeSignature, this, scope, irContext);
        case CLASS_INSTANCE_TYPE_SOURCE:
            return _irStrategyMap.getClassInstanceTypeSignatureIRStrategy()->generate(
                    (ClassInstanceTypeSignature*) typeSignature, this, scope, irContext);
        case LAMBDA_SCOPE_TYPE_SOURCE:
            return _irStrategyMap.getLambdaScopeTypeSignatureIRStrategy()->generate(
                    (LambdaScopeTypeSignature*) typeSignature, this, scope, irContext);
        case INT_LITERAL_TYPE_SOURCE:
        case FLOAT_LITERAL_TYPE_SOURCE:
        case CHAR_LITERAL_TYPE_SOURCE:
        case STRING_LITERAL_TYPE_SOURCE:
        case BOOL_LITERAL_TYPE_SOURCE:
        case LITERAL_TYPE_SOURCE:
            return _irStrategyMap.getLiteralTypeSignatureIRStrategy()->generate((LiteralTypeSignature*) typeSignature,
                                                                                this, scope, irContext);
        default:
            Logger::log("UH OH");
            typeSignature->print();
            throw std::logic_error("unable to generate llvm type for type-signature " + typeSignature->toString());
    }
}

IRArrayPointerType* IRGenerator::generateTypeFor(ArrayTypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext) {
    return _irStrategyMap.getArrayTypeSignatureIRStrategy()->generate(typeSignature, this, scope, irContext);
}

IREnumType* IRGenerator::generateTypeFor(EnumTypeSignature* typeSignature, std::vector<llvm::Constant*> enumValues, IRLookupTable* scope, IRContext* irContext) {
    return _irStrategyMap.getEnumTypeSignatureIRStrategy()->generate(typeSignature, enumValues, this, scope, irContext);
}

IRStructType* IRGenerator::generateTypeFor(InterfaceTypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext) {
    return _irStrategyMap.getInterfaceTypeSignatureIRStrategy()->generate(typeSignature, this, scope, irContext);
}

IRStructRefType* IRGenerator::generateTypeFor(StructTypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext) {
    return _irStrategyMap.getStructTypeSignatureIRStrategy()->generate(typeSignature, this, scope, irContext);
}

IRStructRefType* IRGenerator::generateTypeFor(TupleTypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext) {
    return _irStrategyMap.getTupleTypeSignatureIRStrategy()->generate(typeSignature, this, scope, irContext);
}

IRStructType* IRGenerator::generateTypeFor(LambdaScopeTypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext) {
    return _irStrategyMap.getLambdaScopeTypeSignatureIRStrategy()->generate(typeSignature, this, scope, irContext);
}

IRModuleType* IRGenerator::generateTypeFor(ModuleTypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext) {
    return _irStrategyMap.getModuleTypeSignatureIRStrategy()->generate(typeSignature, this, scope, irContext);
}

IRClassType* IRGenerator::generateTypeFor(ClassTypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext) {
    return _irStrategyMap.getClassTypeSignatureIRStrategy()->generate(typeSignature, this, scope, irContext);
}


IRPointerType* IRGenerator::generateTypeFor(PointerTypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext) {
    return _irStrategyMap.getPointerTypeSignatureIRStrategy()->generate(typeSignature, this, scope, irContext);
}

IRRefType* IRGenerator::generateTypeFor(RefTypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext) {
    return _irStrategyMap.getRefTypeSignatureIRStrategy()->generate(typeSignature, this, scope, irContext);
}

llvm::Type* IRGenerator::getVoidType() {
    return llvm::Type::getVoidTy(*_context);
}

IRType* IRGenerator::generateVoidType() {
    return _irStrategyMap.getVoidTypeSignatureIRStrategy()->generate(this);
}

IRPointerType* IRGenerator::generateIRInvocableCleanupType() {
    return this->generateIrPointerType(
        new IRFunctionType(llvm::FunctionType::get(this->getVoidType(), { this->generatePointerType() }, false))
    );
}

IRInvocableType* IRGenerator::generateIRInvocableType() {
    return new IRInvocableType(
            this->getFunctionParameterType(),
            this->generateIrPointerType(),
            this->generateIRInvocableCleanupType(),
            new IRInvocableParameterListType(),
            this->generateVoidType()
    );
}

IRPointerType* IRGenerator::generateIrPointerType() {
    return new IRPointerType(llvm::PointerType::get(*_context, 0));
}

IRPointerType* IRGenerator::generateIrPointerType(IRType* type) {
    return new IRPointerType(llvm::PointerType::get(type->getType(), 0), type);
}

IRRefType* IRGenerator::generateIrRefType(IRType* underlyingIRType) {
    auto irRefType = new IRRefType(_refType, new IRType(this->generateIntType()), underlyingIRType);
    return irRefType;
}

llvm::StructType* IRGenerator::getFunctionParameterType() {
    return _invocableType;
}

IRArrayType* IRGenerator::generateIRArrayType(IRType* elementType, unsigned long size) {
    auto irArrayType = new IRArrayType(llvm::ArrayType::get(elementType->getType(), size), elementType);
    return irArrayType;
}

std::string IRGenerator::getArrayPrototypeFunctionName(std::string id) {
    return ArrayPrototypeMap::getIRName(id);
}

std::string IRGenerator::getRefPrototypeFunctionName(std::string id) {
    return RefPrototypeMap::getIRName(id);
}

std::string IRGenerator::getJetUtilsFunctionName(std::string id) {
    return IRUtilInternalModule::getIRName(id);
}

std::string IRGenerator::getJetDebugFunctionName(std::string id) {
    return IRDebugInternalModule::getIRName(id);
}

IRFunctionType* IRGenerator::generateFunctionIrType(llvm::FunctionType* functionType) {
    return new IRFunctionType(functionType);
}

IRArrayType* IRGenerator::generateVarArgsTypeValuesIrType(unsigned long numVarArgs) {
    return this->generateIRArrayType(this->generateIrTypeValueType(), numVarArgs);
}

std::vector<llvm::Value*> IRGenerator::generateArgumentPlaceholderList(IRFunctionType* irFunctionType) {
    auto pointerType = this->generatePointerType();
    auto argList = std::vector<llvm::Value*>();
    auto numArguments = irFunctionType->getType()->getNumParams();
    for (unsigned int i = 0; i < numArguments; ++i) {
        argList.push_back(llvm::ConstantPointerNull::get(pointerType));
    }
    return argList;
}

std::vector<llvm::Value*> IRGenerator::generateArgumentPlaceholderList(IRInvocableType* irInvocableType) {
    auto pointerType = this->generatePointerType();
    auto argList = std::vector<llvm::Value*>();
    auto numArguments = irInvocableType->getIRFunctionType()->getType()->getNumParams();
    for (unsigned int i = 0; i < numArguments; ++i) {
        argList.push_back(llvm::ConstantPointerNull::get(pointerType));
    }

    // for scope argument
    argList.push_back(llvm::ConstantPointerNull::get(pointerType));

    return argList;
}

llvm::PointerType* IRGenerator::generatePointerType() {
    return llvm::PointerType::get(*_context, 0);
}

llvm::PointerType* IRGenerator::generatePointerType(llvm::Type* type) {
    return llvm::PointerType::get(type, 0);
}

llvm::IntegerType* IRGenerator::generateIntType() {
    return llvm::Type::getInt64Ty(*_context);
}

llvm::IntegerType* IRGenerator::generateInt32Type() {
    return llvm::Type::getInt32Ty(*_context);
}

llvm::Type* IRGenerator::generateFloatType() {
    return llvm::Type::getDoubleTy(*_context);
}

llvm::Type* IRGenerator::generateDoubleType() {
    return llvm::Type::getDoubleTy(*_context);
}

llvm::Type* IRGenerator::generateLiteralType() {
    return llvm::IntegerType::get(*_context, 2);
}

llvm::IntegerType* IRGenerator::generateBooleanType() {
    return llvm::IntegerType::get(*_context, 1);
}

llvm::IntegerType* IRGenerator::generateCharType() {
    return llvm::IntegerType::get(*_context, 8);
}

llvm::IntegerType* IRGenerator::generatePointerIntType() {
    return llvm::IntegerType::get(*_context, 8);
}

IRTypeValueInstructionNode* IRGenerator::generateIRTypeValueFor(IRType* irType, IRContext* irContext) {
    if (irType->isRefType()) {
        return this->_irStrategyMap.getRefTypeSignatureIRStrategy()->generateTypeValue((IRRefType*)irType, this, irContext);
    } else if (irType->isStructType()) {
        return this->_irStrategyMap.getStructTypeSignatureIRStrategy()->generateTypeValue((IRStructType*)irType, this, irContext);
    } else if (irType->isStructRefType()) {
        return this->_irStrategyMap.getStructTypeSignatureIRStrategy()->generateTypeValue((IRStructRefType*)irType, this, irContext);
    } else if (irType->isArrayPointerType()) {
        return this->_irStrategyMap.getArrayTypeSignatureIRStrategy()->generateTypeValue((IRArrayPointerType*)irType, this, irContext);
    } else if (irType->isPointerType()) {
        return this->_irStrategyMap.getPointerTypeSignatureIRStrategy()->generateTypeValue((IRPointerType*)irType, this);
    }
    throw std::logic_error("unable to generate type value for ir type");
}

IRTypeValueType* IRGenerator::generateIrTypeValueType() {
    return new IRTypeValueType(_typeValueType);
}

llvm::AllocaInst* IRGenerator::generateIrTypeValueTypeAllocation() {
    auto irTypeValueType = this->generateIrTypeValueType();
    return new llvm::AllocaInst(
            irTypeValueType->getType(),
            AddressSpaceGenerator::generate(irTypeValueType),
            nullptr,
            irTypeValueType->getAlignment()
    );
}

llvm::GetElementPtrInst* IRGenerator::generateGEP(IRType* irType, llvm::Value* pointer, unsigned long index) {
    return llvm::GetElementPtrInst::Create(irType->getType(), pointer, { this->generateIntConstant(0), this->generateIntConstant(index) });
}

llvm::ExtractValueInst* IRGenerator::generateExtractValue(llvm::Value* value, unsigned int index) {
    return llvm::ExtractValueInst::Create(value, { index });
}

llvm::StoreInst* IRGenerator::generateStoreInstruction(llvm::Value* value, llvm::Value* pointer, IRType* irType) {
    return new llvm::StoreInst(value, pointer, false, irType->getAlignment());
}

llvm::LoadInst* IRGenerator::generateLoadInstruction(llvm::Value* pointer, IRType* irType) {
    return new llvm::LoadInst(irType->getType(), pointer, "", false, irType->getAlignment());
}

IRParameterListType* IRGenerator::generateParameterList(ParameterListTypeSignature* parameterList, IRLookupTable* scope, IRContext* irContext, std::optional<ParameterListItemTypeSignature*> scopeParameter) {
    return _irStrategyMap.getParameterListTypeSignatureIRStrategy()->generate(parameterList, this, scope, irContext, scopeParameter);
}

IRParameterType* IRGenerator::generateParameterType(ParameterListItemTypeSignature* parameter, IRLookupTable* scope, IRContext* irContext) {
    return _irStrategyMap.getParameterTypeSignatureIRStrategy()->generate(parameter, this, scope, irContext);
}

llvm::ConstantInt* IRGenerator::generateIntConstant(int integer) {
    return llvm::ConstantInt::get(*_context, llvm::APInt(64, integer));
}

llvm::ConstantInt* IRGenerator::generateIntConstant(unsigned int integer) {
    return llvm::ConstantInt::get(*_context, llvm::APInt(64, integer));
}

llvm::ConstantInt* IRGenerator::generateIntConstant(uint64_t integer) {
    return llvm::ConstantInt::get(*_context, llvm::APInt(64, integer));
}

llvm::ConstantInt* IRGenerator::generateIntConstant(unsigned long integer) {
    return llvm::ConstantInt::get(*_context, llvm::APInt(64, integer));
}

llvm::ConstantFP* IRGenerator::generateFloatConstant(double floatValue) {
    return llvm::ConstantFP::get(*_context, llvm::APFloat(floatValue));
}

llvm::ConstantInt* IRGenerator::generateChar(char character) {
    return llvm::ConstantInt::get(*_context, llvm::APInt(CHAR_BIT, character));
}

llvm::ConstantInt* IRGenerator::generateBoolean(bool value) {
    if (value) {
        return llvm::ConstantInt::get(*_context, llvm::APInt(1, 1));
    }
    return llvm::ConstantInt::get(*_context, llvm::APInt(1, 0));
}

llvm::ConstantInt* IRGenerator::generateInt64Constant(int integer) {
    return llvm::ConstantInt::get(*_context, llvm::APInt(64, integer));
}

llvm::ConstantInt* IRGenerator::generateInt64Constant(unsigned int integer) {
    return llvm::ConstantInt::get(*_context, llvm::APInt(64, integer));
}

llvm::ConstantInt* IRGenerator::generateInt64Constant(uint64_t integer) {
    return llvm::ConstantInt::get(*_context, llvm::APInt(64, integer));
}

llvm::ConstantInt* IRGenerator::generateInt64Constant(unsigned long integer) {
    return llvm::ConstantInt::get(*_context, llvm::APInt(64, integer));
}

llvm::Constant* IRGenerator::generateRawString(std::string rawString) {
    return this->_irStrategyMap.getStringLiteralIRStrategy()->generateIRString(rawString, this, &_context);
}

llvm::Constant* IRGenerator::getOrInsertGlobalVariableString(std::string id, std::string rawString, IRContext* irContext) {
    auto stringValue = this->generateRawString(rawString);
    return irContext->getModule()->getOrInsertGlobal(
            id,
            stringValue->getType(),
            [irContext, stringValue, id]() -> llvm::GlobalVariable* {
                return new llvm::GlobalVariable(
                        *irContext->getModule(),
                        stringValue->getType(),
                        true,
                        llvm::GlobalValue::PrivateLinkage,
                        stringValue,
                        id
                );
            }
    );
}

IRArrayPointerType* IRGenerator::generateIrArrayPointerType(IRPointerType* irPointerType) {
    auto irArrayPointerType = new IRArrayPointerType(this->getArrayPointerType(), irPointerType->getSourceType());
    return irArrayPointerType;
}

IRArrayPointerType* IRGenerator::generateIrArrayPointerType(IRType* arrayElementType) {
    auto irArrayPointerType = new IRArrayPointerType(this->getArrayPointerType(), arrayElementType);
    return irArrayPointerType;
}

IRStructRefType* IRGenerator::generateIRStructRefType(IRStructType* irStructType) {
    return new IRStructRefType(
        this->getStructRefType(),
        this->generateIRStructRefCounterType(),
        irStructType
    );
}

IRStructRefType* IRGenerator::generateIRStructRefType() {
    return new IRStructRefType(
            this->getStructRefType(),
            this->generateIRStructRefCounterType(),
            this->generateIRStructType()
    );
}

IRStructType* IRGenerator::generateIRStructType() {
    return new IRStructType(
            llvm::StructType::get(*_context),
            std::unordered_map<std::string, unsigned long>(),
            std::unordered_map<std::string, IRType*>()
    );
}

IRInstructionNode* IRGenerator::generateFunctionParameterAllocation(IRType* irType) {
    return new IRInstructionNode(
            new llvm::AllocaInst(
                    irType->getType(),
                    AddressSpaceGenerator::generate(irType),
                    nullptr,
                    irType->getAlignment()
            ), this->generateIrPointerType(irType));
}

IRInstructionNode* IRGenerator::generateFunctionParameterAllocation(ASTFunctionParameterNode* functionParameter, IRParameterType* irParameterType, IRContext* irContext) {
    auto irType = irParameterType->getIRType();
    if (functionParameter->isCaptured()) {
        return new IRInstructionNode(
            llvm::CallInst::Create(
                irContext->getIRModule()->getMallocFunction(),
                { this->generateInt64Constant(1), this->generateInt64Constant(irType->getSizeInBytes()) }
            ),
            this->generateIrPointerType(irType)
        );
    }
    return new IRInstructionNode(
        new llvm::AllocaInst(
            irType->getType(),
            AddressSpaceGenerator::generate(irType),
            nullptr,
            irType->getAlignment()
        ),
        this->generateIrPointerType(irType)
    );
}

IRType* IRGenerator::generateIRCaptureCounterType() {
    return new IRType(this->generateIntType());
}

IRType* IRGenerator::generateIRStructRefCounterType() {
    return new IRType(this->generateIntType());
}

IRType* IRGenerator::generateIRArcType() {
    return new IRType(this->generateIntType());
}

IRInstructionNode* IRGenerator::generateArcAllocationForFunctionParameter(IRContext* irContext, llvm::Value* source, unsigned long count) {
    auto irType = this->generateIRArcType();
    auto functionParameterType = this->generateIRInvocableType();
    auto pointerToArcPointer = llvm::GetElementPtrInst::Create(functionParameterType->getType(), source, { this->generateIntConstant(0), this->generateIntConstant(functionParameterType->getFunctionRefCounterIndex()) });
    auto ancestorValues = std::vector<llvm::Value*> { pointerToArcPointer };
    if (count > 0) {
        auto loadedArcPointerForCount = this->generateLoadInstruction(pointerToArcPointer, this->generateIrPointerType(irType));
        auto currentArcValue = this->generateLoadInstruction(loadedArcPointerForCount, irType);
        auto newArcValue = llvm::BinaryOperator::Create(llvm::Instruction::BinaryOps::Add, currentArcValue, this->generateIntConstant(count));
        auto setArcValue = this->generateStoreInstruction(newArcValue, loadedArcPointerForCount, irType);
        ancestorValues.push_back(loadedArcPointerForCount);
        ancestorValues.push_back(currentArcValue);
        ancestorValues.push_back(newArcValue);
        ancestorValues.push_back(setArcValue);
    }
    return new IRInstructionNode(
            this->generateLoadInstruction(pointerToArcPointer, this->generateIrPointerType(irType)),
            this->generateIrPointerType(irType),
            ancestorValues
    );
}

IRInstructionNode* IRGenerator::generateArcAllocationForStructRef(IRContext* irContext, llvm::Value* source, unsigned long count) {
    auto irType = this->generateIRArcType();
    auto structRefType = this->generateIRStructRefType();
    auto pointerToArcPointer = llvm::GetElementPtrInst::Create(structRefType->getType(), source, { this->generateIntConstant(0), this->generateIntConstant(structRefType->getCounterIndex()) });
    auto ancestorValues = std::vector<llvm::Value*> { pointerToArcPointer };
    if (count > 0) {
        auto loadedArcPointerForCount = this->generateLoadInstruction(pointerToArcPointer, this->generateIrPointerType(irType));
        auto currentArcValue = this->generateLoadInstruction(loadedArcPointerForCount, irType);
        auto newArcValue = llvm::BinaryOperator::Create(llvm::Instruction::BinaryOps::Add, currentArcValue, this->generateIntConstant(count));
        auto setArcValue = this->generateStoreInstruction(newArcValue, loadedArcPointerForCount, irType);
        ancestorValues.push_back(loadedArcPointerForCount);
        ancestorValues.push_back(currentArcValue);
        ancestorValues.push_back(newArcValue);
        ancestorValues.push_back(setArcValue);
    }
    return new IRInstructionNode(
            this->generateLoadInstruction(pointerToArcPointer, this->generateIrPointerType(irType)),
            this->generateIrPointerType(irType),
            ancestorValues
    );
}

IRInstructionNode* IRGenerator::generateArcAllocation(IRContext* irContext, IRType* irType, llvm::Value* source, unsigned long count) {
    if (irType->isInvocableType()) {
        return this->generateArcAllocationForFunctionParameter(irContext, source, count);
    }
    return this->generateArcAllocationForStructRef(irContext, source, count);
}

IRInstructionNode* IRGenerator::generateArcAllocation(IRContext* irContext, unsigned long initialCount) {
    auto irType = this->generateIRArcType();
    auto malloc = llvm::CallInst::Create(
            irContext->getIRModule()->getMallocFunction(),
            { this->generateInt64Constant(1), this->generateInt64Constant(irType->getSizeInBytes()) }
    );
    auto captureCount = this->generateIntConstant(initialCount);
    auto storeInstruction = this->generateStoreInstruction(captureCount, malloc, irType);
    return new IRInstructionNode(
            malloc,
            this->generateIrPointerType(irType),
            {},
            { storeInstruction }
    );
}

IRCapturedVariableType* IRGenerator::generateIRCapturedVariableType(IRType* variableIrType) {
    return new IRCapturedVariableType(
        llvm::StructType::get(*_context, { this->generatePointerType(), this->generatePointerType() }),
        this->generateIRCaptureCounterType(),
        variableIrType
    );
}

IRType* IRGenerator::generateIRCharType() {
    return new IRType(this->generateCharType());
}

IRArrayPointerType* IRGenerator::generateIrStringArrayPointerType() {
    auto irArrayPointerType = new IRArrayPointerType(this->getArrayPointerType(), this->generateIRCharType());
    return irArrayPointerType;
}

llvm::StructType* IRGenerator::generateArrayPointerType() {
    return llvm::StructType::get(*_context, {
            this->generateIntType(),
            this->generateIntType(),
            this->generatePointerType()
    });
}

llvm::StructType* IRGenerator::getArrayPointerType() {
    return _arrayPointerType;
}

llvm::StructType* IRGenerator::getStructRefType() {
    return _structRefType;
}

IRBlockNode* IRGenerator::generateFunctionBlock(llvm::Function* irFunction, std::optional<IRLookupTable*> scope) {
    return new IRBlockNode(llvm::BasicBlock::Create(*_context, "", irFunction), IR_BASIC_BT, scope.value_or(new IRLookupTable()));
}

IRBlockNode* IRGenerator::generateIfBlock(IRContext* irContext, IRLookupTable* scope, std::string prefix) {
    return new IRControlFlowBlockNode(llvm::BasicBlock::Create(*_context, prefix + "if.cond", irContext->getFunction()), IR_IF_BT, scope);
}

IRBlockNode* IRGenerator::generateIfThenBlock(IRContext* irContext, IRLookupTable* scope, std::string prefix) {
    return new IRControlFlowBlockNode(llvm::BasicBlock::Create(*_context, prefix + "if.true", irContext->getFunction()), IR_IF_THEN_BT, new IRLookupTable(scope));
}

IRBlockNode* IRGenerator::generateIfElseBlock(IRContext* irContext, IRLookupTable* scope, std::string prefix) {
    return new IRControlFlowBlockNode(llvm::BasicBlock::Create(*_context, prefix + "if.false", irContext->getFunction()), IR_IF_ELSE_BT, new IRLookupTable(scope));
}

IRBlockNode* IRGenerator::generateIfEndBlock(IRContext* irContext, IRLookupTable* scope, std::string prefix) {
    return new IRControlFlowBlockNode(llvm::BasicBlock::Create(*_context, prefix + "if.end", irContext->getFunction()), IR_IF_END_BT, scope);
}

IRBlockNode* IRGenerator::generateWhileConditionBlock(IRContext* irContext, IRLookupTable* scope, std::string prefix) {
    return new IRControlFlowBlockNode(llvm::BasicBlock::Create(*_context, prefix + "while.condition", irContext->getFunction()), IR_WHILE_BT, scope);
}

IRBlockNode* IRGenerator::generateWhileBodyBlock(IRContext* irContext, IRLookupTable* scope, std::string prefix) {
    return new IRControlFlowBlockNode(llvm::BasicBlock::Create(*_context, prefix + "while.body", irContext->getFunction()), IR_WHILE_BODY_BT, new IRLookupTable(scope));
}

IRBlockNode* IRGenerator::generateWhileEndBlock(IRContext* irContext, IRLookupTable* scope, std::string prefix) {
    return new IRControlFlowBlockNode(llvm::BasicBlock::Create(*_context, prefix + "while.end", irContext->getFunction()), IR_WHILE_END_BT, scope);
}

IRBlockNode* IRGenerator::generateForLoopConditionBlock(IRContext* irContext, IRLookupTable* scope, std::string prefix) {
    return new IRControlFlowBlockNode(llvm::BasicBlock::Create(*_context, prefix + "for.loop.condition", irContext->getFunction()), IR_FOR_LOOP_BT, scope);
}

IRBlockNode* IRGenerator::generateForLoopBodyBlock(IRContext* irContext, IRLookupTable* scope, std::string prefix) {
    return new IRControlFlowBlockNode(llvm::BasicBlock::Create(*_context, prefix + "for.loop.body", irContext->getFunction()), IR_FOR_LOOP_BODY_BT, new IRLookupTable(scope));
}

IRBlockNode* IRGenerator::generateForLoopEndBlock(IRContext* irContext, IRLookupTable* scope, std::string prefix) {
    return new IRControlFlowBlockNode(llvm::BasicBlock::Create(*_context, prefix + "for.loop.end", irContext->getFunction()), IR_FOR_LOOP_END_BT, scope);
}

IRBlockNode* IRGenerator::generateForInBlock(IRContext* irContext, IRLookupTable* scope, std::string prefix) {
    return new IRControlFlowBlockNode(llvm::BasicBlock::Create(*_context, prefix + "for.in", irContext->getFunction()), IR_FOR_IN_BT, scope);
}

IRBlockNode* IRGenerator::generateForInSetupBlock(IRContext* irContext, IRLookupTable* scope, std::string prefix) {
    return new IRControlFlowBlockNode(llvm::BasicBlock::Create(*_context, prefix + "for.in.setup", irContext->getFunction()), IR_FOR_IN_SETUP_BT, new IRLookupTable(scope));
}

IRBlockNode* IRGenerator::generateForInBodyBlock(IRContext* irContext, IRLookupTable* scope, std::string prefix) {
    return new IRControlFlowBlockNode(llvm::BasicBlock::Create(*_context, prefix + "for.in.body", irContext->getFunction()), IR_FOR_IN_BODY_BT, new IRLookupTable(scope));
}

IRBlockNode* IRGenerator::generateForInEndBlock(IRContext* irContext, IRLookupTable* scope, std::string prefix) {
    return new IRControlFlowBlockNode(llvm::BasicBlock::Create(*_context, prefix + "for.in.end", irContext->getFunction()), IR_FOR_IN_END_BT, scope);
}

IRBlockNode* IRGenerator::generateBasicBlock() {
    return new IRBlockNode(llvm::BasicBlock::Create(*_context, "entry"), IR_BASIC_BT, new IRLookupTable());
}

IRBlockNode* IRGenerator::generateBasicBlock(std::string label, IRContext* irContext, std::optional<IRLookupTable*> scope) {
    return new IRBlockNode(llvm::BasicBlock::Create(*_context, label, irContext->getFunction()), IR_BASIC_BT, scope.value_or(new IRLookupTable()));
}

IRContext* IRGenerator::generateContext(IRBlockNode* irBlock, std::shared_ptr<IRModuleNode> irModule) {
    return new IRContext(irBlock, irModule, &_context);
}

std::shared_ptr<IRModuleNode> IRGenerator::generateModule(std::string moduleName) {
    return std::make_shared<IRModuleNode>(IRModuleNode(
            std::make_unique<llvm::Module>(moduleName,*_context),
            ArrayAccessIRFunction::getArrayAccessIRFunctionName(),
            CopyArrayIRFunction::getCopyArrayIRFunctionName(),
            CopyPointerIRFunction::getCopyPointerIRFunctionName(),
            CopyLambdaIRFunction::getCopyLambdaIRFunctionName(),
            CopyStructIRFunction::getCopyStructIRFunctionName(),
            CopyStructRefIRFunction::getCopyStructRefIRFunctionName(),
            CopyValueIRFunction::getCopyValueIRFunctionName(),
            CopyStringIRFunction::getCopyStringIRFunctionName(),
            CopyRefIRFunction::getCopyRefIRFunctionName(),
            FreeArrayIRFunction::getFreeArrayIRFunctionName(),
            FreePointerIRFunction::getFreePointerIRFunctionName(),
            FreeLambdaIRFunction::getFreeLambdaIRFunctionName(),
            FreeInvocableIRFunction::getFreeInvocableIRFunctionName(),
            FreeStructIRFunction::getFreeStructIRFunctionName(),
            FreeStructRefIRFunction::getFreeStructRefIRFunctionName(),
            FreeValueIRFunction::getFreeValueIRFunctionName(),
            FreeStringIRFunction::getFreeStringIRFunctionName(),
            FreeRefIRFunction::getFreeRefIRFunctionName(),
            FreeRefValueIRFunction::getFreeRefValueIRFunctionName(),
            FreeCapturedVariableIRFunction::getFreeCapturedVariableIRFunctionName(),
            PrintIRFunction::getPrintIRFunctionName(),
            PrintIRFunction::getPrintIntIRFunctionName(),
            PrintIRFunction::getPrintFloatIRFunctionName(),
            PrintIRFunction::getPrintCharIRFunctionName(),
            PrintIRFunction::getPrintBoolIRFunctionName(),
            PrintIRFunction::getPrintStringIRFunctionName(),
            PrintIRFunction::getPrintRefIRFunctionName(),
            PrintIRFunction::getPrintArrayIRFunctionName(),
            PrintIRFunction::getPrintStructIRFunctionName(),
            PrintIRFunction::getPrintStructRefIRFunctionName(),
            PrintIRFunction::getPrintLambdaIRFunctionName(),
            PrintIRFunction::getPrintWhitespaceIRFunctionName(),
            PrintIRFunction::getPrintCommaIRFunctionName(),
            PrintIRFunction::getPrintNewLineIRFunctionName(),
            PrintIRFunction::getPrintDebugMarkerIRFunctionName(),
            PrintIRFunction::getPrintDebugPointerIRFunctionName(),
            PrintIRFunction::getPrintDebugStringIRFunctionName(),
            PrintIRFunction::getPrintDebugRefCountIRFunctionName(),
            RangeIRFunction::getRange1pIRFunctionName(),
            RangeIRFunction::getRange2pIRFunctionName(),
            RangeIRFunction::getRange3pIRFunctionName(),
            MallocIRFunction::getMallocIRFunctionName(),
            MallocFreeIRFunction::getMallocFreeIRFunctionName(),
            MallocSizeIRFunction::getMallocSizeIRFunctionName(),
            EqualValueIRFunction::getEqualValueIRFunctionName(),
            EqualStringIRFunction::getEqualStringIRFunctionName(),
            EqualArrayIRFunction::getEqualArrayIRFunctionName(),
            EqualStructIRFunction::getEqualStructIRFunctionName(),
            EqualStructRefIRFunction::getEqualStructRefIRFunctionName(),
            EqualLambdaIRFunction::getEqualLambdaIRFunctionName(),
            EqualRefIRFunction::getEqualRefIRFunctionName(),
            EqualRefIRFunction::getEqualRefLeftOnlyIRFunctionName(),
            EqualRefIRFunction::getEqualRefRightOnlyIRFunctionName(),
            StringConcatIRFunction::getStringConcatIRFunctionName(),
            ArrayAppendIRFunction::getArrayAppendIRFunctionName(),
            ArrayPrependIRFunction::getArrayPrependIRFunctionName(),
            ArrayConcatIRFunction::getArrayConcatIRFunctionName(),
            ArrayHeadIRFunction::getArrayHeadIRFunctionName(),
            ArrayLastIRFunction::getArrayLastIRFunctionName(),
            ArrayDropIRFunction::getArrayDropIRFunctionName(),
            ArrayDropLastIRFunction::getArrayDropLastIRFunctionName(),
            ArrayTailIRFunction::getArrayTailIRFunctionName(),
            ArrayTakeIRFunction::getArrayTakeIRFunctionName(),
            ArrayTakeLastIRFunction::getArrayTakeLastIRFunctionName(),
            ArraySizeIRFunction::getArraySizeIRFunctionName(),
            ArrayEmptyIRFunction::getArrayEmptyIRFunctionName(),
            MemcpyIRFunction::getMemcpyIRFunctionName(),
            SetupSrefIRFunction::getSetupSrefIRFunctionName(),
            SetupRefIRFunction::getSetupRefIRFunctionName(),
            SetupRefForStructIRFunction::getSetupRefForStructIRFunctionName(),
            RefOfIRFunction::getRefOfIRFunctionName(),
            SrefWithIRFunction::getSrefWithIRFunctionName(),
            SameRefAsIRFunction::getSameRefAsIRFunctionName(),
            SetRefValueIRFunction::getSetRefValueIRFunctionName(),
            IncrementRefCountIRFunction::getIncrementRefCountIRFunctionName(),
            IncrementLambdaRefCountIRFunction::getIncrementLambdaRefCountIRFunctionName(),
            IncrementRefCountIfNecessaryIRFunction::getIncrementRefCountIfNecessaryIRFunctionName(),
            GetRefCountIRFunction::getGetRefCountIRFunctionName()
    ));
}

IRFunctionNode* IRGenerator::generateMainFunction(std::string functionName, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto functionType = llvm::FunctionType::get(llvm::Type::getInt64Ty(*_context), {}, false);
    return new IRFunctionNode(
        llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, functionName, irModuleNode->getModule()->get())
    );
}

void IRGenerator::augmentUtilInternalModule(std::shared_ptr<IRModuleNode> coreIRModule) {
    IRUtilInternalModule::augment(this, &_context, coreIRModule);
}

void IRGenerator::augmentDebugInternalModule(std::shared_ptr<IRModuleNode> coreIRModule) {
    IRDebugInternalModule::augment(this, &_context, coreIRModule);
}

std::shared_ptr<IRModuleNode> IRGenerator::generateCoreModule() {
    return IRCoreInternalModule::generate(this, &_context);
}

IRInjector* IRGenerator::getInjector() {
    return _irInjector;
}