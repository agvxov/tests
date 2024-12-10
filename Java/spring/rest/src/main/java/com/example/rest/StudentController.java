package myPackage;

import java.util.List;

import org.springframework.web.bind.annotation.*;

@RestController
class StudentController {

  private final StudentRepository repository;

  StudentController(StudentRepository repository) {
    this.repository = repository;
  }

  @GetMapping("/students")
  List<Student> all() {
    return repository.findAll();
  }
  
  @GetMapping("/students/{id}")
  Student one(@PathVariable Long id) {
    
    return repository.findById(id).orElse(null);
  }

  @PostMapping("/students")
  Student newStudent(@RequestBody Student newStudent) {
    return repository.save(newStudent);
  }

  @PutMapping("/students/{id}")
  Student replaceStudent(@RequestBody Student newStudent, @PathVariable Long id) {
    
    return repository.findById(id)
      .map(student -> {
        student.name = newStudent.name;
        student.age = newStudent.age;
        student.credit = newStudent.credit;
        return repository.save(student);
      })
      .orElseGet(() -> {
        newStudent.setId(id);
        return repository.save(newStudent);
      });
  }

  @DeleteMapping("/students/{id}")
  void deleteStudent(@PathVariable Long id) {
    repository.deleteById(id);
  }
}
