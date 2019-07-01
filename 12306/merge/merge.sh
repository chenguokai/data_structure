ls *.txt |
while read file_name;
do
    # 用.为分隔符只要文件名，去掉文件后缀
    cat "$file_name" >> all.txt
    echo "" >> all.txt
done
