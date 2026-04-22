//
// Created by Johny Georges on 2026-01-17.
//

#include "ir-core-internal-module.h"
#include "../../ir-util-functions/print-ir-function/print-ir-function.h"
#include "../../../../core/pre-processor/semantic-analyzer/jet-utils-type-signature-map/jet-utils-type-signature-map.h"
#include "../../ir-util-functions/copy-value-ir-function/copy-value-ir-function.h"
#include "../../ir-util-functions/copy-array-ir-function/copy-array-ir-function.h"
#include "../../ir-util-functions/copy-pointer-ir-function/copy-pointer-ir-function.h"
#include "../../ir-util-functions/copy-lambda-ir-function/copy-lambda-ir-function.h"
#include "../../ir-util-functions/copy-struct-ir-function/copy-struct-ir-function.h"
#include "../../ir-util-functions/copy-struct-ref-ir-function/copy-struct-ref-ir-function.h"
#include "../../ir-util-functions/copy-ref-ir-function/copy-ref-ir-function.h"
#include "../../ir-util-functions/equal-value-ir-function/equal-value-ir-function.h"
#include "../../ir-util-functions/equal-array-ir-function/equal-array-ir-function.h"
#include "../../ir-util-functions/equal-string-ir-function/equal-string-ir-function.h"
#include "../../ir-util-functions/equal-struct-ir-function/equal-struct-ir-function.h"
#include "../../ir-util-functions/equal-struct-ref-ir-function/equal-struct-ref-ir-function.h"
#include "../../ir-util-functions/free-value-ir-function/free-value-ir-function.h"
#include "../../ir-util-functions/equal-ref-ir-function/equal-ref-ir-function.h"
#include "../../ir-util-functions/free-array-ir-function/free-array-ir-function.h"
#include "../../ir-util-functions/free-pointer-ir-function/free-pointer-ir-function.h"
#include "../../ir-util-functions/free-lambda-ir-function/free-lambda-ir-function.h"
#include "../../ir-util-functions/free-invocable-ir-function/free-invocable-ir-function.h"
#include "../../ir-util-functions/free-struct-ir-function/free-struct-ir-function.h"
#include "../../ir-util-functions/free-struct-ref-ir-function/free-struct-ref-ir-function.h"
#include "../../ir-util-functions/free-string-ir-function/free-string-ir-function.h"
#include "../../ir-util-functions/free-ref-ir-function/free-ref-ir-function.h"
#include "../../ir-util-functions/free-captured-variable-ir-function/free-captured-variable-ir-function.h"
#include "../../ir-util-functions/array-access-ir-function/array-access-ir-function.h"
#include "../../ir-util-functions/malloc-ir-function/malloc-ir-function.h"
#include "../../ir-util-functions/malloc-free-ir-function/malloc-free-ir-function.h"
#include "../../ir-util-functions/malloc-size-ir-function/malloc-size-ir-function.h"
#include "../../ir-util-functions/memcpy-ir-function/memcpy-ir-function.h"
#include "../../ir-util-functions/increment-ref-count-ir-function/increment-ref-count-ir-function.h"
#include "../../ir-util-functions/increment-lambda-ref-count-ir-function/increment-lambda-ref-count-ir-function.h"
#include "../../ir-util-functions/ref-of-ir-function/ref-of-ir-function.h"
#include "../../ir-util-functions/sref-with-ir-function/sref-with-ir-function.h"
#include "../../ir-util-functions/same-ref-as-ir-function/same-ref-as-ir-function.h"
#include "../../ir-util-functions/setup-sref-ir-function/setup-sref-ir-function.h"
#include "../../ir-util-functions/setup-ref-ir-function/setup-ref-ir-function.h"
#include "../../ir-util-functions/setup-ref-for-struct-ir-function/setup-ref-for-struct-ir-function.h"
#include "../../ir-util-functions/copy-string-ir-function/copy-string-ir-function.h"
#include "../../ir-util-functions/string-concat-ir-function/string-concat-ir-function.h"
#include "../../ir-util-functions/array-concat-ir-function/array-concat-ir-function.h"
#include "../../ir-util-functions/array-head-ir-function/array-head-ir-function.h"
#include "../../ir-util-functions/array-last-ir-function/array-last-ir-function.h"
#include "../../ir-util-functions/array-drop-ir-function/array-drop-ir-function.h"
#include "../../ir-util-functions/array-drop-last-ir-function/array-drop-last-ir-function.h"
#include "../../ir-util-functions/array-tail-ir-function/array-tail-ir-function.h"
#include "../../ir-util-functions/array-append-ir-function/array-append-ir-function.h"
#include "../../ir-util-functions/array-prepend-ir-function/array-prepend-ir-function.h"
#include "../../ir-util-functions/array-take-ir-function/array-take-ir-function.h"
#include "../../ir-util-functions/array-take-last-ir-function/array-take-last-ir-function.h"
#include "../../ir-util-functions/array-size-ir-function/array-size-ir-function.h"
#include "../../ir-util-functions/array-empty-ir-function/array-empty-ir-function.h"
#include "../../ir-util-functions/get-ref-count-ir-function/get-ref-count-ir-function.h"
#include "../../ir-util-functions/equal-lambda-ir-function/equal-lambda-ir-function.h"
#include "../../ir-util-functions/increment-ref-count-if-necessary-ir-function/increment-ref-count-if-necessary-ir-function.h"
#include "../../ir-util-functions/set-ref-value-ir-function/set-ref-value-ir-function.h"
#include "../../ir-util-functions/free-ref-value-ir-function/free-ref-value-ir-function.h"
#include "../../ir-util-functions/string-drop-ir-function/string-drop-ir-function.h"
#include "../../ir-util-functions/string-drop-last-ir-function/string-drop-last-ir-function.h"
#include "../../ir-util-functions/string-empty-ir-function/string-empty-ir-function.h"
#include "../../ir-util-functions/string-head-ir-function/string-head-ir-function.h"
#include "../../ir-util-functions/string-last-ir-function/string-last-ir-function.h"
#include "../../ir-util-functions/string-size-ir-function/string-size-ir-function.h"
#include "../../ir-util-functions/string-tail-ir-function/string-tail-ir-function.h"
#include "../../ir-util-functions/string-take-ir-function/string-take-ir-function.h"
#include "../../ir-util-functions/string-take-last-ir-function/string-take-last-ir-function.h"
#include "../../ir-util-functions/string-at-ir-function/string-at-ir-function.h"
#include "../../ir-util-functions/string-append-ir-function/string-append-ir-function.h"
#include "../../ir-util-functions/string-prepend-ir-function/string-prepend-ir-function.h"

std::shared_ptr<IRModuleNode> IRCoreInternalModule::generate(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context) {
    auto irModule = irGenerator->generateModule("jet-core");
    new llvm::GlobalVariable(
            **irModule->getModule(),
            irGenerator->generateIntType(),
            false,
            llvm::GlobalValue::ExternalLinkage,
            irGenerator->generateIntConstant(0),
            "DEBUG_MALLOC_COUNTER"
    );
    new llvm::GlobalVariable(
            **irModule->getModule(),
            irGenerator->generateIntType(),
            false,
            llvm::GlobalValue::ExternalLinkage,
            irGenerator->generateIntConstant(0),
            "DEBUG_FREE_COUNTER"
    );
    CopyValueIRFunction::declareCopyValueFunction(irGenerator, context, irModule);
    CopyArrayIRFunction::declareCopyArrayFunction(irGenerator, context, irModule);
    CopyPointerIRFunction::declareCopyPointerFunction(irGenerator, context, irModule);
    CopyLambdaIRFunction::declareCopyLambdaFunction(irGenerator, context, irModule);
    CopyStructIRFunction::declareCopyStructFunction(irGenerator, context, irModule);
    CopyStructRefIRFunction::declareCopyStructRefFunction(irGenerator, context, irModule);
    CopyRefIRFunction::declareCopyRefFunction(irGenerator, context, irModule);
    EqualValueIRFunction::declareEqualValueFunction(irGenerator, context, irModule);
    EqualArrayIRFunction::declareEqualArrayFunction(irGenerator, context, irModule);
    EqualStringIRFunction::declareEqualStringFunction(irGenerator, context, irModule);
    EqualStructIRFunction::declareEqualStructFunction(irGenerator, context, irModule);
    EqualStructRefIRFunction::declareEqualStructRefFunction(irGenerator, context, irModule);
    EqualLambdaIRFunction::declareEqualLambdaFunction(irGenerator, context, irModule);
    EqualRefIRFunction::declareEqualRefFunction(irGenerator, context, irModule);
    EqualRefIRFunction::declareEqualRefLeftOnlyFunction(irGenerator, context, irModule);
    EqualRefIRFunction::declareEqualRefRightOnlyFunction(irGenerator, context, irModule);
    FreeValueIRFunction::declareFreeValueFunction(irGenerator, context, irModule);
    FreeArrayIRFunction::declareFreeArrayFunction(irGenerator, context, irModule);
    FreePointerIRFunction::declareFreePointerFunction(irGenerator, context, irModule);
    FreeLambdaIRFunction::declareFreeLambdaFunction(irGenerator, context, irModule);
    FreeInvocableIRFunction::declareFreeInvocableFunction(irGenerator, context, irModule);
    FreeStructIRFunction::declareFreeStructFunction(irGenerator, context, irModule);
    FreeStructRefIRFunction::declareFreeStructRefFunction(irGenerator, context, irModule);
    FreeStringIRFunction::declareFreeStringFunction(irGenerator, context, irModule);
    FreeRefIRFunction::declareFreeRefFunction(irGenerator, context, irModule);
    FreeCapturedVariableIRFunction::declareFreeCapturedVariableFunction(irGenerator, context, irModule);
    PrintIRFunction::declarePrintDebugMarkerFunction(irGenerator, context, irModule);
    PrintIRFunction::declarePrintDebugPointerFunction(irGenerator, context, irModule);
    PrintIRFunction::declarePrintDebugStringFunction(irGenerator, context, irModule);
    PrintIRFunction::declarePrintDebugRefCountFunction(irGenerator, context, irModule);
    PrintIRFunction::declarePrintWhitespaceFunction(irGenerator, context, irModule);
    PrintIRFunction::declarePrintCommaFunction(irGenerator, context, irModule);
    PrintIRFunction::declarePrintNewLineFunction(irGenerator, context, irModule);

    // generate
    ArrayAccessIRFunction::generateArrayAccessFunction(irGenerator, context, irModule);
    MallocIRFunction::generateMallocFunction(irGenerator, context, irModule);
    MallocFreeIRFunction::generateMallocFreeFunction(irGenerator, context, irModule);
    MallocSizeIRFunction::generateMallocSizeFunction(irGenerator, context, irModule);
    MemcpyIRFunction::generateMemcpyFunction(irGenerator, context, irModule);
    IncrementRefCountIRFunction::generateIncrementRefCountFunction(irGenerator, context, irModule);
    IncrementLambdaRefCountIRFunction::generateIncrementLambdaRefCountFunction(irGenerator, context, irModule);
    IncrementRefCountIfNecessaryIRFunction::generateIncrementRefCountIfNecessaryFunction(irGenerator, context, irModule);
    RefOfIRFunction::generateRefOfFunction(irGenerator, context, irModule);
    SrefWithIRFunction::generateSrefWithFunction(irGenerator, context, irModule);
    SameRefAsIRFunction::generateSameRefAsFunction(irGenerator, context, irModule);
    FreeRefValueIRFunction::generateFreeRefValueFunction(irGenerator, context, irModule);
    SetRefValueIRFunction::generateSetRefValueFunction(irGenerator, context, irModule);
    SetupSrefIRFunction::generateSetupSrefFunction(irGenerator, context, irModule);
    SetupRefIRFunction::generateSetupRefFunction(irGenerator, context, irModule);
    SetupRefForStructIRFunction::generateSetupRefForStructFunction(irGenerator, context, irModule);
    CopyValueIRFunction::generateCopyValueFunction(irGenerator, context, irModule);
    CopyArrayIRFunction::generateCopyArrayFunction(irGenerator, context, irModule);
    CopyPointerIRFunction::generateCopyPointerFunction(irGenerator, context, irModule);
    CopyLambdaIRFunction::generateCopyLambdaFunction(irGenerator, context, irModule);
    CopyStructIRFunction::generateCopyStructFunction(irGenerator, context, irModule);
    CopyStructRefIRFunction::generateCopyStructRefFunction(irGenerator, context, irModule);
    CopyStringIRFunction::generateCopyStringFunction(irGenerator, context, irModule);
    CopyRefIRFunction::generateCopyRefFunction(irGenerator, context, irModule);
    EqualValueIRFunction::generateEqualValueFunction(irGenerator, context, irModule);
    EqualArrayIRFunction::generateEqualArrayFunction(irGenerator, context, irModule);
    EqualStringIRFunction::generateEqualStringFunction(irGenerator, context, irModule);
    EqualStructIRFunction::generateEqualStructFunction(irGenerator, context, irModule);
    EqualStructRefIRFunction::generateEqualStructRefFunction(irGenerator, context, irModule);
    EqualLambdaIRFunction::generateEqualLambdaFunction(irGenerator, context, irModule);
    EqualRefIRFunction::generateEqualRefFunction(irGenerator, context, irModule);
    EqualRefIRFunction::generateEqualRefLeftOnlyFunction(irGenerator, context, irModule);
    EqualRefIRFunction::generateEqualRefRightOnlyFunction(irGenerator, context, irModule);
    FreeValueIRFunction::generateFreeValueFunction(irGenerator, context, irModule);
    FreeArrayIRFunction::generateFreeArrayFunction(irGenerator, context, irModule);
    FreePointerIRFunction::generateFreePointerFunction(irGenerator, context, irModule);
    FreeLambdaIRFunction::generateFreeLambdaFunction(irGenerator, context, irModule);
    FreeInvocableIRFunction::generateFreeInvocableFunction(irGenerator, context, irModule);
    FreeStructIRFunction::generateFreeStructFunction(irGenerator, context, irModule);
    FreeStructRefIRFunction::generateFreeStructRefFunction(irGenerator, context, irModule);
    FreeStringIRFunction::generateFreeStringFunction(irGenerator, context, irModule);
    FreeRefIRFunction::generateFreeRefFunction(irGenerator, context, irModule);
    FreeCapturedVariableIRFunction::generateFreeCapturedVariableFunction(irGenerator, context, irModule);
    PrintIRFunction::generatePrintDebugGlobals(irGenerator, context, irModule);
    PrintIRFunction::generatePrintDebugMarkerFunction(irGenerator, context, irModule);
    PrintIRFunction::generatePrintDebugPointerFunction(irGenerator, context, irModule);
    PrintIRFunction::generatePrintDebugStringFunction(irGenerator, context, irModule);
    PrintIRFunction::generatePrintDebugRefCountFunction(irGenerator, context, irModule);
    PrintIRFunction::generatePrintWhitespaceFunction(irGenerator, context, irModule);
    PrintIRFunction::generatePrintCommaFunction(irGenerator, context, irModule);
    PrintIRFunction::generatePrintNewLineFunction(irGenerator, context, irModule);
    StringConcatIRFunction::generateStringConcatFunction(irGenerator, context, irModule);
    StringDropIRFunction::generateStringDropFunction(irGenerator, context, irModule);
    StringDropLastIRFunction::generateStringDropLastFunction(irGenerator, context, irModule);
    StringEmptyIRFunction::generateStringEmptyFunction(irGenerator, context, irModule);
    StringAtIRFunction::generateStringAtFunction(irGenerator, context, irModule);
//    will support head and last once we add null support
//    StringHeadIRFunction::generateStringHeadFunction(irGenerator, context, irModule);
//    StringLastIRFunction::generateStringLastFunction(irGenerator, context, irModule);
    StringSizeIRFunction::generateStringSizeFunction(irGenerator, context, irModule);
    StringTailIRFunction::generateStringTailFunction(irGenerator, context, irModule);
    StringAppendIRFunction::generateStringAppendFunction(irGenerator, context, irModule);
    StringPrependIRFunction::generateStringPrependFunction(irGenerator, context, irModule);
    StringTakeIRFunction::generateStringTakeFunction(irGenerator, context, irModule);
    StringTakeLastIRFunction::generateStringTakeLastFunction(irGenerator, context, irModule);
    ArrayConcatIRFunction::generateArrayConcatFunction(irGenerator, context, irModule);
//    will support head and last once we add null support
//    ArrayHeadIRFunction::generateArrayHeadFunction(irGenerator, context, irModule);
//    ArrayLastIRFunction::generateArrayLastFunction(irGenerator, context, irModule);
    ArrayDropIRFunction::generateArrayDropFunction(irGenerator, context, irModule);
    ArrayDropLastIRFunction::generateArrayDropLastFunction(irGenerator, context, irModule);
    ArrayTailIRFunction::generateArrayTailFunction(irGenerator, context, irModule);
    ArrayAppendIRFunction::generateArrayAppendFunction(irGenerator, context, irModule);
    ArrayPrependIRFunction::generateArrayPrependFunction(irGenerator, context, irModule);
    ArrayTakeIRFunction::generateArrayTakeFunction(irGenerator, context, irModule);
    ArrayTakeLastIRFunction::generateArrayTakeLastFunction(irGenerator, context, irModule);
    ArraySizeIRFunction::generateArraySizeFunction(irGenerator, context, irModule);
    ArrayEmptyIRFunction::generateArrayEmptyFunction(irGenerator, context, irModule);
    GetRefCountIRFunction::generateGetRefCountFunction(irGenerator, context, irModule);
    return irModule;
}