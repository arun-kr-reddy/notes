#pragma once

// ************************************************************************************************************************************************************
// preprocessor
// ************************************************************************************************************************************************************
#include <iostream>
#include <vector>

#include "NEON_2_SSE.h"

// ************************************************************************************************************************************************************
// types
// ************************************************************************************************************************************************************

// ************************************************************************************************************************************************************
// declarations
// ************************************************************************************************************************************************************

// ************************************************************************************************************************************************************
// definitions
// ************************************************************************************************************************************************************

void array_sum(int *a, int *b, int * target, int size)
{
    for (int i = 0; i < size; i += 4)
    {
        int32x4_t av = vld1q_s32(&(a[i]));
        int32x4_t bv = vld1q_s32(&(b[i]));

        int32x4_t targetv = vaddq_s32(av, bv);

        vst1q_s32(&(target[i]), targetv);
    }
}