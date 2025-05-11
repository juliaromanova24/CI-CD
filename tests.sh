SUCCESS=0
FAIL=0
TEXT=(" " "1" "2" "row" "Row")
FILES=(" " "test1" "test1 test2" "test1 test2 test3" "test3" "test2")
COUNT=0
arguments=(" " "-e" "-i" "-v" "-c" "-l" "-n" "-h" "-s" "-o")

for arguments in ${arguments[@]}; do 
	for text in ${TEXT[@]}; do 
        for files in ${FILES[@]}; do 
            (( COUNT++ ))

            grep $arguments $text $files 1>grep 2>>var3
            ./s21_grep $arguments $text $files 1>s21_grep 2>>var3
            if [ "$?" != "0" ]
                then
                echo "$arguments $text $files" >> error.txt
            fi
            res="$(diff -s grep s21_grep)"

            if [ "$res" == "Files grep and s21_grep are identical" ]
                    then
                    (( SUCCESS++ ))
                    else
                        echo "$arguments $text $files" >> result.txt
                        (( FAIL++ ))
            fi
        done
	done
done



text1=(" " "1" "Row" "row" "text" "lalla")
text2=(" " "1" "Row" "row" "text")


for arg1 in ${text1[@]}; do 
        for arg2 in ${text2[@]}; do 
                for files in ${FILES[@]}; do 
                        (( COUNT++ ))

                        grep -e $arg1 -e $arg2 $files 1>grep 2>>var3
                        ./s21_grep -e $t1 -e $t2 $f 1>s21_grep 2>>var3
                        if [ "$?" != "0" ]
                                then
                                echo "$arg1 $arg2 $files" >> error.txt
                        fi
                        res="$(diff -s grep s21_grep)"

                        if [ "$res" == "Files grep and s21_grep are identical" ]
                                then
                                (( SUCCESS++ ))
                        else
                                echo  "$arg1 $arg2 $files"  >> result.txt
                                (( FAIL++ ))
                        fi
                done
        done
done



for arg1 in ${text1[@]}; do 
        for arg2 in ${text2[@]}; do 
                for arg3 in ${text2[@]}; do 
                        for files in ${files[@]}; do 
                                (( count++ ))
                                grep -e $arg1 -e $arg2 -e $arg3 $files 1>grep 2>>var3
                                ./s21_grep -e $arg1 -e $arg2 -e $arg3 $files 1>s21_grep 2>>var3
                                if [ "$?" != "0" ]
                                        then
                                        echo "$arg1 $arg2 $arg3 $files" >> error.txt
                                fi
                                res="$(diff -s grep s21_grep)"

                                if [ "$res" == "Files grep and s21_grep are identical" ]
                                        then
                                        (( SUCCESS++ ))
                                        else
                                        echo  "$arg1 $arg2 $arg3 $files"  >> result.txt
                                        (( FAIL++ ))
                                fi
                        done   
                done
        done
done



echo "SUCCESS: $SUCCESS"
echo "FAIL: $FAIL"