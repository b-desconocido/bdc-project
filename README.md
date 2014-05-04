BlackDragonCoin integration/staging tree
========================================
http://blackdragoncoin.com  
http://forum.blackdragoncoin.com   

Copyright (c) 2009-2013 Bitcoin Developers  
Copyright (c) 2011-2013 Litecoin Developers  
Copyright (c) 2014 BlackDragonCoin Developers  

What is BlackDragonCoin?
------------------------

BlackDragonCoin is a lite version of Litecoin using scrypt-jane with adaptive N-factor as a proof-of-work algorithm.

Specs
--------------------------------------------------------------------------------------------------------------------
**Block target time:**
 - 20 seconds before 1000th block
 - 2 minutes after 1000th block

**Confirmations:**
 - 6 Confirmations per transaction, 1000 confirmations for mined blocks

**Block rewards:**
 - Block 1- 200: 1 + 1d4
 - Block 200-50,000: 100 + 1d20 *(20 roll is critical hit: block reward doubles and miner gets another 100 bonus coins)*
 - Block 50,000-100,000: 50 + 1d16 *(+ 1/20 chance to get double rewards)*
 - Block 100,000-150,000: 30 + 1d8 *(+ 1/20 chance to get double rewards)*
 - Block 150,000-200,000: 20 + 1d6 *(+ 1/20 chance to get double rewards)*
 - Block 200,000+: 10 + 1d4 *(+ 1/20 chance to get double rewards)*
 - DGW2 as retargeting method *(difficulty recalculating for each new block)*
 - Premine: 1.5 % of 1 year mining period for coin development and support  

Random rewards delayed by one block.

The rest is the same as Litecoin.
For more information, as well as an immediately useable, binary version of
the BlackDragonCoin client sofware, see http://forum.blackdragoncoin.com

License
-------

BlackDragonCoin is released under the terms of the MIT license. See `COPYING` for more
information or see http://opensource.org/licenses/MIT.

Development process
-------------------

Developers work in their own trees, then submit pull requests when they think
their feature or bug fix is ready.

If it is a simple/trivial/non-controversial change, then one of the BlackDragonCoin
development team members simply pulls it.

If it is a *more complicated or potentially controversial* change, then the patch
submitter will be asked to start a discussion (if they haven't already) on the
[mailing list](http://sourceforge.net/mailarchive/forum.php?forum_name=bitcoin-development).

The patch will be accepted if there is broad consensus that it is a good thing.
Developers should expect to rework and resubmit patches if the code doesn't
match the project's coding conventions (see `doc/coding.txt`) or are
controversial.

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/bitcoin/bitcoin/tags) are created
regularly to indicate new official, stable release versions of BlackDragonCoin.

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test. Please be patient and help out, and
remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write unit tests for new code, and to
submit new unit tests for old code.

Unit tests for the core code are in `src/test/`. To compile and run them:

    cd src; make -f makefile.unix test

Unit tests for the GUI code are in `src/qt/test/`. To compile and run them:

    qmake BDC_QT_TEST=1 -o Makefile.test blackdragoncoin-qt.pro
    make -f Makefile.test
    ./blackdragoncoin-qt_test


