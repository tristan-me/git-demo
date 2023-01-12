// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py
// RUN: %clang_cc1 -triple thumbv8.1m.main-none-none-eabi -target-feature +mve.fp -mfloat-abi hard -fallow-half-arguments-and-returns -disable-O0-optnone -S -emit-llvm -o - %s | opt -S -mem2reg | FileCheck %s
// RUN: %clang_cc1 -triple thumbv8.1m.main-none-none-eabi -target-feature +mve.fp -mfloat-abi hard -fallow-half-arguments-and-returns -disable-O0-optnone -DPOLYMORPHIC -S -emit-llvm -o - %s | opt -S -mem2reg | FileCheck %s

// REQUIRES: aarch64-registered-target || arm-registered-target

#include <arm_mve.h>

// CHECK-LABEL: @test_vmaxq_s8(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = icmp sge <16 x i8> [[A:%.*]], [[B:%.*]]
// CHECK-NEXT:    [[TMP1:%.*]] = select <16 x i1> [[TMP0]], <16 x i8> [[A]], <16 x i8> [[B]]
// CHECK-NEXT:    ret <16 x i8> [[TMP1]]
//
int8x16_t test_vmaxq_s8(int8x16_t a, int8x16_t b)
{
#ifdef POLYMORPHIC
    return vmaxq(a, b);
#else /* POLYMORPHIC */
    return vmaxq_s8(a, b);
#endif /* POLYMORPHIC */
}

// CHECK-LABEL: @test_vmaxq_u16(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = icmp uge <8 x i16> [[A:%.*]], [[B:%.*]]
// CHECK-NEXT:    [[TMP1:%.*]] = select <8 x i1> [[TMP0]], <8 x i16> [[A]], <8 x i16> [[B]]
// CHECK-NEXT:    ret <8 x i16> [[TMP1]]
//
uint16x8_t test_vmaxq_u16(uint16x8_t a, uint16x8_t b)
{
#ifdef POLYMORPHIC
    return vmaxq(a, b);
#else /* POLYMORPHIC */
    return vmaxq_u16(a, b);
#endif /* POLYMORPHIC */
}

// CHECK-LABEL: @test_vmaxq_s32(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = icmp sge <4 x i32> [[A:%.*]], [[B:%.*]]
// CHECK-NEXT:    [[TMP1:%.*]] = select <4 x i1> [[TMP0]], <4 x i32> [[A]], <4 x i32> [[B]]
// CHECK-NEXT:    ret <4 x i32> [[TMP1]]
//
int32x4_t test_vmaxq_s32(int32x4_t a, int32x4_t b)
{
#ifdef POLYMORPHIC
    return vmaxq(a, b);
#else /* POLYMORPHIC */
    return vmaxq_s32(a, b);
#endif /* POLYMORPHIC */
}

// CHECK-LABEL: @test_vmaxq_m_u8(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = zext i16 [[P:%.*]] to i32
// CHECK-NEXT:    [[TMP1:%.*]] = call <16 x i1> @llvm.arm.mve.pred.i2v.v16i1(i32 [[TMP0]])
// CHECK-NEXT:    [[TMP2:%.*]] = call <16 x i8> @llvm.arm.mve.max.predicated.v16i8.v16i1(<16 x i8> [[A:%.*]], <16 x i8> [[B:%.*]], i32 1, <16 x i1> [[TMP1]], <16 x i8> [[INACTIVE:%.*]])
// CHECK-NEXT:    ret <16 x i8> [[TMP2]]
//
uint8x16_t test_vmaxq_m_u8(uint8x16_t inactive, uint8x16_t a, uint8x16_t b, mve_pred16_t p)
{
#ifdef POLYMORPHIC
    return vmaxq_m(inactive, a, b, p);
#else /* POLYMORPHIC */
    return vmaxq_m_u8(inactive, a, b, p);
#endif /* POLYMORPHIC */
}

// CHECK-LABEL: @test_vmaxq_m_s16(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = zext i16 [[P:%.*]] to i32
// CHECK-NEXT:    [[TMP1:%.*]] = call <8 x i1> @llvm.arm.mve.pred.i2v.v8i1(i32 [[TMP0]])
// CHECK-NEXT:    [[TMP2:%.*]] = call <8 x i16> @llvm.arm.mve.max.predicated.v8i16.v8i1(<8 x i16> [[A:%.*]], <8 x i16> [[B:%.*]], i32 0, <8 x i1> [[TMP1]], <8 x i16> [[INACTIVE:%.*]])
// CHECK-NEXT:    ret <8 x i16> [[TMP2]]
//
int16x8_t test_vmaxq_m_s16(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p)
{
#ifdef POLYMORPHIC
    return vmaxq_m(inactive, a, b, p);
#else /* POLYMORPHIC */
    return vmaxq_m_s16(inactive, a, b, p);
#endif /* POLYMORPHIC */
}

// CHECK-LABEL: @test_vmaxq_m_u32(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = zext i16 [[P:%.*]] to i32
// CHECK-NEXT:    [[TMP1:%.*]] = call <4 x i1> @llvm.arm.mve.pred.i2v.v4i1(i32 [[TMP0]])
// CHECK-NEXT:    [[TMP2:%.*]] = call <4 x i32> @llvm.arm.mve.max.predicated.v4i32.v4i1(<4 x i32> [[A:%.*]], <4 x i32> [[B:%.*]], i32 1, <4 x i1> [[TMP1]], <4 x i32> [[INACTIVE:%.*]])
// CHECK-NEXT:    ret <4 x i32> [[TMP2]]
//
uint32x4_t test_vmaxq_m_u32(uint32x4_t inactive, uint32x4_t a, uint32x4_t b, mve_pred16_t p)
{
#ifdef POLYMORPHIC
    return vmaxq_m(inactive, a, b, p);
#else /* POLYMORPHIC */
    return vmaxq_m_u32(inactive, a, b, p);
#endif /* POLYMORPHIC */
}

// CHECK-LABEL: @test_vmaxq_x_u8(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = zext i16 [[P:%.*]] to i32
// CHECK-NEXT:    [[TMP1:%.*]] = call <16 x i1> @llvm.arm.mve.pred.i2v.v16i1(i32 [[TMP0]])
// CHECK-NEXT:    [[TMP2:%.*]] = call <16 x i8> @llvm.arm.mve.max.predicated.v16i8.v16i1(<16 x i8> [[A:%.*]], <16 x i8> [[B:%.*]], i32 1, <16 x i1> [[TMP1]], <16 x i8> undef)
// CHECK-NEXT:    ret <16 x i8> [[TMP2]]
//
uint8x16_t test_vmaxq_x_u8(uint8x16_t a, uint8x16_t b, mve_pred16_t p)
{
#ifdef POLYMORPHIC
    return vmaxq_x(a, b, p);
#else /* POLYMORPHIC */
    return vmaxq_x_u8(a, b, p);
#endif /* POLYMORPHIC */
}

// CHECK-LABEL: @test_vmaxq_x_u16(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = zext i16 [[P:%.*]] to i32
// CHECK-NEXT:    [[TMP1:%.*]] = call <8 x i1> @llvm.arm.mve.pred.i2v.v8i1(i32 [[TMP0]])
// CHECK-NEXT:    [[TMP2:%.*]] = call <8 x i16> @llvm.arm.mve.max.predicated.v8i16.v8i1(<8 x i16> [[A:%.*]], <8 x i16> [[B:%.*]], i32 1, <8 x i1> [[TMP1]], <8 x i16> undef)
// CHECK-NEXT:    ret <8 x i16> [[TMP2]]
//
uint16x8_t test_vmaxq_x_u16(uint16x8_t a, uint16x8_t b, mve_pred16_t p)
{
#ifdef POLYMORPHIC
    return vmaxq_x(a, b, p);
#else /* POLYMORPHIC */
    return vmaxq_x_u16(a, b, p);
#endif /* POLYMORPHIC */
}

// CHECK-LABEL: @test_vmaxq_x_s32(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = zext i16 [[P:%.*]] to i32
// CHECK-NEXT:    [[TMP1:%.*]] = call <4 x i1> @llvm.arm.mve.pred.i2v.v4i1(i32 [[TMP0]])
// CHECK-NEXT:    [[TMP2:%.*]] = call <4 x i32> @llvm.arm.mve.max.predicated.v4i32.v4i1(<4 x i32> [[A:%.*]], <4 x i32> [[B:%.*]], i32 0, <4 x i1> [[TMP1]], <4 x i32> undef)
// CHECK-NEXT:    ret <4 x i32> [[TMP2]]
//
int32x4_t test_vmaxq_x_s32(int32x4_t a, int32x4_t b, mve_pred16_t p)
{
#ifdef POLYMORPHIC
    return vmaxq_x(a, b, p);
#else /* POLYMORPHIC */
    return vmaxq_x_s32(a, b, p);
#endif /* POLYMORPHIC */
}
