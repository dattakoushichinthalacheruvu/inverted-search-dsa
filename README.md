# Inverted Search - DSA Project

An efficient Inverted Search Engine implemented in C using Hash Tables. Searches for any word across multiple text files instantly.

### Features
- Creates inverted index of words from multiple files
- Fast search using Hash Table
- Displays file names where word is found
- Shows number of occurrences per file
- Handles multiple file inputs
- Save and update database

### How it Works
- Reads all input text files
- Tokenizes words and hashes them
- Stores in hash table with linked list of files
- For search query, hash the word and traverse list

### Data Structures Used
- Hash Table
- Singly Linked List
- File Handling

### Tech Stack
- Language: C
- Concepts: Hashing, DSA, File I/O
- Compiler: GCC

### How to Run
```bash
gcc main.c file_list.c create_database.c search.c display.c save.c update.c -o inverted_search
./inverted_search file1.txt file2.txt file3.txt
# Menu:
# 1. Create Database
# 2. Display Database
# 3. Search
# 4. Save Database
# 5. Update Database
