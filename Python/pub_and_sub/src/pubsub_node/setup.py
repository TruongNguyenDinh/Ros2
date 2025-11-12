from setuptools import find_packages, setup

package_name = 'pubsub_node'

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
    maintainer='ntruong1124',
    maintainer_email='truongnd1124@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    #Thêm cách đường dẫn file vào trong entry_point
    entry_points={
        'console_scripts': [
            'publish_nums = pubsub_node.publisher:main',
            'subcriber_nums = pubsub_node.subcriber:main',
        ],
    },
)
