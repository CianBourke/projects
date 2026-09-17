# Production Sorting & Search System

## About
I built this in my first year of college as a Data Structures & Algorithms end-of-year assignment during my time at TU Dublin. It's a C program that processes 
production data across multiple delivery batches — sorting, merging, searching, and reporting on it using classic algorithms, each with a required time complexity.
This was the hardest project I'd worked on at the time. The brief set four separate tasks, each with its own Big-O requirement, and getting all four 
to actually meet their complexity targets (not just "work") took a lot of testing and re-checking. It was my first real experience working with algorithms 
and Big O notation properly, rather than just as a theoretical topic.

## What it does
- Combines four separate batches of production data into a single dataset
- Sorts the combined dataset by weight using merge sort
- Searches for the earliest product matching a given weight using binary search
- Generates a summary report (total weight, total price, product count) for any batch or the combined dataset

## Assignment requirements
The brief set four tasks, each with a required time complexity:

| Task | Requirement | Complexity |
|------|-------------|------------|
| 1 | Sort production data by weight | O(N log N) |
| 2 | Merge multiple structure arrays into a single list | O(N) or better |
| 3 | Search for the earliest occurrence of a product by weight | O(log N) or better |
| 4 | Generate a summary report of products across all delivery batches | O(N) or better |

## Tech used
- C
- GCC

## Files
| File | Description |
|---|---|
| `Assignment_Fixed.c` | Full program: data setup, merge sort, binary search, and report generation |

## What I learned
- Implementing merge sort and binary search from scratch, and reasoning about why each one meets its required time complexity
- Working with arrays of structs in C, including merging and searching across them
- Why exact floating-point equality comparisons are unreliable, and how to use a tolerance-based comparison instead
- How to read and debug compiler warnings (`-Wall -Wextra`) to catch real issues like buffer overflows and dead code

## Known limitations
These are things that would need to be addressed if this were developed further:
- The current implementation concatenates all four batches into a single array first, then sorts the whole thing once. An alternative reading of the brief would be to sort each batch individually first and then properly merge the four pre-sorted batches together. Both meet the overall O(N log N) requirement, but they demonstrate the merge step differently.
- The `date` field is stored as a fixed-size array (`int date[SIZE]`) even though it only ever holds a single value — a plain `int` would be a cleaner fit.
- All batch data is hardcoded directly in the source file rather than read from an external file (e.g. CSV) at runtime.
- User input isn't validated beyond basic buffer-size protection — an invalid entry (like a letter instead of a number) isn't explicitly handled.

## How to run
1. Make sure you have `gcc` installed
2. Compile the program, linking the math library (needed for the floating-point comparison):
   ```bash
   gcc Assignment_Fixed.c -o assignment -Wall -Wextra -lm
   ```
3. Run the compiled program:
   ```bash
   ./assignment
   ```

note: `-lm` is required here because the binary search uses `fabsf()` from the standard math library. Without it, you'll get an "undefined reference to `fabsf`" error at compile time.

## Post-Submission Changes
This version includes a few small improvements made after the assignment was submitted and graded, intended to make the code more clean and easier to read:
- Fixed a buffer size issue that could cause a stack overflow on user input
- Removed an unused global variable
- Replaced an exact floating-point equality check in the binary search with a tolerance-based comparison, since comparing floats with `==` is unreliable
- Cleaned up inconsistent and outdated comments

The original submitted logic and structure are otherwise unchanged.
