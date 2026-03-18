#!/bin/bash

rm -rf /var/lib/mysql
rm -rf /etc/mysql
rm -rf /var/log/mysql

rc-service mariadb setup

cp -r /data/bak/debian/var/lib/mysql/giteadb/ /var/lib/mysql/
cp    /data/bak/debian/var/lib/mysql/ib*      /var/lib/mysql/

chown -R mysql /var/lib/mysql/

rc-service mariadb start
