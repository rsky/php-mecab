How to make debian package of php-mecab
=======================================

REQUIREMENTS
------------

* build-essential
* devscripts
* dh-make
* dh-make-php
* libmecab-dev
* mecab
* php5-dev
* xsltproc

HOW-TO
------

1. $ `sudo pear channel-discover pecl.opendogs.org`
2. $ `cd php-mecab/mecab`
3. $ `pear package package.xml`
4. $ `mv mecab-x.y.z.tgz ../packages/debian/`
5. $ `cd ../packages/debian` *[HERE]*
6. $ `dh-make-pecl --only 5 mecab-x.y.z.tgz`
7. $ `cd php-mecab-x.y.z`
8. Edit *debian/control*.
    * Add `mecab` and `libmecab-dev` to **Build-Depends**.
    * Add `libmecab1` to **Depends**.
9. $ `debuild -uc -us`
10. $ `cd ..` *[HERE]*
11. $ `sudo dpkg -i php5-mecab_x.y.z-1_{amd64,i386}.deb`
