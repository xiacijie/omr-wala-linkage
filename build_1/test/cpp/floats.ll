; ModuleID = '/Users/cijiexia/Project/lljb/test/cpp/floats.cpp'
source_filename = "/Users/cijiexia/Project/lljb/test/cpp/floats.cpp"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.14.0"

; Function Attrs: noinline nounwind optnone ssp uwtable
define float @_Z3foov() #0 {
  %1 = alloca float, align 4
  %2 = alloca float, align 4
  store float 0x4008CCCCC0000000, float* %1, align 4
  store float 0x3FB99999A0000000, float* %2, align 4
  %3 = load float, float* %1, align 4
  %4 = fcmp ogt float %3, 0.000000e+00
  br i1 %4, label %5, label %10

; <label>:5:                                      ; preds = %0
  %6 = load float, float* %1, align 4
  %7 = fadd float %6, 0x3FF3333340000000
  store float %7, float* %1, align 4
  %8 = load float, float* %2, align 4
  %9 = fadd float %8, 0x3FF19999A0000000
  store float %9, float* %2, align 4
  br label %10

; <label>:10:                                     ; preds = %5, %0
  %11 = load float, float* %1, align 4
  %12 = load float, float* %2, align 4
  %13 = fsub float %11, %12
  ret float %13
}

; Function Attrs: noinline norecurse nounwind optnone ssp uwtable
define i32 @main() #1 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = call float @_Z3foov()
  %3 = fptosi float %2 to i32
  ret i32 %3
}

attributes #0 = { noinline nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { noinline norecurse nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{!"clang version 8.0.1 (tags/RELEASE_801/final)"}
