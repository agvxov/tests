#!/bin/sh
find . -name "*.php"  -exec sed -i 's/\.html"/\.php"/g' {} +
find . -name "*.html" -exec sed -i 's/\.html"/\.php"/g' {} +
find . -name "*.html" -exec sh -c 'mv "$0" "${0%.html}.php"' {} \;
