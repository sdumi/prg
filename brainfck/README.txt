
$Id: README,v 1.5 2000/07/19 18:17:53 panu Exp $

Bfc
===

This software package includes parts of the old brainfuck software
package by Urban Müller as well as some utilities by Panu Kalliokoski,
most important of which is `bfc', an optimising compiler for the
brainfuck language.

Read the file bfc.txt for more information.

Licences
--------

Different parts of this distribution fall under different conditions. 

Parts of bfc: bfc.h, bfc.c, bfo.c and bft.c as well as bfc.txt, which
describes these, are distributed under the license shown in the file
LICENSE.

Parts of old brainfuck software package: bfi.c, some .b files, and
brainfuck.txt, are not under any license as far as I know. Thus, they
must be considered freely distributable intellectual property of
Urban Müller.

src-bf/Ha_BF.b, which is supposed to be a brainfuck interpreter in
brainfuck (I haven't been able to prove this :)) is written by Frank
Faase. I don't think it's under any license either.

Other files, including makefiles and some short brainfuck examples,
are trivial and public domain.

Installation
------------

Just type `make'. There is no rule for installing; if you like, you
can copy the binary `bfc' to some good place (e.g. ~/bin).

