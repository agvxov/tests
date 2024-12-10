@annot
public class Main {
	public static void main(String args[]) {
		System.out.print("Foo");
		AnnotSniffer.sniff(Main.class);
		MyGeneric<Integer> a = new MyGeneric<>(10);
		MyGeneric<?>       b = new MyGeneric<>("asd");
	}
}
