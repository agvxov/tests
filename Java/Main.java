/* @BAKE
    /opt/openjdk-bin-21.0.1_p12/bin/javac $@ 
    /opt/openjdk-bin-21.0.1_p12/bin/java $*.java
   @STOP
*/
class Main {
    public static
    class Singleton {
        private int field;
        private static Singleton inst;

        private
        Singleton() {
            super();
            System.out.println("const call");
            field = 10;
        }

        public static
        synchronized
        Singleton getInstance() {
            if (inst == null) {
                inst = new Singleton();
            }
            return inst;
        }
    }

    public static
    void main(String[] args) {
        Singleton s1 = Singleton.getInstance();
        Singleton s2 = Singleton.getInstance();
    }
}
