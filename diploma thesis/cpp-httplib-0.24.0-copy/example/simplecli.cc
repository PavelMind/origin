//
//  simplecli.cc
//
//  Copyright (c) 2019 Yuji Hirose. All rights reserved.
//  MIT License
//

#include <httplib_S.h>
#include <iostream>

using namespace std;

int main(void) {
#ifdef S_CPPHTTPLIB_OPENSSL_SUPPORT_S
  auto scheme_host_port = "https://localhost:8080";
#else
  auto scheme_host_port = "http://localhost:8080";
#endif

  if (auto res = httplib_S::Client(scheme_host_port).Get("/hi")) {
    cout << res->status << endl;
    cout << res->get_header_value("Content-Type") << endl;
    cout << res->body << endl;
  } else {
    cout << res.error() << endl;
  }

  return 0;
}
