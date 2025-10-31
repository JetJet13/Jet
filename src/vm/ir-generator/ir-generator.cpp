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
#include "ir-strategies/type-signature-ir-strategies/class-instance-type-signature-ir-strategy/class-instance-type-signature-ir-strategy.h"
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
    _typeValueType = llvm::StructType::create(*_context, {
            this->generateIntType(),
            this->generateIntType(),
            this->generateIntType(),
            this->generatePointerType()
    }, "TypeValueType");
    _refType = llvm::StructType::create(*_context, {
            this->generatePointerType(),
            this->generatePointerType()
    }, "Ref");
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
    } else if (node->is(AST_BINARY_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getBinaryExpressionIRStrategy()->generate((ASTBinaryExpressionNode*)node,  this, scope, irContext, irOperation);
    } else if (node->is(AST_CONCAT_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getConcatExpressionIRStrategy()->generate((ASTConcatExpressionNode*)node,  this, scope, irContext, irOperation);
    } else if (node->is(AST_LOGICAL_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getLogicalExpressionIRStrategy()->generate((ASTLogicalExpressionNode*)node,  this, scope, irContext, irOperation);
    } else if (node->is(AST_ARRAY_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getArrayExpressionIRStrategy()->generate((ASTArrayExpressionNode*)node,  this, scope, irContext, irOperation);
    } else if (node->is(AST_ARRAY_ACCESS_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getArrayAccessExpressionIRStrategy()->generate((ASTArrayAccessExpressionNode*)node,  this, scope, irContext, irOperation);
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

IRExpressionNode* IRGenerator::generateFor(ASTFunctionArgumentNode* node, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    return this->generateFor(node->getArgument(), scope, irContext, irOperation);
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
            return this->generateVoidType();
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
        case CLASS_INSTANCE_TYPE_SOURCE:
            return _irStrategyMap.getClassInstanceTypeSignatureIRStrategy()->generate(
                    (ClassInstanceTypeSignature*) typeSignature, this, scope, irContext);
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

IRStructType* IRGenerator::generateTypeFor(StructTypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext) {
    return _irStrategyMap.getStructTypeSignatureIRStrategy()->generate(typeSignature, this, scope, irContext);
}

IRStructType* IRGenerator::generateTypeFor(TupleTypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext) {
    return _irStrategyMap.getTupleTypeSignatureIRStrategy()->generate(typeSignature, this, scope, irContext);
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

IRType* IRGenerator::generateVoidType() {
    return new IRType(llvm::Type::getVoidTy(*_context));
}

IRPointerType* IRGenerator::generateIrPointerType() {
    return new IRPointerType(llvm::PointerType::get(*_context, 0));
}

IRPointerType* IRGenerator::generateIrPointerType(IRType* type) {
    return new IRPointerType(llvm::PointerType::get(type->getType(), 0), type);
}

IRRefType* IRGenerator::generateIrRefType(IRType* underlyingIRType) {
    return new IRRefType(_refType, new IRType(this->generateIntType()), underlyingIRType);
}

IRArrayType* IRGenerator::generateIRArrayType(IRType* elementType, unsigned long size) {
    return new IRArrayType(llvm::ArrayType::get(elementType->getType(), size), elementType);
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

IRFunctionType* IRGenerator::generateFunctionIrType(llvm::FunctionType* functionType) {
    return new IRFunctionType(functionType);
}

IRArrayType* IRGenerator::generateVarArgsTypeValuesIrType(unsigned long numVarArgs) {
    return this->generateIRArrayType(this->generateIrTypeValueType(), numVarArgs);
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
    return llvm::Type::getFloatTy(*_context);
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

IRInstructionNode* IRGenerator::generateIRTypeValueFor(IRType* irType) {
    if (irType->isRefType()) {
        return this->_irStrategyMap.getRefTypeSignatureIRStrategy()->generateTypeValue((IRRefType*)irType, this);
    } else if (irType->isStructType()) {
        return this->_irStrategyMap.getStructTypeSignatureIRStrategy()->generateTypeValue((IRStructType*)irType, this);
    } else if (irType->isArrayPointerType()) {
        return this->_irStrategyMap.getArrayTypeSignatureIRStrategy()->generateTypeValue((IRArrayPointerType*)irType, this);
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

llvm::StoreInst* IRGenerator::generateStoreInstruction(llvm::Value* value, llvm::Value* pointer, IRType* irType) {
    return new llvm::StoreInst(value, pointer, false, irType->getAlignment());
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

llvm::Constant* IRGenerator::generateRawString(std::string rawString) {
    return this->_irStrategyMap.getStringLiteralIRStrategy()->generateIRString(rawString, this, &_context);
}

IRArrayPointerType* IRGenerator::generateIrArrayPointerType(IRPointerType* irPointerType) {
    return new IRArrayPointerType(this->getArrayPointerType(), irPointerType->getSourceType());
}

IRArrayPointerType* IRGenerator::generateIrArrayPointerType(IRType* arrayElementType) {
    return new IRArrayPointerType(this->getArrayPointerType(), arrayElementType);
}

IRType* IRGenerator::generateIRCharType() {
    return new IRType(this->generateCharType());
}

IRArrayPointerType* IRGenerator::generateIrStringArrayPointerType() {
    return new IRArrayPointerType(this->getArrayPointerType(), this->generateIRCharType());
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

IRBlockNode* IRGenerator::generateFunctionBlock(llvm::Function* irFunction) {
    return new IRBlockNode(llvm::BasicBlock::Create(*_context, "", irFunction));
}

IRBlockNode* IRGenerator::generateIfBlock(IRContext* irContext, std::string prefix) {
    return new IRBlockNode(llvm::BasicBlock::Create(*_context, prefix + "if.cond", irContext->getFunction()));
}

IRBlockNode* IRGenerator::generateIfThenBlock(IRContext* irContext, std::string prefix) {
    return new IRBlockNode(llvm::BasicBlock::Create(*_context, prefix + "if.true", irContext->getFunction()));
}

IRBlockNode* IRGenerator::generateIfElseBlock(IRContext* irContext, std::string prefix) {
    return new IRBlockNode(llvm::BasicBlock::Create(*_context, prefix + "if.false", irContext->getFunction()));
}

IRBlockNode* IRGenerator::generateIfEndBlock(IRContext* irContext, std::string prefix) {
    return new IRBlockNode(llvm::BasicBlock::Create(*_context, prefix + "if.end", irContext->getFunction()));
}

IRBlockNode* IRGenerator::generateWhileConditionBlock(IRContext* irContext, std::string prefix) {
    return new IRBlockNode(llvm::BasicBlock::Create(*_context, prefix + "while.condition", irContext->getFunction()));
}

IRBlockNode* IRGenerator::generateWhileBodyBlock(IRContext* irContext, std::string prefix) {
    return new IRBlockNode(llvm::BasicBlock::Create(*_context, prefix + "while.body", irContext->getFunction()));
}

IRBlockNode* IRGenerator::generateWhileEndBlock(IRContext* irContext, std::string prefix) {
    return new IRBlockNode(llvm::BasicBlock::Create(*_context, prefix + "while.end", irContext->getFunction()));
}

IRBlockNode* IRGenerator::generateForLoopConditionBlock(IRContext* irContext, std::string prefix) {
    return new IRBlockNode(llvm::BasicBlock::Create(*_context, prefix + "for.loop.condition", irContext->getFunction()));
}

IRBlockNode* IRGenerator::generateForLoopBodyBlock(IRContext* irContext, std::string prefix) {
    return new IRBlockNode(llvm::BasicBlock::Create(*_context, prefix + "for.loop.body", irContext->getFunction()));
}

IRBlockNode* IRGenerator::generateForLoopEndBlock(IRContext* irContext, std::string prefix) {
    return new IRBlockNode(llvm::BasicBlock::Create(*_context, prefix + "for.loop.end", irContext->getFunction()));
}

IRBlockNode* IRGenerator::generateForInBlock(IRContext* irContext, std::string prefix) {
    return new IRBlockNode(llvm::BasicBlock::Create(*_context, prefix + "for.in", irContext->getFunction()));
}

IRBlockNode* IRGenerator::generateForInSetupBlock(IRContext* irContext, std::string prefix) {
    return new IRBlockNode(llvm::BasicBlock::Create(*_context, prefix + "for.in.setup", irContext->getFunction()));
}

IRBlockNode* IRGenerator::generateForInBodyBlock(IRContext* irContext, std::string prefix) {
    return new IRBlockNode(llvm::BasicBlock::Create(*_context, prefix + "for.in.body", irContext->getFunction()));
}

IRBlockNode* IRGenerator::generateForInEndBlock(IRContext* irContext, std::string prefix) {
    return new IRBlockNode(llvm::BasicBlock::Create(*_context, prefix + "for.in.end", irContext->getFunction()));
}

IRBlockNode* IRGenerator::generateBasicBlock() {
    return new IRBlockNode(llvm::BasicBlock::Create(*_context, "entry"));
}

IRBlockNode* IRGenerator::generateBasicBlock(std::string label, IRContext* irContext) {
    return new IRBlockNode(llvm::BasicBlock::Create(*_context, label, irContext->getFunction()));
}

IRContext* IRGenerator::generateContext(IRBlockNode* irBlock, IRModuleNode* irModule) {
    return new IRContext(irBlock, irModule, &_context);
}

IRModuleNode* IRGenerator::generateModule(std::string moduleName) {
    return new IRModuleNode(
            new llvm::Module(moduleName,*_context),
            ArrayAccessIRFunction::getArrayAccessIRFunctionName(),
            CopyArrayIRFunction::getCopyArrayIRFunctionName(),
            CopyPointerIRFunction::getCopyPointerIRFunctionName(),
            CopyStructIRFunction::getCopyStructIRFunctionName(),
            CopyValueIRFunction::getCopyValueIRFunctionName(),
            CopyStringIRFunction::getCopyStringIRFunctionName(),
            CopyRefIRFunction::getCopyRefIRFunctionName(),
            FreeArrayIRFunction::getFreeArrayIRFunctionName(),
            FreePointerIRFunction::getFreePointerIRFunctionName(),
            FreeStructIRFunction::getFreeStructIRFunctionName(),
            FreeValueIRFunction::getFreeValueIRFunctionName(),
            FreeStringIRFunction::getFreeStringIRFunctionName(),
            FreeRefIRFunction::getFreeRefIRFunctionName(),
            PrintIRFunction::getPrintIRFunctionName(),
            PrintIRFunction::getPrintIntIRFunctionName(),
            PrintIRFunction::getPrintFloatIRFunctionName(),
            PrintIRFunction::getPrintCharIRFunctionName(),
            PrintIRFunction::getPrintBoolIRFunctionName(),
            PrintIRFunction::getPrintStringIRFunctionName(),
            PrintIRFunction::getPrintRefIRFunctionName(),
            PrintIRFunction::getPrintWhitespaceIRFunctionName(),
            PrintIRFunction::getPrintNewLineIRFunctionName(),
            PrintIRFunction::getPrintDebugMarkerIRFunctionName(),
            PrintIRFunction::getPrintDebugPointerIRFunctionName(),
            PrintIRFunction::getPrintDebugStringIRFunctionName(),
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
            EqualRefIRFunction::getEqualRefIRFunctionName(),
            EqualRefIRFunction::getEqualRefLeftOnlyIRFunctionName(),
            EqualRefIRFunction::getEqualRefRightOnlyIRFunctionName(),
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
            RefOfIRFunction::getRefOfIRFunctionName(),
            SrefWithIRFunction::getSrefWithIRFunctionName(),
            SameRefAsIRFunction::getSameRefAsIRFunctionName()
    );
}

void IRGenerator::initModule(IRModuleNode* irModule) {
    // declare (if necessary)
    CopyValueIRFunction::declareCopyValueFunction(this, &_context, irModule);
    CopyArrayIRFunction::declareCopyArrayFunction(this, &_context, irModule);
    CopyPointerIRFunction::declareCopyPointerFunction(this, &_context, irModule);
    CopyStructIRFunction::declareCopyStructFunction(this, &_context, irModule);
    CopyRefIRFunction::declareCopyRefFunction(this, &_context, irModule);
    EqualValueIRFunction::declareEqualValueFunction(this, &_context, irModule);
    EqualArrayIRFunction::declareEqualArrayFunction(this, &_context, irModule);
    EqualStringIRFunction::declareEqualStringFunction(this, &_context, irModule);
    EqualStructIRFunction::declareEqualStructFunction(this, &_context, irModule);
    EqualRefIRFunction::declareEqualRefFunction(this, &_context, irModule);
    EqualRefIRFunction::declareEqualRefLeftOnlyFunction(this, &_context, irModule);
    EqualRefIRFunction::declareEqualRefRightOnlyFunction(this, &_context, irModule);
    FreeValueIRFunction::declareFreeValueFunction(this, &_context, irModule);
    FreeArrayIRFunction::declareFreeArrayFunction(this, &_context, irModule);
    FreePointerIRFunction::declareFreePointerFunction(this, &_context, irModule);
    FreeStructIRFunction::declareFreeStructFunction(this, &_context, irModule);
    FreeStringIRFunction::declareFreeStringFunction(this, &_context, irModule);
    FreeRefIRFunction::declareFreeRefFunction(this, &_context, irModule);
    PrintIRFunction::declarePrintDebugMarkerFunction(this, &_context, irModule);
    PrintIRFunction::declarePrintDebugPointerFunction(this, &_context, irModule);
    PrintIRFunction::declarePrintDebugStringFunction(this, &_context, irModule);
    PrintIRFunction::declarePrintWhitespaceFunction(this, &_context, irModule);
    PrintIRFunction::declarePrintNewLineFunction(this, &_context, irModule);

    // generate
    ArrayAccessIRFunction::generateArrayAccessFunction(this, &_context, irModule);
    MallocIRFunction::generateMallocFunction(this, &_context, irModule);
    MallocFreeIRFunction::generateMallocFreeFunction(this, &_context, irModule);
    MallocSizeIRFunction::generateMallocSizeFunction(this, &_context, irModule);
    MemcpyIRFunction::generateMemcpyFunction(this, &_context, irModule);
    RefOfIRFunction::generateRefOfFunction(this, &_context, irModule);
    SrefWithIRFunction::generateSrefWithFunction(this, &_context, irModule);
    SameRefAsIRFunction::generateSameRefAsFunction(this, &_context, irModule);
    SetupSrefIRFunction::generateSetupSrefFunction(this, &_context, irModule);
    SetupRefIRFunction::generateSetupRefFunction(this, &_context, irModule);
    CopyValueIRFunction::generateCopyValueFunction(this, &_context, irModule);
    CopyArrayIRFunction::generateCopyArrayFunction(this, &_context, irModule);
    CopyPointerIRFunction::generateCopyPointerFunction(this, &_context, irModule);
    CopyStructIRFunction::generateCopyStructFunction(this, &_context, irModule);
    CopyStringIRFunction::generateCopyStringFunction(this, &_context, irModule);
    CopyRefIRFunction::generateCopyRefFunction(this, &_context, irModule);
    EqualValueIRFunction::generateEqualValueFunction(this, &_context, irModule);
    EqualArrayIRFunction::generateEqualArrayFunction(this, &_context, irModule);
    EqualStringIRFunction::generateEqualStringFunction(this, &_context, irModule);
    EqualStructIRFunction::generateEqualStructFunction(this, &_context, irModule);
    EqualRefIRFunction::generateEqualRefFunction(this, &_context, irModule);
    EqualRefIRFunction::generateEqualRefLeftOnlyFunction(this, &_context, irModule);
    EqualRefIRFunction::generateEqualRefRightOnlyFunction(this, &_context, irModule);
    FreeValueIRFunction::generateFreeValueFunction(this, &_context, irModule);
    FreeArrayIRFunction::generateFreeArrayFunction(this, &_context, irModule);
    FreePointerIRFunction::generateFreePointerFunction(this, &_context, irModule);
    FreeStructIRFunction::generateFreeStructFunction(this, &_context, irModule);
    FreeStringIRFunction::generateFreeStringFunction(this, &_context, irModule);
    FreeRefIRFunction::generateFreeRefFunction(this, &_context, irModule);
    ArrayConcatIRFunction::generateArrayConcatFunction(this, &_context, irModule);
    ArrayHeadIRFunction::generateArrayHeadFunction(this, &_context, irModule);
    ArrayLastIRFunction::generateArrayLastFunction(this, &_context, irModule);
    ArrayDropIRFunction::generateArrayDropFunction(this, &_context, irModule);
    ArrayDropLastIRFunction::generateArrayDropLastFunction(this, &_context, irModule);
    ArrayTailIRFunction::generateArrayTailFunction(this, &_context, irModule);
    ArrayAppendIRFunction::generateArrayAppendFunction(this, &_context, irModule);
    ArrayPrependIRFunction::generateArrayPrependFunction(this, &_context, irModule);
    ArrayTakeIRFunction::generateArrayTakeFunction(this, &_context, irModule);
    ArrayTakeLastIRFunction::generateArrayTakeLastFunction(this, &_context, irModule);
    ArraySizeIRFunction::generateArraySizeFunction(this, &_context, irModule);
    ArrayEmptyIRFunction::generateArrayEmptyFunction(this, &_context, irModule);
}

IRFunctionNode* IRGenerator::generateMainFunction(std::string functionName, IRModuleNode* irModuleNode) {
    auto functionType = llvm::FunctionType::get(llvm::Type::getInt64Ty(*_context), {}, false);
    return new IRFunctionNode(
        llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, functionName, irModuleNode->getModule())
    );
}

IRModuleNode* IRGenerator::generateUtilInternalModule() {
    return IRUtilInternalModule::generate(this, &_context);
}

IRInjector* IRGenerator::getInjector() {
    return _irInjector;
}