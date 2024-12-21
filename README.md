### dir-organizer
****

**Compiling:**
```bash
gcc main.c -o main
```
****

**Usage 1:**
```bash
./main
Enter the path to directory: </path/to/directory>
```
**Usage 2:**
```bash
./main </path/to/directory>
```
****

**Test:**

*test/create-test.py* create "sample_data/", random files and folders in **n** range.

```bash
python test/create-test.py
Enter range => <n>
```
```bash
./main sample_data
```