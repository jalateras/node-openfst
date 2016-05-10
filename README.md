# node-openfst
NodeJS binding for OpenFST

## Pre-requisite

Macos:
```
brew install openfst opengrm-ngram opengrm-thrax
```

Linux:
...

Visualization:
```
brew install graphviz
```

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

------------------------------------------------------------

FST Search example 1: keywords (0-grams, dummy)
Create as many fsas (Finite state acceptors, no output symbols) as their are symbols.
Make a lexicon acceptor that is the union of all those, then make it deterministic and minimal

Now when searching for a keyword: make an fsa of the keyword.
Then intersect that fsa with the lexicon.

FST Search example 1: fuzzy (n-grams)
Take the previous lexicon.
Make an ngram fsa of the word to search
Intersect that fsa with the lexicon


http://www.openfst.org/twiki/bin/view/FST/FstExamples Tokenization
===================================================================
fstcompile --isymbols=ascii.syms --osymbols=wotw.syms >Mars.fst <<EOF
0 1 M Mars
1 2 a <epsilon>
2 3 r <epsilon>
3 4 s <epsilon>
4
EOF
fstdraw --isymbols=ascii.syms --osymbols=wotw.syms -portrait Mars.fst | dot -Tjpg >Mars.jpg

fstcompile --isymbols=ascii.syms --osymbols=wotw.syms >Martian.fst <<EOF
0 1 M Martian
1 2 a <epsilon>
2 3 r <epsilon>
3 4 t <epsilon>
4 5 i <epsilon>
5 6 a <epsilon>
6 7 n <epsilon>
7
EOF

fstdraw --isymbols=ascii.syms --osymbols=wotw.syms -portrait Martian.fst | dot -Tjpg >Martian.jpg

fstcompile --isymbols=ascii.syms --osymbols=wotw.syms >man.fst <<EOF
0 1 m man
1 2 a <epsilon>
2 3 n <epsilon>
3
EOF
fstdraw --isymbols=ascii.syms --osymbols=wotw.syms -portrait man.fst | dot -Tjpg >man.jpg


fstunion man.fst Mars.fst | fstunion - Martian.fst | fstclosure >lexicon.fst
fstdraw --isymbols=ascii.syms --osymbols=wotw.syms -portrait lexicon.fst | dot -Tjpg >lexicon-non-determinism-non-minimal.jpg

fstrmepsilon lexicon.fst | fstdeterminize | fstminimize >lexicon_opt.fst
fstdraw --isymbols=ascii.syms --osymbols=wotw.syms -portrait lexicon_opt.fst | dot -Tjpg >lexicon-determinist-minimal.jpg


-----------------------------
Acceptors

fstcompile --acceptor --isymbols=ascii.syms >Mars.fsa <<EOF
0 1 M
1 2 a
2 3 r
3 4 s
4
EOF
fstdraw --isymbols=ascii.syms -portrait Mars.fsa | dot -Tjpg >Marsa.jpg

fstcompile --acceptor --isymbols=ascii.syms >man.fsa <<EOF
0 1 m
1 2 a
2 3 n
3
EOF
fstdraw --isymbols=ascii.syms -portrait man.fsa | dot -Tjpg >mana.jpg

fstcompile --acceptor --isymbols=ascii.syms >Martian.fsa <<EOF
0 1 M
1 2 a
2 3 r
3 4 t
4 5 i
5 6 a
6 7 n
7
EOF
fstdraw --isymbols=ascii.syms -portrait Martian.fsa | dot -Tjpg >Martiana.jpg

fstunion man.fsa Mars.fsa | fstunion - Martian.fsa | fstclosure >lexicon.fsa
fstdraw --isymbols=ascii.syms -portrait lexicon.fsa | dot -Tjpg >lexicona-non-determinism-non-minimal.jpg

fstrmepsilon lexicon.fsa | fstdeterminize | fstminimize >lexicon_opt.fsa
fstdraw --isymbols=ascii.syms -portrait lexicon_opt.fsa | dot -Tjpg >lexicona-determinist-minimal.jpg

Search === intersect:
---------------------
fstintersect man.fsa lexicon_opt.fsa | fstprint -isymbols=ascii.syms

fstcompile --acceptor --isymbols=ascii.syms >not.fsa <<EOF
0 1 n
1 2 o
2 3 t
3
EOF
fstintersect not.fsa lexicon_opt.fsa | fstprint -isymbols=ascii.syms
