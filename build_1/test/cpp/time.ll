; ModuleID = '/Users/cijiexia/Project/lljb/test/cpp/time.cpp'
source_filename = "/Users/cijiexia/Project/lljb/test/cpp/time.cpp"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.14.0"

%struct.timespec = type { i64, i64 }

@.str = private unnamed_addr constant [22 x i8] c"current time %lf (s)\0A\00", align 1

; Function Attrs: noinline optnone ssp uwtable
define void @_Z12current_timeP8timespec(%struct.timespec*) #0 {
  %2 = alloca %struct.timespec*, align 8
  store %struct.timespec* %0, %struct.timespec** %2, align 8
  %3 = load %struct.timespec*, %struct.timespec** %2, align 8
  %4 = call i32 @clock_gettime(i32 6, %struct.timespec* %3)
  ret void
}

declare i32 @clock_gettime(i32, %struct.timespec*) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @_Z9time_diffP8timespecS0_S0_(%struct.timespec*, %struct.timespec*, %struct.timespec*) #2 {
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
  %2 = alloca %struct.timespec, align 8
  %3 = alloca %struct.timespec, align 8
  %4 = alloca %struct.timespec, align 8
  %5 = alloca double, align 8
  store i32 0, i32* %1, align 4
  call void @_Z12current_timeP8timespec(%struct.timespec* %2)
  %6 = call i32 @"\01_usleep"(i32 2000000)
  call void @_Z12current_timeP8timespec(%struct.timespec* %3)
  call void @_Z9time_diffP8timespecS0_S0_(%struct.timespec* %2, %struct.timespec* %3, %struct.timespec* %4)
  %7 = getelementptr inbounds %struct.timespec, %struct.timespec* %4, i32 0, i32 0
  %8 = load i64, i64* %7, align 8
  %9 = sitofp i64 %8 to double
  %10 = getelementptr inbounds %struct.timespec, %struct.timespec* %4, i32 0, i32 1
  %11 = load i64, i64* %10, align 8
  %12 = sitofp i64 %11 to double
  %13 = fmul double %12, 1.000000e-09
  %14 = fadd double %9, %13
  store double %14, double* %5, align 8
  %15 = load double, double* %5, align 8
  %16 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str, i32 0, i32 0), double %15)
  %17 = load double, double* %5, align 8
  %18 = fptosi double %17 to i32
  ret i32 %18
}

declare i32 @"\01_usleep"(i32) #1

declare i32 @printf(i8*, ...) #1

attributes #0 = { noinline optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { noinline nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { noinline norecurse optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{!"clang version 8.0.1 (tags/RELEASE_801/final)"}
