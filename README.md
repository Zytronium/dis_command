Copy the `dis` file into /bin/ to be able to use `dis` the same way you use `ls`.

### Flags
all same as single-letter flags for `ls` *except* `-e` and `-E` are also flags for `dis`

- -e: surround the output in empty lines
- -E: prevent empty line between directory contents and current directory path


-e and -E are mutually exclusive. Whichever is last in the command takes precedence 

how to copy into `/bin/` to use as a command:
(assuming the `dis` executable file is in the current working directory)
```bash
sudo cp ./dis /bin/
```
