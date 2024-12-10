package com.example.Farm;

import org.springframework.data.jpa.repository.JpaRepository;

public interface AnimalRepository extends JpaRepository<FarmApplication.Animal, Long> {}

