-- @BAKE gnatmake-10 -gnat2022 -o vigenere_cipher $@
-- NOTE: this code is broken
with Ada.Command_Line;
with Ada.Strings.Unbounded;
with Ada.Text_IO;
use Ada.Text_IO;
use Ada.Command_Line;
use Ada.Strings.Unbounded;

procedure Vigenere is
	type Letter       is new Character range 'a' .. 'z';
	type Tabula_Recta is     array(0 .. 25, 0 .. 25) of Letter;

	t: Tabula_Recta;

	is_decrypt_mode:	Boolean;
	secret:				Ada.Strings.Unbounded.Unbounded_String;
	message: 			Unbounded_String;

	Usage_exception: exception;

	procedure Help is
	begin
		Ada.Text_IO.Put_Line("[c|x|p] <secret> <message>");
		return;
	end Help;

	procedure Fill_Tabula_Recta(t: Tabula_Recta) is
		type Tabula_Recta_source is array (Positive range <>) of Letter;
		source : array(0 .. 25) of Letter := [for i in 'a' .. 'z' => i];
	begin
		--source := ('a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'); -- allowed
		for i in 1 .. 25 loop
			null;
		end loop;
	end Fill_Tabula_Recta;

	procedure Print_Tabula_Recta(t: Tabula_Recta) is
	begin
		for i in 0 .. 25 loop
			for h in 0 .. 25 loop
				Ada.Text_IO.Put(t(i, h)'Image & ' ');
			end loop;
			Ada.Text_IO.Put_Line("");
		end loop;
	end Print_Tabula_Recta;

	function Decrypt(t       : Tabula_Recta;
	                 secret  : Ada.Strings.Unbounded.Unbounded_String;
	                 message : Ada.Strings.Unbounded.Unbounded_String)
	return Ada.Strings.Unbounded.Unbounded_String is
		r: Ada.Strings.Unbounded.Unbounded_String;
	begin
		return r;
	end Decrypt;

	function Encrypt(t       : Tabula_Recta;
	                 secret  : Ada.Strings.Unbounded.Unbounded_String;
	                 message : Ada.Strings.Unbounded.Unbounded_String)
	return Ada.Strings.Unbounded.Unbounded_String is
		r: Ada.Strings.Unbounded.Unbounded_String;
	begin
		return r;
	end Encrypt;
begin
	begin
		if Ada.Command_Line.Argument_count /= 3 then
			raise Usage_exception;
		end if;

		case Ada.Command_Line.Argument(1)(1) is
			when 'x' =>
				is_decrypt_mode := True;
			when 'c' =>
				is_decrypt_mode := False;
			when 'p' =>
				Fill_Tabula_Recta(t);
				Print_Tabula_Recta(t);
				return;
			when others =>
				Ada.Text_IO.Put_Line(
					"Unknown operation: '" & Ada.Command_Line.Argument(1)(1)'Image & "'"
				);
				raise Usage_exception;
		end case;

		secret  := Ada.Strings.Unbounded.To_Unbounded_String(Ada.Command_Line.Argument(2));
		message := Ada.Strings.Unbounded.To_Unbounded_String(Ada.Command_Line.Argument(3));
	exception
		when Usage_exception =>
			Help;
			return;
	end;

	Fill_Tabula_Recta(t);
	Print_Tabula_Recta(t);

end Main;
