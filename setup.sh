#!/bin/bash

echo -e 'Created			/tmp/www/ '

mkdir -p /tmp/www > /dev/null

echo "Moving webpages to	/tmp/www/"

cp -r ./default /tmp/www

echo 

if ! command -v tree &> /dev/null
then ls /tmp/www/*; 
else tree /tmp/www
fi
