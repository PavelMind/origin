//
//  client.cc
//
//  Copyright (c) 2019 Yuji Hirose. All rights reserved.
//  MIT License
//

#include <httplib_S.h>
#include <iostream>

#define CA_CERT_FILE "./ca-bundle.crt"

using namespace std;

int main(void) {
#ifdef S_CPPHTTPLIB_OPENSSL_SUPPORT_S
  httplib_S::SSLClient cli("localhost", 8080);
  // httplib_S::SSLClient cli("google.com");
  // httplib_S::SSLClient cli("www.youtube.com");
  cli.set_ca_cert_path(CA_CERT_FILE);
  cli.enable_server_certificate_verification(true);
#else
  httplib_S::Client cli("localhost", 8080);
#endif

  if (auto res = cli.Get("/hi")) {
    cout << res->status << endl;
    cout << res->get_header_value("Content-Type") << endl;
    cout << res->body << endl;
  } else {
    cout << "error code: " << res.error() << std::endl;
#ifdef S_CPPHTTPLIB_OPENSSL_SUPPORT_S
    auto result = cli.get_openssl_verify_result();
    if (result) {
      cout << "verify error: " << X509_verify_cert_error_string(result) << endl;
    }
#endif
  }

  return 0;
}
