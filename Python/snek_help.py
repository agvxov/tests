### Your Go code
#    case "out":
#        fmt.Println("Same as print, but without a newline at the end.")
#    case "join":
#        fmt.Println("Accepts two inputs - a list of strings to be joined and a delimiter.")
#    case "proc":
#        fmt.Println("Sets the number of cores used in the \"do\" blocks. It is recommended to use (system \"cores\") as the passed value, as it defaults to 4.")
#    case "prec":
#        fmt.Println("Sets the precision of decimals globally.")
#    case "str":
#        fmt.Println("Converts any data type to a string.")
#    case "len":
#        fmt.Println("Returns an int that represents the length of a list, array or the number of keys inside a pairing.")
#    case "list":
#        fmt.Println("The list maker function. Every argument becomes the returned list's item.")
#    case "goto":
#        fmt.Println("Allows navigating named code blocks marked using the \"set\" command.")

### Python equivalent because i dont know GO
v = "str"

if v == "out":
    print("Same as print, but without a newline at the end.")
elif v == "join":
    print("Accepts two inputs - a list of strings to be joined and a delimiter.")
elif v == "proc":
    print("Sets the number of cores used in the \"do\" blocks. It is recommended to use (system \"cores\") as the passed value, as it defaults to 4.")
elif v == "prec":
    print("Sets the precision of decimals globally.")
elif v == "str":
    print("Converts any data type to a string.")
elif v == "len":
    print("Returns an int that represents the length of a list, array or the number of keys inside a pairing.")
elif v == "list":
    print("The list maker function. Every argument becomes the returned list's item.")
elif v == "goto":
    print("Allows navigating named code blocks marked using the \"set\" command.")

### What you should be doing
v = "str"
help_table = {
	"out": "Same as print, but without a newline at the end.",
	"join": "Accepts two inputs - a list of strings to be joined and a delimiter.",
	"proc": "Sets the number of cores used in the \"do\" blocks. It is recommended to use (system \"cores\", as the passed value, as it defaults to 4.",
	"prec": "Sets the precision of decimals globally.",
	"str": "Converts any data type to a string.",
	"len": "Returns an int that represents the length of a list, array or the number of keys inside a pairing.",
	"list": "The list maker function. Every argument becomes the returned list's item.",
	"goto": "Allows navigating named code blocks marked using the \"set\" command.",
}

print(help_table[v])

### NOTES
# i dont know what kind of data structures you have access to, i guess while describing what i mean i wasnt clear about this,
#  if you can do simple look ups with actual dicts, do that, if not keep the key-value "structure", but just search
#  the container (that is how it would be done in plain C without involving extra work / dependencies)
