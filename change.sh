#!/bin/bash 

for file in $(find . -name '*.c' -o -name '*.h'); do
    echo "$file"
    gsed -i 's/\<GM_AddListItem\>/GM_AddListItemByData/g' "$file"
    gsed -i 's/\<GM_DelListItem\>/GM_DelListItemByData/g' "$file"
done
