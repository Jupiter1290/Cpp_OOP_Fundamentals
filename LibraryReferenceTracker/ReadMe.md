# Library Reference Tracker

This C++ program simulates a basic library system that tracks how often each book is referenced.  
It demonstrates object-oriented design principles, smart pointer usage, and formatted data visualization.

---

## Purpose
The program maintains a list of books, each with:
- **Title**
- **Department**
- **Reference count**

Users can interactively:
1. Refer to a book (increments its reference count)
2. Display all books with current reference counts
3. Display the least-referenced book(s)

---

## Key Concepts Demonstrated
- **Classes and Encapsulation:** The `Book` class encapsulates book data and reference behavior.  
- **Smart Pointers:** `std::unique_ptr` ensures safe, automatic memory management.  
- **Containers:** Uses `std::vector` for dynamic book collection.  
- **Input Handling:** Uses formatted console input/output for clean interaction.  
- **Formatted Output:** Uses `<iomanip>` for table-style display.

---

## Features
- Add an initial list of books interactively.  
- Refer to books by title (search by string).  
- Display all books with their departments and reference counts.  
- Identify and display the least-referenced book(s).  
- Clean and simple menu-driven interface.

---
