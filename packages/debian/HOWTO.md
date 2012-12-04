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
4. $ `mv mecab-x.y.z.tgz ../packages/debian/` *[HERE]*
5. $ `dh-make-pecl --only 5 mecab-x.y.z.tgz`
6. $ `cd php-mecab-x.y.z`
7. Edit 'debian/control'.
    * Add 'mecab' and 'libmecab-dev` to 'Build-Depends'.
    * Add 'libmecab1' to 'Depends'.
8. $ `debuild -uc -us`
9. $ `cd ..` *[HERE]*
10. $ `sudo dpkg -i php5-mecab_x.y.z-1_{amd64,i386}.deb`
