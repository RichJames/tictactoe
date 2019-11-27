#include "io_redirects.h"

// Capture std::out
std::stringstream io_redirect::outbuffer;
io_redirect::StdCoutTester io_redirect::cout_tester(outbuffer);

// Capture any messages to std::cerr
std::stringstream io_redirect::errbuffer;
io_redirect::StdCerrTester io_redirect::cerr_tester(errbuffer);

std::string io_redirect::inbuffer;
io_redirect::StdCinTester io_redirect::cin(inbuffer);
