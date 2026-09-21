# CS 149 - CountNames

## Students

- Ebsan Iqbal
- Raymond Okolo

## Description

`countnames` is a C program that reads names from a text input and counts how
many times each distinct name appears.

Each name is stored on a separate line. Names may contain spaces. Completely
empty lines are ignored and produce a warning on `stderr`. A line containing
one or more whitespace characters is still considered a valid name.

The program supports two methods of input:

1. A filename passed as a command-line argument.
2. Standard input (`stdin`) when no filename is provided.

Our implementation uses a hash table to store names and their occurrence
counts.

---

# Compilation

Compile the program with:

```bash
gcc -o countnames countnames.c -Wall -Werror
```

If compilation is successful, an executable named `countnames` is created.
The program should compile without warnings or errors.

---

# Running the Program

## Using a filename

```bash
./countnames test/names.txt
```

## Using standard input

```bash
cat test/names2.txt | ./countnames
```

Input redirection can also be used:

```bash
./countnames < test/names2.txt
```

---

# Provided Test Cases

## Test - names.txt

Command:

```bash
./countnames test/names.txt
```

Input:

```text
Nicky

Dave Joe
Yuan Cheng Chang

Dave Joe
John Smith
Yuan Cheng Chang
Yuan Cheng Chang
```

Expected output:

```text
Warning - Line 2 is empty.
Warning - Line 5 is empty.
Nicky: 1
Dave Joe: 2
Yuan Cheng Chang: 3
John Smith: 1
```

Purpose:

This test checks duplicate names, names containing spaces, and handling of
empty lines.

---

## Test - names1.txt

Command:

```bash
./countnames test/names1.txt
```

Input:

```text
Tom Wu
Tom Wu

Tom Wu
```

Expected output:

```text
Warning - Line 3 is empty.
Tom Wu: 3
```

Purpose:

This test checks repeated occurrences of the same name and verifies that an
empty line is ignored while producing a warning.

---

## Test - names2.txt

Command:

```bash
./countnames test/names2.txt
```

Input:

```text
Jenn Xu
Jenn Xu
Tom Wu
```

Expected output:

```text
Jenn Xu: 2
Tom Wu: 1
```

Purpose:

This test checks basic counting of repeated and distinct names.

---

## Test - namesB.txt

Command:

```bash
./countnames test/namesB.txt
```

Expected output:

```text
Warning - Line 2 is empty.
Warning - Line 5 is empty.
Nicky: 1
Dave Joe: 2
Yuan Cheng Chang: 3
John Smith: 1
```

Purpose:

This test checks duplicate counting, multi-word names, and empty-line
handling.

---

# Standard Input Test

Command:

```bash
cat test/names2.txt | ./countnames
```

Expected output:

```text
Jenn Xu: 2
Tom Wu: 1
```

Purpose:

This verifies that the program correctly reads names from `stdin` when no
filename is supplied as a command-line argument.

---

# stdout and stderr Test

To discard normal output and display only warnings sent to `stderr`:

```bash
./countnames test/names.txt > /dev/null
```

Expected output:

```text
Warning - Line 2 is empty.
Warning - Line 5 is empty.
```

To discard `stderr` and display only the normal name counts from `stdout`:

```bash
./countnames test/names.txt 2> /dev/null
```

Expected output:

```text
Nicky: 1
Dave Joe: 2
Yuan Cheng Chang: 3
John Smith: 1
```

Purpose:

This verifies that name counts are sent to `stdout`, while empty-line warnings
are sent to `stderr`.

---

# Student-Created Test Cases

## Test Case 1 - Duplicate Names

File:

```text
test/mytest1.txt
```

Input:

```text
Alice
Bob
Alice
Charlie
Bob
Alice
```

Command:

```bash
./countnames test/mytest1.txt
```

Expected output:

```text
Alice: 3
Bob: 2
Charlie: 1
```

Purpose:

This test verifies that several occurrences of the same names are counted
correctly. `Alice` occurs three times, `Bob` occurs twice, and `Charlie`
occurs once.

---

## Test Case 2 - Spaces and Case Sensitivity

File:

```text
test/mytest2.txt
```

Input:

```text
Tom Wu
tom wu
Tom Wu
Mary Jane
tom wu
```

Command:

```bash
./countnames test/mytest2.txt
```

Expected output:

```text
Tom Wu: 2
tom wu: 2
Mary Jane: 1
```

Purpose:

This test checks that names containing spaces are treated as complete names.
It also checks case sensitivity. `Tom Wu` and `tom wu` are different strings
and therefore must be counted separately.

---

## Test Case 3 - Empty Line and Whitespace-Only Name

File:

```text
test/mytest3.txt
```

The file contains:

```text
David

Sarah
 
David
```

Line 2 is completely empty. Line 4 contains exactly one space.

Command:

```bash
./countnames test/mytest3.txt
```

Expected output:

```text
Warning - Line 2 is empty.
David: 2
Sarah: 1
 : 1
```

Purpose:

This test verifies the difference between a completely empty line and a line
containing whitespace.

The empty line should be ignored and produce a warning. The line containing
one space is a valid name according to the assignment requirements and should
therefore be counted once.

---

## Test Case 4 - Completely Empty File

File:

```text
test/mytest4.txt
```

The file contains no data.

Command:

```bash
./countnames test/mytest4.txt
```

Expected output:

```text
(no output)
```

To verify the exit status:

```bash
echo $?
```

Expected result:

```text
0
```

Purpose:

This test verifies that the program handles a completely empty input file
correctly. It should produce no name counts or warnings and should exit
successfully with status code `0`.

---

# Large Provided Test Cases

The larger test files supplied with the assignment can be run with:

```bash
./countnames test/names_long.txt
./countnames test/names_long_redundant.txt
./countnames test/names_long_redundant1.txt
./countnames test/names_long_redundant2.txt
./countnames test/names_long_redundant3.txt
```

These files test the program with larger input streams and repeated names.
They help verify that the number of input lines processed by the program is
not artificially limited.

For a quick success check without displaying the potentially large normal
output, a test can also be run as:

```bash
./countnames test/names_long.txt > /dev/null
echo $?
```

A successful execution should return:

```text
0
```

---

# File Open Error Test

Command:

```bash
./countnames test/file_that_does_not_exist.txt
```

Expected error message:

```text
error: cannot open file
```

The exit status can be checked immediately afterward:

```bash
echo $?
```

Expected result:

```text
1
```

Purpose:

This test verifies that a failed `fopen()` is detected and that the program
returns a non-zero exit status for the error case.

---

# Lessons learned

This assignment helped us connect several C concepts that we had previously
seen separately.

We learned how command-line arguments work using `argc` and `argv`. When a
filename is supplied after the executable, `argv[1]` contains the filename
that the program needs to open.

We also learned how file input works in C. `fopen()` opens a file and returns
a `FILE *`, which can then be passed to functions such as `fgets()`. We
learned why the result of `fopen()` must be checked for `NULL` before using
the file.

Using `fgets()` also helped us understand why reading an entire line is
important for this assignment. A name such as `John Smith` contains a space,
so reading one whitespace-separated word at a time would not work correctly.

We learned more about how strings are represented in C. Strings are arrays of
characters ending with the null character `'\0'`. Since `fgets()` can include
the newline character from the input, that newline must be removed before a
name is stored or compared.

The assignment also helped us understand the difference between `stdout` and
`stderr`. Normal name counts are printed to `stdout`, while warnings about
empty lines are printed to `stderr`. We used UNIX redirection to verify the
two streams independently.

We also gained a basic understanding of hash tables. The hash function maps a
name to a location in the table. If multiple different names map to the same
location, the implementation handles the collision by keeping multiple names
and counts within that entry.

We also learned how dynamically allocated arrays can be expanded using
`realloc()` when more space is required.

Finally, we became more comfortable using a UNIX terminal to compile C code
with GCC, run executables using `./`, inspect test files, use pipes and
redirection, and check program exit statuses.

---

# References

1. CS 149 Operating Systems assignment instructions and course materials,
   San Jose State University.

2. zyBooks CS 149 course materials and C programming exercises.

3. C and UNIX manual pages and standard-library documentation for concepts
   and functions used in the assignment, including `fopen()`, `fgets()`,
   `fclose()`, `strlen()`, `strcmp()`, `malloc()`, and `realloc()`.

4. ChatGPT, OpenAI. Used as a learning resource for clarification of basic C
   and UNIX concepts including `stdout`, `stderr`, redirection, compilation,
   and testing.

   Shared conversation:

   https://chatgpt.com/share/6a9c6118-c224-83eb-9727-6192eb9360e9

5. Claude, Anthropic. Used as a learning resource for clarification of how
   `realloc()` works in C.

   Shared conversation:

   https://claude.ai/share/f705b6e7-b3c7-4a3a-8401-14c32c5fbb9d

---

# Acknowledgements

This assignment was completed collaboratively by Ebsan Iqbal and Raymond
Okolo.

We worked together on the `countnames` assignment, including the
hash-table-based implementation, testing, additional test-case development,
verification of program behavior, documentation, and execution evidence.

We also used the CS 149 course materials, zyBooks, C and UNIX documentation,
ChatGPT, and Claude as learning resources while understanding and testing the
concepts used in the assignment.
