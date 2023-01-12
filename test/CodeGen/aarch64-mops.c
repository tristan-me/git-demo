// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py

// RUN: %clang_cc1 -triple aarch64-arm-unknown-eabi -target-feature +mops -target-feature +mte -S -emit-llvm -o - %s  | FileCheck %s

#define __ARM_FEATURE_MOPS 1
#include <arm_acle.h>
#include <stddef.h>

// CHECK-LABEL: @bzero_0(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[DST_ADDR:%.*]] = alloca i8*, align 8
// CHECK-NEXT:    store i8* [[DST:%.*]], i8** [[DST_ADDR]], align 8
// CHECK-NEXT:    [[TMP0:%.*]] = load i8*, i8** [[DST_ADDR]], align 8
// CHECK-NEXT:    [[TMP1:%.*]] = call i8* @llvm.aarch64.mops.memset.tag(i8* [[TMP0]], i8 0, i64 0)
// CHECK-NEXT:    ret i8* [[TMP1]]
//
void *bzero_0(void *dst) {
  return __arm_mops_memset_tag(dst, 0, 0);
}

// CHECK-LABEL: @bzero_1(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[DST_ADDR:%.*]] = alloca i8*, align 8
// CHECK-NEXT:    store i8* [[DST:%.*]], i8** [[DST_ADDR]], align 8
// CHECK-NEXT:    [[TMP0:%.*]] = load i8*, i8** [[DST_ADDR]], align 8
// CHECK-NEXT:    [[TMP1:%.*]] = call i8* @llvm.aarch64.mops.memset.tag(i8* [[TMP0]], i8 0, i64 1)
// CHECK-NEXT:    ret i8* [[TMP1]]
//
void *bzero_1(void *dst) {
  return __arm_mops_memset_tag(dst, 0, 1);
}

// CHECK-LABEL: @bzero_10(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[DST_ADDR:%.*]] = alloca i8*, align 8
// CHECK-NEXT:    store i8* [[DST:%.*]], i8** [[DST_ADDR]], align 8
// CHECK-NEXT:    [[TMP0:%.*]] = load i8*, i8** [[DST_ADDR]], align 8
// CHECK-NEXT:    [[TMP1:%.*]] = call i8* @llvm.aarch64.mops.memset.tag(i8* [[TMP0]], i8 0, i64 10)
// CHECK-NEXT:    ret i8* [[TMP1]]
//
void *bzero_10(void *dst) {
  return __arm_mops_memset_tag(dst, 0, 10);
}

// CHECK-LABEL: @bzero_10000(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[DST_ADDR:%.*]] = alloca i8*, align 8
// CHECK-NEXT:    store i8* [[DST:%.*]], i8** [[DST_ADDR]], align 8
// CHECK-NEXT:    [[TMP0:%.*]] = load i8*, i8** [[DST_ADDR]], align 8
// CHECK-NEXT:    [[TMP1:%.*]] = call i8* @llvm.aarch64.mops.memset.tag(i8* [[TMP0]], i8 0, i64 10000)
// CHECK-NEXT:    ret i8* [[TMP1]]
//
void *bzero_10000(void *dst) {
  return __arm_mops_memset_tag(dst, 0, 10000);
}

// CHECK-LABEL: @bzero_n(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[DST_ADDR:%.*]] = alloca i8*, align 8
// CHECK-NEXT:    [[SIZE_ADDR:%.*]] = alloca i64, align 8
// CHECK-NEXT:    store i8* [[DST:%.*]], i8** [[DST_ADDR]], align 8
// CHECK-NEXT:    store i64 [[SIZE:%.*]], i64* [[SIZE_ADDR]], align 8
// CHECK-NEXT:    [[TMP0:%.*]] = load i8*, i8** [[DST_ADDR]], align 8
// CHECK-NEXT:    [[TMP1:%.*]] = load i64, i64* [[SIZE_ADDR]], align 8
// CHECK-NEXT:    [[TMP2:%.*]] = call i8* @llvm.aarch64.mops.memset.tag(i8* [[TMP0]], i8 0, i64 [[TMP1]])
// CHECK-NEXT:    ret i8* [[TMP2]]
//
void *bzero_n(void *dst, size_t size) {
  return __arm_mops_memset_tag(dst, 0, size);
}

// CHECK-LABEL: @memset_0(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[DST_ADDR:%.*]] = alloca i8*, align 8
// CHECK-NEXT:    [[VALUE_ADDR:%.*]] = alloca i32, align 4
// CHECK-NEXT:    store i8* [[DST:%.*]], i8** [[DST_ADDR]], align 8
// CHECK-NEXT:    store i32 [[VALUE:%.*]], i32* [[VALUE_ADDR]], align 4
// CHECK-NEXT:    [[TMP0:%.*]] = load i8*, i8** [[DST_ADDR]], align 8
// CHECK-NEXT:    [[TMP1:%.*]] = load i32, i32* [[VALUE_ADDR]], align 4
// CHECK-NEXT:    [[TMP2:%.*]] = trunc i32 [[TMP1]] to i8
// CHECK-NEXT:    [[TMP3:%.*]] = call i8* @llvm.aarch64.mops.memset.tag(i8* [[TMP0]], i8 [[TMP2]], i64 0)
// CHECK-NEXT:    ret i8* [[TMP3]]
//
void *memset_0(void *dst, int value) {
  return __arm_mops_memset_tag(dst, value, 0);
}

// CHECK-LABEL: @memset_1(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[DST_ADDR:%.*]] = alloca i8*, align 8
// CHECK-NEXT:    [[VALUE_ADDR:%.*]] = alloca i32, align 4
// CHECK-NEXT:    store i8* [[DST:%.*]], i8** [[DST_ADDR]], align 8
// CHECK-NEXT:    store i32 [[VALUE:%.*]], i32* [[VALUE_ADDR]], align 4
// CHECK-NEXT:    [[TMP0:%.*]] = load i8*, i8** [[DST_ADDR]], align 8
// CHECK-NEXT:    [[TMP1:%.*]] = load i32, i32* [[VALUE_ADDR]], align 4
// CHECK-NEXT:    [[TMP2:%.*]] = trunc i32 [[TMP1]] to i8
// CHECK-NEXT:    [[TMP3:%.*]] = call i8* @llvm.aarch64.mops.memset.tag(i8* [[TMP0]], i8 [[TMP2]], i64 1)
// CHECK-NEXT:    ret i8* [[TMP3]]
//
void *memset_1(void *dst, int value) {
  return __arm_mops_memset_tag(dst, value, 1);
}

// CHECK-LABEL: @memset_10(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[DST_ADDR:%.*]] = alloca i8*, align 8
// CHECK-NEXT:    [[VALUE_ADDR:%.*]] = alloca i32, align 4
// CHECK-NEXT:    store i8* [[DST:%.*]], i8** [[DST_ADDR]], align 8
// CHECK-NEXT:    store i32 [[VALUE:%.*]], i32* [[VALUE_ADDR]], align 4
// CHECK-NEXT:    [[TMP0:%.*]] = load i8*, i8** [[DST_ADDR]], align 8
// CHECK-NEXT:    [[TMP1:%.*]] = load i32, i32* [[VALUE_ADDR]], align 4
// CHECK-NEXT:    [[TMP2:%.*]] = trunc i32 [[TMP1]] to i8
// CHECK-NEXT:    [[TMP3:%.*]] = call i8* @llvm.aarch64.mops.memset.tag(i8* [[TMP0]], i8 [[TMP2]], i64 10)
// CHECK-NEXT:    ret i8* [[TMP3]]
//
void *memset_10(void *dst, int value) {
  return __arm_mops_memset_tag(dst, value, 10);
}

// CHECK-LABEL: @memset_10000(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[DST_ADDR:%.*]] = alloca i8*, align 8
// CHECK-NEXT:    [[VALUE_ADDR:%.*]] = alloca i32, align 4
// CHECK-NEXT:    store i8* [[DST:%.*]], i8** [[DST_ADDR]], align 8
// CHECK-NEXT:    store i32 [[VALUE:%.*]], i32* [[VALUE_ADDR]], align 4
// CHECK-NEXT:    [[TMP0:%.*]] = load i8*, i8** [[DST_ADDR]], align 8
// CHECK-NEXT:    [[TMP1:%.*]] = load i32, i32* [[VALUE_ADDR]], align 4
// CHECK-NEXT:    [[TMP2:%.*]] = trunc i32 [[TMP1]] to i8
// CHECK-NEXT:    [[TMP3:%.*]] = call i8* @llvm.aarch64.mops.memset.tag(i8* [[TMP0]], i8 [[TMP2]], i64 10000)
// CHECK-NEXT:    ret i8* [[TMP3]]
//
void *memset_10000(void *dst, int value) {
  return __arm_mops_memset_tag(dst, value, 10000);
}

// CHECK-LABEL: @memset_n(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[DST_ADDR:%.*]] = alloca i8*, align 8
// CHECK-NEXT:    [[VALUE_ADDR:%.*]] = alloca i32, align 4
// CHECK-NEXT:    [[SIZE_ADDR:%.*]] = alloca i64, align 8
// CHECK-NEXT:    store i8* [[DST:%.*]], i8** [[DST_ADDR]], align 8
// CHECK-NEXT:    store i32 [[VALUE:%.*]], i32* [[VALUE_ADDR]], align 4
// CHECK-NEXT:    store i64 [[SIZE:%.*]], i64* [[SIZE_ADDR]], align 8
// CHECK-NEXT:    [[TMP0:%.*]] = load i8*, i8** [[DST_ADDR]], align 8
// CHECK-NEXT:    [[TMP1:%.*]] = load i32, i32* [[VALUE_ADDR]], align 4
// CHECK-NEXT:    [[TMP2:%.*]] = load i64, i64* [[SIZE_ADDR]], align 8
// CHECK-NEXT:    [[TMP3:%.*]] = trunc i32 [[TMP1]] to i8
// CHECK-NEXT:    [[TMP4:%.*]] = call i8* @llvm.aarch64.mops.memset.tag(i8* [[TMP0]], i8 [[TMP3]], i64 [[TMP2]])
// CHECK-NEXT:    ret i8* [[TMP4]]
//
void *memset_n(void *dst, int value, size_t size) {
  return __arm_mops_memset_tag(dst, value, size);
}
