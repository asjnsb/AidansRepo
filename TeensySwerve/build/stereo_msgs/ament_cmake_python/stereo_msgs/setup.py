from setuptools import find_packages
from setuptools import setup

setup(
    name='stereo_msgs',
    version='4.8.0',
    packages=find_packages(
        include=('stereo_msgs', 'stereo_msgs.*')),
)
