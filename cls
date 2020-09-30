#!/bin/bash
help_text="
NAME
   cls - Clear terminal and putty terminal buffer

USAGE
   cls

DESCRIPTION
   Clear terminal and putty terminal buffer.

AUTHOR
   mjnurse.dev - 2019
"
help_line="Clear terminal and putty terminal buffer"
desc_line="Clear terminal and putty terminal buffer"

# doesn't always work first time round so twice.
printf '\033[3J'
clear
printf '\033[3J'
clear
