#!/usr/bin/env python3
import site
from setuptools import setup, Extension

site.ENABLE_USER_SITE = True

version = {}
with open("fdlo/version.py", "r") as f:
    exec(f.read(), version)

with open("README.md", "r") as f:
    long_description = f.read()

libs = []
libdirs = []

sources = ["fdlo/fdloCoremodule.c", "fdlo/fdlo.c", "fdlo/integrate.c",
            "fdlo/interval.c"]
depends = ["fdlo/fdlo.h", "fdlo/integrate.h", "fdlo/interval.h"]

module = Extension('fdlo.fdloCore', sources=sources, include_dirs=[],
                   depends=depends, extra_compile_args=['-Wall'])

setup(
    name='fdlo',
    version=version['__version__'],
    author="Geoffrey Ryan",
    author_email="gryan@perimeterinstitute.ca",
    description='Lo-Tech Fermi-Dirac Integrals',
    long_description=long_description,
    long_description_content_type='text/markdown',
    license='MIT',
    url='https://github.com/geoffryan/fdlo',
    packages=['fdlo'],
    ext_modules=[module],
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Intended Audience :: Science/Research",
        "Topic :: Scientific/Engineering :: Astronomy"],
    )
