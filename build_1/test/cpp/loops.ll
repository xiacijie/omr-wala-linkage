; ModuleID = '/Users/cijiexia/Project/lljb/test/cpp/loops.cpp'
source_filename = "/Users/cijiexia/Project/lljb/test/cpp/loops.cpp"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.14.0"

; Function Attrs: noinline norecurse nounwind optnone ssp uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32 0, i32* %2, align 4
  store i32 0, i32* %3, align 4
  store i32 0, i32* %4, align 4
  br label %5

; <label>:5:                                      ; preds = %19, %0
  %6 = load i32, i32* %4, align 4
  %7 = icmp slt i32 %6, 10
  br i1 %7, label %8, label %17

; <label>:8:                                      ; preds = %5
  %9 = load i32, i32* %2, align 4
  %10 = load i32, i32* %3, align 4
  %11 = icmp sge i32 %9, %10
  br i1 %11, label %15, label %12

; <label>:12:                                     ; preds = %8
  %13 = load i32, i32* %3, align 4
  %14 = icmp sge i32 %13, 0
  br label %15

; <label>:15:                                     ; preds = %12, %8
  %16 = phi i1 [ true, %8 ], [ %14, %12 ]
  br label %17

; <label>:17:                                     ; preds = %15, %5
  %18 = phi i1 [ false, %5 ], [ %16, %15 ]
  br i1 %18, label %19, label %24

; <label>:19:                                     ; preds = %17
  %20 = load i32, i32* %2, align 4
  %21 = add nsw i32 %20, 1
  store i32 %21, i32* %2, align 4
  %22 = load i32, i32* %4, align 4
  %23 = add nsw i32 %22, 1
  store i32 %23, i32* %4, align 4
  br label %5

; <label>:24:                                     ; preds = %17
  store i32 0, i32* %4, align 4
  br label %25

; <label>:25:                                     ; preds = %31, %24
  %26 = load i32, i32* %4, align 4
  %27 = icmp slt i32 %26, 7
  br i1 %27, label %28, label %34

; <label>:28:                                     ; preds = %25
  %29 = load i32, i32* %3, align 4
  %30 = add nsw i32 %29, 1
  store i32 %30, i32* %3, align 4
  br label %31

; <label>:31:                                     ; preds = %28
  %32 = load i32, i32* %4, align 4
  %33 = add nsw i32 %32, 1
  store i32 %33, i32* %4, align 4
  br label %25

; <label>:34:                                     ; preds = %25
  %35 = load i32, i32* %2, align 4
  %36 = load i32, i32* %3, align 4
  %37 = sub nsw i32 %35, %36
  ret i32 %37
}

attributes #0 = { noinline norecurse nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{!"clang version 8.0.1 (tags/RELEASE_801/final)"}
