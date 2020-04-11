## C++ Text File Compressor
This small program uses a very basic algorithm to compress basic text files. 
After compressing a file, a .zac and .dict file is generated. The .zac file is
the 'compressed' file, and the .dict file is the dictionary file used by the 
extraction algorithm to reconstruct the file. In order to properly restore a file,
both the .zac and .dict file must be in the same directory.

## Compiling Source Code
This program can be compiled with only one file: compressor.cpp. To compile on Windows 
I recommend Cygwin.

```g++ -o compressor.exe compressor.cpp```

## Usage
When running the program, you'll be presented with an option to \[E\]xtract or \[C\]ompress a file:

# Compress File
```
>>./compressor.exe
[E]xtract or [C]ompress a file:
C
Please enter the file to compress:
example.txt
Creating dictionary for 'example.txt'...
Compressing file 'example.txt'...
--SUCCESS--
```

# Extract File
```
>>./compressor.exe
[E]xtract or [C]ompress a file:
E
Please enter the file to compress:
example.txt.zac
Reading file's dictionary...
Extracting 'example.txt.zac'...
--SUCCESS--
```