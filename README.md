# pipex


fd[0] ===> pipe 0

fd[1] ===> pipe 1

fd[2] ===> infile

fd[3] ===> Parent STD_IN (0)

fd[4] ===> Parent STD_OUT (1)

fd[5] ===> Child 2 STD_IN (0)

fd[6] ===> Child 2 STD_OUT (1)





[X] if ac != 5 print error message → Just a simple condition check and error message.

[X] add pipex header to makefile → Straightforward Makefile modification.

[X] handle libft relink

[] cmd not found message in last cmd → Likely just an extra check before execution.

[] print allocation errors → Requires checking all mallocs but still relatively simple.

[] empty cmd's in ft_split → Might need adjusting how ft_split handles empty strings.

[] fd leaks after args count check → Requires tracking open file descriptors.

[] unlink here_doc file 2 times after creating it → Involves process logic, could be tricky.

[] change libft ---> make pipex → This sounds like a significant structural change.


# issues:

fd leaks after args count check

empty cmd's in ft_split

cmd not found message in last cmd

change libft ---> make pipex

add pipex header to makefile

if ac != 5 print error message

print allocation errors

unlink here_doc file 2 times after creating it