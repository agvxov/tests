@Configuration
@ComponentScan(basePackageClasses = BeanChild.class)
public class BeanConfiguration {
	@Bean
	public BeanParent getBeanParent() {
		return new BeanParent(2000);
	}
}
