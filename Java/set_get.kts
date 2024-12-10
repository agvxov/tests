// @BAKE kotlin $@
class Book {
    var author = ""
        get(){
            field = field.uppercase();
            return field;
        }
        set(value){
            field = value;
            field = field.trim();
        }
    ;
}

var book = Book();
book.author = "        Dmitry Glukhovsky ";
println(book.author)
