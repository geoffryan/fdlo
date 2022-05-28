## fdlo ##

Low tech Fermi-Dirac integrals.

Just a handful of astrophysically relevant Fermi-Dirac integrals computed with direct integration, no fancy asymptotic approximations or fitting formulae.

With default settings, evaluates an integral in about ~ 7 μs.  This is slow compared to a fitting formula, but much faster than a pure Python approach with SciPy which takes ~ 450 μs per evaluation with the same desired tolerance. About a 64x speedup!

Note this package only computes the dimensionless Fermi-Dirac integrals.  It does not include the various constants (c, m<sub>e</sub>, ħ, etc) or the numerical prefactors (1/3, 2π, etc).

#### installation ####

Install locally with `pip`:

```bash
$ git clone git@github.com:geoffryan/fdlo
$ cd fdlo
$ pip3 install -e .
```

#### usage ####

`fdlo` functions can be called with just a temperature θ (in electron masses) and degeneracy η (dimensionless).  Additional parameters are the desired relative tolerance `rtol` (defaults to 10<sup>-12</sup>) and integration routine `method` (defaults to `fdlo.gk1021`: adaptive quadrature with the Gauss-Kronrod 10-21 rule stencil).

The functions return a tuple `(result, error, numEvals)`:
    - `result` is the desired value, a Fermi-dirac type integral
    - `error` is the (approximate) uncertainty in `result`
    - `numEvals` is the number of function evaluations used.

Here's an example

```python
>>> import fdlo
>>> theta = 3.0
>>> eta = 0.5
>>> fdlo.P_eminus(theta, eta)
(720.8874231042558, 2.3028377235560364e-10, 273)
>>>
```

The integral has a value of `720.8874231042558` with an approximate error `2.30e-10` after `273` function evaluations.

Increasing the tolerance will use less function evals at the cost of more error:

```python
>>> import fdlo
>>> fdlo.P_eminus(3, 0.5, rtol=1.0e-5)
(720.8874230739101, 0.001521589698322771, 189)
```

This only took `189` evaluations, with potentially much larger error (although comparing this to the previous value the apprpximation appears to be an over-estimate in this case) 

#### function list ####

EOS integrals currently included:

    - `n_eminus`: Number density of electrons.
    - `n_eplus`: Number density of positrons.
    - `P_eminus`: Pressure of electrons.
    - `P_eplus`: Pressure of positrons.
    - `U_eminus`: Energy density of electrons.
    - `U_eplus`: Energy density of positrons.

Neutrino integrals in transparent limit currently included (*all use `eta_e`*):

    - `Ndot_nu_transp`: Number flux of neutrinos in transparent limit.
    - `Ndot_nubar_transp`: Number flux of anti-neutrinos in transparent limit.
    - `F_nu_transp`: Energy flux of neutrinos in transparent limit.
    - `F_nubar_transp`: Energy flux of anti-neutrinos in transparent limit.

Neutrino integrals in opaque limit currently included (*all use `eta_nu`*):

    - `n_nu_opaque`: Number density of neutrinos in opaque limit.
    - `n_nubar_opaque`: Number density of anti-neutrinos in opaque limit.
    - `U_nu_opaque`: Energy density of neutrinos in opaque limit.
    - `U_nubar_opaque`: Energy density of anti-neutrinos in opaque limit.

#### More examples ####

Check out `examples/`
