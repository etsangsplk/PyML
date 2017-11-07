from setuptools import setup
from setuptools import Extension
import distutils.sysconfig

# Workaround setuptools -Wstrict-prototypes warnings
# From https://stackoverflow.com/a/29634231/23845
cfg_vars = distutils.sysconfig.get_config_vars()
for key, value in cfg_vars.items():
    if type(value) == str:
        cfg_vars[key] = value.replace("-Wstrict-prototypes", "")

about = {}
with open('./pyml/__about__.py', 'r') as f:
    exec(f.read(), about)

linear_algebra_module = Extension('pyml.maths.Clinear_algebra',
                                  sources=['pyml/maths/src/linearalgebramodule.cpp',
                                           'pyml/maths/src/linearalgebraextension.cpp'],
                                  extra_compile_args=['-std=c++11'],
                                  include_dirs=['pyml/maths/include'],
                                  language='c++')

gradient_descent_module = Extension('pyml.maths.gradient_descent',
                                    sources=['pyml/maths/src/gradientdescentmodule.cpp',
                                             'pyml/maths/src/linearalgebramodule.cpp'],
                                    extra_compile_args=['-std=c++11'],
                                    include_dirs=['pyml/maths/include'],
                                    language='c++')

setup(
    name='PyML',
    classifiers=['Development Status :: 2 - Pre-Alpha',
                 'Intended Audience :: Science/Research',
                 'License :: OSI Approved :: MIT License',
                 'Natural Language :: English',
                 'Programming Language :: Python :: 3 :: Only',
                 'Programming Language :: Python :: Implementation :: CPython'
                 'Programming Language :: C++',
                 'Programming Language :: C',
                 'Topic :: Scientific/Engineering :: Artificial Intelligence'],
    keywords='machine learning',
    version=about['__version__'],
    package_dir={'pyml': 'pyml'},
    packages=['pyml',
              'pyml.maths',
              'pyml.metrics',
              'pyml.nearest_neighbours',
              'pyml.datasets',
              'pyml.preprocessing',
              'pyml.linear_models',
              'pyml.utils'],
    url='https://github.com/gf712/PyML',
    license=about['__license__'],
    author=about['__author__'],
    author_email=about['__author_email__'],
    description='Machine learning with Python and C/C++',
    test_suite="tests",
    ext_modules=[linear_algebra_module, gradient_descent_module],
)
