//
// Created by Johny Georges on 2026-05-30.
//

#ifndef JETLANG_SYNTAX_ANALYZER_MODE_UTILS_H
#define JETLANG_SYNTAX_ANALYZER_MODE_UTILS_H

#include "../types/syntax-analyzer-mode.h"

namespace SyntaxAnalyzerModeUtils {

    static bool isTypeMode(SyntaxAnalyzerMode mode) {
        switch (mode) {
            case SA_STRUCT_TYPE_MODE:
            case SA_TUPLE_TYPE_MODE:
            case SA_TYPE_PARAMETER_LIST_MODE:
            case SA_LAMBDA_TYPE_PARAMETER_LIST_MODE:
            case SA_INTERFACE_MODE:
                return true;
            default:
                return false;
        }
    }
}

#endif //JETLANG_SYNTAX_ANALYZER_MODE_UTILS_H
