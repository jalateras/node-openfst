# node-openfst
NodeJS binding for OpenFST

## Pre-requisite

Macos:
```
brew install openfst opengrm-ngram opengrm-thrax
```

Linux:
...


## Walkthrough
Let's try to make a 3-gram model of war of the worlds and use it to search
http://openfst.cs.nyu.edu/twiki/bin/view/GRM/NGramQuickTour#ConvenienceScript
```
# Generate symbols (aka: tokenizer?)
ngramsymbols <wotw.txt >wotw.syms

# Given a symbol table, a text corpus can be converted to a binary FAR archive with:
farcompilestrings -symbols=wotw.syms -keep_symbols=1 wotw.txt >wotw.far

# We can retrieve the original text from the fst:
farprintstrings wotw.far

# ngramcount is a command line utility for counting n-grams from an input corpus, represented in FAR format. It produces an n-gram model in the FST format
ngramcount -order=4 wotw.far >wotw4.cnts

# ngrammake is a command line utility for normalizing and smoothing an n-gram model.
# Flags to ngrammake specify the smoothing (e.g. Katz, Knesser-Ney, etc) used with the default being Witten-Bell.
ngrammake wotw4.cnts >wotw4.mod

# If we devided the work in multiple shards we can merge generated n-gram models.
# ngrammerge earnest.aa.cnts earnest.ab.cnts >earnest.merged.cnts

# If we want to shrink:
# The following command shrinks the 5-gram model created above using entropy pruning to roughly 1/10 the original size:
ngramshrink -method=relative_entropy -theta=.00015 earnest.mod >earnest.pru


# now can we use all this stuff?
echo "world" | farcompilestrings -generate_keys=1 -symbols=wotw.syms --keep_symbols=1 | ngramperplexity --v=1 wotw4.mod -

```
