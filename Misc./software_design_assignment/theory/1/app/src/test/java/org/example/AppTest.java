package egerTavolsag;

import java.util.*;
import java.io.*;
import java.net.URL;
import org.junit.Test;
import static org.junit.Assert.*;

public class AppTest {
    @Test
    public
    void test_new_evertavolsag() {
        var e = new EgerTavolsag(); // could throw
    }

    @Test(expected = IOException.class)
    public
    void test_new_pontosit() throws IOException {
        var p = new Pontosit("no_such_file_exists.txt");
        var e = new MockPontosithato();
        p.pontosit(e);
    }

    @Test
    public
    void test_pontosit() throws IOException {
        HashMap<String, Integer> expected = new HashMap<String, Integer>();
        expected.put("Budapest", 140);
        expected.put("Szeged", 200);

        var e = new MockPontosithato();
        var p = new Pontosit("mock_updates.txt");
        p.pontosit(e);

        assertEquals(expected, e.map);
    }

    @Test(expected = SajatKivetel.class)
    public
    void test_kivitelezheto_null() throws SajatKivetel {
        var e = new EgerTavolsag();
        e.kivitelezheto(null);
    }

    @Test
    public
    void test_kivitelezheto() throws SajatKivetel {
        var e = new EgerTavolsag();
        var utvonal = new ArrayList<String>();
        utvonal.add("Budapest");

        assertEquals(e.kivitelezheto(utvonal), true);
    }

    @Test
    public
    void test_kivitelezheto_false() throws SajatKivetel {
        var e = new EgerTavolsag();
        var utvonal = new ArrayList<String>();
        utvonal.add("Budapest");
        utvonal.add("Győr");
        utvonal.add("Szeged");
        utvonal.add("Pécs");

        assertEquals(e.kivitelezheto(utvonal), false);
    }

    @Test
    public
    void test_tavolsag_pontositas() throws SajatKivetel {
        var e = new EgerTavolsag();
        assertEquals((long)e.getTavolsag("Budapest"), 124);
    }
}
