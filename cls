#!/bin/bash
help_text="
NAME
   cls - Clear terminal and putty terminal buffer

USAGE
   cls

DESCRIPTION
   Clear terminal and putty terminal buffer.

AUTHOR
   mjnurse.uk - 2019
"
help_line="Clear terminal and putty terminal buffer"

# doesn't always work first time round so twice.
printf '\033[3J'
clear
printf '\033[3J'
clear
