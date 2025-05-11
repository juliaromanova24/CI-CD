#!/bin/bash

HOST="172.24.116.8"
USER="deployer"
TMP_DIR="/home/deployer"
DEST_DIR="/usr/local/bin"

scp ./src/cat/s21_cat $USER@$HOST:$TMP_DIR
if [ $? -eq 0 ];
then
    echo "File s21_cat copied to $HOST"
else
    echo "Error: file s21_cat wasn't copied to $HOST"
    exit 1
fi

scp ./src/grep/s21_grep $USER@$HOST:$TMP_DIR
if [ $? -eq 0 ];
then
    echo "File s21_grep copied to $HOST"
else
    echo "Error: file s21_grep wasn't copied to $HOST"
    exit 1
fi

ssh $USER@$HOST "
    sudo rm -f $DEST_DIR/s21_cat
    sudo rm -f $DEST_DIR/s21_grep


    sudo mv $TMP_DIR/s21_cat $DEST_DIR
    sudo mv $TMP_DIR/s21_grep $DEST_DIR
    "
    if [ $? -eq 0 ];
then
    echo "FIles s21_cat s21_grep moved to $DEST_DIR"
else
    echo "Error: files s21_cat s21_grep weren'tmoved to $DEST_DIR"
    exit 1
fi
    
