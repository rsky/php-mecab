How to make Ubuntu package of php-mecab
=======================================

REQUIREMENTS
------------

* build-essential
* devscripts
* dh-make
* dh-make-php
* libmecab-dev
* mecab
* php5-cli
* php5-dev
* xsltproc


PREPARE
-------

You will have to discover the PEAR channel.

$ `sudo pear channel-discover pecl.opendogs.org`


MAKE A PACKAGE
--------------

1. $ `cd php-mecab/mecab`
2. $ `pear package package.xml`
3. $ `mv mecab-x.y.z.tgz ../packages/ubuntu/`
4. $ `cd ../packages/ubuntu`
5. $ `dh-make-pecl --phpversion 5 mecab-x.y.z.tgz`
6. $ `cd php-mecab-x.y.z`
7. Edit *debian/control*.
    * Add `mecab` and `libmecab-dev` to **Build-Depends**.
    * Add `libmecab1` to **Depends**.
8. $ `debuild -uc -us` *[without GPG signing]*


INSTALL
-------

The .deb file will be generated at *php-mecab/packages/ubuntu*.

$ `sudo dpkg -i php5-mecab_x.y.z-1_{amd64,i386}.deb`
