from setuptools import find_packages
from setuptools import setup

setup(
    name='tnsy_interfaces',
    version='0.0.0',
    packages=find_packages(
        include=('tnsy_interfaces', 'tnsy_interfaces.*')),
)
