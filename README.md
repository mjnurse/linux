# Linux Utility Scripts

The following list of script descriptions is generated using the help_line extraction script.

```
-----------
help_lines:
-----------
a - article:      Creates a new website article: article <title: spaces allowed> 
b - blog:         Creates a Blog article: blog <title: spaces allowed> 
c - cls:          Clear terminal and putty terminal buffer 
    crreadme:     Creates a README.md document from READMEscr.md 
g - gvim:         Runs windows gvim and fixes file paths 
n - note:         Creates a Note article: note <title: spaces allowed> 
o - or:           Connect to oracle using sqlplus 
p - pg:           Connect to postgresql using psql 
t - tidy:         Fixes issues such as permission issues with files in current directory 
```

### h - help_line Extraction Script

File: h
```bash
#!/bin/bash
help_text="
NAME
   h - Extracts and displays the (single line) help lines.

USAGE
   h

DESCRIPTION
   Extracts and displays the (single line) help lines.

AUTHOR
  mjnurse.uk 2020
"
help_line="This script"

no_help_list="$(grep -L help_line= * | sed '/README.*.md/d')"
if [[ "$no_help_list" != "" ]]; then
   echo -------------
   echo No help_line:
   echo -------------
   echo $no_help_list
fi

echo -----------
echo help_lines:
echo -----------

prev_chr=""
grep help_line= * | \
   sed '/^h:/d; s/help_line=//; s/"/ /g; /tidy:.*echo/d; /^README.*md/d' | \
   sort | while IFS= read -r line ; do 
      curr_char="${line:0:1}"
      if [[ "$curr_char" != "$prev_char" ]]; then
         prev_char="$curr_char"
         echo "$curr_char - $line"
      else
         echo "    $line" 
      fi
   done | sed  '
      s/: /:                 /;
      s/\(..................\) *\(.*\)/\1\2/; /tidy:.*echo/d' 
```

