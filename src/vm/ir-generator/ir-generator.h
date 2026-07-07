//
// Created by Johny Georges on 2024-06-11.
//

#ifndef JETLANG_IR_GENERATOR_H
#define JETLANG_IR_GENERATOR_H

#include "llvm/ADT/APSInt.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/Linker/Linker.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "../ir-lookup-table/ir-lookup-table.h"
#include "../../core/ast/ast-nodes/ast-declaration-nodes/ast-declaration-node.h"
#include "../../core/ast/ast-nodes/ast-expression-nodes/ast-expression-node.h"
#include "../../core/ast/ast-nodes/ast-literal-nodes/ast-literal-node.h"
#include "../../core/ast/ast-nodes/ast-statement-nodes/ast-statement-node.h"
#include "ir-strategies/ir-strategy-map.h"
#include "../../core/type-signature/array-type-signature/array-type-signature.h"
#include "../ir-nodes/ir-node.h"
#include "../ir-nodes/ir-expression-nodes/ir-expression-node.h"
#include "../ir-nodes/ir-literal-nodes/ir-literal-node.h"
#include "../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../ir-nodes/ir-module-node.h"
#include "../ir-nodes/ir-function-nodes/ir-function-node.h"
#include "../ir-nodes/ir-function-nodes/ir-function-parameter-list-node.h"
#include "../ir-type/ir-type.h"
#include "../ir-type/ir-parameter-type.h"
#include "../ir-type/ir-parameter-list-type.h"
#include "../ir-nodes/ir-statement-nodes/ir-statement-node.h"
#include "../ir-type/ir-struct-type.h"
#include "../../core/type-signature/enum-type-signature/enum-type-signature.h"
#include "../../core/type-signature/struct-type-signature/struct-type-signature.h"
#include "../../core/type-signature/tuple-type-signature/tuple-type-signature.h"
#include "../../core/type-signature/module-type-signature/module-type-signature.h"
#include "../../core/type-signature/class-type-signature/class-type-signature.h"
#include "../ir-type/ir-enum-type.h"
#include "../ir-type/ir-pointer-type.h"
#include "../ir-type/ir-function-type.h"
#include "../../core/type-signature/invocable-type-signature/function-type-signature/function-type-signature.h"
#include "../../core/type-signature/invocable-type-signature/procedure-type-signature/procedure-type-signature.h"
#include "../../core/type-signature/invocable-type-signature/lambda-type-signature/lambda-expression-type-signature/lambda-expression-type-signature.h"
#include "../../core/type-signature/enum-type-signature/enum-access-type-signature/enum-access-type-signature.h"
#include "../ir-type/ir-array-pointer-type.h"
#include "../ir-nodes/ir-declaration-nodes/ir-declaration-node.h"
#include "../ir-injector/ir-injector.h"
#include "../types/ir-operation-type.h"
#include "../ir-type/ir-module-type.h"
#include "../ir-type/ir-class-type.h"
#include "../../core/ast/ast-nodes/ast-function-nodes/ast-function-argument-node.h"
#include "../../core/ast/ast-nodes/ast-expression-nodes/ast-lambda-return-expression-node.h"
#include "../ir-nodes/ir-context.h"
#include "../ir-type/ir-type-value-type.h"
#include "../ir-type/ir-ref-type.h"
#include "../../core/type-signature/ref-type-signature/ref-type-signature.h"
#include "../../core/type-signature/interface-type-signature/interface-type-signature.h"
#include "../ir-nodes/ir-type-declaration-nodes/ir-type-declaration-node.h"
#include "../../core/ast/ast-nodes/ast-type-declaration-nodes/ast-type-declaration-node.h"
#include "../../core/ast/ast-nodes/ast-function-nodes/ast-function-argument-list-node.h"
#include "../ir-type/ir-array-type.h"
#include "../ir-nodes/ir-block-nodes/ir-control-flow-block-node.h"
#include "../ir-type/ir-captured-variable-type.h"
#include "../ir-type/ir-invocable-type.h"
#include "../ir-type/ir-struct-ref-type.h"
#include "../ir-nodes/ir-function-nodes/ir-function-argument-node.h"
#include "../ir-type/ir-class-instance-type.h"

class IRGenerator {
private:
    std::unique_ptr<llvm::LLVMContext> _context;
    IRStrategyMap _irStrategyMap;
    IRInjector* _irInjector;
    llvm::StructType* _arrayPointerType;
    llvm::StructType* _structRefType;
    llvm::StructType* _typeValueType;
    llvm::StructType* _refType;
    llvm::StructType* _invocableType;
    std::shared_ptr<IRClassInstanceType> _genericClassInstanceIRType;
public:
    explicit IRGenerator(IRInjector* irInjector);
    std::shared_ptr<IRNode> generateFor(std::shared_ptr<ASTNode> node, std::shared_ptr<IRLookupTable> scope, IRContext* irContext);
    void generateInitialTypeFor(std::shared_ptr<ASTNode> node, std::shared_ptr<IRLookupTable> scope, IRContext* irContext);
    void generatePostInitialTypeFor(std::shared_ptr<ASTNode> node, std::shared_ptr<IRLookupTable> scope, IRContext* irContext);
    std::shared_ptr<IRClassInstanceType> getGenericClassInstanceIRType();
    std::shared_ptr<IRStatementNode> generateFor(std::shared_ptr<ASTStatementNode> node, std::shared_ptr<IRLookupTable> scope, IRContext* irContext);
    std::shared_ptr<IRDeclarationNode> generateFor(std::shared_ptr<ASTDeclarationNode> node, std::shared_ptr<IRLookupTable> scope, IRContext* irContext);
    std::shared_ptr<IRTypeDeclarationNode> generateFor(std::shared_ptr<ASTTypeDeclarationNode> node, std::shared_ptr<IRLookupTable> scope, IRContext* irContext);
    std::shared_ptr<IRFunctionParameterListNode> generateFor(std::shared_ptr<ASTFunctionParameterListNode> node, std::shared_ptr<IRLookupTable> scope, IRContext* irContext, llvm::Function* irFunction);
    std::shared_ptr<IRExpressionNode> generateFor(std::shared_ptr<ASTExpressionNode> node, std::shared_ptr<IRLookupTable> scope, IRContext* irContext, std::shared_ptr<IROperation> irOperation);
    std::shared_ptr<IRFunctionArgumentNode> generateFor(std::shared_ptr<ASTFunctionArgumentNode> node, unsigned long index, std::shared_ptr<IRLookupTable> scope, IRContext* irContext, std::shared_ptr<IROperation> irOperation, std::shared_ptr<InvocableTypeSignature> invocableTypeSignature);
    std::shared_ptr<IRLiteralNode> generateFor(std::shared_ptr<ASTLiteralNode> node, std::shared_ptr<IRLookupTable> scope, IRContext* irContext);
    std::shared_ptr<IRType> generateInitialTypeFor(std::shared_ptr<TypeSignature> typeSignature, std::shared_ptr<IRLookupTable> scope, IRContext* irContext);
    std::shared_ptr<IRType> generatePostInitialTypeFor(std::shared_ptr<TypeSignature> typeSignature, std::shared_ptr<IRLookupTable> scope, IRContext* irContext);
    std::shared_ptr<IRType> generateTypeFor(llvm::Constant* constant);
    std::shared_ptr<IRType> generateTypeFor(std::shared_ptr<TypeSignature> typeSignature, std::shared_ptr<IRLookupTable> scope, IRContext* irContext);
    std::shared_ptr<IRArrayPointerType> generateTypeFor(std::shared_ptr<ArrayTypeSignature> typeSignature, std::shared_ptr<IRLookupTable> scope, IRContext* irContext);
    std::shared_ptr<IREnumType> generateTypeFor(std::shared_ptr<EnumTypeSignature> typeSignature, std::vector<llvm::Constant*> enumValues, std::shared_ptr<IRLookupTable> scope, IRContext* irContext);
    std::shared_ptr<IRStructType> generateTypeFor(std::shared_ptr<InterfaceTypeSignature> typeSignature, std::shared_ptr<IRLookupTable> scope, IRContext* irContext);
    std::shared_ptr<IRStructRefType> generateTypeFor(std::shared_ptr<StructTypeSignature> typeSignature, std::shared_ptr<IRLookupTable> scope, IRContext* irContext);
    std::shared_ptr<IRStructRefType> generateTypeFor(std::shared_ptr<TupleTypeSignature> typeSignature, std::shared_ptr<IRLookupTable> scope, IRContext* irContext);
    std::shared_ptr<IRStructType> generateTypeFor(std::shared_ptr<LambdaScopeTypeSignature> typeSignature, std::shared_ptr<IRLookupTable> scope, IRContext* irContext);
    std::shared_ptr<IRModuleType> generateTypeFor(std::shared_ptr<ModuleTypeSignature> typeSignature, std::shared_ptr<IRLookupTable> scope, IRContext* irContext);
    std::shared_ptr<IRClassType> generateTypeFor(std::shared_ptr<ClassTypeSignature> typeSignature, std::shared_ptr<IRLookupTable> scope, IRContext* irContext);
    std::shared_ptr<IRPointerType> generateTypeFor(std::shared_ptr<PointerTypeSignature> typeSignature, std::shared_ptr<IRLookupTable> scope, IRContext* irContext);
    std::shared_ptr<IRRefType> generateTypeFor(std::shared_ptr<RefTypeSignature> typeSignature, std::shared_ptr<IRLookupTable> scope, IRContext* irContext);
    llvm::Type* getVoidType();
    std::shared_ptr<IRType> generateVoidType();
    std::shared_ptr<IRPointerType> generateIRInvocableCleanupType();
    std::shared_ptr<IRInvocableType> generateIRInvocableType();
    std::shared_ptr<IRPointerType> generateIrPointerType();
    std::shared_ptr<IRPointerType> generateIrPointerType(std::shared_ptr<IRType> type);
    llvm::ConstantPointerNull* generateConstantPointer();
    llvm::Constant* generatePlaceholderTypeValueArgument();
    llvm::Constant* generatePlaceholderArrayPointerArgument();
    llvm::Constant* generatePlaceholderValueForIRType(std::shared_ptr<IRType> irType);
    llvm::Constant* generateInitialValueForIRType(std::shared_ptr<IRType> irType);
    std::shared_ptr<IRRefType> generateIrRefType(std::shared_ptr<IRType> type);
    llvm::StructType* getFunctionParameterType();
    std::shared_ptr<IRArrayType> generateIRArrayType(std::shared_ptr<IRType> elementType, unsigned long size);
    std::string getArrayPrototypeFunctionName(std::string id);
    std::string getStringPrototypeFunctionName(std::string id);
    std::optional<std::string> getRefPrototypeFunctionName(std::string id);
    std::string getJetUtilsFunctionName(std::string id, unsigned long numArgs);
    std::string getJetDebugFunctionName(std::string id);
    std::shared_ptr<IRFunctionType> generateFunctionIrType(llvm::FunctionType* functionType);
    std::vector<llvm::Value*> generateArgumentPlaceholderList(std::shared_ptr<IRFunctionType> irFunctionType, std::vector<std::shared_ptr<IRFunctionArgumentNode>>* irArguments);
    std::vector<llvm::Value*> generateArgumentPlaceholderList(std::shared_ptr<IRInvocableType> irInvocableType, std::vector<std::shared_ptr<IRFunctionArgumentNode>>* irArguments);
    std::vector<llvm::Value*> generateArgumentPlaceholderListForFunction(std::shared_ptr<InvocableTypeSignature> invocableTypeSignature, std::vector<std::shared_ptr<IRFunctionArgumentNode>>* irArguments, std::shared_ptr<IRLookupTable> scope, IRContext* irContext);
    llvm::PointerType* generatePointerType();
    llvm::PointerType* generatePointerType(llvm::Type* type);
    llvm::IntegerType* generateIntType();
    llvm::IntegerType* generateInt32Type();
    llvm::Type* generateFloatType();
    llvm::Type* generateDoubleType();
    llvm::Type* generateLiteralType();
    llvm::IntegerType* generateBooleanType();
    llvm::IntegerType* generateCharType();
    llvm::IntegerType* generatePointerIntType();
    std::shared_ptr<IRTypeValueInstructionNode> generateIRTypeValueFor(std::shared_ptr<IRType> irType, IRContext* irContext);
    std::shared_ptr<IRTypeValueType> generateIrTypeValueType();
    llvm::AllocaInst* generateIrTypeValueTypeAllocation();
    llvm::GetElementPtrInst* generateGEP(std::shared_ptr<IRType> irType, llvm::Value* pointer, unsigned long index);
    llvm::ExtractValueInst* generateExtractValue(llvm::Value* value, unsigned int index);
    llvm::StoreInst* generateStoreInstruction(llvm::Value* value, llvm::Value* pointer, std::shared_ptr<IRType> irType);
    llvm::LoadInst* generateLoadInstruction(llvm::Value* pointer, std::shared_ptr<IRType> irType);
    std::shared_ptr<IRParameterListType> generateParameterList(std::shared_ptr<ParameterListTypeSignature> parameterList, std::shared_ptr<IRLookupTable> scope, IRContext* irContext, std::optional<std::shared_ptr<ParameterListItemTypeSignature>> scopeParameter = {});
    std::shared_ptr<IRParameterType> generateParameterType(std::shared_ptr<ParameterListItemTypeSignature> parameter, std::shared_ptr<IRLookupTable> scope, IRContext* irContext);
    std::vector<std::shared_ptr<IRType>> generateIRTypes(std::vector<std::shared_ptr<TypeSignature>>* parameters, std::shared_ptr<IRLookupTable> scope, IRContext* irContext);
    llvm::ConstantInt* generateIntConstant(int integer);
    llvm::ConstantInt* generateIntConstant(unsigned int integer);
    llvm::ConstantInt* generateIntConstant(uint64_t integer);
    llvm::ConstantInt* generateIntConstant(int64_t integer);
    llvm::ConstantInt* generateIntConstant(unsigned long integer);
    llvm::ConstantFP* generateFloatConstant(double floatValue);
    llvm::ConstantInt* generateChar(char character);
    llvm::ConstantInt* generateBoolean(bool value);
    llvm::ConstantInt* generateInt64Constant(int integer);
    llvm::ConstantInt* generateInt64Constant(uint64_t integer);
    llvm::ConstantInt* generateInt64Constant(unsigned int integer);
    llvm::ConstantInt* generateInt64Constant(unsigned long integer);
    llvm::Constant* generateRawString(std::string rawString);
    llvm::Constant* getOrInsertGlobalVariableString(std::string id, std::string rawString, IRContext* irContext);
    std::shared_ptr<IRArrayPointerType> generateIrArrayPointerType(std::shared_ptr<IRPointerType> irPointerType);
    std::shared_ptr<IRArrayPointerType> generateIrArrayPointerType(std::shared_ptr<IRType> arrayElementType);
    std::shared_ptr<IRStructRefType> generateIRStructRefType(std::shared_ptr<IRStructType> irStructType);
    std::shared_ptr<IRStructRefType> generateIRStructRefType();
    std::shared_ptr<IRStructType> generateIRStructType();
    std::shared_ptr<IRInstructionNode> generateFunctionParameterAllocation(std::shared_ptr<IRType> irType);
    std::shared_ptr<IRInstructionNode> generateFunctionParameterAllocation(std::shared_ptr<ASTFunctionParameterNode> functionParameter, std::shared_ptr<IRParameterType> irParameterType, IRContext* irContext);
    std::shared_ptr<IRType> generateIRCaptureCounterType();
    std::shared_ptr<IRType> generateIRStructRefCounterType();
    std::shared_ptr<IRType> generateIRArcType();
    std::shared_ptr<IRInstructionNode> generateArcAllocationForInvocable(IRContext* irContext, llvm::Value* source, unsigned long count);
    std::shared_ptr<IRInstructionNode> generateArcAllocationForStructRef(IRContext* irContext, llvm::Value* source, unsigned long count);
    std::shared_ptr<IRInstructionNode> generateArcAllocationForRef(IRContext* irContext, llvm::Value* source, unsigned long count);
    std::shared_ptr<IRInstructionNode> generateArcAllocation(IRContext* irContext, std::shared_ptr<IRType> irType, llvm::Value* source, unsigned long count = 0);
    std::shared_ptr<IRInstructionNode> generateArcAllocation(IRContext* irContext, unsigned long initialCount = 0);
    std::shared_ptr<IRCapturedVariableType> generateIRCapturedVariableType(std::shared_ptr<IRType> variableIrType);
    std::shared_ptr<IRType> generateIRCharType();
    std::shared_ptr<IRArrayPointerType> generateIrStringArrayPointerType();
    llvm::StructType* generateArrayPointerType();
    llvm::StructType* getArrayPointerType();
    llvm::StructType* getStructRefType();
    std::shared_ptr<IRBlockNode> generateFunctionBlock(llvm::Function* irFunction, std::optional<std::shared_ptr<IRLookupTable>> scope = {});
    std::shared_ptr<IRBlockNode> generateIfBlock(IRContext* irContext, std::shared_ptr<IRLookupTable> scope, std::string prefix = "");
    std::shared_ptr<IRBlockNode> generateIfThenBlock(IRContext* irContext, std::shared_ptr<IRLookupTable> scope, std::string prefix = "");
    std::shared_ptr<IRBlockNode> generateIfElseBlock(IRContext* irContext, std::shared_ptr<IRLookupTable> scope, std::string prefix = "");
    std::shared_ptr<IRBlockNode> generateIfEndBlock(IRContext* irContext, std::shared_ptr<IRLookupTable> scope, std::string prefix = "");
    std::shared_ptr<IRBlockNode> generateWhileConditionBlock(IRContext* irContext, std::shared_ptr<IRLookupTable> scope, std::string prefix = "");
    std::shared_ptr<IRBlockNode> generateWhileBodyBlock(IRContext* irContext, std::shared_ptr<IRLookupTable> scope, std::string prefix = "");
    std::shared_ptr<IRBlockNode> generateWhileEndBlock(IRContext* irContext, std::shared_ptr<IRLookupTable> scope, std::string prefix = "");
    std::shared_ptr<IRBlockNode> generateForLoopConditionBlock(IRContext* irContext, std::shared_ptr<IRLookupTable> scope, std::string prefix = "");
    std::shared_ptr<IRBlockNode> generateForLoopBodyBlock(IRContext* irContext, std::shared_ptr<IRLookupTable> scope, std::string prefix = "");
    std::shared_ptr<IRBlockNode> generateForLoopEndBlock(IRContext* irContext, std::shared_ptr<IRLookupTable> scope, std::string prefix = "");
    std::shared_ptr<IRBlockNode> generateForInBlock(IRContext* irContext, std::shared_ptr<IRLookupTable> scope, std::string prefix = "");
    std::shared_ptr<IRBlockNode> generateForInSetupBlock(IRContext* irContext, std::shared_ptr<IRLookupTable> scope, std::string prefix = "");
    std::shared_ptr<IRBlockNode> generateForInBodyBlock(IRContext* irContext, std::shared_ptr<IRLookupTable> scope, std::string prefix = "");
    std::shared_ptr<IRBlockNode> generateForInEndBlock(IRContext* irContext, std::shared_ptr<IRLookupTable> scope, std::string prefix = "");
    std::shared_ptr<IRBlockNode> generateBasicBlock();
    std::shared_ptr<IRBlockNode> generateBasicBlock(std::string label, IRContext* irContext, std::optional<std::shared_ptr<IRLookupTable>> scope = {});
    IRContext* generateContext(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRModuleNode> irModule);
    std::shared_ptr<IRModuleNode> generateModule(std::string moduleName);
    std::shared_ptr<IRFunctionNode> generateMainFunction(std::string functionName, std::shared_ptr<IRModuleNode> irModuleNode);
    void augmentUtilInternalModule(std::shared_ptr<IRModuleNode> commonIRModule);
    void augmentDebugInternalModule(std::shared_ptr<IRModuleNode> commonIRModule);
    std::shared_ptr<IRModuleNode> generateCoreModule();
    IRInjector* getInjector();
};

#endif //JETLANG_IR_GENERATOR_H
