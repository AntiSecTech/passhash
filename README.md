# passhash - generate hashed password strings using OpenSSL

## Synopsis

**passhash** [password] | -p:[password] [-u:[username]] [-s:[salt]]

## Description

**passhash** is a command-line utility that generates hashed password strings using OpenSSL. It accepts options to specify the password, username, and salt for hash generation.

## Options

- **-p:[password]**  
  Specifies the password for which the hash will be generated. This option is required.

- **-u:[username]**  
  Specifies the username associated with the hashed password. If not provided, defaults to "root".

- **-s:[salt]**  
  Specifies the salt to be used in the hashing process. If not provided, defaults to "salted".

## Examples

To generate a hashed password for the password "my_password" with the default username "root" and default salt "salted":

```bash
passhash -p:my_password
```

To generate a hashed password for the password "secure_pass" with a specific username "admin" and a custom salt "my_salt":

```bash
passhash -p:secure_pass -u:admin -s:my_salt
```
## Exit Status

- **0**
  Successful execution.

- **1**
  Errors encountered during execution.

## Authors

Written by [AntiSecTech](https://antisectech.github.io/).

## Reporting Bugs

Report any bugs to [contact.antisec@pm.me](mailto:contact.antisec@pm.me).

## Copyright

This program is licensed under the **[CC BY-NC 4.0]**. See [CC BY-NC 4.0](https://creativecommons.org/licenses/by-nc/4.0/legalcode.txt) for more details.
## See Also

    openssl(1)

## Notes

This documentation is based on the functionality of the passhash utility using OpenSSL for password hashing.
