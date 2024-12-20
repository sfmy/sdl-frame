#!bin/bash 

for json_file in $(find res -name "*.json"); do
    csv_file="${json_file%.json}.txt"
    echo "$json_file" "$csv_file"
    cat /dev/null > "$csv_file"
    for ((i=0; i<10; ++i)); do
        jq -r -j ".point[$i].x" "$json_file" >> "$csv_file"
        echo -n "," >> "$csv_file"
        jq -r -j ".point[$i].y" "$json_file" >> "$csv_file"
        echo -n "," >> "$csv_file"
        jq -r -j ".point[$i].w" "$json_file" >> "$csv_file"
        echo -n "," >> "$csv_file"
        jq -r ".point[$i].h" "$json_file" >> "$csv_file"
    done
done
