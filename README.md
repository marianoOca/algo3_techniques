# Algorithmic Techniques – Algorithms and Data Structures III

The project explores the implementation and performance comparison of multiple algorithmic strategies — including **Backtracking**, **Dynamic Programming**, and **Greedy Algorithms** — across four different optimization problems.

---

## 📌 Project Overview

The assignment was divided into four main exercises, each focused on solving a classic algorithmic problem using a different technique:

1. **Backtracking**: Finding the most influential clique in a social network.
2. **Backtracking with Pruning**: Improved clique search using bounding techniques.
3. **Dynamic Programming**: Activity selection to maximize total benefit without overlap.
4. **Greedy Algorithm**: Optimized activity selection when all benefits are equal.

Each implementation includes:
- Problem modeling
- Algorithm design and complexity analysis
- Experimental results

---

## 🧠 Topics Covered

- Recursive backtracking with state pruning
- Clique detection in graphs
- Dynamic programming for activity selection
- Greedy heuristics and correctness proofs
- Algorithmic complexity trade-offs
- Performance benchmarking and input ordering effects

---

## 🗂️ Repository Structure

```
📁 src/
├── ejercicio1_bt/          # Backtracking for maximum clique
├── ejercicio2_bt_poda/     # Backtracking with pruning
├── ejercicio3_dp/          # Dynamic programming for activity selection
├── ejercicio4_greedy/      # Greedy activity selection
📄 informe.pdf              # Final report (original, in Spanish)
📄 README.md                # This file
```

---

## 🧪 Benchmarking

All implementations were tested on a variety of real-world and synthetic graph datasets.  
Key observations:
- Sorting input data (e.g., by influence) can significantly impact performance in backtracking.
- Pruning strategies reduce runtime on large inputs but don’t always outperform simpler versions.
- Greedy algorithms are correct only under specific constraints (e.g., equal weights).

Detailed performance results and analysis are available in the [informe.pdf](./informe.pdf) file.

---

## 📚 Academic Context

- 📘 Course: *Algorithms and Data Structures III*  
- 🏛️ University: Universidad de Buenos Aires – Facultad de Ciencias Exactas y Naturales  
- 📅 Term: 1st semester of 2022  
- 🧑‍💻 Language: C++ and Python

---

## 📄 Final Report

The original project report (in Spanish), including full algorithm explanations, proofs, pseudocode, and performance graphs, is available here:

📄 [informe.pdf](./informe.pdf)

---

## 📑 License

This project is for academic and educational purposes only.
