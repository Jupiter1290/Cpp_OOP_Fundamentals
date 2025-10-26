# Odd–Even Vehicle Allowance Simulator

A small C++ program that simulates vehicle entry policy over multiple days using an odd–even registration rule.

## Purpose
Given a daily vehicle list, the program evaluates which vehicles are allowed based on:
- Day parity (odd or even day)
- Vehicle registration id parity (odd or even id)

It demonstrates:
- Abstract base class and pure virtual method (`Vehicle::isAllowed`)
- Derived classes `twoWheeler` and `fourWheeler`
- Run-time polymorphism and `unique_ptr` usage
- Use of `static` class counters to aggregate statistics

## Features
- Reads per-day vehicle entries from user input
- Calculates how many vehicles are allowed each day and updates global counts
- Produces a final report listing:
  - total vehicles allowed on odd/even days
  - breakdown of 2-wheelers and 4-wheelers allowed on odd and even days


