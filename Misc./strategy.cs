// @BAKE mcs -out:$*.exe $@ && mono $*.exe
using System;
using System.Collections.Generic;

// --- Stratigized behaviour ---
public interface Operation {
    string description { get; set; }
    ConsoleColor color { get; set; }
    void action();
}

public class ToDown : Operation {
    public string description { get; set; }
    public ConsoleColor color { get; set; }
    public void action() {
        int n = Menu.items.FindIndex(o => o.operation == this);
        if (n != Menu.items.Count-1) {
            Menu.swap(n, n+1);
        } else {
            Menu.swap(0, n);
        }
    }
}
public class ToUp : Operation {
    public string description { get; set; }
    public ConsoleColor color { get; set; }
    public void action() {
        int n = Menu.items.FindIndex(o => o.operation == this);
        if (n != 0) {
            Menu.swap(n-1, n);
        } else {
            Menu.swap(n, Menu.items.Count-1);
        }
    }
}
public class ToTop : Operation {
    public string description { get; set; }
    public ConsoleColor color { get; set; }
    public void action() {
        int n = Menu.items.FindIndex(o => o.operation == this);
        Menu.swap(0, n);
    }
}

// --- Root object ---
public class Item {
    public string name { get; set; }
    public ConsoleColor color { get; set; }
    public Operation operation { get; set; }
}
// --- Demo ---
public class Menu {
    public static List<Item> items = new List<Item>();

    public static void swap(int a, int b) {
        Operation swap = items[a].operation;
        Menu.items[a].operation = Menu.items[b].operation;
        Menu.items[b].operation = swap;
    }

    public static void print() {
        foreach (var item in items) {
            Console.ForegroundColor = item.color;
            Console.WriteLine($"{item.name}:");
            Console.ForegroundColor = item.operation.color;
            Console.WriteLine($"  { item.operation.description}\n");
            Console.ResetColor();
        }
    }

    public static void Main(string[] args) {
        items.Add(new Item { name = "Item 1", color = ConsoleColor.Yellow,
            operation = new ToUp { description = "Move up", color = ConsoleColor.Yellow }
        });
        items.Add(new Item { name = "Item 2", color = ConsoleColor.Green,
            operation = new ToDown { description = "Move down", color = ConsoleColor.Green }
        });
        items.Add(new Item { name = "Item 3", color = ConsoleColor.Blue,
            operation = new ToTop { description = "Move to top", color = ConsoleColor.Blue }
        });

        while (true) {
            print();
            Console.Write("$ ");
            string input = Console.ReadLine();
            if (string.IsNullOrEmpty(input)) continue;
            if (int.TryParse(input, out int number)) {
                if (number > 0 && number <= items.Count) {
                    items[number - 1].operation.action();
                }
            }
        }
    }
}
