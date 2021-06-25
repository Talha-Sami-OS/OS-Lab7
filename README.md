# OS-Lab7
## Lab: A Simple Filesystem

Using the emulated disk access functions described above, you will now implement the following simple
operations on files in our simple filesystem. These operations are defined in _simplefs-ops.h_ and
must be implemented in _simplefs-ops.c_.

Unlike Linux, our simple filesystem has separate functions to create and open a file. Creating a
file only creates it on disk, while opening a file opens an already created file for reading and writing.
_simplefs-disk.h_ defines an additional in-memory datastructure related to the filesystem, called the
file handle array. The state of open files in the system (the inode number and the offset of reading/writing)
is captured in a file handle of an open file. The filesystem maintains an array of all such file handles of
open files, and the index of a file handle in this array is used to uniquely identify an open file in all
subsequent read/write operations.

##Testing your code
The folder testcases in branch uploaded contains several sample test programs to test your filesystem implementation.
Each test formats the file system, and performs several operations like creating, reading and writing
files. Each program prints the success/failure status of each operation performed, and the final state of
the disk after all operations have completed. You may compile and link any of these test programs with
your simplefs C files to generate an executable to run. The folder expected output contains the
output we expect your completed code will generate; this output was generated using our solution code.
After you complete your implementation, you should ensure that the output of your program matches
the expected output exactly.

_gcc testcase.c simplefs-ops.c simplefs-disk.c
./a.out_

