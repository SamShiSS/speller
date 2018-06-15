# speller

/texts: This folder contains text files to be checked for misspelled words

/dictionaries: This folder contains two dictionaries of different size

speller.c: This is the main program that implements the spellcheck using a hash table for dictionary storage and lookup

dictionary.{c,h}: In these two files are four functions used by speller.c: load (for loading the dictionary file), check (for checking the spelling in text), size (for calculating size of the dictionary), unload (for unloading the dictionary file)
