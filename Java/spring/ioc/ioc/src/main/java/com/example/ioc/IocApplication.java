package com.example.ioc;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class IocApplication {

	public static void main(String[] args) {
		BeanChild c = new BeanChild();
		SpringApplication.run(IocApplication.class, args);
	}

}