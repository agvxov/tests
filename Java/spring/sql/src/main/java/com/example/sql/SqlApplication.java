package com.example.sql;

import java.util.List;
import jakarta.persistence.*;
import org.slf4j.*;
import org.springframework.boot.*;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.*;
import org.springframework.web.bind.annotation.*;
import org.springframework.data.jpa.repository.Query;

@SpringBootApplication
public class SqlApplication {

	@Entity
	public
	class Sheep {
		@Id
		@GeneratedValue(strategy = GenerationType.IDENTITY)
		public Long id;
		public String name;

		Sheep(String name_) {
			this.name = name_;
		}
	}

	public static void main(String[] args) {
		SpringApplication.run(SqlApplication.class, args);
	}

	@Bean
	public
	CommandLineRunner cmdlr(SheepRepository repository) {
		return (args) -> {
			repository.save(new Sheep("Ross"));
			repository.save(new Sheep("Joe"));
		};
	}

}
