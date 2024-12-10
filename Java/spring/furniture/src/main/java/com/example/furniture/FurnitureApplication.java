package com.example.furniture;

import java.util.List;
import jakarta.persistence.*;
import org.springframework.boot.*;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.*;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.ModelAndView;
import org.slf4j.LoggerFactory;
import org.slf4j.Logger;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.springframework.util.MultiValueMap;

@SpringBootApplication
public class FurnitureApplication {
	@Entity
	public static
	class Furniture {
		@Id
		@GeneratedValue(strategy = GenerationType.IDENTITY)
		public
		Long id;

		public
		String name;

		private
		int price;

		Furniture(String name, int price) {
			this.name = name;
			this.price = price;
		}
		Furniture() { ; }
	}

	@RestController
	static
	class Controller {
		private final
		FurnitureRepository repository;
		
		static private
		Logger logger = LoggerFactory.getLogger("connectionLogger");

		Controller(FurnitureRepository repository) {
			this.repository = repository;
		}

		@GetMapping("/")
		ModelAndView index(){
			logger.info("connection");
			ModelAndView mav = new ModelAndView();
			mav.addObject("title", "Furniture list:");
			mav.addObject("furnitures", this.repository);
			mav.setViewName("inde");
			return mav;
		}

		@PostMapping("/")
		ModelAndView indexPost(@RequestBody MultiValueMap<String, String> data) {
			ObjectMapper objectMapper = new ObjectMapper();
			try {
				logger.info("post: " + objectMapper.writeValueAsString(data));
				repository.save(new Furniture(data.getFirst("name"), 0));
			} catch(Exception e) { ; }
			return index();
		}

		//@GetMapping("/error")
		//ModelAndView error(){
		//	ModelAndView mav = new ModelAndView();
		//	mav.setViewName("error");
		//	return mav;
		//}
	}

	public static void main(String[] args) {
		SpringApplication.run(FurnitureApplication.class, args);
	}

}
