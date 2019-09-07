; ModuleID = '/Users/cijiexia/Project/lljb/test/cpp/structs.cpp'
source_filename = "/Users/cijiexia/Project/lljb/test/cpp/structs.cpp"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.14.0"

%struct.Foo = type { i32, [2 x i32] }

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @_Z14fooMemberAdderP3Foo(%struct.Foo*) #0 {
  %2 = alloca %struct.Foo*, align 8
  store %struct.Foo* %0, %struct.Foo** %2, align 8
  %3 = load %struct.Foo*, %struct.Foo** %2, align 8
  %4 = getelementptr inbounds %struct.Foo, %struct.Foo* %3, i32 0, i32 0
  %5 = load i32, i32* %4, align 4
  %6 = load %struct.Foo*, %struct.Foo** %2, align 8
  %7 = getelementptr inbounds %struct.Foo, %struct.Foo* %6, i32 0, i32 1
  %8 = getelementptr inbounds [2 x i32], [2 x i32]* %7, i64 0, i64 1
  %9 = load i32, i32* %8, align 4
  %10 = add nsw i32 %5, %9
  ret i32 %10
}

; Function Attrs: noinline norecurse nounwind optnone ssp uwtable
define i32 @main() #1 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca %struct.Foo, align 4
  store i32 0, i32* %1, align 4
  store i32 1, i32* %2, align 4
  %4 = getelementptr inbounds %struct.Foo, %struct.Foo* %3, i32 0, i32 0
  %5 = load i32, i32* %2, align 4
  store i32 %5, i32* %4, align 4
  %6 = getelementptr inbounds %struct.Foo, %struct.Foo* %3, i32 0, i32 1
  %7 = getelementptr inbounds [2 x i32], [2 x i32]* %6, i64 0, i64 0
  store i32 1, i32* %7, align 4
  %8 = getelementptr inbounds i32, i32* %7, i64 1
  store i32 2, i32* %8, align 4
  %9 = call i32 @_Z14fooMemberAdderP3Foo(%struct.Foo* %3)
  ret i32 %9
}

attributes #0 = { noinline nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { noinline norecurse nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{!"clang version 8.0.1 (tags/RELEASE_801/final)"}
