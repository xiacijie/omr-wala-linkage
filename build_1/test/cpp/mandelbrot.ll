; ModuleID = '/Users/cijiexia/Project/lljb/test/cpp/mandelbrot.cpp'
source_filename = "/Users/cijiexia/Project/lljb/test/cpp/mandelbrot.cpp"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.14.0"

%struct.timespec = type { i64, i64 }

@.str = private unnamed_addr constant [2 x i8] c"*\00", align 1
@.str.1 = private unnamed_addr constant [2 x i8] c" \00", align 1
@.str.2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str.3 = private unnamed_addr constant [38 x i8] c"Calculated Mandelbrot set in %lf (s)\0A\00", align 1

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @_Z10mandelbrotiiPii(i32, i32, i32*, i32) #0 {
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32*, align 8
  %8 = alloca i32, align 4
  %9 = alloca double, align 8
  %10 = alloca double, align 8
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca double, align 8
  %14 = alloca double, align 8
  %15 = alloca double, align 8
  %16 = alloca double, align 8
  %17 = alloca i32, align 4
  %18 = alloca double, align 8
  store i32 %0, i32* %5, align 4
  store i32 %1, i32* %6, align 4
  store i32* %2, i32** %7, align 8
  store i32 %3, i32* %8, align 4
  %19 = load i32, i32* %5, align 4
  %20 = sitofp i32 %19 to double
  %21 = fdiv double 3.500000e+00, %20
  store double %21, double* %9, align 8
  %22 = load i32, i32* %6, align 4
  %23 = sitofp i32 %22 to double
  %24 = fdiv double 2.000000e+00, %23
  store double %24, double* %10, align 8
  store i32 0, i32* %11, align 4
  br label %25

; <label>:25:                                     ; preds = %92, %4
  %26 = load i32, i32* %11, align 4
  %27 = load i32, i32* %6, align 4
  %28 = icmp slt i32 %26, %27
  br i1 %28, label %29, label %95

; <label>:29:                                     ; preds = %25
  store i32 0, i32* %12, align 4
  br label %30

; <label>:30:                                     ; preds = %88, %29
  %31 = load i32, i32* %12, align 4
  %32 = load i32, i32* %5, align 4
  %33 = icmp slt i32 %31, %32
  br i1 %33, label %34, label %91

; <label>:34:                                     ; preds = %30
  %35 = load i32, i32* %12, align 4
  %36 = sitofp i32 %35 to double
  %37 = load double, double* %9, align 8
  %38 = fmul double %36, %37
  %39 = fsub double %38, 2.500000e+00
  store double %39, double* %13, align 8
  %40 = load i32, i32* %11, align 4
  %41 = sitofp i32 %40 to double
  %42 = load double, double* %10, align 8
  %43 = fmul double %41, %42
  %44 = fsub double %43, 1.000000e+00
  store double %44, double* %14, align 8
  store double 0.000000e+00, double* %15, align 8
  store double 0.000000e+00, double* %16, align 8
  store i32 0, i32* %17, align 4
  br label %45

; <label>:45:                                     ; preds = %59, %34
  %46 = load double, double* %15, align 8
  %47 = load double, double* %15, align 8
  %48 = fmul double %46, %47
  %49 = load double, double* %16, align 8
  %50 = load double, double* %16, align 8
  %51 = fmul double %49, %50
  %52 = fadd double %48, %51
  %53 = fcmp ole double %52, 4.000000e+00
  br i1 %53, label %54, label %78

; <label>:54:                                     ; preds = %45
  %55 = load i32, i32* %17, align 4
  %56 = load i32, i32* %8, align 4
  %57 = icmp eq i32 %55, %56
  br i1 %57, label %58, label %59

; <label>:58:                                     ; preds = %54
  br label %78

; <label>:59:                                     ; preds = %54
  %60 = load double, double* %15, align 8
  %61 = load double, double* %15, align 8
  %62 = fmul double %60, %61
  %63 = load double, double* %16, align 8
  %64 = load double, double* %16, align 8
  %65 = fmul double %63, %64
  %66 = fsub double %62, %65
  %67 = load double, double* %13, align 8
  %68 = fadd double %66, %67
  store double %68, double* %18, align 8
  %69 = load double, double* %15, align 8
  %70 = fmul double 2.000000e+00, %69
  %71 = load double, double* %16, align 8
  %72 = fmul double %70, %71
  %73 = load double, double* %14, align 8
  %74 = fadd double %72, %73
  store double %74, double* %16, align 8
  %75 = load double, double* %18, align 8
  store double %75, double* %15, align 8
  %76 = load i32, i32* %17, align 4
  %77 = add nsw i32 %76, 1
  store i32 %77, i32* %17, align 4
  br label %45

; <label>:78:                                     ; preds = %58, %45
  %79 = load i32, i32* %17, align 4
  %80 = load i32*, i32** %7, align 8
  %81 = load i32, i32* %11, align 4
  %82 = load i32, i32* %5, align 4
  %83 = mul nsw i32 %81, %82
  %84 = load i32, i32* %12, align 4
  %85 = add nsw i32 %83, %84
  %86 = sext i32 %85 to i64
  %87 = getelementptr inbounds i32, i32* %80, i64 %86
  store i32 %79, i32* %87, align 4
  br label %88

; <label>:88:                                     ; preds = %78
  %89 = load i32, i32* %12, align 4
  %90 = add nsw i32 %89, 1
  store i32 %90, i32* %12, align 4
  br label %30

; <label>:91:                                     ; preds = %30
  br label %92

; <label>:92:                                     ; preds = %91
  %93 = load i32, i32* %11, align 4
  %94 = add nsw i32 %93, 1
  store i32 %94, i32* %11, align 4
  br label %25

; <label>:95:                                     ; preds = %25
  ret void
}

; Function Attrs: noinline optnone ssp uwtable
define void @_Z11print_imageiiPi(i32, i32, i32*) #1 {
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32*, align 8
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  store i32 %0, i32* %4, align 4
  store i32 %1, i32* %5, align 4
  store i32* %2, i32** %6, align 8
  store i32 0, i32* %7, align 4
  br label %9

; <label>:9:                                      ; preds = %39, %3
  %10 = load i32, i32* %7, align 4
  %11 = load i32, i32* %5, align 4
  %12 = icmp slt i32 %10, %11
  br i1 %12, label %13, label %42

; <label>:13:                                     ; preds = %9
  store i32 0, i32* %8, align 4
  br label %14

; <label>:14:                                     ; preds = %34, %13
  %15 = load i32, i32* %8, align 4
  %16 = load i32, i32* %4, align 4
  %17 = icmp slt i32 %15, %16
  br i1 %17, label %18, label %37

; <label>:18:                                     ; preds = %14
  %19 = load i32*, i32** %6, align 8
  %20 = load i32, i32* %7, align 4
  %21 = load i32, i32* %4, align 4
  %22 = mul nsw i32 %20, %21
  %23 = load i32, i32* %8, align 4
  %24 = add nsw i32 %22, %23
  %25 = sext i32 %24 to i64
  %26 = getelementptr inbounds i32, i32* %19, i64 %25
  %27 = load i32, i32* %26, align 4
  %28 = icmp sgt i32 %27, 150
  br i1 %28, label %29, label %31

; <label>:29:                                     ; preds = %18
  %30 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str, i32 0, i32 0))
  br label %33

; <label>:31:                                     ; preds = %18
  %32 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.1, i32 0, i32 0))
  br label %33

; <label>:33:                                     ; preds = %31, %29
  br label %34

; <label>:34:                                     ; preds = %33
  %35 = load i32, i32* %8, align 4
  %36 = add nsw i32 %35, 1
  store i32 %36, i32* %8, align 4
  br label %14

; <label>:37:                                     ; preds = %14
  %38 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.2, i32 0, i32 0))
  br label %39

; <label>:39:                                     ; preds = %37
  %40 = load i32, i32* %7, align 4
  %41 = add nsw i32 %40, 1
  store i32 %41, i32* %7, align 4
  br label %9

; <label>:42:                                     ; preds = %9
  ret void
}

declare i32 @printf(i8*, ...) #2

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @_Z5tdiffP8timespecS0_S0_(%struct.timespec*, %struct.timespec*, %struct.timespec*) #0 {
  %4 = alloca %struct.timespec*, align 8
  %5 = alloca %struct.timespec*, align 8
  %6 = alloca %struct.timespec*, align 8
  store %struct.timespec* %0, %struct.timespec** %4, align 8
  store %struct.timespec* %1, %struct.timespec** %5, align 8
  store %struct.timespec* %2, %struct.timespec** %6, align 8
  %7 = load %struct.timespec*, %struct.timespec** %5, align 8
  %8 = getelementptr inbounds %struct.timespec, %struct.timespec* %7, i32 0, i32 1
  %9 = load i64, i64* %8, align 8
  %10 = load %struct.timespec*, %struct.timespec** %4, align 8
  %11 = getelementptr inbounds %struct.timespec, %struct.timespec* %10, i32 0, i32 1
  %12 = load i64, i64* %11, align 8
  %13 = sub nsw i64 %9, %12
  %14 = icmp slt i64 %13, 0
  br i1 %14, label %15, label %36

; <label>:15:                                     ; preds = %3
  %16 = load %struct.timespec*, %struct.timespec** %5, align 8
  %17 = getelementptr inbounds %struct.timespec, %struct.timespec* %16, i32 0, i32 0
  %18 = load i64, i64* %17, align 8
  %19 = load %struct.timespec*, %struct.timespec** %4, align 8
  %20 = getelementptr inbounds %struct.timespec, %struct.timespec* %19, i32 0, i32 0
  %21 = load i64, i64* %20, align 8
  %22 = sub nsw i64 %18, %21
  %23 = sub nsw i64 %22, 1
  %24 = load %struct.timespec*, %struct.timespec** %6, align 8
  %25 = getelementptr inbounds %struct.timespec, %struct.timespec* %24, i32 0, i32 0
  store i64 %23, i64* %25, align 8
  %26 = load %struct.timespec*, %struct.timespec** %5, align 8
  %27 = getelementptr inbounds %struct.timespec, %struct.timespec* %26, i32 0, i32 1
  %28 = load i64, i64* %27, align 8
  %29 = add nsw i64 1000000000, %28
  %30 = load %struct.timespec*, %struct.timespec** %4, align 8
  %31 = getelementptr inbounds %struct.timespec, %struct.timespec* %30, i32 0, i32 1
  %32 = load i64, i64* %31, align 8
  %33 = sub nsw i64 %29, %32
  %34 = load %struct.timespec*, %struct.timespec** %6, align 8
  %35 = getelementptr inbounds %struct.timespec, %struct.timespec* %34, i32 0, i32 1
  store i64 %33, i64* %35, align 8
  br label %55

; <label>:36:                                     ; preds = %3
  %37 = load %struct.timespec*, %struct.timespec** %5, align 8
  %38 = getelementptr inbounds %struct.timespec, %struct.timespec* %37, i32 0, i32 0
  %39 = load i64, i64* %38, align 8
  %40 = load %struct.timespec*, %struct.timespec** %4, align 8
  %41 = getelementptr inbounds %struct.timespec, %struct.timespec* %40, i32 0, i32 0
  %42 = load i64, i64* %41, align 8
  %43 = sub nsw i64 %39, %42
  %44 = load %struct.timespec*, %struct.timespec** %6, align 8
  %45 = getelementptr inbounds %struct.timespec, %struct.timespec* %44, i32 0, i32 0
  store i64 %43, i64* %45, align 8
  %46 = load %struct.timespec*, %struct.timespec** %5, align 8
  %47 = getelementptr inbounds %struct.timespec, %struct.timespec* %46, i32 0, i32 1
  %48 = load i64, i64* %47, align 8
  %49 = load %struct.timespec*, %struct.timespec** %4, align 8
  %50 = getelementptr inbounds %struct.timespec, %struct.timespec* %49, i32 0, i32 1
  %51 = load i64, i64* %50, align 8
  %52 = sub nsw i64 %48, %51
  %53 = load %struct.timespec*, %struct.timespec** %6, align 8
  %54 = getelementptr inbounds %struct.timespec, %struct.timespec* %53, i32 0, i32 1
  store i64 %52, i64* %54, align 8
  br label %55

; <label>:55:                                     ; preds = %36, %15
  ret void
}

; Function Attrs: noinline norecurse optnone ssp uwtable
define i32 @main() #3 {
  %1 = alloca i32, align 4
  %2 = alloca [3 x [4 x i32]], align 16
  %3 = alloca [34 x [80 x i32]], align 16
  %4 = alloca i32, align 4
  %5 = alloca %struct.timespec, align 8
  %6 = alloca %struct.timespec, align 8
  %7 = alloca %struct.timespec, align 8
  %8 = alloca double, align 8
  store i32 0, i32* %1, align 4
  %9 = getelementptr inbounds [3 x [4 x i32]], [3 x [4 x i32]]* %2, i32 0, i32 0
  %10 = bitcast [4 x i32]* %9 to i32*
  call void @_Z10mandelbrotiiPii(i32 4, i32 3, i32* %10, i32 10)
  %11 = getelementptr inbounds [3 x [4 x i32]], [3 x [4 x i32]]* %2, i32 0, i32 0
  %12 = bitcast [4 x i32]* %11 to i32*
  call void @_Z11print_imageiiPi(i32 4, i32 3, i32* %12)
  store i32 6, i32* %4, align 4
  %13 = load i32, i32* %4, align 4
  %14 = call i32 @clock_gettime(i32 %13, %struct.timespec* %5)
  %15 = getelementptr inbounds [34 x [80 x i32]], [34 x [80 x i32]]* %3, i32 0, i32 0
  %16 = bitcast [80 x i32]* %15 to i32*
  call void @_Z10mandelbrotiiPii(i32 80, i32 34, i32* %16, i32 300000)
  %17 = load i32, i32* %4, align 4
  %18 = call i32 @clock_gettime(i32 %17, %struct.timespec* %6)
  call void @_Z5tdiffP8timespecS0_S0_(%struct.timespec* %5, %struct.timespec* %6, %struct.timespec* %7)
  %19 = getelementptr inbounds %struct.timespec, %struct.timespec* %7, i32 0, i32 0
  %20 = load i64, i64* %19, align 8
  %21 = sitofp i64 %20 to double
  %22 = getelementptr inbounds %struct.timespec, %struct.timespec* %7, i32 0, i32 1
  %23 = load i64, i64* %22, align 8
  %24 = sitofp i64 %23 to double
  %25 = fmul double %24, 1.000000e-09
  %26 = fadd double %21, %25
  store double %26, double* %8, align 8
  %27 = load double, double* %8, align 8
  %28 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.3, i32 0, i32 0), double %27)
  %29 = getelementptr inbounds [34 x [80 x i32]], [34 x [80 x i32]]* %3, i32 0, i32 0
  %30 = bitcast [80 x i32]* %29 to i32*
  call void @_Z11print_imageiiPi(i32 80, i32 34, i32* %30)
  ret i32 0
}

declare i32 @clock_gettime(i32, %struct.timespec*) #2

attributes #0 = { noinline nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { noinline optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { noinline norecurse optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{!"clang version 8.0.1 (tags/RELEASE_801/final)"}
