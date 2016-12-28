qre2
====

Regex extension for kdb+/q, using Google's re2 library.

# Checkout

    $ git clone https://github.com/jfenton/qre2.git
    $ cd qre2
    $ git submodule init
    $ git submodule update

# Build

    $ make {m32,m64,l32,l64}
    $ QHOME=/path/to/kdb make install

# Usage

    q) \l rex.q

    q)rex[("heLLO123";"hello321");"he(?P<blah>[^0-9]+)(?P<tst2>\\d)(?P<moo>\\d+)"]
    input    blah  moo  tst2
    ------------------------
    heLLO123 "LLO" ,"1" "23"
    hello321 "llo" ,"3" "21"

    q)rexs[("heLLO123";"hello321");"he(?P<blah>[^0-9]+)(?P<tst2>\\d)(?P<moo>\\d+)"]
    "blah" "moo" "tst2"
    "LLO"  "23"  ,"1"
    "llo"  "21"  ,"3"

    q)rexm[("heLLO123";"hello321");"he(?P<blah>[^0-9]+)(?P<tst2>\\d)(?P<moo>\\d+)"]
    11b

# Licence

LGPLv3. See `LICENSE` and `COPYING.LESSER`.

Copyright (c) 2016 Jay Fenton <na.nu@na.nu>

Other parts of this software (e.g. Google re2, Kx k.h) are covered by other licences.
