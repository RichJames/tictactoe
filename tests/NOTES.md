I am using googletest to orchestrate unit testing. To make
this possible, I need to have googletest installed on my
system.

I have added the unit tests to the parent folder makefile. I need to learn more about how to efficiently construct a makefile so this is more generic and still works. For now, I have hard-coded the commands I need to build and link the unit tests.

An alternative approach is to use bazel, which seems very elegant.
But, like make, I need to learn some of its nuances in order to
manage construction across multiple directories. It seems to
want the project directory structure to have a top-level, parent
directory, then source, test, etc. directories under that. And
that is probably a good idea, but I haven't setup this project
that way. I might change it later, as that is a pretty clean
way to do things.

This site has some helpful information: http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

To do:

- Find out how to properly utilize macros in a make file.
- What is canonical way to specify "current directory"?
- How to set up multiple -iquote flags?
