// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2024-10-21.
//

#include "ir-util-internal-module.h"
#include "../../ir-util-functions/print-ir-function/print-ir-function.h"
#include "../../ir-util-functions/range-ir-function/range-ir-function.h"
#include "../../../../core/pre-processor/semantic-analyzer/jet-utils-type-signature-map/jet-utils-type-signature-map.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../ir-util-functions/assert-ir-function/assert-ir-function.h"

void IRUtilInternalModule::augment(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> coreIrModule) {
    PrintIRFunction::generatePrintGlobals(irGenerator, context, coreIrModule);
    PrintIRFunction::declarePrintRefFunction(irGenerator, context, coreIrModule);
    PrintIRFunction::declarePrintArrayFunction(irGenerator, context, coreIrModule);
    PrintIRFunction::declarePrintStructFunction(irGenerator, context, coreIrModule);
    PrintIRFunction::declarePrintStructRefFunction(irGenerator, context, coreIrModule);

    PrintIRFunction::generatePrintIntFunction(irGenerator, context, coreIrModule);
    PrintIRFunction::generatePrintFloatFunction(irGenerator, context, coreIrModule);
    PrintIRFunction::generatePrintCharFunction(irGenerator, context, coreIrModule);
    PrintIRFunction::generatePrintBoolFunction(irGenerator, context, coreIrModule);
    PrintIRFunction::generatePrintStringFunction(irGenerator, context, coreIrModule);
    PrintIRFunction::generatePrintLambdaFunction(irGenerator, context, coreIrModule);
    PrintIRFunction::generatePrintRefFunction(irGenerator, context, coreIrModule);
    PrintIRFunction::generatePrintArrayFunction(irGenerator, context, coreIrModule);
    PrintIRFunction::generatePrintStructFunction(irGenerator, context, coreIrModule);
    PrintIRFunction::generatePrintStructRefFunction(irGenerator, context, coreIrModule);
    PrintIRFunction::generatePrintFunction(irGenerator, context, coreIrModule);
    RangeIRFunction::generateRange3pFunction(irGenerator, context, coreIrModule);
    RangeIRFunction::generateRange2pFunction(irGenerator, context, coreIrModule);
    RangeIRFunction::generateRange1pFunction(irGenerator, context, coreIrModule);
    AssertIRFunction::generateAssertGlobals(irGenerator, context, coreIrModule);
    AssertIRFunction::generateAssertFunction(irGenerator, context, coreIrModule);
    AssertIRFunction::generateAssertWithMessageFunction(irGenerator, context, coreIrModule);
}

std::string IRUtilInternalModule::getIRName(std::string id, uint64_t numArgs) {
    if (id == JetUtilsTypeSignatureMap::getPrintTypeSignatureKey()) {
        return PrintIRFunction::getPrintIRFunctionName();
    }

    if (id == JetUtilsTypeSignatureMap::getRangeTypeSignatureKey()) {
        if (numArgs == 1) {
            return RangeIRFunction::getRange1pIRFunctionName();
        } else if (numArgs == 2) {
            return RangeIRFunction::getRange2pIRFunctionName();
        } else if (numArgs == 3) {
            return RangeIRFunction::getRange3pIRFunctionName();
        }
    }

    if (id == JetUtilsTypeSignatureMap::getAssertTypeSignatureKey()) {
        if (numArgs == 1) {
            return AssertIRFunction::getAssertIRFunctionName();
        } else if (numArgs == 2) {
            return AssertIRFunction::getAssertWithMessageIRFunctionName();
        }
    }
    throw std::logic_error("unable to find util internal function name");
}