; ModuleID = '/Users/cijiexia/Project/lljb/test/cpp/ternary.cpp'
source_filename = "/Users/cijiexia/Project/lljb/test/cpp/ternary.cpp"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.14.0"

; Function Attrs: noinline norecurse nounwind optnone ssp uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca float, align 4
  %6 = alloca float, align 4
  %7 = alloca float, align 4
  store i32 0, i32* %1, align 4
  store i32 1, i32* %2, align 4
  %8 = load i32, i32* %2, align 4
  %9 = icmp ne i32 %8, 0
  %10 = zext i1 %9 to i64
  %11 = select i1 %9, i32 2, i32 3
  store i32 %11, i32* %3, align 4
  %12 = load i32, i32* %2, align 4
  %13 = load i32, i32* %3, align 4
  %14 = add nsw i32 %12, %13
  store i32 %14, i32* %4, align 4
  store float 0.000000e+00, float* %5, align 4
  %15 = load float, float* %5, align 4
  %16 = fcmp une float %15, 0.000000e+00
  %17 = zext i1 %16 to i64
  %18 = select i1 %16, float 1.000000e+00, float 0.000000e+00
  store float %18, float* %6, align 4
  %19 = load float, float* %5, align 4
  %20 = load float, float* %6, align 4
  %21 = fadd float %19, %20
  store float %21, float* %7, align 4
  %22 = load i32, i32* %4, align 4
  %23 = sitofp i32 %22 to float
  %24 = load float, float* %7, align 4
  %25 = fadd float %23, %24
  %26 = fptosi float %25 to i32
  ret i32 %26
}

attributes #0 = { noinline norecurse nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{!"clang version 8.0.1 (tags/RELEASE_801/final)"}
