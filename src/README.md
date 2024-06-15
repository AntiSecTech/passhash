# passhash Makefile

This project uses a Makefile to automate the build process. Below are the available targets and their functionalities.

## Targets

### `make`
The default target. Compiles the `passhash` program.
```sh
make
```

### `make install`
Compiles the `passhash` program and copies the binary to the **/bin** directory.
If a manpage file (`passhash.1`) is present, it will be copied to the manpage directory (**/usr/share/man/man1**).
```sh
make install
```

### `make uninstall`
Removes the installed binary (`passhash`) from the **/bin** directory and the manpage file (`passhash.1`) from the manpage directory (**/usr/share/man/man1**), if it exists.
```sh
make uninstall
```

### `make clean`
Deletes the compiled binary (`passhash`) to clean up the build directory.
```sh
make clean
```

## Notes
- Ensure you have the necessary permissions to write to and delete files in **/bin** and **/usr/share/man/man1**.<br>
  Otherwise you can use the `sudo make install` or `sudo make uninstall` command.
- The Makefile assumes that a manpage file named `passhash.1` exists if a manpage is to be installed.
