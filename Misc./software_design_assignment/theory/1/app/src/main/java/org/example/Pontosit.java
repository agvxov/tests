package egerTavolsag;

import java.util.*;
import java.io.*;
import java.net.URL;

public
class Pontosit {
    private String filename;

    public
    Pontosit(String filename_) {
        filename = filename_;
    }

    public
    void pontosit(Pontosithato p) throws IOException {
        URL resource = getClass().getClassLoader().getResource(filename);
        if (resource == null) { throw new IOException(); }
        File file = new File(resource.getFile());
        BufferedReader reader = new BufferedReader(new FileReader(file));
        String line;
        String key;
        int value;
        
        while ((line = reader.readLine()) != null) {
            String[] parts = line.split(";");
            
            if (parts.length != 2) {
                throw new IOException();
            }

            key = parts[0].trim();
            try {
                value = Integer.parseInt(parts[1].trim());
            } catch (NumberFormatException e) {
                throw new IOException();
            }
                
            p.pontositasando(key, value);
        }
    }
}
