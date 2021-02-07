#!/bin/bash
help_text="
NAME
   h - Extracts and displays the (single line) help lines.

USAGE
   h

DESCRIPTION
   Extracts and displays the (single line) help lines.

AUTHOR
  mjnurse.dev - 2020
"
help_line="Extracts and displays the help_lines"
web_desc_line="Extracts and displays the help_lines"

grep -s -L -e "^help_line=" -e "^-- help_line:" * | sed '/README.*.md/d; /^h:/d' | sort -f > /tmp/h.tmp
if [[ $(cat /tmp/h.tmp | wc -l) != 0 ]]; then
   echo -------------
   echo No help_line:
   echo -------------
   cat /tmp/h.tmp
fi

grep -s -l -e "help_line=.*tbc.*" * | sed '/README.*.md/d; /^h$/d' | sort -f > /tmp/h.tmp
if [[ $(cat /tmp/h.tmp | wc -l) != 0 ]]; then
   echo --------------
   echo help_line: tbc
   echo --------------
   cat /tmp/h.tmp | sed "/tidy/d"
fi

echo -----------
echo help_lines:
echo -----------

prev_chr=""
grep -s -e "^help_line=" -e "^-- help_line:" * | \
   sed ' 
      /help_line=.*tbc.*/d
      /^h:/d; s/help_line=//; s/-- help_line://; s/"/ /g;
      /tidy:.*echo/d; /^README.*md/d' | \
   sort | while IFS= read -r line ; do 
      curr_char="${line:0:1}"
      if [[ "$curr_char" != "$prev_char" ]]; then
         prev_char="$curr_char"
         echo "$curr_char - $line"
      else
         echo "    $line" 
      fi
   done | sed  '
      s/: /:                        /;
      s/\(.........................\) *\(.*\)/\1\2/; /tidy:.*echo/d' > .h.out
cat .h.out
