#!/bin/bash

echo -e 'Created			/tmp/www/ '

rm -r /tmp/www/
mkdir -p /tmp/www > /dev/null
mkdir -p /tmp/www/upload/ > /dev/null


echo "Moving webpages to	/tmp/www/"

cp -r ./default /tmp/www

echo 

if ! command -v tree &> /dev/null
then ls /tmp/www/*; 
else tree /tmp/www
fi
