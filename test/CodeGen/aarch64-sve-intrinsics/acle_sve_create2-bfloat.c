// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py
// RUN: %clang_cc1 -triple aarch64-none-linux-gnu -target-feature +sve -target-feature +bf16 -fallow-half-arguments-and-returns -S -O1 -Werror -Wall -emit-llvm -o - %s | FileCheck %s
// RUN: %clang_cc1 -triple aarch64-none-linux-gnu -target-feature +sve -target-feature +bf16 -fallow-half-arguments-and-returns -S -O1 -Werror -Wall -emit-llvm -o - -x c++ %s | FileCheck %s -check-prefix=CPP-CHECK
// RUN: %clang_cc1 -DSVE_OVERLOADED_FORMS -triple aarch64-none-linux-gnu -target-feature +sve -target-feature +bf16 -fallow-half-arguments-and-returns -S -O1 -Werror -Wall -emit-llvm -o - %s | FileCheck %s
// RUN: %clang_cc1 -DSVE_OVERLOADED_FORMS -triple aarch64-none-linux-gnu -target-feature +sve -target-feature +bf16 -fallow-half-arguments-and-returns -S -O1 -Werror -Wall -emit-llvm -o - -x c++ %s | FileCheck %s -check-prefix=CPP-CHECK
// RUN: %clang_cc1 -triple aarch64-none-linux-gnu -target-feature +sve -fallow-half-arguments-and-returns -fsyntax-only -verify -verify-ignore-unexpected=error -verify-ignore-unexpected=note %s

// REQUIRES: aarch64-registered-target

#include <arm_sve.h>

#ifdef SVE_OVERLOADED_FORMS
// A simple used,unused... macro, long enough to represent any SVE builtin.
#define SVE_ACLE_FUNC(A1,A2_UNUSED,A3,A4_UNUSED) A1##A3
#else
#define SVE_ACLE_FUNC(A1,A2,A3,A4) A1##A2##A3##A4
#endif

// CHECK-LABEL: @test_svcreate2_bf16(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = call <vscale x 16 x bfloat> @llvm.aarch64.sve.tuple.create2.nxv16bf16.nxv8bf16(<vscale x 8 x bfloat> [[X0:%.*]], <vscale x 8 x bfloat> [[X1:%.*]])
// CHECK-NEXT:    ret <vscale x 16 x bfloat> [[TMP0]]
//
// CPP-CHECK-LABEL: @_Z19test_svcreate2_bf16u14__SVBFloat16_tu14__SVBFloat16_t(
// CPP-CHECK-NEXT:  entry:
// CPP-CHECK-NEXT:    [[TMP0:%.*]] = call <vscale x 16 x bfloat> @llvm.aarch64.sve.tuple.create2.nxv16bf16.nxv8bf16(<vscale x 8 x bfloat> [[X0:%.*]], <vscale x 8 x bfloat> [[X1:%.*]])
// CPP-CHECK-NEXT:    ret <vscale x 16 x bfloat> [[TMP0]]
//
svbfloat16x2_t test_svcreate2_bf16(svbfloat16_t x0, svbfloat16_t x1)
{
  // expected-warning@+1 {{implicit declaration of function 'svcreate2_bf16'}}
  return SVE_ACLE_FUNC(svcreate2,_bf16,,)(x0, x1);
}
