#!/usr/bin/env python3
"""
====
fdlo
====

This module computes some Fermi-Dirac integrals useful for astrophysical disks.
The approach is low tech and slow, the integrals are computed directly using
numerical quadrature with adaptive stencils.

Functions
---------

================ =============================
:func:`P_eminus` Compute the electron pressure
================ =============================
"""

from .version import __version__

from . import fdloCore
from .fdloCore import *
