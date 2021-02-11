#!/bin/bash
help_text="
NAME
  h - Extracts and displays the (single line) help lines in bash scripts.

USAGE
  h [<filenames - wildcards allowed>]

OPTIONS
  -m|--matchesonly
    Only display the help lines available, don't report on files missing a help line or with
    a help line 'tbc'.

DESCRIPTION
  Extracts and displays the (single line) help lines.

AUTHOR
  mjnurse.dev - 2020
"
help_line="Extracts and displays the help_lines"
web_desc_line="Extracts and displays the help_lines"

matches_only_yn=n

case $1 in
  -m|--matchesonly)
    matches_only_yn=y
    shift
    ;;
esac

files="$*"

if [[ "$files" == "" ]]; then
  files="*"
fi

files="00000000000000000 $files"

if [[ $matches_only_yn == n ]]; then

  grep -s -L -e "^help_line=" -e "^-- help_line:" $files \
      | sed '/README.*.md/d; /^h:/d' \
      | sort -f > /tmp/h.tmp

  if [[ $(cat /tmp/h.tmp | wc -l) != 0 ]]; then
    echo -------------
    echo No help_line:
    echo -------------
    cat /tmp/h.tmp
  fi

  grep -s -l -e "help_line=.*tbc.*" $files \
      | sed '/README.*.md/d; /^h$/d' \
      | sort -f > /tmp/h.tmp

  if [[ $(cat /tmp/h.tmp | wc -l) != 0 ]]; then
    echo --------------
    echo help_line: tbc
    echo --------------
    cat /tmp/h.tmp | sed "/tidy/d"
  fi

  echo -----------
  echo help_lines:
  echo -----------
fi

prev_chr=""
grep -s -e "^help_line=" -e "^-- help_line:" $files | \
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
