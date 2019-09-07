; ModuleID = '/Users/cijiexia/Project/lljb/test/c/mandelbrot.c'
source_filename = "/Users/cijiexia/Project/lljb/test/c/mandelbrot.c"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.14.0"

%struct.__sFILE = type { i8*, i32, i32, i16, i16, %struct.__sbuf, i32, i8*, i32 (i8*)*, i32 (i8*, i8*, i32)*, i64 (i8*, i64, i32)*, i32 (i8*, i8*, i32)*, %struct.__sbuf, %struct.__sFILEX*, i32, [3 x i8], [1 x i8], %struct.__sbuf, i32, i64 }
%struct.__sFILEX = type opaque
%struct.__sbuf = type { i8*, i32 }
%struct.timespec = type { i64, i64 }

@__stdoutp = external global %struct.__sFILE*, align 8
@.str = private unnamed_addr constant [38 x i8] c"Calculated Mandelbrot set in %lf (s)\0A\00", align 1

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @mandelbrot(i32, i32, i32*, i32) #0 {
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

; <label>:25:                                     ; preds = %93, %4
  %26 = load i32, i32* %11, align 4
  %27 = load i32, i32* %6, align 4
  %28 = icmp slt i32 %26, %27
  br i1 %28, label %29, label %96

; <label>:29:                                     ; preds = %25
  store i32 0, i32* %12, align 4
  br label %30

; <label>:30:                                     ; preds = %89, %29
  %31 = load i32, i32* %12, align 4
  %32 = load i32, i32* %5, align 4
  %33 = icmp slt i32 %31, %32
  br i1 %33, label %34, label %92

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

; <label>:45:                                     ; preds = %60, %34
  %46 = load double, double* %15, align 8
  %47 = load double, double* %15, align 8
  %48 = fmul double %46, %47
  %49 = load double, double* %16, align 8
  %50 = load double, double* %16, align 8
  %51 = fmul double %49, %50
  %52 = fadd double %48, %51
  %53 = fcmp ole double %52, 4.000000e+00
  br i1 %53, label %54, label %58

; <label>:54:                                     ; preds = %45
  %55 = load i32, i32* %17, align 4
  %56 = load i32, i32* %8, align 4
  %57 = icmp slt i32 %55, %56
  br label %58

; <label>:58:                                     ; preds = %54, %45
  %59 = phi i1 [ false, %45 ], [ %57, %54 ]
  br i1 %59, label %60, label %79

; <label>:60:                                     ; preds = %58
  %61 = load double, double* %15, align 8
  %62 = load double, double* %15, align 8
  %63 = fmul double %61, %62
  %64 = load double, double* %16, align 8
  %65 = load double, double* %16, align 8
  %66 = fmul double %64, %65
  %67 = fsub double %63, %66
  %68 = load double, double* %13, align 8
  %69 = fadd double %67, %68
  store double %69, double* %18, align 8
  %70 = load double, double* %15, align 8
  %71 = fmul double 2.000000e+00, %70
  %72 = load double, double* %16, align 8
  %73 = fmul double %71, %72
  %74 = load double, double* %14, align 8
  %75 = fadd double %73, %74
  store double %75, double* %16, align 8
  %76 = load double, double* %18, align 8
  store double %76, double* %15, align 8
  %77 = load i32, i32* %17, align 4
  %78 = add nsw i32 %77, 1
  store i32 %78, i32* %17, align 4
  br label %45

; <label>:79:                                     ; preds = %58
  %80 = load i32, i32* %17, align 4
  %81 = load i32*, i32** %7, align 8
  %82 = load i32, i32* %11, align 4
  %83 = load i32, i32* %5, align 4
  %84 = mul nsw i32 %82, %83
  %85 = load i32, i32* %12, align 4
  %86 = add nsw i32 %84, %85
  %87 = sext i32 %86 to i64
  %88 = getelementptr inbounds i32, i32* %81, i64 %87
  store i32 %80, i32* %88, align 4
  br label %89

; <label>:89:                                     ; preds = %79
  %90 = load i32, i32* %12, align 4
  %91 = add nsw i32 %90, 1
  store i32 %91, i32* %12, align 4
  br label %30

; <label>:92:                                     ; preds = %30
  br label %93

; <label>:93:                                     ; preds = %92
  %94 = load i32, i32* %11, align 4
  %95 = add nsw i32 %94, 1
  store i32 %95, i32* %11, align 4
  br label %25

; <label>:96:                                     ; preds = %25
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @print_image(i32, i32, i32*) #0 {
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32*, align 8
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i8, align 1
  store i32 %0, i32* %4, align 4
  store i32 %1, i32* %5, align 4
  store i32* %2, i32** %6, align 8
  store i32 0, i32* %7, align 4
  br label %10

; <label>:10:                                     ; preds = %43, %3
  %11 = load i32, i32* %7, align 4
  %12 = load i32, i32* %5, align 4
  %13 = icmp slt i32 %11, %12
  br i1 %13, label %14, label %46

; <label>:14:                                     ; preds = %10
  store i32 0, i32* %8, align 4
  br label %15

; <label>:15:                                     ; preds = %37, %14
  %16 = load i32, i32* %8, align 4
  %17 = load i32, i32* %4, align 4
  %18 = icmp slt i32 %16, %17
  br i1 %18, label %19, label %40

; <label>:19:                                     ; preds = %15
  %20 = load i32*, i32** %6, align 8
  %21 = load i32, i32* %7, align 4
  %22 = load i32, i32* %4, align 4
  %23 = mul nsw i32 %21, %22
  %24 = load i32, i32* %8, align 4
  %25 = add nsw i32 %23, %24
  %26 = sext i32 %25 to i64
  %27 = getelementptr inbounds i32, i32* %20, i64 %26
  %28 = load i32, i32* %27, align 4
  %29 = icmp sgt i32 %28, 150
  %30 = zext i1 %29 to i64
  %31 = select i1 %29, i32 42, i32 32
  %32 = trunc i32 %31 to i8
  store i8 %32, i8* %9, align 1
  %33 = load i8, i8* %9, align 1
  %34 = sext i8 %33 to i32
  %35 = load %struct.__sFILE*, %struct.__sFILE** @__stdoutp, align 8
  %36 = call i32 @putc(i32 %34, %struct.__sFILE* %35)
  br label %37

; <label>:37:                                     ; preds = %19
  %38 = load i32, i32* %8, align 4
  %39 = add nsw i32 %38, 1
  store i32 %39, i32* %8, align 4
  br label %15

; <label>:40:                                     ; preds = %15
  %41 = load %struct.__sFILE*, %struct.__sFILE** @__stdoutp, align 8
  %42 = call i32 @putc(i32 10, %struct.__sFILE* %41)
  br label %43

; <label>:43:                                     ; preds = %40
  %44 = load i32, i32* %7, align 4
  %45 = add nsw i32 %44, 1
  store i32 %45, i32* %7, align 4
  br label %10

; <label>:46:                                     ; preds = %10
  ret void
}

declare i32 @putc(i32, %struct.__sFILE*) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define { i64, i64 } @tdiff(i64, i64, i64, i64) #0 {
  %5 = alloca %struct.timespec, align 8
  %6 = alloca %struct.timespec, align 8
  %7 = alloca %struct.timespec, align 8
  %8 = bitcast %struct.timespec* %6 to { i64, i64 }*
  %9 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %8, i32 0, i32 0
  store i64 %0, i64* %9, align 8
  %10 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %8, i32 0, i32 1
  store i64 %1, i64* %10, align 8
  %11 = bitcast %struct.timespec* %7 to { i64, i64 }*
  %12 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %11, i32 0, i32 0
  store i64 %2, i64* %12, align 8
  %13 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %11, i32 0, i32 1
  store i64 %3, i64* %13, align 8
  %14 = getelementptr inbounds %struct.timespec, %struct.timespec* %7, i32 0, i32 1
  %15 = load i64, i64* %14, align 8
  %16 = getelementptr inbounds %struct.timespec, %struct.timespec* %6, i32 0, i32 1
  %17 = load i64, i64* %16, align 8
  %18 = sub nsw i64 %15, %17
  %19 = icmp slt i64 %18, 0
  br i1 %19, label %20, label %35

; <label>:20:                                     ; preds = %4
  %21 = getelementptr inbounds %struct.timespec, %struct.timespec* %7, i32 0, i32 0
  %22 = load i64, i64* %21, align 8
  %23 = getelementptr inbounds %struct.timespec, %struct.timespec* %6, i32 0, i32 0
  %24 = load i64, i64* %23, align 8
  %25 = sub nsw i64 %22, %24
  %26 = sub nsw i64 %25, 1
  %27 = getelementptr inbounds %struct.timespec, %struct.timespec* %5, i32 0, i32 0
  store i64 %26, i64* %27, align 8
  %28 = getelementptr inbounds %struct.timespec, %struct.timespec* %7, i32 0, i32 1
  %29 = load i64, i64* %28, align 8
  %30 = add nsw i64 1000000000, %29
  %31 = getelementptr inbounds %struct.timespec, %struct.timespec* %6, i32 0, i32 1
  %32 = load i64, i64* %31, align 8
  %33 = sub nsw i64 %30, %32
  %34 = getelementptr inbounds %struct.timespec, %struct.timespec* %5, i32 0, i32 1
  store i64 %33, i64* %34, align 8
  br label %48

; <label>:35:                                     ; preds = %4
  %36 = getelementptr inbounds %struct.timespec, %struct.timespec* %7, i32 0, i32 0
  %37 = load i64, i64* %36, align 8
  %38 = getelementptr inbounds %struct.timespec, %struct.timespec* %6, i32 0, i32 0
  %39 = load i64, i64* %38, align 8
  %40 = sub nsw i64 %37, %39
  %41 = getelementptr inbounds %struct.timespec, %struct.timespec* %5, i32 0, i32 0
  store i64 %40, i64* %41, align 8
  %42 = getelementptr inbounds %struct.timespec, %struct.timespec* %7, i32 0, i32 1
  %43 = load i64, i64* %42, align 8
  %44 = getelementptr inbounds %struct.timespec, %struct.timespec* %6, i32 0, i32 1
  %45 = load i64, i64* %44, align 8
  %46 = sub nsw i64 %43, %45
  %47 = getelementptr inbounds %struct.timespec, %struct.timespec* %5, i32 0, i32 1
  store i64 %46, i64* %47, align 8
  br label %48

; <label>:48:                                     ; preds = %35, %20
  %49 = bitcast %struct.timespec* %5 to { i64, i64 }*
  %50 = load { i64, i64 }, { i64, i64 }* %49, align 8
  ret { i64, i64 } %50
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca [3 x [4 x i32]], align 16
  %3 = alloca [34 x [80 x i32]], align 16
  %4 = alloca i32, align 4
  %5 = alloca %struct.timespec, align 8
  %6 = alloca %struct.timespec, align 8
  %7 = alloca %struct.timespec, align 8
  store i32 0, i32* %1, align 4
  %8 = bitcast [3 x [4 x i32]]* %2 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %8, i8 0, i64 48, i1 false)
  %9 = getelementptr inbounds [3 x [4 x i32]], [3 x [4 x i32]]* %2, i32 0, i32 0
  %10 = bitcast [4 x i32]* %9 to i32*
  call void @mandelbrot(i32 4, i32 3, i32* %10, i32 10)
  %11 = getelementptr inbounds [3 x [4 x i32]], [3 x [4 x i32]]* %2, i32 0, i32 0
  %12 = bitcast [4 x i32]* %11 to i32*
  call void @print_image(i32 4, i32 3, i32* %12)
  %13 = bitcast [34 x [80 x i32]]* %3 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %13, i8 0, i64 10880, i1 false)
  store i32 6, i32* %4, align 4
  %14 = load i32, i32* %4, align 4
  %15 = call i32 @clock_gettime(i32 %14, %struct.timespec* %5)
  %16 = getelementptr inbounds [34 x [80 x i32]], [34 x [80 x i32]]* %3, i32 0, i32 0
  %17 = bitcast [80 x i32]* %16 to i32*
  call void @mandelbrot(i32 80, i32 34, i32* %17, i32 300000)
  %18 = load i32, i32* %4, align 4
  %19 = call i32 @clock_gettime(i32 %18, %struct.timespec* %6)
  %20 = bitcast %struct.timespec* %5 to { i64, i64 }*
  %21 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %20, i32 0, i32 0
  %22 = load i64, i64* %21, align 8
  %23 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %20, i32 0, i32 1
  %24 = load i64, i64* %23, align 8
  %25 = bitcast %struct.timespec* %6 to { i64, i64 }*
  %26 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %25, i32 0, i32 0
  %27 = load i64, i64* %26, align 8
  %28 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %25, i32 0, i32 1
  %29 = load i64, i64* %28, align 8
  %30 = call { i64, i64 } @tdiff(i64 %22, i64 %24, i64 %27, i64 %29)
  %31 = bitcast %struct.timespec* %7 to { i64, i64 }*
  %32 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %31, i32 0, i32 0
  %33 = extractvalue { i64, i64 } %30, 0
  store i64 %33, i64* %32, align 8
  %34 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %31, i32 0, i32 1
  %35 = extractvalue { i64, i64 } %30, 1
  store i64 %35, i64* %34, align 8
  %36 = getelementptr inbounds %struct.timespec, %struct.timespec* %7, i32 0, i32 0
  %37 = load i64, i64* %36, align 8
  %38 = sitofp i64 %37 to double
  %39 = getelementptr inbounds %struct.timespec, %struct.timespec* %7, i32 0, i32 1
  %40 = load i64, i64* %39, align 8
  %41 = sitofp i64 %40 to double
  %42 = fmul double %41, 1.000000e-09
  %43 = fadd double %38, %42
  %44 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str, i32 0, i32 0), double %43)
  %45 = getelementptr inbounds [34 x [80 x i32]], [34 x [80 x i32]]* %3, i32 0, i32 0
  %46 = bitcast [80 x i32]* %45 to i32*
  call void @print_image(i32 80, i32 34, i32* %46)
  ret i32 0
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1) #2

declare i32 @clock_gettime(i32, %struct.timespec*) #1

declare i32 @printf(i8*, ...) #1

attributes #0 = { noinline nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { argmemonly nounwind }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{!"clang version 8.0.1 (tags/RELEASE_801/final)"}
