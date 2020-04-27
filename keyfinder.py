#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
sys.setrecursionlimit(2500)

abc_minus = "abcdefghilmnopqrstuvxyz"
abc_majus = "ABCDEFGHILMNOPQRSTUVXYZ"

def search_word(decoded_text):
    global known_word
    if known_word in decoded_text:
        return True
    else:
        return False

def decode_text(contingut, key, long, count, count_key):
    #Cas base
    if(count >= long):
        return '' 
    #Cas recursiu
    else:
        if(contingut[count] in abc_minus):
            index = abc_minus.index(contingut[count]) - abc_minus.index(key[count_key % len(key)])
            return abc_minus[index % len(abc_minus)] + decode_text(contingut, key, long, count+1, count_key+1)
        elif(contingut[count] in abc_majus):
            index = abc_majus.index(contingut[count]) - abc_minus.index(key[count_key % len(key)])
            return abc_majus[index % len(abc_majus)] + decode_text(contingut, key, long, count+1, count_key+1)
        else:
            return contingut[count] + decode_text(contingut, key, long, count+1, count_key)

def permutacions(abc_minus, key_actual, key_length):
    global coded_file
    #Cas base
    if(key_length == 0):
        fitxer = open(coded_file, 'r')
        contingut = fitxer.read()
        decoded_text = decode_text(contingut, key_actual, len(contingut), 0, 0)
        print("Desxifrem el text amb la clau: " + key_actual)
        print("Text desxifrat: " + decoded_text)
        if(search_word(decoded_text)):
            print("Clau trobada!: " + key_actual)
            exit()
        print("Clau no trobada, seguim provant")
    #Cas recursiu
    else:
        for i in range(0, len(abc_minus)):
            permutacions(abc_minus, key_actual + abc_minus[i], key_length-1)

def search_key():
    global min_len_key, max_len_key
    key_actual = ""
    for i in range(int(min_len_key), int(max_len_key)+1):
        permutacions(abc_minus, key_actual, i)

def main():
    if(len(sys.argv) <= 2):
        print("Falten arguments")
        print("Us: python keyfinder.py fitxer_codificat.txt paraula_coneguda")
        exit()
    else:
        global coded_file, known_word, min_len_key, max_len_key
        coded_file = sys.argv[1]
        known_word = sys.argv[2]
        min_len_key = 1
        max_len_key = 23
        if(len(sys.argv) > 2):
            try:
                min_len_key = sys.argv[3]
                max_len_key = sys.argv[4]
                search_key()
            except:
                search_key()

if __name__ == "__main__":
    main()
