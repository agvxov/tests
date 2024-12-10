package myPackage;


import java.util.Objects;

import jakarta.persistence.*;

@Entity
public class Student {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

	public int age;
	public String name;
	public int credit;

	public void setId(Long id){
		this.id = id;
	}

	public Long getId(){
		return this.id;
	}

	Student() {}
	Student(String n, int a, int c) {
		this.age = a;
		this.credit = c;
		this.name = n;
	}

	@Override
	public String toString() {
		return String.format("(Student){%s, %d, %d}", this.name, this.age, this.credit);
	}
}
