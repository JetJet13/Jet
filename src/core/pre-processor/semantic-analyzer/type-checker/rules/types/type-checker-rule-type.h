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
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_TYPE_CHECKER_RULE_TYPE_H
#define JETLANG_TYPE_CHECKER_RULE_TYPE_H

typedef enum {
    REQUIRED_RETURN_EXPRESSION_TCR,
    ALL_PATHS_RETURN_TCR,
    NO_RETURN_EXPRESSION_TCR,
    DREF_TYPE_SIGNATURE_TCR,
    REF_TYPE_SIGNATURE_TCR,
    SHARED_TYPE_SIGNATURE_TCR,
    SHARED_VALUE_ASSIGNMENT_TCR,
    DEFINED_TYPE_SIGNATURE_TCR,
    TYPE_SIGNATURE_MISMATCH_TCR,
    ITERABLE_TYPE_SIGNATURE_TCR,
    INVOCABLE_TYPE_SIGNATURE_TCR,
    UNIQUE_SCOPED_NAMES_TCR,
    UNIQUE_TYPE_SIGNATURE_KEYS_TCR,
    UNIQUE_TYPE_SIGNATURE_WITH_ID_TCR,
    UNIQUE_TYPE_SIGNATURES_TCR,
    RETURN_TYPE_SIGNATURE_TCR,
    MATCH_ARGUMENT_LIST_COUNT_WITH_PARAMETER_LIST_COUNT_TCR,
    ARGUMENT_LIST_TYPE_SIGNATURE_MISMATCH_TCR,
    CLASS_SELF_REFERENCE_TCR,
    CLASS_CIRCULAR_REFERENCE_TCR
} TypeCheckerRuleType;

#endif //JETLANG_TYPE_CHECKER_RULE_TYPE_H
