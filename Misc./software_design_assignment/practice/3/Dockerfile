# @BAKE docker build -t agvxov/site .
FROM jitesoft/lighttpd
MAINTAINER agvxov

RUN apk add php82 fcgi php82-cgi

COPY agvxov_site/source/ /var/www/html
COPY lighttpd.conf /

ENV CONFIG_FILE=/lighttpd.conf

EXPOSE 5050
