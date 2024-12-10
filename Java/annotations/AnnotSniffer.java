public class AnnotSniffer {
	public static void sniff(Class c) {
		if (c.isAnnotationPresent(annot.class)) {
			System.out.println("Bar");
		} else {
			System.out.println("");
		}
	}
}
