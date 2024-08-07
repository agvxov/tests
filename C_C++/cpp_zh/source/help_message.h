/* a main "shell"-hez szolgáló segítség üzenet;
 *  külön fájlban mert én így személyesen egyszerűbbnek találom szerkeszteni;
 *  ".h" amiért semmilyen C++ specifikus bővítményt nem tartalmaz és nem is kell neki
 */
const char help_message[] =
	" === SÚGÓ ===\n"
	"| :---------: | :--------: | :-------: |\n"
	"|    Állás    |    Class   | Rövidités |\n"
	"| :---------: | :--------: | :-------: |\n"
	"| Alkalmazott | Worker     |         w |\n"
	"| Szerződéses | Contractee |         c |\n"
	"| Vezető      | Manager    |         m |\n"
	"| :---------: | :--------: | :-------: |\n"
	"Elérhető parancsok:\n"
	"\tc <állás> <név>        # új dolgozó hozzá adása\n"
	"\ti <id>                 # dolgozó részletes lekérdezése\n"
	"\tm <id> <field>=<value> # dolgozó módosítása\n"
	"\t\tA következő mezők módosíthatók a dolgozó pozíciójától függően:\n"
	"\t\t-- Közös\n"
	"\t\t  birth        : egész\n"
	"\t\t-- Worker\n"
	"\t\t  pay          : egész\n"
	"\t\t  performance  : byte[7] # ellenőrzött\n"
	"\t\t-- Contractee\n"
	"\t\t  pay          : egész\n"
	"\t\t  hour         : egész\n"
	"\t\t-- Manager\n"
	"\t\t  pay          : egész\n"
	"\td <id>                 # törlése\n"
	"\tl                      # info dump (mint a kezdő képernyőn)\n"
	"\tr                      # biztonsági mentés be olvasása; megjegyzés: hozzáfüz\n"
	"\tw                      # biztonságimentés írása fölül \n"
	"Keresést '/' prefix-el lehet kezdeményezni.\n"
	"Minden találat az 'i' parancsnak megfelelően lesz megjelenítve.\n"
	"\tPélda:\n"
	"\t\t/a\t# Minden alkalmazott akinek a neve \"a\" szöveget tartalmaz\n"
;
