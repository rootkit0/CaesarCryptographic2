#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
sys.setrecursionlimit(2500)

abc_majus = "ABCDEFGHILMNOPQRSTUVXYZ"
abc_minus = "abcdefghilmnopqrstuvxyz"

#Xifrem el text de forma recursiva
def encrypt_file(contingut, key, long, count, count_key):
    #Cas base
    if(count >= long):
        return '' 
    #Cas recursiu
    else:
        if(contingut[count] in abc_minus):
            index = abc_minus.index(contingut[count]) + abc_minus.index(key[count_key % len(key)])
            return abc_minus[index % len(abc_minus)] + encrypt_file(contingut, key, long, count+1, count_key+1)
        elif(contingut[count] in abc_majus):
            index = abc_majus.index(contingut[count]) + abc_minus.index(key[count_key % len(key)])
            return abc_majus[index % len(abc_majus)] + encrypt_file(contingut, key, long, count+1, count_key+1)
        else:
            return contingut[count] + encrypt_file(contingut, key, long, count+1, count_key)
        
def main():
    if(len(sys.argv) <= 2):
        print("Falten arguments")
        print("Us: python encrypt.py fitxer_descodificat.txt clau")
        exit()
    else:
        decoded_file = open(sys.argv[1], 'r')
        contingut = decoded_file.read()
        key = sys.argv[2]
        print(encrypt_file(contingut, key, len(contingut), 0, 0))

if __name__ == "__main__":
    main()
