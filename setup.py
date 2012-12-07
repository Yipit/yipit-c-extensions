from distutils.core import setup, Extension

module1 = Extension('yipit',
                    sources=['yipit.c'])

setup(name='yipit',
      version='1.0',
      description='This is a demo package',
      ext_modules=[module1])
