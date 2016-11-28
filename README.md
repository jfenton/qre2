qre2
====

Google RE2 extension for kdb+/q.

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

Copyright (c) 2016 Jay Fenton.

Other parts of this software (eg: Google RE2) are covered by other licences.
