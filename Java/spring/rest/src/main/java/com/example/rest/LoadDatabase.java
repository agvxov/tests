package myPackage;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.boot.CommandLineRunner;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

import com.github.javafaker.Faker;

@Configuration
class LoadDatabase {

  private static final Logger log = LoggerFactory.getLogger(LoadDatabase.class);

  @Bean
  CommandLineRunner initDatabase(StudentRepository repository) {

    return args -> {
		Faker faker =  new Faker();
		for (int i = 0; i < 100; i++) {
			log.info("Preloading " + repository.save(
		  		new Student(
					faker.name().firstName(),
					faker.number().numberBetween(18, 22),
					faker.number().numberBetween(0, 300))
				)
			);
		}
    };
  }
}
