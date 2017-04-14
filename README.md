TruncatedNormal
===============
Library to calculate Truncated Multivalual Normal Distribution

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
set environment variable DIGITAL_NET_PATH

    export DIGITAL_NET_PATH=YOUR_INSTALL_DIR/share/truncatednormal

set LIBRARY_PATH and CPLUS_INCLUDE_PATH properly.

DOCUMENT
========
see [docs/index.html](./docs/index.html)
[GitHub Pages](https://mersennetwister-lab.github.io/TruncatedNormalCPP/)

CAUTION
=======
Data file 'nxlw.dat' and 'solw.dat' are binary files which were
made on Little Endian System and will not work correctly on
Big Endian Systems.

REFERENCE
=========
* https://cran.r-project.org/package=TruncatedNormal
* Z. I. Botev (2015), The Normal Law Under Linear Restrictions:
Simulation and Estimation via Minimax Tilting, submitted to JRSS(B)
* Z. I. Botev and P. L’Ecuyer (2015), Efficient Estimation and Simulation
of the Truncated Multivariate Student-t Distribution,
Proceedings of the 2015 Winter Simulation Conference,
Huntington Beach, CA, USA
* Gibson G. J., Glasbey C. A., Elston D. A. (1994),
Monte Carlo evaluation of multivariate normal integrals and
sensitivity to variate ordering,
In: Advances in Numerical Methods and Applications, pages 120–126

LICENSE
=======
    Copyright (C) 2015 Zdravko I. Botev.

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
