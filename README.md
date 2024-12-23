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

*test/create-test.py* create "sample_data/":
- **mode 1** --> *n* random files
- **mode 2** --> *n* random files and folders (with subfolders)

```bash
python test/create-test.py
Enter range => <n>

1. Only files
2. Files and folders (with subfolders)
Enter choice (1/2) => <1/2>
```
```bash
./main sample_data
```

****

### Supported Categories and Extensions

The program supports file categorization into the following categories:

#### **Documents**
- Extensions: `txt`, `doc`, `docx`, `pdf`, `rtf`, `odt`, `xls`, `xlsx`, `ppt`, `pptx`

#### **Images**
- Extensions: `jpg`, `jpeg`, `png`, `gif`, `bmp`, `tiff`, `svg`, `ico`

#### **Videos**
- Extensions: `mp4`, `mkv`, `avi`, `mov`, `wmv`, `flv`

#### **Audio**
- Extensions: `mp3`, `wav`, `flac`, `aac`, `ogg`, `m4a`

#### **Archives**
- Extensions: `zip`, `rar`, `7z`, `tar`, `gz`, `iso`

#### **Data**
- Extensions: `csv`, `json`, `xml`, `sql`

#### **Programming**
- Extensions: `c`, `cpp`, `h`, `java`, `py`, `js`, `html`, `css`, `php`

#### **Executables**
- Extensions: `exe`, `bat`, `sh`, `msi`, `apk`, `jar`

#### **Configuration**
- Extensions: `ini`

#### **Logs**
- Extensions: `log`
