#!/bin/bash

mv libs .libs

norminette \
    | grep -v OK! \
    | grep -v INVALID_HEADER \
    | grep -v LINE_TOO_LONG \
    | grep -v PREPROC_CONSTANT \
    | grep -v TOO_MANY_FUNCS \
    | grep -v TERNARY_FBIDDEN \
    | grep -v DECL_ASSIGN_LINE \
    | grep -v TOO_MANY_LINES \
    | grep -v FORBIDDEN_CS \
    | grep -v WRONG_SCOPE_VAR \
    | grep -v TOO_MANY_VARS_FUNC \
    | grep -v FORBIDDEN_CHAR_NAME \
    | grep -v TOO_MANY_ARGS \
    | awk '
    {
        line[NR] = $0
    }
    END {
        for (i = 1; i < NR; i++) {
            if (line[i] ~ /Error!/ && line[i+1] ~ /Error!/) {
                continue
            }
            print line[i]
        }
        if (line[NR] !~ /Error!/) {
            print line[NR]
        }
    }'

mv .libs libs


