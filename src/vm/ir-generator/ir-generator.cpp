//
// Created by Johny Georges on 2024-06-11.
//

#include "ir-generator.h"
#include "ir-strategies/literal-ir-strategies/int-literal-ir-strategy/int-literal-ir-strategy.h"
#include "ir-strategies/literal-ir-strategies/float-literal-ir-strategy/float-literal-ir-strategy.h"
#include "ir-strategies/literal-ir-strategies/char-literal-ir-strategy/char-literal-ir-strategy.h"
#include "ir-strategies/literal-ir-strategies/string-literal-ir-strategy/string-literal-ir-strategy.h"
#include "ir-strategies/literal-ir-strategies/bool-literal-ir-strategy/bool-literal-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/literal-expression-ir-strategy/literal-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/binary-expression-ir-strategy/binary-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/logical-expression-ir-strategy/logical-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/array-expression-ir-strategy/array-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/array-access-expression-ir-strategy/array-access-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/struct-expression-ir-strategy/struct-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/unary-expression-ir-strategy/unary-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/tuple-expression-ir-strategy/tuple-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/identifier-expression-ir-strategy/identifier-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/object-access-expression-ir-strategy/object-access-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/tuple-access-expression-ir-strategy/tuple-access-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/function-invocation-expression-ir-strategy/function-invocation-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/lambda-expression-ir-strategy/lambda-expression-ir-strategy.h"
#include "ir-strategies/variable-declaration-ir-strategy/variable-declaration-ir-strategy.h"
#include "ir-strategies/function-declaration-ir-strategy/function-declaration-ir-strategy.h"
#include "ir-strategies/function-parameter-list-ir-strategy/function-parameter-list-ir-strategy.h"
#include "ir-strategies/function-return-expression-ir-strategy/function-return-expression-ir-strategy.h"
#include "ir-strategies/procedure-declaration-ir-strategy/procedure-declaration-ir-strategy.h"
#include "ir-strategies/enum-declaration-ir-strategy/enum-declaration-ir-strategy.h"
#include "ir-strategies/module-declaration-ir-strategy/module-declaration-ir-strategy.h"
#include "ir-strategies/import-single-module-declaration-ir-strategy/import-single-module-declaration-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/array-type-signature-ir-strategy/array-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/literal-type-signature-ir-strategy/literal-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/class-type-signature-ir-strategy/class-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/enum-type-signature-ir-strategy/enum-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/invocable-type-signature-ir-strategies/function-type-signature-ir-strategy/function-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/invocable-type-signature-ir-strategies/lambda-type-signature-ir-strategy/lambda-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/invocable-type-signature-ir-strategies/procedure-type-signature-ir-strategy/procedure-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/parameter-list-type-signature-ir-strategy/parameter-list-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/parameter-list-type-signature-ir-strategy/parameter-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/struct-type-signature-ir-strategy/struct-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/tuple-type-signature-ir-strategy/tuple-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/enum-access-type-signature-ir-strategy/enum-access-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/module-type-signature-ir-strategy/module-type-signature-ir-strategy.h"
#include "../../core/ast/ast-nodes/ast-node-utils/ast-node-utils.h"
#include "ir-util-functions/array-access-ir-function/array-access-ir-function.h"
#include "ir-util-functions/copy-string-ir-function/copy-string-ir-function.h"
#include "../../core/ast/ast-nodes/ast-expression-nodes/ast-tuple-access-expression.h"
#include "ir-util-functions/print-ir-function/print-ir-function.h"
#include "ir-internal-modules/ir-util-internal-module/ir-util-internal-module.h"


// The IRGenerator will be responsible for programmatically generating
// vm code.
// we need to figure out how to generate vm code for an ASTNode and its
// type signature.
IRGenerator::IRGenerator(IRInjector* irInjector) {
    _context = std::make_unique<llvm::LLVMContext>();
    _irStrategyMap = IRStrategyMap();
    _irInjector = irInjector;
}

IRNode* IRGenerator::generateFor(ASTNode* node, IRLookupTable* scope, IRModuleNode* irModuleNode) {
    if (ASTNodeUtils::isDeclarationNode(node)) {
        return this->generateFor(((ASTDeclarationNode*)node), scope, irModuleNode);
    } else if (ASTNodeUtils::isStatementNode(node)) {
        return this->generateFor(((ASTStatementNode*)node), scope, irModuleNode);
    }
    throw std::logic_error("unable to generate llvm value for node " + node->toString());
}

IRStatementNode* IRGenerator::generateFor(ASTStatementNode* node, IRLookupTable* scope, IRModuleNode* irModuleNode) {
    if (node->is(AST_FUNCTION_RETURN_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getFunctionReturnExpressionIRStrategy()->generate((ASTFunctionReturnExpressionNode*)node, &_context, this, scope, irModuleNode);
    }
    throw std::logic_error("unable to generate llvm value for statement " + node->toString());
}

IRDeclarationNode* IRGenerator::generateFor(ASTDeclarationNode* node, IRLookupTable* scope, IRModuleNode* irModuleNode) {
    if (node->is(AST_VARIABLE_DECLARATION_NODE)) {
        return this->_irStrategyMap.getVariableDeclarationIRStrategy()->generate((ASTVariableDeclarationNode*)node, &_context, this, scope, irModuleNode);
    } else if (node->is(AST_FUNCTION_DECLARATION_NODE)) {
        return this->_irStrategyMap.getFunctionDeclarationIRStrategy()->generate((ASTFunctionDeclarationNode*)node, &_context, this, scope, irModuleNode);
    } else if (node->is(AST_PROCEDURE_DECLARATION_NODE)) {
        return this->_irStrategyMap.getProcedureDeclarationIRStrategy()->generate((ASTProcedureDeclarationNode*)node, &_context, this, scope, irModuleNode);
    } else if (node->is(AST_ENUM_DECLARATION_NODE)) {
        return this->_irStrategyMap.getEnumDeclarationIRStrategy()->generate((ASTEnumDeclarationNode*)node, &_context, this, scope, irModuleNode);
    } else if (node->is(AST_MODULE_DECLARATION_NODE)) {
        return this->_irStrategyMap.getModuleDeclarationIRStrategy()->generate((ASTModuleDeclarationNode*)node, &_context, this, scope, irModuleNode);
    } else if (node->is(AST_IMPORT_SINGLE_MODULE_DECLARATION_NODE)) {
        return this->_irStrategyMap.getImportSingleModuleDeclarationIRStrategy()->generate((ASTImportSingleModuleDeclarationNode*)node, &_context, this, scope, irModuleNode);
    }
    throw std::logic_error("unable to generate llvm value for declaration " + node->toString());
}

IRFunctionParameterListNode* IRGenerator::generateFor(ASTFunctionParameterListNode* node, IRLookupTable* scope, IRModuleNode* irModuleNode, llvm::Function* irFunction) {
    return this->_irStrategyMap.getFunctionParameterListIRStrategy()->generate(node, &_context, this, scope, irModuleNode, irFunction);
}

IRExpressionNode* IRGenerator::generateFor(ASTExpressionNode* node, IRLookupTable* scope, IRModuleNode* irModuleNode, IROperationType irOperationType) {
    if (node->is(AST_LITERAL_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getLiteralExpressionIRStrategy()->generate((ASTLiteralExpressionNode*)node, &_context, this, scope, irModuleNode, irOperationType);
    } else if (node->is(AST_BINARY_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getBinaryExpressionIRStrategy()->generate((ASTBinaryExpressionNode*)node, &_context, this, scope, irModuleNode, irOperationType);
    } else if (node->is(AST_LOGICAL_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getLogicalExpressionIRStrategy()->generate((ASTLogicalExpressionNode*)node, &_context, this, scope, irModuleNode, irOperationType);
    } else if (node->is(AST_ARRAY_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getArrayExpressionIRStrategy()->generate((ASTArrayExpressionNode*)node, &_context, this, scope, irModuleNode, irOperationType);
    } else if (node->is(AST_ARRAY_ACCESS_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getArrayAccessExpressionIRStrategy()->generate((ASTArrayAccessExpressionNode*)node, &_context, this, scope, irModuleNode, irOperationType);
    } else if (node->is(AST_STRUCT_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getStructExpressionIRStrategy()->generate((ASTStructExpressionNode*)node, &_context, this, scope, irModuleNode, irOperationType);
    } else if (node->is(AST_UNARY_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getUnaryExpressionIRStrategy()->generate((ASTUnaryExpressionNode*)node, &_context, this, scope, irModuleNode, irOperationType);
    } else if (node->is(AST_TUPLE_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getTupleExpressionIRStrategy()->generate((ASTTupleExpressionNode *) node, &_context, this, scope, irModuleNode, irOperationType);
    } else if (node->is(AST_IDENTIFIER_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getIdentifierExpressionIRStrategy()->generate((ASTIdentifierExpressionNode*)node, &_context, this, scope, irModuleNode, irOperationType);
    } else if (node->is(AST_OBJECT_ACCESS_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getObjectAccessExpressionIRStrategy()->generate((ASTObjectAccessExpressionNode*)node, &_context, this, scope, irModuleNode, irOperationType);
    } else if (node->is(AST_TUPLE_ACCESS_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getTupleAccessExpressionIRStrategy()->generate((ASTTupleAccessExpressionNode*)node, &_context, this, scope, irModuleNode, irOperationType);
    } else if (node->is(AST_FUNCTION_INVOCATION_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getFunctionInvocationExpressionIRStrategy()->generate((ASTFunctionInvocationExpressionNode*)node, &_context, this, scope, irModuleNode, irOperationType);
    } else if (node->is(AST_LAMBDA_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getLambdaExpressionIRStrategy()->generate((ASTLambdaExpressionNode*)node, &_context, this, scope, irModuleNode);
    }
    throw std::logic_error("unable to generate llvm value for expression " + node->toString());
}

IRExpressionNode* IRGenerator::generateFor(ASTFunctionArgumentNode* node, IRLookupTable* scope, IRModuleNode* irModuleNode, IROperationType irOperationType) {
    return this->generateFor(node->getArgument(), scope, irModuleNode, irOperationType);
}

IRLiteralNode* IRGenerator::generateFor(ASTLiteralNode* node, IRLookupTable* scope, IRModuleNode* irModuleNode) {
    switch (node->getNodeType()) {
        case AST_INT_LITERAL_NODE:
            return _irStrategyMap.getIntLiteralIRStrategy()->generate((ASTIntLiteralNode*)node, &_context);;
        case AST_FLOAT_LITERAL_NODE:
            return _irStrategyMap.getFloatLiteralIRStrategy()->generate((ASTFloatLiteralNode*)node, &_context);
        case AST_CHAR_LITERAL_NODE:
            return _irStrategyMap.getCharLiteralIRStrategy()->generate((ASTCharLiteralNode*)node, &_context);
        case AST_STRING_LITERAL_NODE:
            return _irStrategyMap.getStringLiteralIRStrategy()->generate((ASTStringLiteralNode*)node, &_context, this);
        case AST_BOOLEAN_LITERAL_NODE:
            return _irStrategyMap.getBoolLiteralIRStrategy()->generate((ASTBooleanLiteralNode*)node, &_context);
        default:
            throw std::logic_error("unknown literal node");
    }
}

IRType* IRGenerator::generateTypeFor(llvm::Constant* constant) {
    return new IRType(constant->getType());
}

IRType* IRGenerator::generateTypeFor(TypeSignature* typeSignature) {
    switch (typeSignature->getTypeSource()) {
        case VOID_TYPE_SOURCE:
            return this->generateVoidType();
        case ARRAY_TYPE_SOURCE:
            return _irStrategyMap.getArrayTypeSignatureIRStrategy()->generate((ArrayTypeSignature*)typeSignature, &_context, this);
        case CLASS_TYPE_SOURCE:
            return _irStrategyMap.getClassTypeSignatureIRStrategy()->generate((ClassTypeSignature*)typeSignature, &_context, this);
        case ENUM_TYPE_SOURCE:
            return _irStrategyMap.getEnumTypeSignatureIRStrategy()->generate((EnumTypeSignature*)typeSignature, &_context, this);
        case ENUM_ACCESS_TYPE_SOURCE:
            return _irStrategyMap.getEnumAccessTypeSignatureIRStrategy()->generate((EnumAccessTypeSignature*)typeSignature, &_context, this);
        case FUNCTION_TYPE_SOURCE:
            return _irStrategyMap.getFunctionTypeSignatureIRStrategy()->generate((FunctionTypeSignature*)typeSignature, &_context, this);
        case PROCEDURE_TYPE_SOURCE:
            return _irStrategyMap.getProcedureTypeSignatureIRStrategy()->generate((ProcedureTypeSignature*)typeSignature, &_context, this);
        case LAMBDA_EXPRESSION_TYPE_SOURCE:
            return _irStrategyMap.getLambdaTypeSignatureIRStrategy()->generate((LambdaExpressionTypeSignature*)typeSignature, &_context, this);
        case FUNCTION_LAMBDA_TYPE_SOURCE:
            return _irStrategyMap.getLambdaTypeSignatureIRStrategy()->generate((FunctionLambdaTypeSignature*)typeSignature, &_context, this);
        case PROCEDURE_LAMBDA_TYPE_SOURCE:
            return _irStrategyMap.getLambdaTypeSignatureIRStrategy()->generate((ProcedureLambdaTypeSignature*)typeSignature, &_context, this);
        case STRUCT_TYPE_SOURCE:
            return _irStrategyMap.getStructTypeSignatureIRStrategy()->generate((StructTypeSignature*)typeSignature, &_context, this);
        case TUPLE_TYPE_SOURCE:
            return _irStrategyMap.getTupleTypeSignatureIRStrategy()->generate((TupleTypeSignature*)typeSignature, &_context, this);
        case MODULE_TYPE_SOURCE:
            return _irStrategyMap.getModuleTypeSignatureIRStrategy()->generate((ModuleTypeSignature*)typeSignature, &_context, this);
        case INT_LITERAL_TYPE_SOURCE:
        case FLOAT_LITERAL_TYPE_SOURCE:
        case CHAR_LITERAL_TYPE_SOURCE:
        case STRING_LITERAL_TYPE_SOURCE:
        case BOOL_LITERAL_TYPE_SOURCE:
            return _irStrategyMap.getLiteralTypeSignatureIRStrategy()->generate((LiteralTypeSignature*)typeSignature, &_context, this);
        default:
            typeSignature->print();
            throw std::logic_error("unable to generate llvm type for type-signature " + typeSignature->toString());
    }
}

IRArrayPointerType* IRGenerator::generateTypeFor(ArrayTypeSignature* typeSignature) {
    return _irStrategyMap.getArrayTypeSignatureIRStrategy()->generate((ArrayTypeSignature*)typeSignature, &_context, this);
}

IREnumType* IRGenerator::generateTypeFor(EnumTypeSignature* typeSignature, std::vector<llvm::Constant*> enumValues) {
    return _irStrategyMap.getEnumTypeSignatureIRStrategy()->generate((EnumTypeSignature*)typeSignature, enumValues, &_context, this);
}

IRStructType* IRGenerator::generateTypeFor(StructTypeSignature* typeSignature) {
    return _irStrategyMap.getStructTypeSignatureIRStrategy()->generate((StructTypeSignature*)typeSignature, &_context, this);
}

IRStructType* IRGenerator::generateTypeFor(TupleTypeSignature* typeSignature) {
    return _irStrategyMap.getTupleTypeSignatureIRStrategy()->generate((TupleTypeSignature*)typeSignature, &_context, this);
}

IRModuleType* IRGenerator::generateTypeFor(ModuleTypeSignature* typeSignature) {
    return _irStrategyMap.getModuleTypeSignatureIRStrategy()->generate((ModuleTypeSignature*)typeSignature, &_context, this);
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

llvm::PointerType* IRGenerator::generatePointerType() {
    return llvm::PointerType::get(*_context, 0);
}

llvm::PointerType* IRGenerator::generatePointerType(llvm::Type* type) {
    return llvm::PointerType::get(type, 0);
}

llvm::IntegerType* IRGenerator::generateIntType() {
    return llvm::IntegerType::get(*_context, 32);
}

llvm::IntegerType* IRGenerator::generateCharType() {
    return llvm::IntegerType::get(*_context, 8);
}

IRParameterListType* IRGenerator::generateParameterList(ParameterListTypeSignature* parameterList) {
    return _irStrategyMap.getParameterListTypeSignatureIRStrategy()->generate(parameterList, &_context, this);
}

IRParameterType* IRGenerator::generateParameterType(ParameterListItemTypeSignature* parameter) {
    return _irStrategyMap.getParameterTypeSignatureIRStrategy()->generate(parameter, &_context, this);
}

llvm::Constant* IRGenerator::generateIntConstant(int integer) {
    return llvm::ConstantInt::get(*_context, llvm::APInt(32, integer));
}

IRArrayPointerType* IRGenerator::generateArrayPointerType(IRPointerType* irPointerType) {
    return new IRArrayPointerType(llvm::StructType::get(*_context, {
        llvm::IntegerType::get(*_context, 32),
        irPointerType->getType()
    }), irPointerType->getSourceType());
}

IRArrayPointerType* IRGenerator::generateArrayPointerType(llvm::PointerType* pointerType, IRType* arrayElementType) {
    return new IRArrayPointerType(llvm::StructType::get(*_context, {
            llvm::IntegerType::get(*_context, 32),
            pointerType
    }), arrayElementType);
}

IRBlockNode* IRGenerator::generateFunctionBlock(llvm::Function* irFunction) {
    return new IRBlockNode(llvm::BasicBlock::Create(*_context, "entry", irFunction));
}

IRBlockNode* IRGenerator::generateBasicBlock() {
    return new IRBlockNode(llvm::BasicBlock::Create(*_context, "entry"));
}

IRModuleNode* IRGenerator::generateModule(std::string moduleName) {
    return new IRModuleNode(
        new llvm::Module(moduleName, *_context),
        ArrayAccessIRFunction::getArrayAccessIRFunctionName(),
        CopyStringIRFunction::getCopyStringIRFunctionName(),
        PrintIRFunction::getPrintIRFunctionName()
    );
}

void IRGenerator::initModule(IRModuleNode* irModule) {
    ArrayAccessIRFunction::generateArrayAccessFunction(this, &_context, irModule);
    CopyStringIRFunction::generateCopyStringFunction(this, &_context, irModule);
}

IRFunctionNode* IRGenerator::generateEmptyFunction(std::string functionName, IRModuleNode* irModuleNode) {
    auto functionType = llvm::FunctionType::get(llvm::Type::getInt32Ty(*_context), {});
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