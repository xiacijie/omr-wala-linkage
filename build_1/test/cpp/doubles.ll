; ModuleID = '/Users/cijiexia/Project/lljb/test/cpp/doubles.cpp'
source_filename = "/Users/cijiexia/Project/lljb/test/cpp/doubles.cpp"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.14.0"

; Function Attrs: noinline nounwind optnone ssp uwtable
define double @_Z3foov() #0 {
  %1 = alloca double, align 8
  %2 = alloca double, align 8
  store double 3.100000e+00, double* %1, align 8
  store double 1.000000e-01, double* %2, align 8
  %3 = load double, double* %1, align 8
  %4 = fcmp ogt double %3, 0.000000e+00
  br i1 %4, label %5, label %10

; <label>:5:                                      ; preds = %0
  %6 = load double, double* %1, align 8
  %7 = fadd double %6, 1.100000e+00
  store double %7, double* %1, align 8
  %8 = load double, double* %2, align 8
  %9 = fadd double %8, 1.100000e+00
  store double %9, double* %2, align 8
  br label %10

; <label>:10:                                     ; preds = %5, %0
  %11 = load double, double* %1, align 8
  %12 = load double, double* %2, align 8
  %13 = fsub double %11, %12
  ret double %13
}

; Function Attrs: noinline norecurse nounwind optnone ssp uwtable
define i32 @main() #1 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = call double @_Z3foov()
  %3 = fptosi double %2 to i32
  ret i32 %3
}

attributes #0 = { noinline nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { noinline norecurse nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{!"clang version 8.0.1 (tags/RELEASE_801/final)"}
