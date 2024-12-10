package com.example.Farm;

import java.util.List;
import jakarta.persistence.*;
import org.springframework.boot.*;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.*;
import org.springframework.web.bind.annotation.*;
import org.springframework.ui.Model;
import org.springframework.web.servlet.ModelAndView;
import org.springframework.security.web.SecurityFilterChain;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import static org.springframework.security.config.Customizer.withDefaults;

@SpringBootApplication
public
class FarmApplication {
	public
	record FarmAnimal(String name, String animal, String type, int quantity, String location) {
	}

	@Entity
	public static
	class Animal {
		@Id
		@GeneratedValue(strategy = GenerationType.IDENTITY)
		Long id;

		public String name;
		int age;
		int weight;

		Animal() { ; }
		Animal(String name, int age, int weight) {
			this.name = name;
			this.age = age;
			this.weight = weight;
		}

		public int getAge(){
			return this.age;
		}
	}

	@RestController
	static
	class Controller {
		private final
		AnimalRepository repository;

		Controller(AnimalRepository repository) {
			this.repository = repository;
		}

		@GetMapping("/")
		ModelAndView index(){
			ModelAndView mav = new ModelAndView();
			mav.setViewName("index");
			return mav;
		}

		@GetMapping("/list")
		List<Animal> say_hello(){
			return repository.findAll();
		}

		@GetMapping("/login")
		String login(){
			return "login";
		}

		@GetMapping("/secret")
		ModelAndView secret(){
			ModelAndView mav = new ModelAndView();
			mav.setViewName("secret");
			return mav;
		}
	}

	@Bean
	public
	CommandLineRunner cmdlr(AnimalRepository repository) {
		return (args) -> {
			repository.save(new Animal("Bob", 3, 10));
		};
	}

	@Bean
	public
	SecurityFilterChain myFilter(HttpSecurity http) throws Exception {
		return http
				.authorizeHttpRequests(
					auth -> {
						auth.requestMatchers("/secret").authenticated();
						auth.requestMatchers("/*").permitAll();
					}
				)
				.oauth2Login(withDefaults())
				.build()
		;
	}

	public static
	void main(String[] args) {
		SpringApplication.run(FarmApplication.class, args);
	}

}
