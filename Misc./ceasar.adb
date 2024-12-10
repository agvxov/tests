-- @BAKE gnatmake-10 $@
with Ada.Text_IO;           use Ada.Text_IO;
with Ada.Command_Line;      use Ada.Command_Line;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;

procedure Ceasar is
    Offset        : Integer;
    Message       : Unbounded_String;

    procedure Ceasar_Char(Offset : in Integer; Char : in Character) is 
        ASCII_ALPHA_OFFSET : constant Integer := 97;

        subtype Alphabet_Char     is Character range 'a' .. 'z';
        type    Alpha_Constrainer is mod 26;

        Conversion_Character : Alphabet_Char;
        Constrainer          : Alpha_Constrainer;
    begin
        begin
            Conversion_Character := Char;
            Constrainer          := Alpha_Constrainer((Character'Pos(Conversion_Character) - ASCII_ALPHA_OFFSET));
            Constrainer          := Constrainer + Alpha_Constrainer'Mod(offset);
            Conversion_Character := Character'Val(ASCII_ALPHA_OFFSET + Integer(Constrainer));
            Put("" & Conversion_Character);
        exception
            when Constraint_Error => Put("?");
        end;
    end Ceasar_Char;

begin

    if Argument_Count /= 2 then
        Put_Line("ceasar <offset> <message>");
        Set_Exit_Status(1);
        return;
    end if;

    Offset  := Integer'Value(Argument(1));
    Message := To_Unbounded_String(Argument(2));

    for Index in 1 .. Length(Message) loop
        Ceasar_Char(Offset, Element(Message, Index));
    end loop;

end Ceasar;
