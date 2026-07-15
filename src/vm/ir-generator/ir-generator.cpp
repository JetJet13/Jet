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
#include "ir-strategies/expression-ir-strategies/this-expression-ir-strategy/this-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/identifier-expression-ir-strategy/identifier-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/object-access-expression-ir-strategy/object-access-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/object-access-invocation-expression-ir-strategy/object-access-invocation-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/tuple-access-expression-ir-strategy/tuple-access-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/tuple-access-invocation-expression-ir-strategy/tuple-access-invocation-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/function-invocation-expression-ir-strategy/function-invocation-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/lambda-expression-ir-strategy/lambda-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/module-access-expression-ir-strategy/module-access-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/class-property-access-expression-ir-strategy/class-property-access-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/class-method-invocation-expression-ir-strategy/class-method-invocation-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/new-class-instance-expression-ir-strategy/new-class-instance-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/share-expression-ir-strategy/share-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/ref-expression-ir-strategy/ref-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/dref-expression-ir-strategy/dref-expression-ir-strategy.h"
#include "ir-strategies/expression-statement-ir-strategy/expression-statement-ir-strategy.h"
#include "ir-strategies/class-property-assignment-statement-ir-strategy/class-property-assignment-statement-ir-strategy.h"
#include "ir-strategies/class-property-shared-value-assignment-statement-ir-strategy/class-property-shared-value-assignment-statement-ir-strategy.h"
#include "ir-strategies/shared-value-assignment-statement-ir-strategy/shared-value-assignment-statement-ir-strategy.h"
#include "ir-strategies/variable-assignment-statement-ir-strategy/variable-assignment-statement-ir-strategy.h"
#include "ir-strategies/array-access-assignment-statement-ir-strategy/array-access-assignment-statement-ir-strategy.h"
#include "ir-strategies/array-access-shared-value-assignment-statement-ir-strategy/array-access-shared-value-assignment-statement-ir-strategy.h"
#include "ir-strategies/object-access-assignment-statement-ir-strategy/object-access-assignment-statement-ir-strategy.h"
#include "ir-strategies/object-access-shared-value-assignment-statement-ir-strategy/object-access-shared-value-assignment-statement-ir-strategy.h"
#include "ir-strategies/tuple-access-assignment-statement-ir-strategy/tuple-access-assignment-statement-ir-strategy.h"
#include "ir-strategies/tuple-access-shared-value-assignment-statement-ir-strategy/tuple-access-shared-value-assignment-statement-ir-strategy.h"
#include "ir-strategies/module-access-assignment-statement-ir-strategy/module-access-assignment-statement-ir-strategy.h"
#include "ir-strategies/module-access-shared-value-assignment-statement-ir-strategy/module-access-shared-value-assignment-statement-ir-strategy.h"
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
#include "ir-strategies/type-signature-ir-strategies/shared-type-signature-ir-strategy/shared-type-signature-ir-strategy.h"
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
#include "ir-prototypes/ir-string-prototype-map.h"
#include "ir-util-functions/free-class-property-ir-function/free-class-property-ir-function.h"
#include "ir-util-functions/int-add-overflow-ir-function/int-add-overflow-ir-function.h"
#include "ir-util-functions/int-sub-overflow-ir-function/int-sub-overflow-ir-function.h"
#include "ir-util-functions/int-multiply-overflow-ir-function/int-multiply-overflow-ir-function.h"


// The IRGenerator will be responsible for programmatically generating
// vm code.
// we need to figure out how to generate vm code for an ASTNode and its
// type signature.
IRGenerator::IRGenerator(std::shared_ptr<IRInjector> irInjector) {
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
            this->generatePointerType()
    }, "TypeValueType");
    _refType = llvm::StructType::create(*_context, {
            this->generatePointerType(),
            this->generatePointerType()
    }, "Ref");
    _sharedPtrType = llvm::StructType::create(*_context, {
            this->generatePointerType(),
            this->generatePointerType()
    }, "SharedPtr");
    _invocableType = llvm::StructType::create(*_context, {
            this->generatePointerType(),
            this->generatePointerType(),
            this->generatePointerType(),
            this->generatePointerType(),
            this->generateBooleanType()
    }, "Invocable");
    _genericClassInstanceIRType = std::make_shared<IRClassInstanceType>(
        std::make_shared<IRClassType>(
            "generic_class",
            this->generateIRStructRefType()
        )
    );
}

std::shared_ptr<IRNode> IRGenerator::generateFor(std::shared_ptr<ASTNode> node, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    if (ASTNodeUtils::isTypeDeclarationNode(node)) {
        return this->generateFor(std::dynamic_pointer_cast<ASTTypeDeclarationNode>(node), scope, irContext);
    } else if (ASTNodeUtils::isDeclarationNode(node)) {
        return this->generateFor(std::dynamic_pointer_cast<ASTDeclarationNode>(node), scope, irContext);
    } else if (ASTNodeUtils::isStatementNode(node)) {
        return this->generateFor(std::dynamic_pointer_cast<ASTStatementNode>(node), scope, irContext);
    } else if (node->is(AST_FUNCTION_RETURN_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getFunctionReturnExpressionIRStrategy()->generate(
                std::dynamic_pointer_cast<ASTFunctionReturnExpressionNode>(node), shared_from_this(), scope, irContext);
    }
    throw std::logic_error("unable to generate llvm value for node " + node->toString());
}

std::shared_ptr<IRStatementNode> IRGenerator::generateFor(std::shared_ptr<ASTStatementNode> node, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    if (node->is(AST_EXPRESSION_STATEMENT_NODE)) {
        return this->_irStrategyMap.getExpressionStatementIRStrategy()->generate(std::dynamic_pointer_cast<ASTExpressionStatementNode>(node),  shared_from_this(), scope, irContext);
    } else if (node->is(AST_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_NODE)) {
        return this->_irStrategyMap.getClassPropertyAssignmentStatementIRStrategy()->generate(std::dynamic_pointer_cast<ASTClassPropertyAssignmentStatementNode>(node),  shared_from_this(), scope, irContext);
    } else if (node->is(AST_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE)) {
        return this->_irStrategyMap.getClassPropertySharedValueAssignmentStatementIRStrategy()->generate(std::dynamic_pointer_cast<ASTClassPropertySharedValueAssignmentStatementNode>(node),  shared_from_this(), scope, irContext);
    } else if (node->is(AST_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE)) {
        return this->_irStrategyMap.getSharedValueAssignmentStatementIRStrategy()->generate(std::dynamic_pointer_cast<ASTSharedValueAssignmentStatementNode>(node),  shared_from_this(), scope, irContext);
    } else if (node->is(AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE)) {
        return this->_irStrategyMap.getVariableAssignmentStatementIRStrategy()->generate(std::dynamic_pointer_cast<ASTVariableAssignmentStatementNode>(node),  shared_from_this(), scope, irContext);
    } else if (node->is(AST_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_NODE)) {
        return this->_irStrategyMap.getArrayAccessAssignmentStatementIRStrategy()->generate(std::dynamic_pointer_cast<ASTArrayAccessAssignmentStatementNode>(node),  shared_from_this(), scope, irContext);
    } else if (node->is(AST_ARRAY_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE)) {
        return this->_irStrategyMap.getArrayAccessSharedValueAssignmentStatementIRStrategy()->generate(std::dynamic_pointer_cast<ASTArrayAccessSharedValueAssignmentStatementNode>(node),  shared_from_this(), scope, irContext);
    } else if (node->is(AST_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_NODE)) {
        return this->_irStrategyMap.getObjectAccessAssignmentStatementIRStrategy()->generate(std::dynamic_pointer_cast<ASTObjectAccessAssignmentStatementNode>(node),  shared_from_this(), scope, irContext);
    } else if (node->is(AST_OBJECT_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE)) {
        return this->_irStrategyMap.getObjectAccessSharedValueAssignmentStatementIRStrategy()->generate(std::dynamic_pointer_cast<ASTObjectAccessSharedValueAssignmentStatementNode>(node),  shared_from_this(), scope, irContext);
    } else if (node->is(AST_TUPLE_ACCESS_ASSIGNMENT_STATEMENT_NODE)) {
        return this->_irStrategyMap.getTupleAccessAssignmentStatementIRStrategy()->generate(std::dynamic_pointer_cast<ASTTupleAccessAssignmentStatementNode>(node),  shared_from_this(), scope, irContext);
    } else if (node->is(AST_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE)) {
        return this->_irStrategyMap.getTupleAccessSharedValueAssignmentStatementIRStrategy()->generate(std::dynamic_pointer_cast<ASTTupleAccessSharedValueAssignmentStatementNode>(node),  shared_from_this(), scope, irContext);
    } else if (node->is(AST_MODULE_ACCESS_ASSIGNMENT_STATEMENT_NODE)) {
        return this->_irStrategyMap.getModuleAccessAssignmentStatementIRStrategy()->generate(std::dynamic_pointer_cast<ASTModuleAccessAssignmentStatementNode>(node),  shared_from_this(), scope, irContext);
    } else if (node->is(AST_MODULE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE)) {
        return this->_irStrategyMap.getModuleAccessSharedValueAssignmentStatementIRStrategy()->generate(std::dynamic_pointer_cast<ASTModuleAccessSharedValueAssignmentStatementNode>(node),  shared_from_this(), scope, irContext);
    } else if (node->is(AST_IF_STATEMENT_NODE)) {
        return this->_irStrategyMap.getIfStatementIRStrategy()->generate(std::dynamic_pointer_cast<ASTIfStatementNode>(node),  shared_from_this(), scope, irContext);
    } else if (node->is(AST_WHILE_STATEMENT_NODE)) {
        return this->_irStrategyMap.getWhileStatementIRStrategy()->generate(std::dynamic_pointer_cast<ASTWhileStatementNode>(node),  shared_from_this(), scope, irContext);
    } else if (node->is(AST_FOR_IN_STATEMENT_NODE)) {
        return this->_irStrategyMap.getForInStatementIRStrategy()->generate(std::dynamic_pointer_cast<ASTForInStatementNode>(node),  shared_from_this(), scope, irContext);
    }
    throw std::logic_error("unable to generate llvm value for statement " + node->toString());
}

std::shared_ptr<IRDeclarationNode> IRGenerator::generateFor(std::shared_ptr<ASTDeclarationNode> node, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    if (node->is(AST_VARIABLE_DECLARATION_NODE)) {
        return this->_irStrategyMap.getVariableDeclarationIRStrategy()->generate(std::dynamic_pointer_cast<ASTVariableDeclarationNode>(node),  shared_from_this(), scope, irContext);
    } else if (node->is(AST_FUNCTION_DECLARATION_NODE)) {
        return this->_irStrategyMap.getFunctionDeclarationIRStrategy()->generate(std::dynamic_pointer_cast<ASTFunctionDeclarationNode>(node),  shared_from_this(), scope, irContext);
    } else if (node->is(AST_PROCEDURE_DECLARATION_NODE)) {
        return this->_irStrategyMap.getProcedureDeclarationIRStrategy()->generate(std::dynamic_pointer_cast<ASTProcedureDeclarationNode>(node),  shared_from_this(), scope, irContext);
    } else if (node->is(AST_ENUM_DECLARATION_NODE)) {
        return this->_irStrategyMap.getEnumDeclarationIRStrategy()->generate(std::dynamic_pointer_cast<ASTEnumDeclarationNode>(node),  shared_from_this(), scope, irContext);
    } else if (node->is(AST_MODULE_DECLARATION_NODE)) {
        return this->_irStrategyMap.getModuleDeclarationIRStrategy()->generate(std::dynamic_pointer_cast<ASTModuleDeclarationNode>(node),  shared_from_this(), scope, irContext);
    } else if (node->is(AST_IMPORT_SINGLE_MODULE_DECLARATION_NODE)) {
        return this->_irStrategyMap.getImportSingleModuleDeclarationIRStrategy()->generate(std::dynamic_pointer_cast<ASTImportSingleModuleDeclarationNode>(node),  shared_from_this(), scope, irContext);
    } else if (node->is(AST_CLASS_DECLARATION_NODE)) {
        return this->_irStrategyMap.getClassDeclarationIRStrategy()->generate(std::dynamic_pointer_cast<ASTClassDeclarationNode>(node),  shared_from_this(), scope, irContext);
    }
    throw std::logic_error("unable to generate llvm value for declaration " + node->toString());
}

std::shared_ptr<IRTypeDeclarationNode> IRGenerator::generateFor(std::shared_ptr<ASTTypeDeclarationNode> node, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    if (node->is(AST_INTERFACE_TYPE_DECLARATION_NODE)) {
        return this->_irStrategyMap.getInterfaceTypeDeclarationIRStrategy()->generate(std::dynamic_pointer_cast<ASTInterfaceTypeDeclarationNode>(node),  shared_from_this(), scope, irContext);
    } else if (node->is(AST_CUSTOM_TYPE_DECLARATION_NODE)) {
        return this->_irStrategyMap.getCustomTypeDeclarationIRStrategy()->generate(std::dynamic_pointer_cast<ASTCustomTypeDeclarationNode>(node),  shared_from_this(), scope, irContext);
    }
    throw std::logic_error("unable to generate llvm value for type declaration " + node->toString());
}

std::shared_ptr<IRFunctionParameterListNode> IRGenerator::generateFor(std::shared_ptr<ASTFunctionParameterListNode> node, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, llvm::Function* irFunction) {
    return this->_irStrategyMap.getFunctionParameterListIRStrategy()->generate(node,  shared_from_this(), scope, irContext, irFunction);
}

std::shared_ptr<IRExpressionNode> IRGenerator::generateFor(std::shared_ptr<ASTExpressionNode> node, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    if (node->is(AST_LITERAL_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getLiteralExpressionIRStrategy()->generate(std::dynamic_pointer_cast<ASTLiteralExpressionNode>(node),  shared_from_this(), scope, irContext, irOperation);
    } else if (node->is(AST_BINARY_ARITHMETIC_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getBinaryExpressionIRStrategy()->generate(std::dynamic_pointer_cast<ASTBinaryArithmeticExpressionNode>(node), shared_from_this(), scope, irContext, irOperation);
    } else if (node->is(AST_BINARY_COMPARATOR_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getBinaryExpressionIRStrategy()->generate(std::dynamic_pointer_cast<ASTBinaryComparatorExpressionNode>(node), shared_from_this(), scope, irContext, irOperation);
    } else if (node->is(AST_CONCAT_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getConcatExpressionIRStrategy()->generate(std::dynamic_pointer_cast<ASTConcatExpressionNode>(node),  shared_from_this(), scope, irContext, irOperation);
    } else if (node->is(AST_LOGICAL_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getLogicalExpressionIRStrategy()->generate(std::dynamic_pointer_cast<ASTLogicalExpressionNode>(node),  shared_from_this(), scope, irContext, irOperation);
    } else if (node->is(AST_ARRAY_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getArrayExpressionIRStrategy()->generate(std::dynamic_pointer_cast<ASTArrayExpressionNode>(node),  shared_from_this(), scope, irContext, irOperation);
    } else if (node->is(AST_ARRAY_ACCESS_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getArrayAccessExpressionIRStrategy()->generate(std::dynamic_pointer_cast<ASTArrayAccessExpressionNode>(node),  shared_from_this(), scope, irContext, irOperation);
    } else if (node->is(AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getArrayAccessInvocationExpressionIRStrategy()->generate(std::dynamic_pointer_cast<ASTArrayAccessInvocationExpressionNode>(node),  shared_from_this(), scope, irContext, irOperation);
    } else if (node->is(AST_STRUCT_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getStructExpressionIRStrategy()->generate(std::dynamic_pointer_cast<ASTStructExpressionNode>(node),  shared_from_this(), scope, irContext, irOperation);
    } else if (node->is(AST_UNARY_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getUnaryExpressionIRStrategy()->generate(std::dynamic_pointer_cast<ASTUnaryExpressionNode>(node),  shared_from_this(), scope, irContext, irOperation);
    } else if (node->is(AST_TUPLE_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getTupleExpressionIRStrategy()->generate(std::dynamic_pointer_cast<ASTTupleExpressionNode>(node),  shared_from_this(), scope, irContext, irOperation);
    } else if (node->is(AST_THIS_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getThisExpressionIRStrategy()->generate(std::dynamic_pointer_cast<ASTThisExpressionNode>(node),  shared_from_this(), scope, irContext, irOperation);
    } else if (node->is(AST_IDENTIFIER_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getIdentifierExpressionIRStrategy()->generate(std::dynamic_pointer_cast<ASTIdentifierExpressionNode>(node),  shared_from_this(), scope, irContext, irOperation);
    } else if (node->is(AST_OBJECT_ACCESS_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getObjectAccessExpressionIRStrategy()->generate(std::dynamic_pointer_cast<ASTObjectAccessExpressionNode>(node),  shared_from_this(), scope, irContext, irOperation);
    } else if (node->is(AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getObjectAccessInvocationExpressionIRStrategy()->generate(std::dynamic_pointer_cast<ASTObjectAccessInvocationExpressionNode>(node), shared_from_this(), scope, irContext, irOperation);
    } else if (node->is(AST_TUPLE_ACCESS_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getTupleAccessExpressionIRStrategy()->generate(std::dynamic_pointer_cast<ASTTupleAccessExpressionNode>(node),  shared_from_this(), scope, irContext, irOperation);
    } else if (node->is(AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getTupleAccessInvocationExpressionIRStrategy()->generate(std::dynamic_pointer_cast<ASTTupleAccessInvocationExpressionNode>(node),  shared_from_this(), scope, irContext, irOperation);
    } else if (node->is(AST_FUNCTION_INVOCATION_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getFunctionInvocationExpressionIRStrategy()->generate(std::dynamic_pointer_cast<ASTFunctionInvocationExpressionNode>(node),  shared_from_this(), scope, irContext, irOperation);
    } else if (node->is(AST_LAMBDA_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getLambdaExpressionIRStrategy()->generate(std::dynamic_pointer_cast<ASTLambdaExpressionNode>(node),  shared_from_this(), scope, irContext);
    } else if (node->is(AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getLambdaExpressionIRStrategy()->generate(std::dynamic_pointer_cast<ASTLambdaWithFatArrowExpressionNode>(node),  shared_from_this(), scope, irContext);
    } else if (node->is(AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getClassPropertyAccessExpressionIRStrategy()->generate(std::dynamic_pointer_cast<ASTClassPropertyAccessExpressionNode>(node),  shared_from_this(), scope, irContext, irOperation);
    } else if (node->is(AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getClassMethodInvocationExpressionIRStrategy()->generate(std::dynamic_pointer_cast<ASTClassMethodInvocationExpressionNode>(node),  shared_from_this(), scope, irContext, irOperation);
    } else if (node->is(AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getNewClassInstanceExpressionIRStrategy()->generate(std::dynamic_pointer_cast<ASTNewClassInstanceExpressionNode>(node),  shared_from_this(), scope, irContext, irOperation);
    } else if (node->is(AST_SHARE_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getShareExpressionIRStrategy()->generate(std::dynamic_pointer_cast<ASTShareExpressionNode>(node),  shared_from_this(), scope, irContext, irOperation);
    } else if (node->is(AST_REF_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getRefExpressionIRStrategy()->generate(std::dynamic_pointer_cast<ASTRefExpressionNode>(node),  shared_from_this(), scope, irContext, irOperation);
    } else if (node->is(AST_DREF_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getDrefExpressionIRStrategy()->generate(std::dynamic_pointer_cast<ASTDrefExpressionNode>(node),  shared_from_this(), scope, irContext, irOperation);
    } else if (node->is(AST_MODULE_ACCESS_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getModuleAccessExpressionIRStrategy()->generate(std::dynamic_pointer_cast<ASTModuleAccessExpressionNode>(node),  shared_from_this(), scope, irContext, irOperation);
    }
    throw std::logic_error("unable to generate llvm value for expression " + node->toString());
}

std::shared_ptr<IRFunctionArgumentNode> IRGenerator::generateFor(std::shared_ptr<ASTFunctionArgumentNode> node, unsigned long index, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation, std::shared_ptr<InvocableTypeSignature> invocableTypeSignature) {
    auto irExpression = this->generateFor(node->getArgument(), scope, irContext, irOperation);
    auto operation = invocableTypeSignature->isArgumentVarArg(index)
                     || invocableTypeSignature->getParameterTypes()->at(index)->isGeneric()
                     || invocableTypeSignature->isPrototype()
                    ? std::make_shared<IROperation>(IR_OPERAND_POINTER_OP)
                    : std::make_shared<IROperation>(IR_FUNCTION_ARGUMENT_OP);
    return std::make_shared<IRFunctionArgumentNode>(irExpression, operation);
}

std::shared_ptr<IRLiteralNode> IRGenerator::generateFor(std::shared_ptr<ASTLiteralNode> node, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    switch (node->getNodeType()) {
        case AST_INT_LITERAL_NODE:
            return _irStrategyMap.getIntLiteralIRStrategy()->generate(std::dynamic_pointer_cast<ASTIntLiteralNode>(node), irContext);
        case AST_FLOAT_LITERAL_NODE:
            return _irStrategyMap.getFloatLiteralIRStrategy()->generate(std::dynamic_pointer_cast<ASTFloatLiteralNode>(node), shared_from_this(), irContext);
        case AST_CHAR_LITERAL_NODE:
            return _irStrategyMap.getCharLiteralIRStrategy()->generate(std::dynamic_pointer_cast<ASTCharLiteralNode>(node), shared_from_this(), irContext);
        case AST_STRING_LITERAL_NODE:
            return _irStrategyMap.getStringLiteralIRStrategy()->generate(std::dynamic_pointer_cast<ASTStringLiteralNode>(node), shared_from_this(), irContext);
        case AST_BOOLEAN_LITERAL_NODE:
            return _irStrategyMap.getBoolLiteralIRStrategy()->generate(std::dynamic_pointer_cast<ASTBooleanLiteralNode>(node), irContext);
        default:
            throw std::logic_error("unknown literal node");
    }
}

void IRGenerator::generateInitialTypeFor(std::shared_ptr<ASTNode> node, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    if (node->is(AST_CLASS_DECLARATION_NODE)) {
        this->generateInitialTypeFor(node->getTypeSignature(), scope, irContext);
    }
}

void IRGenerator::generatePostInitialTypeFor(std::shared_ptr<ASTNode> node, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    if (node->is(AST_CLASS_DECLARATION_NODE)) {
        this->generatePostInitialTypeFor(node->getTypeSignature(), scope, irContext);
    }
}

std::shared_ptr<IRClassInstanceType> IRGenerator::getGenericClassInstanceIRType() {
    return _genericClassInstanceIRType;
}

std::shared_ptr<IRType> IRGenerator::generateInitialTypeFor(std::shared_ptr<TypeSignature> typeSignature, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    switch (typeSignature->getTypeSource()) {
        case CLASS_TYPE_SOURCE:
            return this->_irStrategyMap.getClassTypeSignatureIRStrategy()->generateInitial(std::dynamic_pointer_cast<ClassTypeSignature>(typeSignature), shared_from_this(), scope, irContext);
        default:
            return this->generateTypeFor(typeSignature, scope, irContext);
    }
}

std::shared_ptr<IRType> IRGenerator::generatePostInitialTypeFor(std::shared_ptr<TypeSignature> typeSignature, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    switch (typeSignature->getTypeSource()) {
        case CLASS_TYPE_SOURCE:
            return this->_irStrategyMap.getClassTypeSignatureIRStrategy()->generatePostInitial(std::dynamic_pointer_cast<ClassTypeSignature>(typeSignature), shared_from_this(), scope, irContext);
        default:
            return this->generateTypeFor(typeSignature, scope, irContext);
    }
}

std::shared_ptr<IRType> IRGenerator::generateTypeFor(llvm::Constant* constant) {
    return std::make_shared<IRType>(constant->getType());
}

std::shared_ptr<IRType> IRGenerator::generateTypeFor(std::shared_ptr<TypeSignature> typeSignature, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto existingIRType = scope->findType(typeSignature->getId());
    if (existingIRType) {
        return existingIRType.value()->clone();
    }
    switch (typeSignature->getTypeSource()) {
        case VOID_TYPE_SOURCE:
            return _irStrategyMap.getVoidTypeSignatureIRStrategy()->generate(shared_from_this());
        case ARRAY_TYPE_SOURCE:
            return _irStrategyMap.getArrayTypeSignatureIRStrategy()->generate(std::dynamic_pointer_cast<ArrayTypeSignature>(typeSignature), shared_from_this(), scope, irContext);
        case CLASS_TYPE_SOURCE:
            return _irStrategyMap.getClassTypeSignatureIRStrategy()->generate(std::dynamic_pointer_cast<ClassTypeSignature>(typeSignature), shared_from_this(), scope, irContext);
        case ENUM_TYPE_SOURCE:
            return _irStrategyMap.getEnumTypeSignatureIRStrategy()->generate(std::dynamic_pointer_cast<EnumTypeSignature>(typeSignature), shared_from_this(), scope, irContext);
        case ENUM_ACCESS_TYPE_SOURCE:
            return _irStrategyMap.getEnumAccessTypeSignatureIRStrategy()->generate(
                    std::dynamic_pointer_cast<EnumAccessTypeSignature>(typeSignature), shared_from_this(), scope, irContext);
        case FUNCTION_TYPE_SOURCE:
            return _irStrategyMap.getFunctionTypeSignatureIRStrategy()->generate(
                    std::dynamic_pointer_cast<FunctionTypeSignature>(typeSignature), shared_from_this(), scope, irContext);
        case PROCEDURE_TYPE_SOURCE:
            return _irStrategyMap.getProcedureTypeSignatureIRStrategy()->generate(
                    std::dynamic_pointer_cast<ProcedureTypeSignature>(typeSignature), shared_from_this(), scope, irContext);
        case LAMBDA_EXPRESSION_TYPE_SOURCE:
            return _irStrategyMap.getLambdaTypeSignatureIRStrategy()->generate(
                    std::dynamic_pointer_cast<LambdaExpressionTypeSignature>(typeSignature), shared_from_this(), scope, irContext);
        case LAMBDA_TYPE_SOURCE:
            return _irStrategyMap.getLambdaTypeSignatureIRStrategy()->generate(
                    std::dynamic_pointer_cast<LambdaTypeSignature>(typeSignature), shared_from_this(), scope, irContext);
        case INTERFACE_TYPE_SOURCE:
            return _irStrategyMap.getInterfaceTypeSignatureIRStrategy()->generate(
                    std::dynamic_pointer_cast<InterfaceTypeSignature>(typeSignature), shared_from_this(), scope, irContext);
        case STRUCT_TYPE_SOURCE:
            return _irStrategyMap.getStructTypeSignatureIRStrategy()->generate(std::dynamic_pointer_cast<StructTypeSignature>(typeSignature),
                                                                               shared_from_this(), scope, irContext);
        case TUPLE_TYPE_SOURCE:
            return _irStrategyMap.getTupleTypeSignatureIRStrategy()->generate(std::dynamic_pointer_cast<TupleTypeSignature>(typeSignature),
                                                                              shared_from_this(), scope, irContext);
        case MODULE_TYPE_SOURCE:
            return _irStrategyMap.getModuleTypeSignatureIRStrategy()->generate(std::dynamic_pointer_cast<ModuleTypeSignature>(typeSignature),
                                                                               shared_from_this(), scope, irContext);
        case POINTER_TYPE_SOURCE:
            return _irStrategyMap.getPointerTypeSignatureIRStrategy()->generate(std::dynamic_pointer_cast<PointerTypeSignature>(typeSignature),
                                                                                shared_from_this(), scope, irContext);
        case REF_TYPE_SOURCE:
            return _irStrategyMap.getRefTypeSignatureIRStrategy()->generate(std::dynamic_pointer_cast<RefTypeSignature>(typeSignature),
                                                                                shared_from_this(), scope, irContext);
        case SHARED_TYPE_SOURCE:
            return _irStrategyMap.getSharedTypeSignatureIRStrategy()->generate(std::dynamic_pointer_cast<SharedTypeSignature>(typeSignature),
                                                                            shared_from_this(), scope, irContext);
        case FUNCTION_INVOCATION_TYPE_SOURCE:
            return _irStrategyMap.getFunctionInvocationTypeSignatureIRStrategy()->generate(
                    std::dynamic_pointer_cast<FunctionInvocationTypeSignature>(typeSignature), shared_from_this(), scope, irContext);
        case CLASS_METHOD_TYPE_SOURCE:
            return _irStrategyMap.getClassMethodTypeSignatureIRStrategy()->generate(
                    std::dynamic_pointer_cast<ClassMethodTypeSignature>(typeSignature), shared_from_this(), scope, irContext);
        case CLASS_PROPERTY_TYPE_SOURCE:
            return _irStrategyMap.getClassPropertyTypeSignatureIRStrategy()->generate(
                    std::dynamic_pointer_cast<ClassPropertyTypeSignature>(typeSignature), shared_from_this(), scope, irContext);
        case NEW_CLASS_INSTANCE_TYPE_SOURCE:
            return _irStrategyMap.getNewClassInstanceTypeSignatureIRStrategy()->generate(
                    std::dynamic_pointer_cast<NewClassInstanceTypeSignature>(typeSignature), shared_from_this(), scope, irContext);
        case CLASS_INSTANCE_TYPE_SOURCE:
            return _irStrategyMap.getClassInstanceTypeSignatureIRStrategy()->generate(
                    std::dynamic_pointer_cast<ClassInstanceTypeSignature>(typeSignature), shared_from_this(), scope, irContext);
        case LAMBDA_SCOPE_TYPE_SOURCE:
            return _irStrategyMap.getLambdaScopeTypeSignatureIRStrategy()->generate(
                    std::dynamic_pointer_cast<LambdaScopeTypeSignature>(typeSignature), shared_from_this(), scope, irContext);
        case INT_LITERAL_TYPE_SOURCE:
        case FLOAT_LITERAL_TYPE_SOURCE:
        case CHAR_LITERAL_TYPE_SOURCE:
        case STRING_LITERAL_TYPE_SOURCE:
        case BOOL_LITERAL_TYPE_SOURCE:
        case LITERAL_TYPE_SOURCE:
            return _irStrategyMap.getLiteralTypeSignatureIRStrategy()->generate(std::dynamic_pointer_cast<LiteralTypeSignature>(typeSignature), shared_from_this(), scope, irContext);
        default:
            Logger::log("UH OH");
            typeSignature->print();
            throw std::logic_error("unable to generate llvm type for type-signature " + typeSignature->toString());
    }
}

std::shared_ptr<IRArrayPointerType> IRGenerator::generateTypeFor(std::shared_ptr<ArrayTypeSignature> typeSignature, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    return _irStrategyMap.getArrayTypeSignatureIRStrategy()->generate(typeSignature, shared_from_this(), scope, irContext);
}

std::shared_ptr<IREnumType> IRGenerator::generateTypeFor(std::shared_ptr<EnumTypeSignature> typeSignature, std::vector<llvm::Constant*> enumValues, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    return _irStrategyMap.getEnumTypeSignatureIRStrategy()->generate(typeSignature, enumValues, shared_from_this(), scope, irContext);
}

std::shared_ptr<IRStructType> IRGenerator::generateTypeFor(std::shared_ptr<InterfaceTypeSignature> typeSignature, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    return _irStrategyMap.getInterfaceTypeSignatureIRStrategy()->generate(typeSignature, shared_from_this(), scope, irContext);
}

std::shared_ptr<IRStructRefType> IRGenerator::generateTypeFor(std::shared_ptr<StructTypeSignature> typeSignature, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    return _irStrategyMap.getStructTypeSignatureIRStrategy()->generate(typeSignature, shared_from_this(), scope, irContext);
}

std::shared_ptr<IRStructRefType> IRGenerator::generateTypeFor(std::shared_ptr<TupleTypeSignature> typeSignature, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    return _irStrategyMap.getTupleTypeSignatureIRStrategy()->generate(typeSignature, shared_from_this(), scope, irContext);
}

std::shared_ptr<IRStructType> IRGenerator::generateTypeFor(std::shared_ptr<LambdaScopeTypeSignature> typeSignature, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    return _irStrategyMap.getLambdaScopeTypeSignatureIRStrategy()->generate(typeSignature, shared_from_this(), scope, irContext);
}

std::shared_ptr<IRModuleType> IRGenerator::generateTypeFor(std::shared_ptr<ModuleTypeSignature> typeSignature, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    return _irStrategyMap.getModuleTypeSignatureIRStrategy()->generate(typeSignature, shared_from_this(), scope, irContext);
}

std::shared_ptr<IRClassType> IRGenerator::generateTypeFor(std::shared_ptr<ClassTypeSignature> typeSignature, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    return _irStrategyMap.getClassTypeSignatureIRStrategy()->generate(typeSignature, shared_from_this(), scope, irContext);
}


std::shared_ptr<IRPointerType> IRGenerator::generateTypeFor(std::shared_ptr<PointerTypeSignature> typeSignature, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    return _irStrategyMap.getPointerTypeSignatureIRStrategy()->generate(typeSignature, shared_from_this(), scope, irContext);
}

std::shared_ptr<IRRefType> IRGenerator::generateTypeFor(std::shared_ptr<RefTypeSignature> typeSignature, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    return _irStrategyMap.getRefTypeSignatureIRStrategy()->generate(typeSignature, shared_from_this(), scope, irContext);
}

std::shared_ptr<IRSharedPtrType> IRGenerator::generateTypeFor(std::shared_ptr<SharedTypeSignature> typeSignature, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    return _irStrategyMap.getSharedTypeSignatureIRStrategy()->generate(typeSignature, shared_from_this(), scope, irContext);
}

llvm::Type* IRGenerator::getVoidType() {
    return llvm::Type::getVoidTy(*_context);
}

std::shared_ptr<IRType> IRGenerator::generateVoidType() {
    return _irStrategyMap.getVoidTypeSignatureIRStrategy()->generate(shared_from_this());
}

std::shared_ptr<IRPointerType> IRGenerator::generateIRInvocableCleanupType() {
    return this->generateIrPointerType(
        std::make_shared<IRFunctionType>(llvm::FunctionType::get(this->getVoidType(), { this->generatePointerType() }, false))
    );
}

std::shared_ptr<IRInvocableType> IRGenerator::generateIRInvocableType() {
    return std::make_shared<IRInvocableType>(
            this->getFunctionParameterType(),
            this->generateIrPointerType(),
            this->generateIRInvocableCleanupType(),
            std::make_shared<IRInvocableParameterListType>(),
            this->generateVoidType()
    );
}

std::shared_ptr<IRPointerType> IRGenerator::generateIrPointerType() {
    return std::make_shared<IRPointerType>(llvm::PointerType::get(*_context, 0));
}

std::shared_ptr<IRPointerType> IRGenerator::generateIrPointerType(std::shared_ptr<IRType> type) {
    return std::make_shared<IRPointerType>(llvm::PointerType::get(type->getType(), 0), type);
}

llvm::ConstantPointerNull* IRGenerator::generateConstantPointer() {
    return llvm::ConstantPointerNull::get(this->generatePointerType());
}

llvm::Constant* IRGenerator::generatePlaceholderTypeValueArgument() {
    return llvm::ConstantStruct::get(_typeValueType, {
            this->generateIntConstant(0),
            this->generateIntConstant(0),
            this->generateIntConstant(0),
            this->generateConstantPointer(),
            this->generateConstantPointer(),
            this->generateConstantPointer()
    });
}

llvm::Constant* IRGenerator::generatePlaceholderArrayPointerArgument() {
    return llvm::ConstantStruct::get(_arrayPointerType, {
            this->generateIntConstant(0),
            this->generateIntConstant(0),
            this->generateConstantPointer()
    });
}

llvm::Constant* IRGenerator::generatePlaceholderValueForIRType(std::shared_ptr<IRType> irType) {
    if (irType->isArrayPointerType()) {
        return this->generatePlaceholderArrayPointerArgument();
    } else if (irType->isStructRefType() || irType->isClassInstanceType() || irType->isNewClassInstanceType()) {
        return llvm::ConstantStruct::get(_structRefType, {
                this->generateConstantPointer(),
                this->generateConstantPointer()
        });
    } else if (irType->isRefType()) {
        return llvm::ConstantStruct::get(_refType, {
                this->generateConstantPointer(),
                this->generateConstantPointer()
        });
    } else if (irType->isSharedType()) {
        return llvm::ConstantStruct::get(_sharedPtrType, {
                this->generateConstantPointer(),
                this->generateConstantPointer()
        });
    } else if (irType->isInvocableType()) {
        return llvm::ConstantStruct::get(_invocableType, {
                this->generateConstantPointer(),
                this->generateConstantPointer(),
                this->generateConstantPointer(),
                this->generateConstantPointer(),
                this->generateBoolean(false)
        });
    } else if (irType->isIntegerType()) {
        return this->generateIntConstant(0);
    } else if (irType->isFloatType()) {
        return this->generateFloatConstant(0);
    } else if (irType->isCharType()) {
        return this->generateChar('a');
    } else if (irType->isBoolType()) {
        return this->generateBoolean(true);
    }
    return this->generateConstantPointer();
}

llvm::Constant* IRGenerator::generateInitialValueForIRType(std::shared_ptr<IRType> irType) {
    return llvm::Constant::getNullValue(irType->getType());
}

std::shared_ptr<IRRefType> IRGenerator::generateIrRefType(std::shared_ptr<IRType> underlyingIRType) {
    return std::make_shared<IRRefType>(_refType, std::make_shared<IRType>(this->generateIntType()), underlyingIRType);
}

std::shared_ptr<IRSharedPtrType> IRGenerator::generateIrSharedPtrType(std::shared_ptr<IRType> underlyingIRType) {
    return std::make_shared<IRSharedPtrType>(_sharedPtrType, std::make_shared<IRType>(this->generateIntType()), underlyingIRType);
}

llvm::StructType* IRGenerator::getFunctionParameterType() {
    return _invocableType;
}

std::shared_ptr<IRArrayType> IRGenerator::generateIRArrayType(std::shared_ptr<IRType> elementType, unsigned long size) {
    auto irArrayType = std::make_shared<IRArrayType>(llvm::ArrayType::get(elementType->getType(), size), elementType);
    return irArrayType;
}

std::string IRGenerator::getArrayPrototypeFunctionName(std::string id) {
    return ArrayPrototypeMap::getIRName(id);
}

std::string IRGenerator::getStringPrototypeFunctionName(std::string id) {
    return StringPrototypeMap::getIRName(id);
}

std::optional<std::string> IRGenerator::getRefPrototypeFunctionName(std::string id) {
    return RefPrototypeMap::getIRName(id);
}

std::string IRGenerator::getJetUtilsFunctionName(std::string id, unsigned long numArgs) {
    return IRUtilInternalModule::getIRName(id, numArgs);
}

std::string IRGenerator::getJetDebugFunctionName(std::string id) {
    return IRDebugInternalModule::getIRName(id);
}

std::shared_ptr<IRFunctionType> IRGenerator::generateFunctionIrType(llvm::FunctionType* functionType) {
    return std::make_shared<IRFunctionType>(functionType);
}

std::vector<llvm::Value*> IRGenerator::generateArgumentPlaceholderList(std::shared_ptr<IRFunctionType> irFunctionType, std::vector<std::shared_ptr<IRFunctionArgumentNode>>* irArguments) {
    auto pointerType = this->generatePointerType();
    auto argList = std::vector<llvm::Value*>();
    auto numArguments = irArguments->size();
    for (unsigned int i = 0; i < numArguments; ++i) {
        argList.push_back(
            this->generatePlaceholderValueForIRType(irArguments->at(i)->getArgument()->getUnderlyingIRType())
        );
    }

    return argList;
}

std::vector<llvm::Value*> IRGenerator::generateArgumentPlaceholderList(std::shared_ptr<IRInvocableType> irInvocableType, std::vector<std::shared_ptr<IRFunctionArgumentNode>>* irArguments) {
    auto pointerType = this->generatePointerType();
    auto argList = std::vector<llvm::Value*>();
    auto numArguments = irArguments->size();
    for (unsigned int i = 0; i < numArguments; ++i) {
        argList.push_back(
            this->generatePlaceholderValueForIRType(irArguments->at(i)->getArgument()->getUnderlyingIRType())
        );
    }

    // for scope argument
    argList.push_back(this->generateConstantPointer());

    return argList;
}

std::vector<llvm::Value*> IRGenerator::generateArgumentPlaceholderListForFunction(std::shared_ptr<InvocableTypeSignature> invocableTypeSignature, std::vector<std::shared_ptr<IRFunctionArgumentNode>>* irArguments, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto parameterIrTypes = this->generateIRTypes(invocableTypeSignature->getParameterTypes(), scope, irContext);
    auto argList = std::vector<llvm::Value*>();

    if (invocableTypeSignature->hasVariableLengthParameters()) {
        argList.push_back(this->generatePlaceholderArrayPointerArgument());
    }

    for (int i = 0; i < parameterIrTypes.size(); ++i) {
        auto parameterIrType = parameterIrTypes.at(i);
        if (invocableTypeSignature->getParameterTypes()->at(i)->isGeneric()) {
            argList.push_back(this->generateConstantPointer());
        } else {
            argList.push_back(this->generatePlaceholderValueForIRType(parameterIrType));
        }
    }


    if (invocableTypeSignature->hasVariableLengthParameters()) {
        for (int i = 0; i < irArguments->size(); ++i) {
            argList.push_back(this->generateConstantPointer());
        }
    }

    if (invocableTypeSignature->hasScopeArgument()) {
        argList.push_back(this->generateConstantPointer());
    }
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

std::shared_ptr<IRTypeValueInstructionNode> IRGenerator::generateIRTypeValueFor(std::shared_ptr<IRType> irType, std::shared_ptr<IRContext> irContext) {
    if (irType->isRefType()) {
        return this->_irStrategyMap.getRefTypeSignatureIRStrategy()->generateTypeValue(std::dynamic_pointer_cast<IRRefType>(irType), shared_from_this(), irContext);
    } else if (irType->isStructType()) {
        return this->_irStrategyMap.getStructTypeSignatureIRStrategy()->generateTypeValue(std::dynamic_pointer_cast<IRStructType>(irType), shared_from_this(), irContext);
    } else if (irType->isStructRefType()) {
        return this->_irStrategyMap.getStructTypeSignatureIRStrategy()->generateTypeValue(std::dynamic_pointer_cast<IRStructRefType>(irType), shared_from_this(), irContext);
    } else if (irType->isArrayPointerType()) {
        return this->_irStrategyMap.getArrayTypeSignatureIRStrategy()->generateTypeValue(std::dynamic_pointer_cast<IRArrayPointerType>(irType), shared_from_this(), irContext);
    } else if (irType->isPointerType()) {
        return this->_irStrategyMap.getPointerTypeSignatureIRStrategy()->generateTypeValue(std::dynamic_pointer_cast<IRPointerType>(irType), shared_from_this());
    }
    throw std::logic_error("unable to generate type value for ir type");
}

std::shared_ptr<IRTypeValueType> IRGenerator::generateIrTypeValueType() {
    return std::make_shared<IRTypeValueType>(_typeValueType);
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

llvm::GetElementPtrInst* IRGenerator::generateGEP(std::shared_ptr<IRType> irType, llvm::Value* pointer, unsigned long index) {
    return llvm::GetElementPtrInst::Create(irType->getType(), pointer, { this->generateIntConstant(0), this->generateIntConstant(index) });
}

llvm::ExtractValueInst* IRGenerator::generateExtractValue(llvm::Value* value, unsigned int index) {
    return llvm::ExtractValueInst::Create(value, { index });
}

llvm::StoreInst* IRGenerator::generateStoreInstruction(llvm::Value* value, llvm::Value* pointer, std::shared_ptr<IRType> irType) {
    return new llvm::StoreInst(value, pointer, false, irType->getAlignment());
}

llvm::LoadInst* IRGenerator::generateLoadInstruction(llvm::Value* pointer, std::shared_ptr<IRType> irType) {
    return new llvm::LoadInst(irType->getType(), pointer, "", false, irType->getAlignment());
}

std::shared_ptr<IRParameterListType> IRGenerator::generateParameterList(std::shared_ptr<ParameterListTypeSignature> parameterList, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::optional<std::shared_ptr<ParameterListItemTypeSignature>> scopeParameter) {
    return _irStrategyMap.getParameterListTypeSignatureIRStrategy()->generate(parameterList, shared_from_this(), scope, irContext, scopeParameter);
}

std::shared_ptr<IRParameterType> IRGenerator::generateParameterType(std::shared_ptr<ParameterListItemTypeSignature> parameter, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    return _irStrategyMap.getParameterTypeSignatureIRStrategy()->generate(parameter, shared_from_this(), scope, irContext);
}

std::vector<std::shared_ptr<IRType>> IRGenerator::generateIRTypes(std::vector<std::shared_ptr<TypeSignature>>* parameters, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto parameterIRTypes = std::vector<std::shared_ptr<IRType>>();
    for (int i = 0; i < parameters->size(); ++i) {
        parameterIRTypes.push_back(this->generateTypeFor(parameters->at(i), scope, irContext));
    }
    return parameterIRTypes;
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

llvm::ConstantInt* IRGenerator::generateIntConstant(int64_t integer) {
    return llvm::ConstantInt::get(*_context, llvm::APInt(64, integer, true));
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
    return this->_irStrategyMap.getStringLiteralIRStrategy()->generateIRString(rawString, shared_from_this(), &_context);
}

llvm::Constant* IRGenerator::getOrInsertGlobalVariableString(std::string id, std::string rawString, std::shared_ptr<IRContext> irContext) {
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

std::shared_ptr<IRArrayPointerType> IRGenerator::generateIrArrayPointerType(std::shared_ptr<IRPointerType> irPointerType) {
    auto irArrayPointerType = std::make_shared<IRArrayPointerType>(this->getArrayPointerType(), irPointerType->getSourceType());
    return irArrayPointerType;
}

std::shared_ptr<IRArrayPointerType> IRGenerator::generateIrArrayPointerType(std::shared_ptr<IRType> arrayElementType) {
    auto irArrayPointerType = std::make_shared<IRArrayPointerType>(this->getArrayPointerType(), arrayElementType);
    return irArrayPointerType;
}

std::shared_ptr<IRStructRefType> IRGenerator::generateIRStructRefType(std::shared_ptr<IRStructType> irStructType) {
    return std::make_shared<IRStructRefType>(
        this->getStructRefType(),
        this->generateIRStructRefCounterType(),
        irStructType
    );
}

std::shared_ptr<IRStructRefType> IRGenerator::generateIRStructRefType() {
    return std::make_shared<IRStructRefType>(
            this->getStructRefType(),
            this->generateIRStructRefCounterType(),
            this->generateIRStructType()
    );
}

std::shared_ptr<IRStructType> IRGenerator::generateIRStructType() {
    return std::make_shared<IRStructType>(
            llvm::StructType::get(*_context),
            std::unordered_map<std::string, unsigned long>(),
            std::unordered_map<unsigned long, std::string>(),
            std::unordered_map<std::string, std::shared_ptr<IRType>>()
    );
}

std::shared_ptr<IRInstructionNode> IRGenerator::generateFunctionParameterAllocation(std::shared_ptr<IRType> irType) {
    return std::make_shared<IRInstructionNode>(
            new llvm::AllocaInst(
                    irType->getType(),
                    AddressSpaceGenerator::generate(irType),
                    nullptr,
                    irType->getAlignment()
            ), this->generateIrPointerType(irType));
}

std::shared_ptr<IRInstructionNode> IRGenerator::generateFunctionParameterAllocation(std::shared_ptr<ASTFunctionParameterNode> functionParameter, std::shared_ptr<IRParameterType> irParameterType, std::shared_ptr<IRContext> irContext) {
    auto irType = irParameterType->getIRType();
    if (functionParameter->isCaptured()) {
        return std::make_shared<IRInstructionNode>(
            llvm::CallInst::Create(
                irContext->getIRModule()->getMallocFunction(),
                { this->generateInt64Constant(1), this->generateInt64Constant(irType->getSizeInBytes()) }
            ),
            this->generateIrPointerType(irType)
        );
    }
    return std::make_shared<IRInstructionNode>(
        new llvm::AllocaInst(
            irType->getType(),
            AddressSpaceGenerator::generate(irType),
            nullptr,
            irType->getAlignment()
        ),
        this->generateIrPointerType(irType)
    );
}

std::shared_ptr<IRType> IRGenerator::generateIRCaptureCounterType() {
    return std::make_shared<IRType>(this->generateIntType());
}

std::shared_ptr<IRType> IRGenerator::generateIRStructRefCounterType() {
    return std::make_shared<IRType>(this->generateIntType());
}

std::shared_ptr<IRType> IRGenerator::generateIRArcType() {
    return std::make_shared<IRType>(this->generateIntType());
}

std::shared_ptr<IRInstructionNode> IRGenerator::generateArcAllocationForInvocable(std::shared_ptr<IRContext> irContext, llvm::Value* source, unsigned long count) {
    auto irType = this->generateIRArcType();
    auto invocableType = this->generateIRInvocableType();
    auto ancestorValues = std::vector<llvm::Value*>();
    if (source->getType()->isPointerTy()) {
        auto pointerToArcPointer = llvm::GetElementPtrInst::Create(invocableType->getType(), source, { this->generateIntConstant(0), this->generateIntConstant(invocableType->getFunctionRefCounterIndex()) });
        ancestorValues.push_back(pointerToArcPointer);
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
        return std::make_shared<IRInstructionNode>(
                this->generateLoadInstruction(pointerToArcPointer, this->generateIrPointerType()),
                this->generateIrPointerType(irType),
                ancestorValues
        );
    } else {
        auto arcPointer = llvm::ExtractValueInst::Create(source, { invocableType->getFunctionRefCounterIndex() });
        ancestorValues.push_back(arcPointer);
        if (count > 0) {
            auto currentArcValue = this->generateLoadInstruction(arcPointer, irType);
            auto newArcValue = llvm::BinaryOperator::Create(llvm::Instruction::BinaryOps::Add, currentArcValue, this->generateIntConstant(count));
            auto setArcValue = this->generateStoreInstruction(newArcValue, arcPointer, irType);
            ancestorValues.push_back(currentArcValue);
            ancestorValues.push_back(newArcValue);
            ancestorValues.push_back(setArcValue);
        }
        return std::make_shared<IRInstructionNode>(
                arcPointer->clone(),
                this->generateIrPointerType(irType),
                ancestorValues
        );
    }
}

std::shared_ptr<IRInstructionNode> IRGenerator::generateArcAllocationForStructRef(std::shared_ptr<IRContext> irContext, llvm::Value* source, unsigned long count) {
    auto irType = this->generateIRArcType();
    auto structRefType = this->generateIRStructRefType();
    auto ancestorValues = std::vector<llvm::Value*>();
    if (source->getType()->isPointerTy()) {
        auto pointerToArcPointer = llvm::GetElementPtrInst::Create(structRefType->getType(), source, { this->generateIntConstant(0), this->generateIntConstant(structRefType->getCounterIndex()) });
        ancestorValues.push_back(pointerToArcPointer);
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
        return std::make_shared<IRInstructionNode>(
                this->generateLoadInstruction(pointerToArcPointer, this->generateIrPointerType()),
                this->generateIrPointerType(irType),
                ancestorValues
        );
    } else {
        auto arcPointer = llvm::ExtractValueInst::Create(source, { structRefType->getCounterIndex() });
        ancestorValues.push_back(arcPointer);
        if (count > 0) {
            auto currentArcValue = this->generateLoadInstruction(arcPointer, irType);
            auto newArcValue = llvm::BinaryOperator::Create(llvm::Instruction::BinaryOps::Add, currentArcValue, this->generateIntConstant(count));
            auto setArcValue = this->generateStoreInstruction(newArcValue, arcPointer, irType);
            ancestorValues.push_back(currentArcValue);
            ancestorValues.push_back(newArcValue);
            ancestorValues.push_back(setArcValue);
        }
        return std::make_shared<IRInstructionNode>(
                arcPointer->clone(),
                this->generateIrPointerType(irType),
                ancestorValues
        );
    }
}

std::shared_ptr<IRInstructionNode> IRGenerator::generateArcAllocationForRef(std::shared_ptr<IRContext> irContext, llvm::Value* source, unsigned long count) {
    auto irType = this->generateIRArcType();
    auto refType = this->generateIrRefType(irType);
    auto ancestorValues = std::vector<llvm::Value*>();
    if (source->getType()->isPointerTy()) {
        auto pointerToArcPointer = llvm::GetElementPtrInst::Create(refType->getType(), source, { this->generateIntConstant(0), this->generateIntConstant(refType->getRefCounterIndex()) });
        ancestorValues.push_back(pointerToArcPointer);
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
        return std::make_shared<IRInstructionNode>(
                this->generateLoadInstruction(pointerToArcPointer, this->generateIrPointerType()),
                this->generateIrPointerType(irType),
                ancestorValues
        );
    } else {
        auto arcPointer = llvm::ExtractValueInst::Create(source, { refType->getRefCounterIndex() });
        ancestorValues.push_back(arcPointer);
        if (count > 0) {
            auto currentArcValue = this->generateLoadInstruction(arcPointer, irType);
            auto newArcValue = llvm::BinaryOperator::Create(llvm::Instruction::BinaryOps::Add, currentArcValue, this->generateIntConstant(count));
            auto setArcValue = this->generateStoreInstruction(newArcValue, arcPointer, irType);
            ancestorValues.push_back(currentArcValue);
            ancestorValues.push_back(newArcValue);
            ancestorValues.push_back(setArcValue);
        }
        return std::make_shared<IRInstructionNode>(
                arcPointer->clone(),
                this->generateIrPointerType(irType),
                ancestorValues
        );
    }
}

std::shared_ptr<IRInstructionNode> IRGenerator::generateArcAllocation(std::shared_ptr<IRContext> irContext, std::shared_ptr<IRType> irType, llvm::Value* source, unsigned long count) {
    if (irType->isInvocableType()) {
        return this->generateArcAllocationForInvocable(irContext, source, count);
    } else if (irType->isRefType()) {
        return this->generateArcAllocationForRef(irContext, source, count);
    }
    return this->generateArcAllocationForStructRef(irContext, source, count);
}

std::shared_ptr<IRInstructionNode> IRGenerator::generateArcAllocation(std::shared_ptr<IRContext> irContext, unsigned long initialCount) {
    auto irType = this->generateIRArcType();
    auto malloc = llvm::CallInst::Create(
            irContext->getIRModule()->getMallocFunction(),
            { this->generateInt64Constant(1), this->generateInt64Constant(irType->getSizeInBytes()) }
    );
    auto captureCount = this->generateIntConstant(initialCount);
    auto storeInstruction = this->generateStoreInstruction(captureCount, malloc, irType);
    return std::make_shared<IRInstructionNode>(
            malloc,
            this->generateIrPointerType(irType),
            std::vector<llvm::Value*> {},
            std::vector<llvm::Value*> { storeInstruction }
    );
}

std::shared_ptr<IRCapturedVariableType> IRGenerator::generateIRCapturedVariableType(std::shared_ptr<IRType> variableIrType) {
    return std::make_shared<IRCapturedVariableType>(
        llvm::StructType::get(*_context, { this->generatePointerType(), this->generatePointerType() }),
        this->generateIRCaptureCounterType(),
        variableIrType
    );
}

std::shared_ptr<IRType> IRGenerator::generateIRCharType() {
    return std::make_shared<IRType>(this->generateCharType());
}

std::shared_ptr<IRArrayPointerType> IRGenerator::generateIrStringArrayPointerType() {
    auto irArrayPointerType = std::make_shared<IRArrayPointerType>(this->getArrayPointerType(), this->generateIRCharType());
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

std::shared_ptr<IRBlockNode> IRGenerator::generateFunctionBlock(llvm::Function* irFunction, std::optional<std::shared_ptr<IRLookupTable>> scope) {
    return std::make_shared<IRBlockNode>(llvm::BasicBlock::Create(*_context, "", irFunction), IR_BASIC_BT, scope.value_or(std::make_shared<IRLookupTable>()));
}

std::shared_ptr<IRBlockNode> IRGenerator::generateIfBlock(std::shared_ptr<IRContext> irContext, std::shared_ptr<IRLookupTable> scope, std::string prefix) {
    return std::make_shared<IRControlFlowBlockNode>(llvm::BasicBlock::Create(*_context, prefix + "if.cond", irContext->getFunction()), IR_IF_BT, scope);
}

std::shared_ptr<IRBlockNode> IRGenerator::generateIfThenBlock(std::shared_ptr<IRContext> irContext, std::shared_ptr<IRLookupTable> scope, std::string prefix) {
    return std::make_shared<IRControlFlowBlockNode>(llvm::BasicBlock::Create(*_context, prefix + "if.true", irContext->getFunction()), IR_IF_THEN_BT, std::make_shared<IRLookupTable>(scope));
}

std::shared_ptr<IRBlockNode> IRGenerator::generateIfElseBlock(std::shared_ptr<IRContext> irContext, std::shared_ptr<IRLookupTable> scope, std::string prefix) {
    return std::make_shared<IRControlFlowBlockNode>(llvm::BasicBlock::Create(*_context, prefix + "if.false", irContext->getFunction()), IR_IF_ELSE_BT, std::make_shared<IRLookupTable>(scope));
}

std::shared_ptr<IRBlockNode> IRGenerator::generateIfEndBlock(std::shared_ptr<IRContext> irContext, std::shared_ptr<IRLookupTable> scope, std::string prefix) {
    return std::make_shared<IRControlFlowBlockNode>(llvm::BasicBlock::Create(*_context, prefix + "if.end", irContext->getFunction()), IR_IF_END_BT, scope);
}

std::shared_ptr<IRBlockNode> IRGenerator::generateWhileConditionBlock(std::shared_ptr<IRContext> irContext, std::shared_ptr<IRLookupTable> scope, std::string prefix) {
    return std::make_shared<IRControlFlowBlockNode>(llvm::BasicBlock::Create(*_context, prefix + "while.condition", irContext->getFunction()), IR_WHILE_BT, scope);
}

std::shared_ptr<IRBlockNode> IRGenerator::generateWhileBodyBlock(std::shared_ptr<IRContext> irContext, std::shared_ptr<IRLookupTable> scope, std::string prefix) {
    return std::make_shared<IRControlFlowBlockNode>(llvm::BasicBlock::Create(*_context, prefix + "while.body", irContext->getFunction()), IR_WHILE_BODY_BT, std::make_shared<IRLookupTable>(scope));
}

std::shared_ptr<IRBlockNode> IRGenerator::generateWhileEndBlock(std::shared_ptr<IRContext> irContext, std::shared_ptr<IRLookupTable> scope, std::string prefix) {
    return std::make_shared<IRControlFlowBlockNode>(llvm::BasicBlock::Create(*_context, prefix + "while.end", irContext->getFunction()), IR_WHILE_END_BT, scope);
}

std::shared_ptr<IRBlockNode> IRGenerator::generateForLoopConditionBlock(std::shared_ptr<IRContext> irContext, std::shared_ptr<IRLookupTable> scope, std::string prefix) {
    return std::make_shared<IRControlFlowBlockNode>(llvm::BasicBlock::Create(*_context, prefix + "for.loop.condition", irContext->getFunction()), IR_FOR_LOOP_BT, scope);
}

std::shared_ptr<IRBlockNode> IRGenerator::generateForLoopBodyBlock(std::shared_ptr<IRContext> irContext, std::shared_ptr<IRLookupTable> scope, std::string prefix) {
    return std::make_shared<IRControlFlowBlockNode>(llvm::BasicBlock::Create(*_context, prefix + "for.loop.body", irContext->getFunction()), IR_FOR_LOOP_BODY_BT, std::make_shared<IRLookupTable>(scope));
}

std::shared_ptr<IRBlockNode> IRGenerator::generateForLoopEndBlock(std::shared_ptr<IRContext> irContext, std::shared_ptr<IRLookupTable> scope, std::string prefix) {
    return std::make_shared<IRControlFlowBlockNode>(llvm::BasicBlock::Create(*_context, prefix + "for.loop.end", irContext->getFunction()), IR_FOR_LOOP_END_BT, scope);
}

std::shared_ptr<IRBlockNode> IRGenerator::generateForInBlock(std::shared_ptr<IRContext> irContext, std::shared_ptr<IRLookupTable> scope, std::string prefix) {
    return std::make_shared<IRControlFlowBlockNode>(llvm::BasicBlock::Create(*_context, prefix + "for.in", irContext->getFunction()), IR_FOR_IN_BT, scope);
}

std::shared_ptr<IRBlockNode> IRGenerator::generateForInSetupBlock(std::shared_ptr<IRContext> irContext, std::shared_ptr<IRLookupTable> scope, std::string prefix) {
    return std::make_shared<IRControlFlowBlockNode>(llvm::BasicBlock::Create(*_context, prefix + "for.in.setup", irContext->getFunction()), IR_FOR_IN_SETUP_BT, std::make_shared<IRLookupTable>(scope));
}

std::shared_ptr<IRBlockNode> IRGenerator::generateForInBodyBlock(std::shared_ptr<IRContext> irContext, std::shared_ptr<IRLookupTable> scope, std::string prefix) {
    return std::make_shared<IRControlFlowBlockNode>(llvm::BasicBlock::Create(*_context, prefix + "for.in.body", irContext->getFunction()), IR_FOR_IN_BODY_BT, std::make_shared<IRLookupTable>(scope));
}

std::shared_ptr<IRBlockNode> IRGenerator::generateForInEndBlock(std::shared_ptr<IRContext> irContext, std::shared_ptr<IRLookupTable> scope, std::string prefix) {
    return std::make_shared<IRControlFlowBlockNode>(llvm::BasicBlock::Create(*_context, prefix + "for.in.end", irContext->getFunction()), IR_FOR_IN_END_BT, scope);
}

std::shared_ptr<IRBlockNode> IRGenerator::generateBasicBlock() {
    return std::make_shared<IRBlockNode>(llvm::BasicBlock::Create(*_context, "entry"), IR_BASIC_BT, std::make_shared<IRLookupTable>());
}

std::shared_ptr<IRBlockNode> IRGenerator::generateBasicBlock(std::string label, std::shared_ptr<IRContext> irContext, std::optional<std::shared_ptr<IRLookupTable>> scope) {
    return std::make_shared<IRBlockNode>(llvm::BasicBlock::Create(*_context, label, irContext->getFunction()), IR_BASIC_BT, scope.value_or(std::make_shared<IRLookupTable>()));
}

std::shared_ptr<IRContext> IRGenerator::generateContext(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRModuleNode> irModule) {
    return std::make_shared<IRContext>(irBlock, irModule, &_context);
}

std::shared_ptr<IRModuleNode> IRGenerator::generateModule(std::string moduleName) {
    return std::make_shared<IRModuleNode>(IRModuleNode(
            std::make_unique<llvm::Module>(moduleName,*_context),
            IntAddOverflowIRFunction::getIntAddOverflowIRFunctionName(),
            IntSubOverflowIRFunction::getIntSubOverflowIRFunctionName(),
            IntMultiplyOverflowIRFunction::getIntMultiplyOverflowIRFunctionName(),
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
            FreeClassPropertyIRFunction::getFreeClassPropertyIRFunctionName(),
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
            SetupRefIRFunction::getSetupRefIRFunctionName(),
            SetupRefForStructIRFunction::getSetupRefForStructIRFunctionName(),
            RefOfIRFunction::getRefOfIRFunctionName(),
            SameRefAsIRFunction::getSameRefAsIRFunctionName(),
            SetRefValueIRFunction::getSetRefValueIRFunctionName(),
            IncrementRefCountIRFunction::getIncrementRefCountIRFunctionName(),
            IncrementLambdaRefCountIRFunction::getIncrementLambdaRefCountIRFunctionName(),
            IncrementRefCountIfNecessaryIRFunction::getIncrementRefCountIfNecessaryIRFunctionName(),
            GetRefCountIRFunction::getGetRefCountIRFunctionName()
    ));
}

std::shared_ptr<IRFunctionNode> IRGenerator::generateMainFunction(std::string functionName, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto functionType = llvm::FunctionType::get(llvm::Type::getInt64Ty(*_context), {}, false);
    return std::make_shared<IRFunctionNode>(
        llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, functionName, irModuleNode->getModule()->get())
    );
}

void IRGenerator::augmentUtilInternalModule(std::shared_ptr<IRModuleNode> coreIRModule) {
    IRUtilInternalModule::augment(shared_from_this(), &_context, coreIRModule);
}

void IRGenerator::augmentDebugInternalModule(std::shared_ptr<IRModuleNode> coreIRModule) {
    IRDebugInternalModule::augment(shared_from_this(), &_context, coreIRModule);
}

std::shared_ptr<IRModuleNode> IRGenerator::generateCoreModule() {
    return IRCoreInternalModule::generate(shared_from_this(), &_context);
}

std::shared_ptr<IRInjector> IRGenerator::getInjector() {
    return _irInjector;
}