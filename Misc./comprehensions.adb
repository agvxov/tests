-- @BAKE gnatmake-10 -gnat2022 -o comprehender $@

procedure Comrehension is
	type Integer_Array is array (Positive range <>) of Integer;
	Vector : Integer_Array := [for J in 1 .. 5 => J * 2];
begin
	null;
end Comrehension;
