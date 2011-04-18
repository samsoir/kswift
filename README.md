# Kswift
## Asynchronous Request Handler for Kohana

A C utility to allow Kohana to bridge directly to FastCGI interface via a message queue such as ZeroMQ or Gearman. This is very much work in progress at the moment.

# Concept

Provide a bridge between Kohana Asynchronous Request pool and request 
execution using a message queue. The Kohana Asynchronous Request pool packages
the Kohana Requests contained within, then passes them to the message queue.

The message queue has a number of execution threads available, which handle
each request individually.

- Internal requests are passed back to a PHP process via FastCGI.
- External requests are handled by kswift internally.
