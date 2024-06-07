// @BAKE javac $@; java $*
public class JarmuProgram {
    public static
    void main(String[] argv) {
        Auto a = new Auto();
        System.out.println(a.getLoEro());
    }

    public static
    abstract class Jarmu {
        abstract double getLoEro();
    }

    public static
    class Auto extends Jarmu {
        Motor motor = new Motor();
        double getLoEro() {
            return motor.getLoEro() * 1.34;
        }
    }

    public static
    class Motor {
        double loero = 30;
        double getLoEro() {
            return loero;
        }
    }

}
