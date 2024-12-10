package com.example.furniture;

import org.springframework.data.jpa.repository.JpaRepository;

public interface FurnitureRepository extends JpaRepository<FurnitureApplication.Furniture, Long> {}
