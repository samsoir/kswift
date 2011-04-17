# Kswift
## Asynchronous Request Handler for Kohana

A C utility to allow Kohana to bridge directly to FastCGI interface via a message queue such as ZeroMQ or Gearman. This is very much work in progress at the moment.

# Concept

Provide a bridge between Kohana Asynchronous Request Pool and processors using
a message queue. The Kohana Asynchronous Request Pool 