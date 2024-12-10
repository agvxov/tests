unit Unit10; // MONTE-CARLO

interface

uses
    Windows, Messages, SysUtils, Variants, Classes, Graphics,
    Controls, Forms, Dialogs, StdCtrls, ExtCtrls, math;

type
    TForm10 = class(TForm)
    Panel1: TPanel;
    Button1: TButton;
    Button2: TButton;
    Button5: TButton;
    Button6: TButton;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    procedure Button6Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure kezdet(Sender: TObject);
    procedure Button2Click(Sender: TObject);
private
    { Private declarations }
    procedure Torles;
    procedure TengelyX;
    procedure TengelyY;
    procedure BeosztasX(i:real);
    procedure PirosPont(a,b:real);
    procedure KekPont(a,b:real);
    procedure fuggvenyabra;
    function fuggveny(t:real):real;
    function primitivfgv(t:real):real;
    procedure ertekkeszlet;
public
    { Public declarations }
end;

var
    Form10: TForm10;
    x1,x2,y1,y2:real;
    pontszam,gyak:integer;

implementation
uses
    Unit1, Unit11;

{$R *.dfm}

// BEGIN
procedure TForm10.kezdet(Sender: TObject);
begin
    panel1.Left:=trunc((screen.Width-panel1.Width)/2);
    button1.Top:=screen.Height-30;
    button2.Top:=screen.Height-30;
    button5.Top:=screen.Height-30;
    button6.Top:=screen.Height-30;
    label1.Top:=5;
    label2.Top:=label1.Top+label1.height+5;
    label3.Top:=label2.Top+label2.height+5;
    label4.Top:=screen.Height-25;
    button1.Enabled:=true;
    button2.Enabled:=false;
    button5.Enabled:=true;
    button6.Enabled:=true;
end;
// CLOSE
procedure TForm10.Button6Click(Sender: TObject);
begin
    form1.Close;
end;
end.
