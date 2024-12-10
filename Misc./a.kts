// @BAKE kotlin $@
class Language(val name : String, var bullshit_score : Int) {}
var kotlin = Language("Kotlin", 3);
//println(kotlin);

var i = 3;
println("Interpolated ${i}")
println("--- ${i * 2} ---")

println("A" to "B")
