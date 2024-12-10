package example.gateway;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.gateway.route.builder.*;
import org.springframework.cloud.gateway.route.*;
import org.springframework.context.annotation.*;

@SpringBootApplication
public class GatewayApplication {
	@Bean
	public RouteLocator rl(RouteLocatorBuilder builder) {
		return builder.routes()
			.route("netcat-1", r -> r.path("/cat1")
				.uri("http://127.0.0.1:8081")
			)
			.route("netcat-2", r -> r.path("/cat2")
				.uri("http://127.0.0.1:8082")
			)
			.build();
	}

	public static void main(String[] args) {
		SpringApplication.run(GatewayApplication.class, args);
	}
}
