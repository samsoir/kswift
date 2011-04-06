# Gerphast
## The Gearman to php-fpm bridge for Kohana asynchronous requests

A C utility to allow Gearman to bridge directly to PHP-FPM using the FastCGI
interface. This will allow the use of Gearman to run multiple asynchronous
requests from within Kohana without having to use an inefficient PHP run loop.