//
// Created by Johny Georges on 2024-10-12.
//

#include "print-ir-function.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"

std::string PrintIRFunction::getPrintIRFunctionName() {
    return "jet.print.i32";
}

void PrintIRFunction::generatePrintFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto printf = irModuleNode->getModule()->getOrInsertFunction("printf", llvm::FunctionType::get(llvm::Type::getInt32Ty(**context), { llvm::Type::getInt8Ty(**context) }, true));
    auto intType = irGenerator->generateIntType();
    auto functionType = llvm::FunctionType::get(intType, { intType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, PrintIRFunction::getPrintIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);


    auto intAllocation = IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(new IRType(intType)));
    // todo: implement ir-function-parameter-declaration injector strategy
    //    irGenerator->getInjector()->inject(
    //        functionBlock,
    //        new IRFunctionParameterDeclarationNode(
    //                function->getArg(0),
    //                intAllocation
    //        ),
    //        irModuleNode
    //    );
    functionBlock->getBuilder()->get()->Insert(intAllocation->getValue());
    functionBlock->getBuilder()->get()->CreateStore(function->getArg(0), intAllocation->getValue());
    auto intValue = functionBlock->getBuilder()->get()->CreateLoad(intAllocation->getAllocatedType(), intAllocation->getValue());
    auto pointerType = irGenerator->generateIrPointerType(new IRType(irGenerator->generateCharType()));
    auto arrayPointerType = irGenerator->generateArrayPointerType(pointerType);
    auto formatStringPointerAllocation = irGenerator->getInjector()->injectRawString(functionBlock, "%d", arrayPointerType, irModuleNode);
    auto pointerToFirstChar = functionBlock->getBuilder()->get()->CreateInBoundsGEP(
        arrayPointerType->getType(),
        formatStringPointerAllocation,
        { irGenerator->generateIntConstant(0),
          irGenerator->generateIntConstant(arrayPointerType->getPointerIndex())
        }
    );
    auto loadedPointerToFirstChar = functionBlock->getBuilder()->get()->CreateLoad(
        arrayPointerType->getPointerType(),
        pointerToFirstChar
    );
    functionBlock->getBuilder()->get()->CreateCall(printf, { loadedPointerToFirstChar, intValue });
    functionBlock->addVoidReturn();
}