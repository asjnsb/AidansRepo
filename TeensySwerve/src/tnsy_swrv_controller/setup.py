from setuptools import find_packages, setup

package_name = 'tnsy_swrv_controller'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='aidan',
    maintainer_email='asjnsb@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            # ROS2_executable = pkg_name.filename:function
            "test_node = tnsy_swrv_controller.my_first_node:main"
        ],
    },
)
