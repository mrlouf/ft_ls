# ft_ls
As simple as listing the files in a directory.

## Workflow

> Parse the arguments if provided

> Get all the DIRs required and store them in a linked list

> Sort the DIRs depending on the options provided (locale too?)

> Print each DIR successively

## Glossary

+ **Directory**: In C/UNIX, a directory is a file that contains other files and/or subdirectories along with their associated information such as names, permissions, timestamps, etc.

+ **Directory stream (DIR)**: Abstract representation of accessing a directory. A directory stream returned by `opendir` can be seen as a command to the system saying 'Please open the directory and start reading it from the first element'. Calling `readdir` on this DIR via its pointer accesses the next element, allowing us to iterate over the whole directory.

## References
+ https://man7.org/linux/man-pages/man1/ls.1.html
+ https://www.gnu.org/software/coreutils/manual/html_node/ls-invocation.html#ls-invocation
+ https://github.com/coreutils/coreutils
