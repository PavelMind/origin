//#include <boost\mpl\aux_\include_preprocessed.hpp>
//
//#include <boost/beast/core.hpp>
//#include <boost/beast/http.hpp>
//#include <boost/beast/version.hpp>
//#include <boost/asio/strand.hpp>
//#include <cstdlib>
//#include <functional>
//#include <iostream>
//#include <memory>
//#include <string>
//#include <chrono>
//#include <future>  // Добавляем для std::promise и std::future
//
//namespace beast = boost::beast;
//namespace http = beast::http;
//namespace net = boost::asio;
//using tcp = boost::asio::ip::tcp;
//
//void fail(beast::error_code ec, char const* what)
//{
//    std::cerr << what << ": " << ec.message() << "\n";
//}
//
//class session : public std::enable_shared_from_this<session>
//{
//    tcp::resolver resolver_;
//    beast::tcp_stream stream_;
//    beast::flat_buffer buffer_;
//    http::request<http::empty_body> req_;
//    http::response<http::dynamic_body> res_;
//    std::promise<std::string>& promise_;  // Добавляем std::promise для результата
//
//public:
//    explicit session(net::io_context& ioc, std::promise<std::string>& promise)
//        : resolver_(net::make_strand(ioc))
//        , stream_(net::make_strand(ioc))
//        , promise_(promise)  // Инициализируем promise
//    {
//    }
//
//    void run(char const* host, char const* port, char const* target, int version)
//    {
//        req_.method(http::verb::get);
//        req_.target(target);
//        req_.set(http::field::host, host);
//        req_.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
//
//        resolver_.async_resolve(
//            host, port,
//            beast::bind_front_handler(&session::on_resolve, shared_from_this()));
//    }
//
//    void on_resolve(beast::error_code ec, tcp::resolver::results_type results)
//    {
//        if (ec) return fail(ec, "resolve");
//
//        stream_.expires_after(std::chrono::seconds(30));
//
//        stream_.async_connect(
//            results,
//            beast::bind_front_handler(&session::on_connect, shared_from_this()));
//    }
//
//    void on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type)
//    {
//        if (ec) return fail(ec, "connect");
//
//        stream_.expires_after(std::chrono::seconds(3));
//
//        http::async_write(stream_, req_,
//            beast::bind_front_handler(&session::on_write, shared_from_this()));
//    }
//
//    void on_write(beast::error_code ec, std::size_t bytes_transferred)
//    {
//        boost::ignore_unused(bytes_transferred);
//
//        if (ec) return fail(ec, "write");
//
//        http::async_read(stream_, buffer_, res_,
//            beast::bind_front_handler(&session::on_read, shared_from_this()));
//    }
//
//    void on_read(beast::error_code ec, std::size_t bytes_transferred)
//    {
//        boost::ignore_unused(bytes_transferred);
//
//        if (ec) return fail(ec, "read");
//
//         //Устанавливаем значение promise
//        promise_.set_value(boost::beast::buffers_to_string(res_.body().data()));
//
//        stream_.socket().shutdown(tcp::socket::shutdown_both, ec);
//
//        if (ec && ec != beast::errc::not_connected)
//            return fail(ec, "shutdown");
//    }
//};
