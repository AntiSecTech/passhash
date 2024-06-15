#!/bin/bash

program_name=$(basename "$0")
if [ "$program_name" != "passhash.sh" ]; then
    echo "Error: The program must be named 'passhash.sh' to run."
    exit 1
fi

show_help() {
    cat << EOF
    
 ██▓███   ▄▄▄        ██████   ██████  ██░ ██  ▄▄▄        ██████  ██░ ██ 
▓██░  ██▒▒████▄    ▒██    ▒ ▒██    ▒ ▓██░ ██▒▒████▄    ▒██    ▒ ▓██░ ██▒
▓██░ ██▓▒▒██  ▀█▄  ░ ▓██▄   ░ ▓██▄   ▒██▀▀██░▒██  ▀█▄  ░ ▓██▄   ▒██▀▀██░
▒██▄█▓▒ ▒░██▄▄▄▄██   ▒   ██▒  ▒   ██▒░▓█ ░██ ░██▄▄▄▄██   ▒   ██▒░▓█ ░██ 
▒██▒ ░  ░ ▓█   ▓██▒▒██████▒▒▒██████▒▒░▓█▒░██▓ ▓█   ▓██▒▒██████▒▒░▓█▒░██▓
▒▓▒░ ░  ░ ▒▒   ▓▒█░▒ ▒▓▒ ▒ ░▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒ ▒▒   ▓▒█░▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒
░▒ ░       ▒   ▒▒ ░░ ░▒  ░ ░░ ░▒  ░ ░ ▒ ░▒░ ░  ▒   ▒▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░
░░         ░   ▒   ░  ░  ░  ░  ░  ░   ░  ░░ ░  ░   ▒   ░  ░  ░   ░  ░░ ░
               ░  ░      ░        ░   ░  ░  ░      ░  ░      ░   ░  ░  ░

Usage: passhash.sh <password> | -p <password>] [-u <username>] [-s <salt>]

Options:
  -p <password>   Password for hash generation (required)
  -u <username>   Username (optional, default: root)
  -s <salt>       Salt for hash generation (optional, default: salted)

EOF
}

username="root"
salt="salted"
password=""
suffix=":0:0:root:/root:/bin/bash"

if [ $# -eq 0 ]; then
    show_help
    exit 1
fi

if [ $# -eq 1 ] && [[ ! $1 =~ ^- ]]; then
    password="$1"
else
    while [[ $# -gt 0 ]]; do
        case $1 in
            -u:*)
                username="${1#-u:}"
                shift
                ;;
            -p:*)
                password="${1#-p:}"
                shift
                ;;
            -s:*)
                salt="${1#-s:}"
                shift
                ;;
            *)
                echo "Unknown parameter: $1"
                show_help
                exit 1
                ;;
        esac
    done
fi

if [ -z "$password" ]; then
    echo "Error: The password must be provided with the -p option."
    show_help
    exit 1
fi

hashed_password=$(openssl passwd -6 -salt "$salt" "$password")

if [ $? -ne 0 ]; then
    echo "Failed to generate hashed password."
    exit 1
fi

prefix="${username}:"
echo "${prefix}${hashed_password}${suffix}"

exit 0
