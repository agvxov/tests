// @BAKE javac $@ && java $*
// Java example to the decorator pattern
class Decorator {
    static
    class Canary {
        private
        String ascii = "   .-.    \n"
                     + "  /'v'\\   \n"
                     + " (/   \\)  \n"
                     + "='=\"=\"===<\n"
                     + "mrf|_|    \n"
                     ;
        public
        void print() {
            System.out.print(ascii);
        }
    }

    static
    class YellowCanary extends Canary {
        public
        void print () {
            System.out.println("\033[33m");
            super.print();
            System.out.println("\033[0m");
        }
    }

    public static
    void main(String[] args) {
        Canary sunny = null;
        sunny = new Canary();
        sunny.print();
        sunny = new YellowCanary();
        sunny.print();
    }
}
