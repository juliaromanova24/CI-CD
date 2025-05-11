#!/bin/bash

SUCCESS=0
FAIL=0
DIFF_RES=""


tests=("VAR test_cat.txt")

# 1 параметр
for arguments in b e n s t v
do
    for a in "${tests[@]}"
    do
        var="-$arguments"  # Используем текущий аргумент из внешнего цикла
        text=$(echo $a | sed "s/VAR/$var/")
        
        ./s21_cat $text > s21_cat.log
        cat $text > cat.log
        
        DIFF_RES="$(diff -s s21_cat.log cat.log)"
        
        if [ "$DIFF_RES" == "Files s21_cat.log and cat.log are identical" ]
        then
            (( SUCCESS++ ))
            echo "SUCCESS: $text"
        else
            (( FAIL++ ))
            echo "FAIL: $text"
        fi
        
        rm s21_cat.log cat.log
    done
done

for var1 in b e n s t v; do
    for var2 in b e n s t v; do
        if [ "$var1" != "$var2" ]; then  
            for a in "${tests[@]}"; do
                var="-$var1 -$var2" 
                text=$(echo $a | sed "s/VAR/$var/")
                
                ./s21_cat $text > s21_cat.log
                cat $text > cat.log
                
                DIFF_RES="$(diff -s s21_cat.log cat.log)"
                
                if [ "$DIFF_RES" == "Files s21_cat.log and cat.log are identical" ]; then
                    (( SUCCESS++ ))
                    echo "SUCCESS: $text"
                else
                    (( FAIL++ ))
                    echo "FAIL: $text"
                fi
                
                rm s21_cat.log cat.log
            done
        fi
    done
done

for var1 in b e n s t v; do
    for var2 in b e n s t v; do
        for var3 in b e n s t v; do
            if [ "$var1" != "$var2" ] && [ "$var2" != "$var3" ] && [ "$var1" != "$var3" ]; then  
                for a in "${tests[@]}"; do
                    var="-$var1 -$var2 -$var3"  
                    text=$(echo $a | sed "s/VAR/$var/")
                    
                    ./s21_cat $text > s21_cat.log
                    cat $text > cat.log
                    
                    DIFF_RES="$(diff -s s21_cat.log cat.log)"
                    
                    if [ "$DIFF_RES" == "Files s21_cat.log and cat.log are identical" ]; then
                        (( SUCCESS++ ))
                        echo "SUCCESS: $text"
                    else
                        (( FAIL++ ))
                        echo "FAIL: $text"
                    fi
                    
                    rm s21_cat.log cat.log
                done
            fi
        done
    done
done

for var1 in b e n s t v; do
    for var2 in b e n s t v; do
        for var3 in b e n s t v; do
            for var4 in b e n s t v; do 
                if [ "$var1" != "$var2" ] && [ "$var2" != "$var3" ] && [ "$var1" != "$var3" ] && [ "$var1" != "$var4" ] && [ "$var2" != "$var4" ] && [ "$var3" != "$var4" ]; then  
                    for a in "${tests[@]}"; do 
                        var="-$var1 -$var2 -$var3 -$var4"  
                        text=$(echo $a | sed "s/VAR/$var/")
                        
                        ./s21_cat $text > s21_cat.log
                        cat $text > cat.log

                        DIFF_RES="$(diff -s s21_cat.log cat.log)"

                        if [ "$DIFF_RES" == "Files s21_cat.log and cat.log are identical" ]; then
                            (( SUCCESS++ ))
                            echo "SUCCESS: $text"
                        else
                            (( FAIL++ ))
                            echo "FAIL: $text"
                        fi

                        rm s21_cat.log cat.log 
                    done 
                fi 
            done 
        done 
    done 
done 


echo "SUCCESS: $SUCCESS"
echo "FAIL: $FAIL"
