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
// Created by Johny Georges on 2024-03-22.
//

#ifndef JETLANG_SYNTAX_ANALYZER_MODE_H
#define JETLANG_SYNTAX_ANALYZER_MODE_H
typedef enum {
    SA_NORMAL_MODE,
    SA_GROUP_MODE,
    SA_STRUCT_MODE,
    SA_STRUCT_TYPE_MODE,
    SA_LAMBDA_TYPE_PARAMETER_LIST_MODE,
    SA_FUNCTION_PARAMETER_LIST_MODE,
    SA_FUNCTION_ARGUMENT_LIST_MODE,
    SA_TYPE_PARAMETER_LIST_MODE,
    SA_ENUM_KEY_VALUE_LIST_MODE,
    SA_CONTROL_FLOW_MODE,
    SA_ARRAY_LIST_MODE,
    SA_TUPLE_LIST_MODE,
    SA_TUPLE_TYPE_MODE,
    SA_INTERFACE_MODE,
    SA_IMPLEMENTS_INTERFACE_MODE,
    SA_IMPORT_MODULE_LIST_MODE,
    SA_MODULE_LIST_MODE,
    SA_BLOCK_MODE
} SyntaxAnalyzerMode;
#endif //JETLANG_SYNTAX_ANALYZER_MODE_H
