DigitalNetIndex
===============
Calculate WAFOM and t-value of Digital Net.

REQUIREMENT
===========
* C++11 or C++14
* Boost 1.48 or later
* Little Endian System

INSTALL
=======

    ./configure --prefix=YOUR_INSTALL_DIR
    make
    make install

PREPARE
=======
before use, unzip data files

    cd YOUR_INSTALL_DIR/share/digitalnetindex
    gunzip bigtyl.dat.gz
    gunzip meantyl.dat.gz

set environment variable DIGITAL_NET_PATH

    export DIGITAL_NET_PATH=YOUR_INSTALL_DIR/share/digitalnetindex

USAGE
=====

    digitalnet_index [-t] [-m] [-w c] digital-net-datafile
      --tvalue, -t	compute t-value of digitalnet
      --mean-wafom, -m	compute mean WAFOM of digitalnet
      --wafom, -w		compute WAFOM of digitalnet for specified c

EXAMPLE
=======
An example of digital net data file is in example directory.

    digitalnet_index -t -m example/nxlw_s4_m10.txt

The last two items of the file are mean-wafom and t-value, and
you can check them with the output.

FILE FORMAT
===========
The file format of digital net data is as follows:

    1st item: 64 fixed
    2nd item: s
    3rd item: m
    from 4th: s * m number of 64-bit unsigned integers
    remain:   ignored

The delimiters of item are whitespaces and/or newlines.

CAUTION
=======
Data file `bigtyl.dat' and `meantyl.dat' are binary files which were
made on Little Endian System and will not work correctly on
Big Endian Systems.

LICENSE
=======
    Copyright (C) 2017 Shinsuke Mori, Makoto Matsutmoto, Mutsuo Saito
    and Hiroshima University.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
