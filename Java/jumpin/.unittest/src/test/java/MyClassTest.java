// @BAKE java MyClassTest.java
import org.junit.Test;
import static org.junit.Assert.assertEquals;

public class MyClassTest {

    @Test
    public void testAdd() {
        MyClass myClass = new MyClass();
        int result = myClass.add(2, 3);
        assertEquals("Sum should be 5", 5, result);
    }
}
