package com.example.sql;

import org.springframework.data.jpa.repository.JpaRepository;

public interface SheepRepository extends JpaRepository<SqlApplication.Sheep, Long> {}
